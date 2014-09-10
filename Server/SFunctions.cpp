/* 
 * File:   SFunctions.cpp
 * Author: karsten
 * 
 * Created on 23. april 2011, 09:57
 */

#include "SFunctions.h"
#include "Client.h"
#include "../Network/Serialize.h"
#include "World/SWorld.h"
#include "Sspacebjects/SShip.h"
#include "Sspacebjects/subsystems/SSubTypeWep.h"
#include "Sspacebjects/subsystems/SSingleFac.h"
#include "Sspacebjects/subsystems/SSubSystemFac.h"
#include "Sspacebjects/subsystems/SSubSystemW.h"
#include "Sspacebjects/subsystems/SLoadout.h"
#include "Commands/CommandTargetPosUpdate.h"
#include "Commands/inputCommands/CommandISubStatusField.h"
#include "Commands/CommandClientSubscription.h"
#include "Commands/inputCommands/CommandIChangeOrders.h"
#include "Commands/inputCommands/CommandIChangeSubTG.h"
void sendtoC(Client* cli, char* buffer, uint32_t len){
	pthread_mutex_lock(&cli->networkSendLock);
		if (cli->networkSendLockBool)
			send(cli->getSocket(),buffer, len,MSG_NOSIGNAL);
	pthread_mutex_unlock(&cli->networkSendLock);
}


void* thread_Listen(){
	struct sockaddr_in stSockAddr;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(-1 == SocketFD)
    {
      perror("can not create socket");
      exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(11142);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;

    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("error bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    if(-1 == listen(SocketFD, 10))
    {
      perror("error listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

	for(;;){
		int ConnectFD = accept(SocketFD, NULL, NULL);
		cerr<<"connected time "<<SDL_GetTicks()<<endl;

		if(0 > ConnectFD){
			perror("error accept failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}


		//create new client
		
		Client* cli = new Client(ConnectFD);
		cerr<<"connected "<<endl;
		networkControl->addClient(cli);


		cerr<<"added to clients"<<endl;
		pthread_create(&(cli->listenThread), NULL, (void*(*)(void*))thread_Recive, cli);
		cerr<<"begin listen"<<endl;
		

	}

    close(SocketFD);
	return 0;
}


void* thread_Recive(Client* client){


	printf ("recv test....\n");
	int recsize;
	uint32_t timeout = 0;

	while(true){

		recsize = recv(client->getSocket(), (client->inputnetworkBuf->networkBuf) + client->inputnetworkBuf->recived, 512,0);

		if (recsize < 0){
			fprintf(stderr, "RECV  ERROR***********************\n");
			break;
		}
		if (recsize)
			timeout = 0;

		client->inputnetworkBuf->recived +=recsize;
		bool switchdone = false;
		while (!switchdone){
			usleep(1000);
			pthread_mutex_lock(&client->networkBufLock);
			//************************************
			//CRITICAL
			if (!client->parsingoutput){
				switchdone = client->switchBuffer();
			}
			//CRITICAL
			//************************************
			pthread_mutex_unlock(&client->networkBufLock);
		}
		timeout+=1;
		if (timeout < 20)
			usleep(400);
		else{
			cerr<<"timeout"<<endl;
			break;
		}
	}

	
	pthread_mutex_lock(&client->networkSendLock);
		client->networkSendLockBool = false;
	pthread_mutex_unlock(&client->networkSendLock);
	
	shutdown(client->getSocket(), SHUT_RDWR);

	close(client->getSocket());
	networkControl->removeClient(client);
	for(map<uint32_t, SGrid*>::iterator it = world->getGrids().begin(); it != world->getGrids().end();it++){
		it->second->UnSubscribe(client);
	}
	cerr<<"Delete"<<endl;
	delete client;
	
	pthread_exit(0);
}


void* ReadBuffer(Client* client){
		if (client->outputnetworkBuf->recived > 0){
			//************************************
			//CRITICAL
			pthread_mutex_lock(&client->networkBufLock);
			client->parsingoutput = true;
			pthread_mutex_unlock(&client->networkBufLock);
			//CRITICAL
			//************************************
			//if(printbufferbool)
			uint32_t delta = parseBuffer(client,client->outputnetworkBuf->recived);

			memmove(client->outputnetworkBuf->networkBuf, client->outputnetworkBuf->networkBuf+ delta, client->outputnetworkBuf->recived- delta);

			client->outputnetworkBuf->recived -= delta;

			//************************************
			//CRITICAL
			pthread_mutex_lock(&client->networkBufLock);
			client->parsingoutput = false;
			pthread_mutex_unlock(&client->networkBufLock);
			//CRITICAL
			//************************************
		}


}

uint32_t parseBuffer(Client* client, uint32_t len){
	char* buffer = client->outputnetworkBuf->networkBuf;
	uint32_t offset = 0;
	printBuffer(buffer,len);
	while (offset < len){
		SerialData* temp = (SerialData*)(buffer + offset);
		if (len - offset >= sizeof(uint32_t)*2 && temp->_size <= len - offset){
			//cerr<<"parse single "<<endl;

			switch(temp->_type)
			{
				case SerialType::SerialTime:{
					SerialTime* st = (SerialTime*)(buffer+offset);

					char message[sizeof(SerialTime)];
					memset(message,0,sizeof(SerialTime));

					SerialTime* data = (SerialTime*)(message);
					data->_type = SerialType::SerialTime;
					data->_size = sizeof(SerialTime);
					data->time = SDL_GetTicks();
					data->local = st->local;
					cerr<<"send Time "<<data->time<<endl;
					send(client->getSocket(),message,sizeof(SerialTime),0);

					break;
				}
				case SerialType::SerialReqJoin:{
					SerialReqJoin* st = (SerialReqJoin*)(buffer+offset);
					client->setPlayerId(st->_unitId);
					client->initTransfere();

					break;
				}
				case SerialType::SerialPCShipTargetPosUpdate:{
					SerialPCShipTargetPosUpdate* st = (SerialPCShipTargetPosUpdate*)(buffer+offset);
					Processor* processor = networkControl->getProcessor(st->_Id);
					
					if(!processor){
						cerr<<"ERROR SFUNCTION SerialType::SerialPCShipTargetPosUpdate processor not found"<<endl;
						break;
					}
					processor->addCommand(new CommandTargetPosUpdate(0,st,client->getId()));
					
					break;
				}

				case SerialType::SerialReqSetOrdreUnit:{
					SerialReqSetOrdreUnit* st = (SerialReqSetOrdreUnit*)(buffer+offset);
					SObjI ob = world->getObjs().find(st->_Id);
					SObjI toob = world->getObjs().find(st->_ToId);

					if(ob != world->getObjs().end() && toob != world->getObjs().end()){
						if (ob->second->isShip() && ob->second->getTeam() == client->getTeamId()){
							ob->second->isShip()->getOrdreObj()[st->_oindex] = toob->second;
						}
					}
					break;
				}
				case SerialType::SerialReqSetOrdrePos:{
					SerialReqSetOrdrePos* st = (SerialReqSetOrdrePos*)(buffer+offset);
					SObjI ob = world->getObjs().find(st->_Id);
					
					if(ob != world->getObjs().end()){
						if (ob->second->isShip() && ob->second->getTeam() == client->getTeamId()){
							if(ob->second->isShip()->getOrdrePos().find(st->_oindex) == ob->second->isShip()->getOrdrePos().end()){
								SPos* tpos = new SPos(st->_Pos_x,st->_Pos_y,st->_Pos_d);
								ob->second->isShip()->getOrdrePos()[st->_oindex] = tpos;
							}else{
								ob->second->isShip()->getOrdrePos()[st->_oindex]->x = st->_Pos_x;
								ob->second->isShip()->getOrdrePos()[st->_oindex]->y = st->_Pos_y;
								ob->second->isShip()->getOrdrePos()[st->_oindex]->d = st->_Pos_d;
							}

						}
					}
					break;
				}
				case SerialType::SerialReqTransfereCargo:{
					SerialReqTransfereCargo* st = (SerialReqTransfereCargo*)(buffer+offset);
					SObjI fromit = world->getObjs().find(st->_FromId);
					SObjI toit = world->getObjs().find(st->_ToId);
					map<uint32_t,SItemType*>::iterator it3 = itemlist.find(st->_itemid);
					if (it3 == itemlist.end())
						break;
					if(fromit == world->getObjs().end()|| toit == world->getObjs().end())
						break;
					if(fromit->second->getTeam() != client->getTeamId())
						break;
					if(toit->second->getTeam() != client->getTeamId())
						break;
					if (!fromit->second->getsubable() || !toit->second->getsubable() )
						break;
					if(!fromit->second->getsubable()->getCargoBay() || !toit->second->getsubable()->getCargoBay())
						break;

					fromit->second->getsubable()->getCargoBay()->TransfereCargo(toit->second->getsubable()->getCargoBay(),it3->second,st->_quantity);
					break;
				}
				case SerialType::SerialReqChangeSubTG:{
					SerialReqChangeSubTG* st = (SerialReqChangeSubTG*)(buffer+offset);
					Processor* processor = networkControl->getProcessor(st->_ShipId);
					
					if(!processor){
						cerr<<"ERROR SFUNCTION SerialType::SerialReqChangeSubTG processor not found"<<endl;
						break;
					}
					processor->addCommand(new CommandIChangeSubTG(st->_ShipId, st->_SubId, (TargetGroup::Enum)st->_TargetGroup, client->getId()));
					break;
				}
				case SerialType::SerialReqChangeOrdres:{
					SerialReqChangeOrdres* st = (SerialReqChangeOrdres*)(buffer+offset);
					Processor* processor = networkControl->getProcessor(st->_ShipId);
					
					if(!processor){
						cerr<<"ERROR SFUNCTION SerialType::SerialReqChangeOrdres processor not found"<<endl;
						break;
					}
					processor->addCommand(new CommandIChangeOrders(st->_ShipId, st->_OrdreId, client->getId()));
					break;
				}

				case SerialType::SerialReqChangePrio:{
					SerialReqChangePrio* st = (SerialReqChangePrio*)(buffer+offset);
					
					//Processor* processor = networkControl->getProcessor(st->_ShipId);
					
//					if(!processor){
					//	cerr<<"ERROR SFUNCTION SerialType::SerialPCShipTargetPosUpdate processor not found"<<endl;
					//	break;
					//}
					//processor->addCommand(new CommandISubStatusField(st->_ShipId,st->_SubId,st->_StatusField, client->getId()));

					
					break;
				}

				case SerialType::SerialReqChangeSubStatus:{
					SerialReqChangeSubStatus* st = (SerialReqChangeSubStatus*)(buffer+offset);
					
					Processor* processor = networkControl->getProcessor(st->_ShipId);
					
					if(!processor){
						cerr<<"ERROR SFUNCTION SerialType::SerialPCShipTargetPosUpdate processor not found"<<endl;
						break;
					}
					processor->addCommand(new CommandISubStatusField(st->_ShipId,st->_SubId,st->_StatusField, client->getId()));

					break;
				}
				case SerialType::SerialReqCreateLoadOut:{
					SerialReqCreateLoadOut* st = (SerialReqCreateLoadOut*)(buffer+offset);
					uint32_t nextFreeId = 0;

					for(map<uint32_t, SLoadout*>::iterator it = globalLoadout[client->getPlayerId()].begin(); it !=globalLoadout[client->getPlayerId()].end();it++){
						if(it->first >= nextFreeId)
							nextFreeId = it->first + 1;
						if(it->second->getName() == string(st->_name) && it->second->getShipType()->getId() == st->_shiptype){
							nextFreeId = it->first;
							if(it->second){
								delete it->second;
							}
							globalLoadout[client->getPlayerId()].erase(it);
							break;
						}
					}
					if(unitTypes.find(st->_shiptype) == unitTypes.end())
						break;
					
					if(!(unitTypes[st->_shiptype]->isShipType()))
						break;
					SLoadout* tload = new SLoadout(nextFreeId,string(st->_name),*unitTypes[st->_shiptype]->isShipType());

					for(uint32_t i = 0; i< st->_xloaditems;i++){
						SerialReqCreateLoadItems* st2 = (SerialReqCreateLoadItems*)(buffer+offset+sizeof(SerialReqCreateLoadOut)+(sizeof(SerialReqCreateLoadItems)*i));
						if(itemlist.find(st2->_itemid) != itemlist.end())
							tload->addItem(st2->_slotid,itemlist[st2->_itemid],st2->_xitem,(TargetGroup::Enum)st2->_targetgroup);
					}
					globalLoadout[client->getPlayerId()][nextFreeId] = tload;
					client->sendLoadout(nextFreeId);
					break;
				}

				case SerialType::SerialReqFitLoadout:{
					SerialReqFitLoadout* st = (SerialReqFitLoadout*)(buffer+offset);
					SObjI fromit = world->getObjs().find(st->_FromId);
					SObjI toit = world->getObjs().find(st->_ToId);
					
					if(globalLoadout[client->getPlayerId()].find(st->_loadoutId) ==  globalLoadout[client->getPlayerId()].end())
						break;

					if(fromit == world->getObjs().end()|| toit == world->getObjs().end())
						break;
					if (!toit->second->getsubable())
						break;
					if(fromit->second->getTeam() != client->getTeamId())
						break;
					if(toit->second->getTeam() != client->getTeamId())
						break;

					if (!fromit->second->getsubable() || !toit->second->getsubable() )
						break;
					if(!fromit->second->getsubable()->getCargoBay())
						break;
					
					SLoadout* loadout = globalLoadout[client->getPlayerId()][st->_loadoutId];
					SSubAble* toobj = toit->second->getsubable();
					SCargoBay* frombay = fromit->second->getsubable()->getCargoBay();

					loadout->fitTo(toobj,frombay);
					break;
				}

				case SerialType::SerialReqFit:{
					SerialReqFit* st = (SerialReqFit*)(buffer+offset);
					SObjI fromit = world->getObjs().find(st->_FromId);
					SObjI toit = world->getObjs().find(st->_ToId);
					map<uint32_t, SSlotNode*>::iterator slotnode;
					if(fromit == world->getObjs().end()|| toit == world->getObjs().end())
						break;
					if (!toit->second->getsubable())
						break;
					if(fromit->second->getTeam() != client->getTeamId())
						break;
					if(toit->second->getTeam() != client->getTeamId())
						break;

					slotnode = toit->second->getsubable()->getSlots().find(st->_subid);
					if (slotnode == toit->second->getsubable()->getSlots().end())
						break;


					map<uint32_t,SItemType*>::iterator it3 = itemlist.find(st->_itemid);
					if (it3 == itemlist.end())
						break;

					if (!fromit->second->getsubable() || !toit->second->getsubable() )
						break;
					if(!fromit->second->getsubable()->getCargoBay())
						break;
					
					SSubAble* toobj = toit->second->getsubable();
					SCargoBay* frombay = fromit->second->getsubable()->getCargoBay();
					
					toobj->FitAddSub(it3->second,slotnode->second->getId(),st->_quantity,frombay);
					break;
				}

				case SerialType::SerialReqUnfit:{
					SerialReqUnfit* st = (SerialReqUnfit*)(buffer+offset);
					SObjI fromit = world->getObjs().find(st->_FromId);
					SObjI toit = world->getObjs().find(st->_ToId);
					map<uint32_t, SSlotNode*>::iterator slotnode;
					if(fromit == world->getObjs().end()|| toit == world->getObjs().end())
						break;

					if(fromit->second->getTeam() != client->getTeamId())
						break;
					if(toit->second->getTeam() != client->getTeamId())
						break;
					if (!toit->second->getsubable())
						break;
					
					if (!fromit->second->getsubable() || !toit->second->getsubable() )
						break;
					slotnode = fromit->second->getsubable()->getSlots().find(st->_subid);
					if (slotnode == fromit->second->getsubable()->getSlots().end())
						break;
					if(!slotnode->second->getSS())
						break;

					if(!toit->second->getsubable()->getCargoBay())
						break;
					SSubAble* toobj = toit->second->getsubable();
					SSubAble* fromobj = fromit->second->getsubable();
					SCargoBay* tobay = toobj->getCargoBay();

					fromobj->FitRemoveSub(st->_subid,st->_quantity,tobay);
					
					break;
				}

				case SerialType::SerialReqInitBuild:{
					SerialReqInitBuild* st = (SerialReqInitBuild*)(buffer+offset);
					SObjI it = world->getObjs().find(st->_ShipId);
					if(it != world->getObjs().end()){
						if(it->second->getTeam() != client->getTeamId())
							break;

						if ( it->second->getsubable()->getSlots().find(st->_SubId) !=it->second->getsubable()->getSlots().end()){
							map<uint32_t, SSlotNode*>::iterator it2 =it->second->getsubable()->getSlots().find(st->_SubId);
							if (it2->second->getSS()){
								if (it2->second->getSS()->getItemType()->getSubType()->isFac()){
									SSubSystemFac* fac = (SSubSystemFac*)it2->second->getSS();
									map<uint32_t,SItemType*>::iterator it3 = itemlist.find(st->_BuildItem);
									if (it3 != itemlist.end()){
										if (it3->second){
											fac->buildItem(it3->second,st->_Quantity);
										}
									}
								}
							}
						}
					}
					break;
				}

				case SerialType::SerialSubscribeObj:{
					
					SerialSubscribeObj* st = (SerialSubscribeObj*)(buffer+offset);
					
					Processor* processor = networkControl->getProcessor(st->_Id);
					
					if(!processor){
						cerr<<"ERROR SFUNCTION SerialType::SerialPCShipTargetPosUpdate processor not found"<<endl;
						break;
					}
					processor->addCommand(new CommandClientSubscription(0,client->getId(),st->_Id,SubscriptionLevel::details));
					
					
					//TODO fix
					/*
					SerialSubscribeObj* st = (SerialSubscribeObj*)(buffer+offset);
					SObjI it = world->getObjs().find(st->_Id);
					if(it != world->getObjs().end()){
						it->second->getSubscribers()[SubscriptionLevel::details].push_back(client);
						if (it->second->isUnit()){
							it->second->isUnit()->sendFull(client);
						}
					}
					*/
					break;
				}
				case SerialType::SerialUnSubscribeObj:{
					
					SerialUnSubscribeObj* st = (SerialUnSubscribeObj*)(buffer+offset);
					Processor* processor = networkControl->getProcessor(st->_Id);
					
					if(!processor){
						cerr<<"ERROR SFUNCTION SerialType::SerialPCShipTargetPosUpdate processor not found"<<endl;
						break;
					}
					processor->addCommand(new CommandClientSubscription(0,client->getId(),st->_Id,SubscriptionLevel::lowFreq));
				
					
					//TODO fix
					/*
					SerialUnSubscribeObj* st = (SerialUnSubscribeObj*)(buffer+offset);
					SObjI it = world->getObjs().find(st->_Id);
					if(it != world->getObjs().end()){
						it->second->getSubscribers()[SubscriptionLevel::details].remove(client);
					}
					*/
					break;
				}
				
				default:{
					cerr<<"error no packet parse function defined"<<endl;
					offset = len;
					break;
				}
			}
			offset += temp->_size;
		}else{
			cerr<<"servermissing data"<<endl;
			break;
		}
			
	}
	//cerr<<"end parse  "<<endl;
	return offset;

}
uint32_t Rangeobj(SPos& pos1, SPos& pos2)
{
	int32_t p1x = pos1.x/100;
	int32_t p2x = pos2.x/100;
	int32_t p1y = pos1.y/100;
	int32_t p2y = pos2.y/100;

	return sqrt(((p1x - p2x)*(p1x - p2x)) + ((p1y - p2y)*(p1y - p2y)));
}

bool InAngle(int32_t angle, FireDir::Enum fd){
	uint16_t a,b = 0;
	switch(fd){
		case FireDir::ALL:{return true;}
		case FireDir::FW:{a = 30;b = 330;break;}

		case FireDir::FW_FL:{a = 60;b = 330;break;}
		case FireDir::FW_FR:{a = 30;b = 300;break;}
		case FireDir::FW_L:{a = 120;b = 330;break;}
		case FireDir::FW_R:{a = 30;b = 240;break;}
		case FireDir::FW_LS:{a = 90;b = 330;break;}
		case FireDir::FW_RS:{a = 30;b = 270;break;}
		case FireDir::FW_AL:{a = 150;b = 330;break;}
		case FireDir::FW_AR:{a = 30;b = 210;break;}
		case FireDir::FW_FL_FR:{a = 60;b = 300;break;}
		case FireDir::FW_LS_RS:{a = 90;b = 270;break;}
		case FireDir::FW_L_R:{a = 120;b = 240;break;}
		case FireDir::FW_AL_AR:{a = 150;b = 210;break;}

		case FireDir::FWS:{a = 15;b = 345;break;}
		case FireDir::FWS_LS:{a = 90;b = 355;break;}
		case FireDir::FWS_RS:{a = 5;b = 270;break;}
		case FireDir::FWS_FL:{a = 60;b = 355;break;}
		case FireDir::FWS_FR:{a = 5;b = 300;break;}

		case FireDir::FWS_L_AFS:{a = 185;b = 355;break;}
		case FireDir::FWS_R_AFS:{a = 5;b = 175;break;}

		case FireDir::FL:{a = 60;b = 30;break;}
		case FireDir::FL_R:{a = 60;b = 240;break;}
		case FireDir::FL_LS:{a = 90;b = 30;break;}
		case FireDir::FL_L:{a = 120;b = 30;break;}
		case FireDir::FL_AL:{a = 150;b = 30;break;}
		case FireDir::FL_AFS:{a = 185;b = 30;break;}
		case FireDir::FL_AF:{a = 210;b = 30;break;}

		case FireDir::FR:{a = 330;b = 300;break;}
		case FireDir::FR_L:{a = 120;b = 300;break;}
		case FireDir::FR_RS:{a = 330;b = 270;break;}
		case FireDir::FR_R:{a = 330;b = 240;break;}
		case FireDir::FR_AR:{a = 330;b = 210;break;}
		case FireDir::FR_AFS:{a = 330;b = 175;break;}
		case FireDir::FR_AF:{a = 330;b = 150;break;}

		case FireDir::L:{a = 120;b = 60;break;}
		case FireDir::L_AL:{a = 150;b = 60;break;}
		case FireDir::L_AFS:{a = 185;b = 60;break;}
		case FireDir::L_AF:{a = 210;b = 60;break;}
		case FireDir::R:{a = 300;b = 240;break;}
		case FireDir::R_AR:{a = 300;b = 210;break;}
		case FireDir::R_AFS:{a = 300;b = 175;break;}
		case FireDir::R_AF:{a = 300;b = 150;break;}

		case FireDir::AL:{a = 150;b = 120;break;}
		case FireDir::AL_AFS:{a = 185;b = 120;break;}
		case FireDir::AL_AF:{a = 210;b = 120;break;}

		case FireDir::AR:{a = 240;b = 210;break;}
		case FireDir::AR_AFS:{a = 240;b = 175;break;}
		case FireDir::AR_AF:{a = 240;b = 150;break;}

		case FireDir::AF:{a = 210;b = 150;break;}
		case FireDir::AF_AL_AR:{a = 240;b = 120;break;}
		case FireDir::AF_LS_RS:{a = 270;b = 90;break;}
		case FireDir::AF_L_R:{a = 300;b = 60;break;}
		case FireDir::AF_FL_FR:{a = 330;b = 30;break;}
	}

	if (b < a){
		if (angle <= a && angle >= b)
			return true;
	}else{
		if (angle <= a)
			return true;
		if (angle >= b)
			return true;
	}
	return false;
}





int32_t Direction(SPos& pos1, SPos& pos2){
	return Deg(pos2.x - pos1.x, pos2.y - pos1.y);
}
