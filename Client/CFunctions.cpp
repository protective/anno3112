/* 
 * File:   CFunctions.cpp
 * Author: karsten
 * 
 * Created on 24. april 2011, 13:54
 */

#include "CFunctions.h"
#include "spaceobjects/subsystems/CSubSystemBoost.h"
#include "spaceobjects/CObj.h"
#include "spaceobjects/subsystems/CSubSystem.h"
#include "spaceobjects/subsystems/CSubSystemW.h"
#include "spaceobjects/subsystems/CSubSystemFac.h"
#include "spaceobjects/subsystems/CSubSystemRef.h"
#include "spaceobjects/subsystems/CSubSystemBonus.h"
#include "spaceobjects/subsystems/CSlotNode.h"
#include "spaceobjects/subsystems/CSubType.h"
#include "spaceobjects/subsystems/CSubTypeWep.h"
#include "spaceobjects/subsystems/CSubTypeBoost.h"
#include "spaceobjects/subsystems/CSubTypeRef.h"

#include "spaceobjects/subsystems/CSingleWep.h"
#include "spaceobjects/CShipType.h"
#include "spaceobjects/subsystems/CSubTypeFac.h"
#include "spaceobjects/subsystems/CSingleFac.h"
#include "CDatabase.h"
#include "spaceobjects/CAstoroidType.h"

#include "spaceobjects/COrdres.h"
#include "spaceobjects/subsystems/CLoadout.h"
#include "UI/CUIMainFrame.h"
#include "spaceobjects/CSubAble.h"
#include "world/CWorld.h"

uint32_t getTime(){
	return SDL_GetTicks()+Gtime;
}

void* Connect(string ip, uint32_t playerid, uint32_t pass){

	struct sockaddr_in stSockAddr;

    int Res;
    connection.SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (-1 == connection.SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(11142);
    Res = inet_pton(AF_INET, ip.c_str(), &stSockAddr.sin_addr);

    if (0 > Res)
    {
      perror("error: first parameter is not a valid address family");
      close(connection.SocketFD);
      exit(EXIT_FAILURE);
    }
    else if (0 == Res)
    {
      perror("char string (second parameter does not contain valid ipaddress");
      close(connection.SocketFD);
      exit(EXIT_FAILURE);
    }

	if (-1 == connect(connection.SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in))){
		perror("connect failed");
		close(connection.SocketFD);
		exit(EXIT_FAILURE);
	}
	//while (true){
	cerr<<"connected time "<<SDL_GetTicks()<<endl;
	connection.connected = true;


	pthread_create(&connection.listenThread, NULL, (void*(*)(void*))thread_Recive, NULL);
		char message[sizeof(SerialReqJoin)];
		memset(message,0,sizeof(SerialReqJoin));

		SerialReqJoin* data = (SerialReqJoin*)(message);
		data->_type = SerialType::SerialReqJoin;
		data->_size = sizeof(SerialReqJoin);
		data->_unitId = playerid; //TODO BIG TODO FIX THIS SOOON
		playerId = playerid;
		data->_pass = pass;
		send(connection.SocketFD,message,sizeof(SerialReqJoin),0);


		for (int i = 0; i < 5; i++){
			char message2[sizeof(SerialTime)];
			memset(message2,0,sizeof(SerialTime));

			SerialTime* data2 = (SerialTime*)(message2);
			data2->_type = SerialType::SerialTime;
			data2->_size = sizeof(SerialTime);
			data2->time = 0;
			data2->local = SDL_GetTicks();
			cerr<<"send Time req"<<data2->local<<endl;

			send(connection.SocketFD,message2,sizeof(SerialTime),0);

			usleep(200000);
		}
  }



void* thread_Recive(){

		connection.messagebuffer = (char*)malloc(1024);
		memset(connection.messagebuffer,0,1024);
		printf ("recv test....\n");
		int recsize;

		int recived = 0;
		uint32_t delta = 0;

	
		while(connection.connected){

			recsize = recv(connection.SocketFD, connection.messagebuffer + recived, 512,0);

			if (recsize < 0)
					fprintf(stderr, "error\n");
			recived +=recsize;

			if (recived >= 1){
				delta = 1;
				while (delta){
					pthread_mutex_lock(&lockInput);
					delta = parseBuffer(connection.messagebuffer,recived);
					pthread_mutex_unlock(&lockInput);
					memmove(connection.messagebuffer, connection.messagebuffer+ delta, 1024- delta);
					recived -= delta;
				}
			}
			usleep(40);
		}


		shutdown(connection.SocketFD, SHUT_RDWR);

		close(connection.SocketFD);
		pthread_exit(0);
}




uint32_t parseBuffer(char* buffer, uint32_t len){
	uint32_t offset = 0;
	//printBuffer(buffer,len);
	while (offset < len){
		SerialData* meta = (SerialData*)(buffer + offset);

		if (len - offset >= sizeof(uint32_t)*2 && meta->_size <= len - offset){


			switch(meta->_type)
			{
				case SerialType::SerialTime:{
					SerialTime* st = (SerialTime*)(buffer+offset);
					cerr<<"recived time req"<<st->time<< " local "<<SDL_GetTicks()<<endl;
					uint32_t tem = st->time + ((SDL_GetTicks()-st->local)/2);

					Gtime += tem -SDL_GetTicks();

					tTime ++;
					cerr<<"t"<<tTime<<endl;
					if (tTime == 5){
						Gtime = Gtime/5;
						cerr<<"final Gtime "<<Gtime<<endl;
					}
					break;

				}
				case SerialType::SerialObjFullUpdate:{
					SerialObjFullUpdate* st = (SerialObjFullUpdate*)(buffer+offset);
					CPos temppos(st->_Pos_x,st->_Pos_y,st->_Pos_d);

					//playerObj->ReciveObjFullUpdate( st->_Id,temppos,st->);
					break;
				}
				case SerialType::SerialGrid:{
					SerialGrid* st = (SerialGrid*)(buffer+offset);
					world->getGrids()[st->_Id] = new CGrid(st->_Id,st->_wight, st->_hight);
					viewPos->grid = world->getGrids()[st->_Id];
					
					break;
				}
				case SerialType::SerialPlayerTeam:{
					SerialPlayerTeam* st = (SerialPlayerTeam*)(buffer+offset);
					teamlist[st->_playerId] = st->_team;

					break;
				}
				case SerialType::SerialLoadout:{
					SerialLoadout* st = (SerialLoadout*)(buffer+offset);
					if( shipTypes.find(st->_shiptype) != shipTypes.end()){
						if(globalLoadout[st->_id])
							delete globalLoadout[st->_id];

						globalLoadout[st->_id] = new CLoadout(st->_id,string(st->_name),*shipTypes[st->_shiptype]);
						cerr<<"new loadout"<<endl;
					}
					break;
				}
				case SerialType::SerialShipFullUpdate:{
					SerialShipFullUpdate* st = (SerialShipFullUpdate*)(buffer+offset);
					CPos temppos(st->_Pos_x,st->_Pos_y,st->_Pos_d);

					playerObj->ReciveShipFullUpdate( st->_Id, st->_playerOwner, temppos, st->_ShipType);
					break;
				}
				case SerialType::SerialShipDetailUpdate:{
					SerialShipDetailUpdate* st = (SerialShipDetailUpdate*)(buffer+offset);
					playerObj->ReciveShipDetailUpdate(st->_Id, st->_OrdreId, st->_energy);
					break;
				}
				case SerialType::SerialObjPrio:{
					SerialObjPrio* st = (SerialObjPrio*)(buffer+offset);
					playerObj->ReciveObjPrioUpdate(st->_Id, st->_prio);
					break;
				}
				case SerialType::SerialAstoroidFullUpdate:{
					SerialAstoroidFullUpdate* st = (SerialAstoroidFullUpdate*)(buffer+offset);
					CPos temppos(st->_Pos_x,st->_Pos_y,st->_Pos_d);

					playerObj->ReciveAstoroidFullUpdate( st->_Id,temppos,st->_astoroidType);
					break;
				}
				case SerialType::SerialShipDestroy:{
					SerialShipDestroy* st = (SerialShipDestroy*)(buffer+offset);
					playerObj->ReciveShipDestroy( st->_Id, (DestroyMode::Enum)st->_mode);
					break;
				}
				case SerialType::SerialAstoroidDestroy:{
					SerialAstoroidDestroy* st = (SerialAstoroidDestroy*)(buffer+offset);
					playerObj->ReciveAstoroidDestroy( st->_Id, (DestroyMode::Enum)st->_mode);
					break;
				}
				case SerialType::SerialShipSub:{
					SerialShipSub* st = (SerialShipSub*)(buffer+offset);
					CObj* obj = NULL;
					if(playerObj->getObjs().find(st->_Id) != playerObj->getObjs().end())
						obj = playerObj->getObjs()[st->_Id];
					map<uint32_t, CSlotNode*>* subs = playerObj->GetShipSubsysytems( st->_Id);
					if(subs){
						map<uint32_t, CSlotNode*>::iterator subhandle = subs->find(st->_subId);
						if (subhandle != subs->end()){
							if(!subhandle->second->getSS() || (subhandle->second->getSS()->getItemType()->getTypeID() != st->_itemType)){
								if(subhandle->second->getSS())
									delete subhandle->second->getSS();
								subhandle->second->setSS(NULL);
								//SUB REMAKE
								map<uint32_t,CItemType*>::iterator tempId = itemlist.find(st->_itemType);
								if (tempId == itemlist.end()){
									cerr<<"WARNING CFunctions::Parsing: itemType not found"<<endl;
									break;
								}else if(!(tempId->second->getSubType())){
									cerr<<"WARNING CFunctions::Parsing: itemType not a subsystem"<<endl;
									break;
								}else{
									switch(tempId->second->getSubType()->getClass()){
										case SubSystemClass::Wep :{
											CSubSystemW* sw = new CSubSystemW(*obj,*subhandle->second,subhandle->first,tempId->second,st->_xitem);
											subhandle->second->setSS(sw);
											break;
										}
										case SubSystemClass::bonus :{
											CSubSystemBonus* sw = new CSubSystemBonus(*obj,*subhandle->second,subhandle->first,tempId->second,st->_xitem);
											subhandle->second->setSS(sw);
											break;
										}
										case SubSystemClass::boost :{
											CSubSystemBoost* sw = new CSubSystemBoost(*obj,*subhandle->second,subhandle->first,tempId->second,st->_xitem);
											subhandle->second->setSS(sw);
											break;
										}
										case SubSystemClass::Fac :{
											CSubSystemFac* sw = new CSubSystemFac(*obj,*subhandle->second,subhandle->first,tempId->second,st->_xitem);
											subhandle->second->setSS(sw);
											break;
										}
										case SubSystemClass::Ref  :{
											CSubSystemRef* sw = new CSubSystemRef(*obj,*subhandle->second,subhandle->first,tempId->second,st->_xitem);
											subhandle->second->setSS(sw);
											break;
										}
										default:{
											cerr<<"WARNING Cfunction::parseBuffer-shipsub no subsystem created"<<endl;

											break;
										}
									}
								}
							}else{ //ITEM is the same
								//if more have added on server add them
								if (subhandle->second->getSS()->Xitem() < st->_xitem){
									subhandle->second->getSS()->AddItem(st->_xitem -subhandle->second->getSS()->Xitem());

								}else if(subhandle->second->getSS()->Xitem() > st->_xitem){
									if (obj->issubable()){
										obj->issubable()->RemoveSub(st->_subId, subhandle->second->getSS()->Xitem() - st->_xitem);
									}
									
								}
								if(st->_xitem == 0){
									mainFrame->shipDetail()->updateShip();
									break;
								}
								
							}
							for (uint32_t i = 0; i < st->_xitem;i++){
								SerialShipSubIndu* st2 = (SerialShipSubIndu*)(buffer+offset+sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*i));
								subhandle->second->getSS()->setCooldown(i,st2->_durration);
								subhandle->second->getSS()->setMaxCooldown(i,st2->_maxdurration);

							}
							
						}else{
							cerr<<"WARNING CFunctions::Parsing: slot not found"<<endl;
						}
						if (subhandle->second->getSS()){
							
							subhandle->second->getSS()->setOnline((bool)(st->_statusField & BitF_online));
							subhandle->second->getSS()->setRecharge((bool)(st->_statusField & BitF_rechargin));
							if(subhandle->second->getSS()->isWeapon())
								subhandle->second->getSS()->isWeapon()->setHaveTarget((bool)(st->_statusField & BitF_HaveTarget));
							subhandle->second->getSS()->setTargetGroup((TargetGroup::Enum)st->_targetGroup);
							subhandle->second->getSS()->setAmo(st->_amo);
							if(obj->issubable()){
								obj->issubable()->setEnergy(st->_shipEnergy);
							}
						}else{
							cerr<<"WARNING CFunctions::Parsing: no sub created"<<endl;
						}
					}
					break;
				}
				case SerialType::SerialShipTargetPosUpdate:{
					SerialShipTargetPosUpdate* st = (SerialShipTargetPosUpdate*)(buffer+offset);
					CPos temppos(st->_Pos_x,st->_Pos_y,st->_Pos_d);
					CPos temptargetpos(st->_TargetPos_x,st->_TargetPos_y,st->_TargetPos_d);
					playerObj->ReciveShipTargetPosUpdate(st->_Id,temppos,temptargetpos,st->_Speed,st->_MovementStatus);
					break;
				}
				case SerialType::SerialAstoroidPosUpdate:{
					SerialAstoroidPosUpdate* st = (SerialAstoroidPosUpdate*)(buffer+offset);
					CPos temppos(st->_Pos_x,st->_Pos_y,st->_Pos_d);
					playerObj->ReciveAstoroidPosUpdate(st->_Id,temppos);
					break;
				}
				case SerialType::SerialShotFullUpdate:{
					SerialShotFullUpdate* st = (SerialShotFullUpdate*)(buffer+offset);
					CPos temppos(st->_Pos_x,st->_Pos_y,st->_Pos_d);
					CPos temptargetpos(st->_TargetPos_x,st->_TargetPos_y,st->_TargetPos_d);
					playerObj->ReciveShotFullUpdate(st->_Id,temppos,temptargetpos,st->_targetId,st->_texId,st->_speed,st->_FlightTime,st->_maxFlightTime, st->_tracking, st->_trackingTime);
					break;
				}
				case SerialType::SerialObjHpUpdate:{
					SerialObjHpUpdate* st = (SerialObjHpUpdate*)(buffer+offset);
					playerObj->ReciveHpUpdate(st->_Id, st->_shield, st->_deflector, st->_armor, st->_hull);
					break;
				}

				case SerialType::SerialShipType:{
					//TODO
					SerialShipType* st = (SerialShipType*)(buffer+offset);
					shipTypes[st->_ShipTypeId] = new CShipType(st->_ShipTypeId);//TODO data for stats
					shipTypes[st->_ShipTypeId]->setTexture(st->_texture);
					shipTypes[st->_ShipTypeId]->setSize(st->_ShipSize);
					shipTypes[st->_ShipTypeId]->setMass(st->_mass);
					shipTypes[st->_ShipTypeId]->setTopSpeed(st->_topspeed);
					shipTypes[st->_ShipTypeId]->setAgility(st->_agility);
					shipTypes[st->_ShipTypeId]->setEnergy(st->_energy);
					shipTypes[st->_ShipTypeId]->setCargo(st->_cargo);
					shipTypes[st->_ShipTypeId]->setHull(st->_hull);
					shipTypes[st->_ShipTypeId]->setarmor(st->_armor);
					shipTypes[st->_ShipTypeId]->setdeflector(st->_deflector);
					shipTypes[st->_ShipTypeId]->setScanRange(st->_scanrange);
					shipTypes[st->_ShipTypeId]->setScanPRange(st->_scanprange);
					for(int i = 0; i < 6; i++)
						shipTypes[st->_ShipTypeId]->setShield(st->_shield[i],i);
					shipTypes[st->_ShipTypeId]->setShieldStr(st->_shieldStr);
					itemlist[st->_item._itemId] = new CItemType(st->_item._itemId,st->_item._itemtex);
					itemlist[st->_item._itemId]->setShipType(shipTypes[st->_ShipTypeId]);

					string ts(st->_item._name);
					itemlist[st->_item._itemId]->setName(ts);
					for (uint32_t i = 0; i != st->_item._matcount; i++){
						SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+ (sizeof(SerialShipType)+ (sizeof(SerialPartMat) * i)));
						bmaterial temp;
						temp._item = NULL;
						temp._quan = st2->_quantity;
						itemlist[st->_item._itemId]->getCost()[st2->_matid] = temp;
					}

					CDatabase db;
					db.updateItemRefs();
					break;
				}
				case SerialType::SerialTypeAstoroid:{
					//TODO
					SerialTypeAstoroid* st = (SerialTypeAstoroid*)(buffer+offset);
					astoroidTypes[st->_astoroidTypeid] = new CAstoroidType(st->_astoroidTypeid);//TODO data for stats
					astoroidTypes[st->_astoroidTypeid]->setTexture(st->_texture);
					astoroidTypes[st->_astoroidTypeid]->setSize(st->_astoroidsize);

					CDatabase db;
					db.updateItemRefs();
					break;
				}
				case SerialType::SerialOrders:{
					
					SerialOrders* st = (SerialOrders*)(buffer+offset);
					globalOrders[st->_OrdreId] = new COrdres(st->_name, st->_OrdreId);//TODO data for stats
					if(st->_unitsset & BitF_MiningUnit)
						globalOrders[st->_OrdreId]->getunitSet()[0] = true;
					if(st->_unitsset & BitF_DropOfUnit)
						globalOrders[st->_OrdreId]->getunitSet()[1] = true;
					if(st->_posesset & BitF_MiningPos)
						globalOrders[st->_OrdreId]->getPosSet()[0] = true;
					mainFrame->shipDetail()->setChangeOrdre(NULL);
					CDatabase db;
					db.updateItemRefs();
					break;
				}
				case SerialType::SerialShipTypeSlotNode:{
					//TODO
					SerialShipTypeSlotNode* st = (SerialShipTypeSlotNode*)(buffer+offset);
					if (shipTypes[st->_ShipTypeId]){
						shipTypes[st->_ShipTypeId]->getSlots()[st->_SlotId] = new CShipTypeSlotData(st->_slotType,st->_gX,st->_gY,st->_uiX,st->_uiY);
					}
					break;
				}

				case SerialType::SerialTypeWeapon:{
					//TODO
					SerialTypeWeapon* st = (SerialTypeWeapon*)(buffer+offset);
					itemlist[st->_item._itemId] = new CItemType(st->_item._itemId,st->_item._itemtex);
					string ts(st->_item._name);
					itemlist[st->_item._itemId]->setName(ts);
					itemlist[st->_item._itemId]->setMass(st->_item._mass);
					itemlist[st->_item._itemId]->setBuildTime(st->_item._buildtime);
					for (uint32_t i = 0; i != st->_item._matcount; i++){
						SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+ (sizeof(SerialTypeWeapon)+ (sizeof(SerialPartMat) * i)));
						bmaterial temp;
						temp._item = NULL;
						temp._quan = st2->_quantity;
						itemlist[st->_item._itemId]->getCost()[st2->_matid] = temp;
					}
					
					itemlist[st->_item._itemId]->setSubType(new CSubTypeWep(st->_mindmg,st->_maxdmg));
					if(itemlist[st->_item._itemId]->getSubType()->isWeapon()){
						itemlist[st->_item._itemId]->getSubType()->isWeapon()->setMaxAmo(st->_maxamo);
						itemlist[st->_item._itemId]->getSubType()->isWeapon()->setAmoCost(st->_amocost);
					}else
						cerr<<"ERROR CFunctions::Parsing: SerialTypeWeapon subtype is not weapon"<<endl;
		
					CDatabase db;
					db.updateItemRefs();
					
					break;
				}



				case SerialType::SerialTypeBonus:{
					//TODO
					SerialTypeBonus* st = (SerialTypeBonus*)(buffer+offset);
					itemlist[st->_item._itemId] = new CItemType(st->_item._itemId,st->_item._itemtex);
					string ts(st->_item._name);
					itemlist[st->_item._itemId]->setName(ts);
					itemlist[st->_item._itemId]->setMass(st->_item._mass);
					itemlist[st->_item._itemId]->setBuildTime(st->_item._buildtime);
					for (uint32_t i = 0; i != st->_item._matcount; i++){
						SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+ (sizeof(SerialTypeBonus)+ (sizeof(SerialPartMat) * i)));
						bmaterial temp;
						temp._item = NULL;
						temp._quan = st2->_quantity;
						itemlist[st->_item._itemId]->getCost()[st2->_matid] = temp;
					}

					itemlist[st->_item._itemId]->setSubType(new CSubTypeBonus());
					if(itemlist[st->_item._itemId]->getSubType()->isBonus()){

						itemlist[st->_item._itemId]->getSubType()->isBonus()->addBonusFromNet(&st->_bonus);

					}else
						cerr<<"ERROR CFunctions::Parsing: SerialTypeBonus subtype is not boost"<<endl;

					CDatabase db;
					db.updateItemRefs();

					break;
				}

				case SerialType::SerialTypeBoost:{
					//TODO
					SerialTypeBoost* st = (SerialTypeBoost*)(buffer+offset);
					itemlist[st->_item._itemId] = new CItemType(st->_item._itemId,st->_item._itemtex);
					string ts(st->_item._name);
					itemlist[st->_item._itemId]->setName(ts);
					itemlist[st->_item._itemId]->setMass(st->_item._mass);
					itemlist[st->_item._itemId]->setBuildTime(st->_item._buildtime);
					for (uint32_t i = 0; i != st->_item._matcount; i++){
						SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+ (sizeof(SerialTypeBoost)+ (sizeof(SerialPartMat) * i)));
						bmaterial temp;
						temp._item = NULL;
						temp._quan = st2->_quantity;
						itemlist[st->_item._itemId]->getCost()[st2->_matid] = temp;
					}

					itemlist[st->_item._itemId]->setSubType(new CSubTypeBoost((BonusTypes::Enum)st->_boostType,st->_boostValue,st->_cooldown, NULL,0, st->_maxamo,st->_amocost, 0));
					if(itemlist[st->_item._itemId]->getSubType()->isBoost()){

						itemlist[st->_item._itemId]->getSubType()->isBoost()->addBonusFromNet(&st->_bonus);

					}else
						cerr<<"ERROR CFunctions::Parsing: SerialTypeBoost subtype is not boost"<<endl;

					CDatabase db;
					db.updateItemRefs();

					break;
				}

				case SerialType::SerialTypeFac:{
					//TODO
					SerialTypeFac* st = (SerialTypeFac*)(buffer+offset);
					itemlist[st->_item._itemId] = new CItemType(st->_item._itemId,st->_item._itemtex);
					itemlist[st->_item._itemId]->setSubType(new CSubTypeFac());
					
					for(uint32_t i = 0; i < st->_xcanbuild; i++){
						SerialPartConstruct* st2 = (SerialPartConstruct*)(buffer+offset+sizeof(SerialTypeFac)+(sizeof(SerialPartConstruct)*i));
						itemlist[st->_item._itemId]->getSubType()->isFac()->getCanBuildList()[st2->_buildTypeId] = NULL;
					}


					string ts(st->_item._name);
					itemlist[st->_item._itemId]->setMass(st->_item._mass);
					itemlist[st->_item._itemId]->setBuildTime(st->_item._buildtime);
					itemlist[st->_item._itemId]->setName(ts);
					for (uint32_t i = 0; i != st->_item._matcount; i++){
						SerialPartMat* st2 = (SerialPartMat*)(buffer+offset + (sizeof(SerialTypeFac) + (sizeof(SerialPartConstruct)*st->_xcanbuild) + (sizeof(SerialPartMat) * i)));
						bmaterial temp;
						temp._item = NULL;
						temp._quan = st2->_quantity;
						itemlist[st->_item._itemId]->getCost()[st2->_matid] = temp;
					}

					CDatabase db;
					db.updateItemRefs();
					break;
				}
				case SerialType::SerialTypeRef:{
					//TODO
					SerialTypeRef* st = (SerialTypeRef*)(buffer+offset);
					itemlist[st->_item._itemId] = new CItemType(st->_item._itemId,st->_item._itemtex);
					itemlist[st->_item._itemId]->setSubType(new CSubTypeRef());

					for(uint32_t i = 0; i < st->_xcanRefine; i++){
						SerialPartRefine* st2 = (SerialPartRefine*)(buffer+offset+sizeof(SerialTypeRef)+(sizeof(SerialPartRefine)*i));
						itemlist[st->_item._itemId]->getSubType()->isRef()->getCanRefineList()[st2->_refineTypeId] = NULL;
					}


					string ts(st->_item._name);
					itemlist[st->_item._itemId]->setMass(st->_item._mass);
					itemlist[st->_item._itemId]->setBuildTime(st->_item._buildtime);
					itemlist[st->_item._itemId]->setName(ts);
					for (uint32_t i = 0; i != st->_item._matcount; i++){
						SerialPartMat* st2 = (SerialPartMat*)(buffer+offset + (sizeof(SerialTypeRef) + (sizeof(SerialPartRefine)*st->_xcanRefine) + (sizeof(SerialPartMat) * i)));
						bmaterial temp;
						temp._item = NULL;
						temp._quan = st2->_quantity;
						itemlist[st->_item._itemId]->getCost()[st2->_matid] = temp;
					}

					CDatabase db;
					db.updateItemRefs();
					break;
				}
				case SerialType::SerialTypeMaterial:{
					//TODO
					SerialTypeMaterial* st = (SerialTypeMaterial*)(buffer+offset);
					itemlist[st->_item._itemId] = new CItemType(st->_item._itemId,st->_item._itemtex);
					string ts(st->_item._name);
					itemlist[st->_item._itemId]->setName(ts);
					itemlist[st->_item._itemId]->setMass(st->_item._mass);
					itemlist[st->_item._itemId]->setBuildTime(st->_item._buildtime);
					for (uint32_t i = 0; i != st->_item._matcount; i++){
						SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+ (sizeof(SerialTypeMaterial)+ (sizeof(SerialPartMat) * i)));
						bmaterial temp;
						temp._item = NULL;
						temp._quan = st2->_quantity;
						itemlist[st->_item._itemId]->getCost()[st2->_matid] = temp;
					}
					CDatabase db;
					db.updateItemRefs();
					break;
				}
				case SerialType::SerialShotHitTarget:{
					SerialShotHitTarget* st = (SerialShotHitTarget*)(buffer+offset);
					CPos temppos(st->_hitPos_x,st->_hitPos_y,st->_hitPos_d);
					playerObj->ReciveShotHit(st->_Id,st->_targetId,st->_textype,temppos);
					break;
				}
				case SerialType::SerialCargoItem:{
					SerialCargoItem* st = (SerialCargoItem*)(buffer+offset);
					playerObj->ReciveCargoUpdate(st->_Id,st->_itemid,st->_quantity);
					break;
				}
				default:{
					cerr<<"ERROR PARSING debug recived = "<<(uint32_t) *(buffer+offset)<<endl;

					break;
				}
			}
				offset += meta->_size;
		}else{
			//cerr<<"missing data "<<endl;
			break;
		}
	}
	//updateFrames();
	return offset;
}

  void* Disconnect(){

	cerr<<"Disconnect"<<endl;
	shutdown(connection.SocketFD, SHUT_RDWR);

	close(connection.SocketFD);
	connection.connected = false;
	pthread_join(connection.listenThread, NULL);
  }

uint32_t Rangeobj(CPos& pos1, CPos& pos2)
{
	int32_t p1x = pos1.x/100;
	int32_t p2x = pos2.x/100;
	int32_t p1y = pos1.y/100;
	int32_t p2y = pos2.y/100;

	//cerr<<"p1x "<<pos1.x<<" p2x "<<pos2.x<<" p1y "<<pos1.y<<" p2y "<<pos2.y<<endl;
	return sqrt(((p1x - p2x)*(p1x - p2x)) + ((p1y - p2y)*(p1y - p2y)));
}

uint32_t Rangeobj(CPos& pos1, int32_t x2, int32_t y2)
{
	int32_t p1x = pos1.x/100;
	int32_t p2x = x2/100;
	int32_t p1y = pos1.y/100;
	int32_t p2y = y2/100;

	//cerr<<"p1x "<<pos1.x<<" p2x "<<pos2.x<<" p1y "<<pos1.y<<" p2y "<<pos2.y<<endl;
	return sqrt(((p1x - p2x)*(p1x - p2x)) + ((p1y - p2y)*(p1y - p2y)));
}

uint32_t Rangeobj(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	int32_t p1x = x1/100;
	int32_t p2x = x2/100;
	int32_t p1y = y1/100;
	int32_t p2y = y2/100;

	//cerr<<"p1x "<<pos1.x<<" p2x "<<pos2.x<<" p1y "<<pos1.y<<" p2y "<<pos2.y<<endl;
	return sqrt(((p1x - p2x)*(p1x - p2x)) + ((p1y - p2y)*(p1y - p2y)));
}






