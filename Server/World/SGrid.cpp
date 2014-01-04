/* 
 * File:   SGrid.cpp
 * Author: karsten
 * 
 * Created on 22. maj 2011, 16:42
 */

#include "SGrid.h"
#include "../Sspacebjects/SShip.h"
#include "../Sspacebjects/SAstoroid.h"
#include "SWorld.h"
#include "../Client.h"

SGrid::SGrid(uint32_t id) {
	this->_id = id;
	_spaceHight = 10;
	_spaceWight = 10;
	pthread_mutex_init(&this->locksubscriber, NULL);
	pthread_mutex_init(&this->lockgrid, NULL);
	cerr<<"init grid"<<endl;
}

SGrid::SGrid(uint32_t id, uint32_t spaceWight, uint32_t spaceHight) {
	this->_id = id;
	_spaceHight = spaceHight;
	_spaceWight = spaceWight;
	pthread_mutex_init(&this->locksubscriber, NULL);
	pthread_mutex_init(&this->lockgrid, NULL);
	cerr<<"init grid"<<endl;
}
void SGrid::addShip(SShip* ship){
	this->addObj((SObj*)ship);
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		if (ship->getVisibleTo().find((*it)->getTeamId()) != ship->getVisibleTo().end()){
			if (ship->getVisibleTo()[(*it)->getTeamId()] == Visibility::Visible){

				this->SendShipFull(*it,ship);
				this->ReportObjHpUdate(*it,ship);
			}
		}
	}
	pthread_mutex_unlock(&locksubscriber);
	
}

void SGrid::addAstoroid(SAstoroid* asto){
	this->addObj((SObj*)asto);
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		this->SendAstoroidFull(*it,asto);

	}
	pthread_mutex_unlock(&locksubscriber);

}

void SGrid::addShot(SShot* shot){

	this->addObj((SObj*)shot);

	//NETWORK*********
	char message[sizeof(SerialShotFullUpdate)];
	memset(message,0,sizeof(SerialShotFullUpdate));

	SerialShotFullUpdate* data = (SerialShotFullUpdate*)(message);
	data->_type = SerialType::SerialShotFullUpdate;
	data->_size = sizeof(SerialShotFullUpdate);
	data->_Id = shot->getId();
	if(shot->getTarget()){
		data->_targetId = shot->getTarget()->obj()->getId();
	}else
		data->_targetId = 0;
	data->_speed = shot->getSpeed();
	data->_texId = shot->getTexId();
	data->_Pos_x = shot->getPos().x;
	data->_Pos_y = shot->getPos().y;
	data->_Pos_d = shot->getPos().d;

	data->_TargetPos_x = shot->getTargetPos().x;
	data->_TargetPos_y = shot->getTargetPos().y;
	data->_TargetPos_d = shot->getTargetPos().d;
	
	data->_FlightTime = shot->getFlightTime();
	data->_maxFlightTime = shot->getMaxFlightTime();
	data->_tracking = shot->getTracking();
	data->_trackingTime = shot->getTrackingTime();
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		sendtoC(*it,message,sizeof(SerialShotFullUpdate));
	}
	pthread_mutex_unlock(&locksubscriber);

}

void SGrid::addObj(SObj* obj){
	pthread_mutex_lock(&this->lockgrid);
	this->objToAdd[obj->getId()] = obj;
	pthread_mutex_unlock(&this->lockgrid);
}

void SGrid::removeObj(SObj* obj){

}

void SGrid::UnSubscribe(Client* cli){
	pthread_mutex_lock(&locksubscriber);
	this->subscriber.remove(cli);
	pthread_mutex_unlock(&locksubscriber);
}

void SGrid::Subscribe(Client* cli)
{
	pthread_mutex_lock(&locksubscriber);
	this->subscriber.push_back(cli);
	pthread_mutex_unlock(&locksubscriber);
	for (SObjI so = this->objInGrid.begin();so != this->objInGrid.end();so++){
		if (so->second->isShip()){
			//SShip* sos = (SShip*)so->second; //TODO fix hard cast


			if (so->second->getVisibleTo().find(cli->getTeamId()) != so->second->getVisibleTo().end()){
				if (so->second->getVisibleTo()[cli->getTeamId()] == Visibility::Visible){
					this->SendShipFull(cli,so->second->isShip());
				}
			}

		}else if (so->second->isAstoroid()){
			this->SendAstoroidFull(cli,so->second->isAstoroid());
		}
	}
}

void SGrid::Proces(uint32_t thead_id){
	for (SObjI it = this->objToAdd.begin() ; it != this->objToAdd.end();it++){
		it->second->getPos().grid = this;
		this->objInGrid[it->second->getId()] = it->second;
		world->getObjs()[it->second->getId()] = it->second;
	}
	this->objToAdd.clear();
	//remove old objects
	for (SObjI it = this->objInGrid.begin() ; it != this->objInGrid.end();){
		if(it->second->canBeRemoved()){
			SObjI oldid = it;
			if (it->second->isShip())
				this->ReportShipDestroyd(it->second->isShip());
			if (it->second->isAstoroid())
				this->ReportAstoroidDepleted(it->second->isAstoroid());
			this->objInGrid.erase(it++);
			world->getObjs().erase(oldid->second->getId());
			for (SObjI it2 = this->objInGrid.begin() ; it2 != this->objInGrid.end();it2++){
				it2->second->announceRemovalOf(oldid->second);
			}
			delete oldid->second;
		}else
			 it++;
	}
}

void SGrid::SendObjInfoToClients(){
	bool gosend = false;
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		if((*it)->getProcesCount() == 0){
			gosend = true;
		}
	}
	for (SObjI so = this->objInGrid.begin();so != this->objInGrid.end();so++){
//		cerr<<so->second->getUpdateCounter()<<endl;
		if (!so->second->getUpdateCounter()){
			so->second->setUpdateCounter(25);
			if (so->second->isShip()){
				//**************************************
				//details
				list<Client*> tempcli;
				
				for (ClientI it = subscriber.begin(); it != subscriber.end(); it++){
					pthread_mutex_lock(&(*it)->getlocksubscriber());
					SObjI obit = (*it)->getsubscribes().find(so->second->getId());
					if (obit != (*it)->getsubscribes().end())
						tempcli.push_back((*it));
					pthread_mutex_unlock(&(*it)->getlocksubscriber());
				}
				
				if (tempcli.size() > 0){
					for(ClientI it = tempcli.begin(); it != tempcli.end(); it++){
						if (so->second->getVisibleTo().find((*it)->getTeamId()) != so->second->getVisibleTo().end()){
							if (so->second->getVisibleTo().find((*it)->getTeamId())->second == Visibility::Visible){
								SendShipDetails(*it,so->second->isShip());
							}
						}
					}
				}
				for(list<uint8_t>::iterator i = allteams.begin(); i != allteams.end(); i++){
					if (so->second->getVisibleTo().find(*i) != so->second->getVisibleTo().end()){
						if (so->second->getVisibleTo()[*i] == Visibility::PreVisible){
							for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
								if((*it)->getTeamId() == *i){
									this->SendShipFull(*it,so->second->isShip());
								}
							}
							so->second->getVisibleTo()[*i] = Visibility::Visible;
						}else if (so->second->getVisibleTo()[*i] == Visibility::PreInvisible){
							for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
								if((*it)->getTeamId() == *i){
									this->SendShipShipDestroyd(*it,so->second->isShip(),DestroyMode::Vanish);
								}
							}
							so->second->getVisibleTo().erase(*i);
						}
					}
				}


				//**************************************
				//position updates
				SShip* sos = so->second->isShip();

				char message[sizeof(SerialShipTargetPosUpdate)];
				memset(message,0,sizeof(SerialShipTargetPosUpdate));

				SerialShipTargetPosUpdate* data = (SerialShipTargetPosUpdate*)(message);
				data->_type = SerialType::SerialShipTargetPosUpdate;
				data->_size = sizeof(SerialShipTargetPosUpdate);
				data->_Id = sos->getId();
				data->_Pos_x = sos->getPos().x;
				data->_Pos_y = sos->getPos().y;
				data->_Pos_d = sos->getPos().d;
				data->_TargetPos_x = sos->getTargetPos().x;
				data->_TargetPos_y = sos->getTargetPos().y;
				data->_TargetPos_d = sos->getTargetPos().d;
				data->_MovementStatus = sos->getMovementStatus();
				data->_Speed = sos->getSpeed();
				for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
					if (so->second->getVisibleTo().find((*it)->getTeamId()) != so->second->getVisibleTo().end()){
						if (so->second->getVisibleTo().find((*it)->getTeamId())->second == Visibility::Visible){
							sendtoC(*it,message,sizeof(SerialShipTargetPosUpdate));
						}
					}
				}
			}else if (so->second->isAstoroid()){
				SAstoroid* sos = so->second->isAstoroid(); //TODO fix hard cast

				char message[sizeof(SerialAstoroidPosUpdate)];
				memset(message,0,sizeof(SerialAstoroidPosUpdate));

				SerialAstoroidPosUpdate* data = (SerialAstoroidPosUpdate*)(message);
				data->_type = SerialType::SerialAstoroidPosUpdate;
				data->_size = sizeof(SerialAstoroidPosUpdate);
				data->_Id = sos->getId();
				data->_Pos_x = sos->getPos().x;
				data->_Pos_y = sos->getPos().y;
				data->_Pos_d = sos->getPos().d;

				for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
					sendtoC(*it,message,sizeof(SerialAstoroidPosUpdate));
				}
			}
		}
	}
	pthread_mutex_unlock(&locksubscriber);
}
void SGrid::SendShipPosUpdate(SShip* ship){

	char message[sizeof(SerialShipTargetPosUpdate)];
	memset(message,0,sizeof(SerialShipTargetPosUpdate));
	SerialShipTargetPosUpdate* data = (SerialShipTargetPosUpdate*)(message);
	data->_type = SerialType::SerialShipTargetPosUpdate;
	data->_size = sizeof(SerialShipTargetPosUpdate);
	data->_Id = ship->getId();
	data->_Pos_x = ship->getPos().x;
	data->_Pos_y = ship->getPos().y;
	data->_Pos_d = ship->getPos().d;
	data->_TargetPos_x = ship->getTargetPos().x;
	data->_TargetPos_y = ship->getTargetPos().y;
	data->_TargetPos_d = ship->getTargetPos().d;
	data->_MovementStatus = ship->getMovementStatus();
	data->_Speed = ship->getSpeed();
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		sendtoC(*it,message,sizeof(SerialShipTargetPosUpdate));
	}
	
	pthread_mutex_unlock(&locksubscriber);

}
void SGrid::SendShipFull(Client* cli,SShip* ship){
	//NETWORK*********
	char message[sizeof(SerialShipFullUpdate)];
	memset(message,0,sizeof(SerialShipFullUpdate));

	SerialShipFullUpdate* data = (SerialShipFullUpdate*)(message);
	data->_type = SerialType::SerialShipFullUpdate;
	data->_size = sizeof(SerialShipFullUpdate);
	data->_Id = ship->getId();
	data->_playerOwner = ship->getPlayerId();
	data->_ShipType = ship->getShipType()->getId();
	data->_Pos_x = ship->getPos().x;
	data->_Pos_y = ship->getPos().y;
	data->_Pos_d = ship->getPos().d;
	sendtoC(cli,message,sizeof(SerialShipFullUpdate));
	for (map<SItemType*,uint32_t>::iterator it = ship->getCargoBay()->getContent().begin(); it != ship->getCargoBay()->getContent().end();it++){
		SendCargoUpdate(ship,it->first,it->second);
	}
	for(SSlotNodeI it = ship->getSlots().begin(); it != ship->getSlots().end(); it++){
		SSubSystem* subs = it->second->getSS();
		SendShipSubsystem(cli,subs);
	}
	SendObjTargetPrio(cli,ship);
	this->ReportObjHpUdate(cli,ship);

}

void SGrid::SendObjTargetPrio(Client* cli,SObj* obj){

	//NETWORK*********
	char message[sizeof(SerialObjPrio)];
	memset(message,0,sizeof(SerialObjPrio));

	SerialObjPrio* data = (SerialObjPrio*)(message);
	data->_type = SerialType::SerialObjPrio;
	data->_size = sizeof(SerialObjPrio);
	data->_Id = obj->getId();
	if(obj->getTargetable())
		data->_prio = obj->getTargetable()->getprio()[cli->getPlayerId()];
	else
		data->_prio = 0;
	sendtoC(cli,message,sizeof(SerialObjPrio));
}


void SGrid::SendShipShipDestroyd(Client* cli,SShip* ship, DestroyMode::Enum mode){

	//NETWORK*********
	char message[sizeof(SerialShipDestroy)];
	memset(message,0,sizeof(SerialShipDestroy));

	SerialShipDestroy* data = (SerialShipDestroy*)(message);
	data->_type = SerialType::SerialShipDestroy;
	data->_size = sizeof(SerialShipDestroy);
	data->_Id = ship->getId();
	data->_mode = (uint32_t)mode;

	sendtoC(cli,message,sizeof(SerialShipDestroy));
	
}

void SGrid::SendAstoroidDestroyd(Client* cli,SAstoroid* asto, DestroyMode::Enum mode){

	//NETWORK*********
	char message[sizeof(SerialAstoroidDestroy)];
	memset(message,0,sizeof(SerialAstoroidDestroy));

	SerialAstoroidDestroy* data = (SerialAstoroidDestroy*)(message);
	data->_type = SerialType::SerialAstoroidDestroy;
	data->_size = sizeof(SerialAstoroidDestroy);
	data->_Id = asto->getId();
	data->_mode = (uint32_t)mode;

	sendtoC(cli,message,sizeof(SerialAstoroidDestroy));

}

void SGrid::SendShipDetails(Client* cli,SShip* ship){
//NETWORK*********
	if(ship){
		if(ship->getOrdres()){
			char message[sizeof(SerialShipDetailUpdate)];
			memset(message,0,sizeof(SerialShipDetailUpdate));

			SerialShipDetailUpdate* data = (SerialShipDetailUpdate*)(message);
			data->_type = SerialType::SerialShipDetailUpdate;
			data->_size = sizeof(SerialShipDetailUpdate);
			data->_Id = ship->getId();
			data->_OrdreId = ship->getOrdres()->getId();
			data->_energy = ship->getEnergy();

			sendtoC(cli,message,sizeof(SerialShipDetailUpdate));
		}
	}
}

void SGrid::SendShipSubsystem(Client* cli, SSubSystem* subs){
	if (subs){
		char message[sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*subs->Xitem())];
		memset(message,0,sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*subs->Xitem()));
		SerialShipSub* data2 = (SerialShipSub*)(message);
		data2->_type = SerialType::SerialShipSub;
		data2->_size = sizeof(SerialShipSub) + sizeof(SerialShipSubIndu)*subs->Xitem();
		data2->_Id = subs->getOwner().getId();
		data2->_subId = subs->getId();
		data2->_xitem = subs->Xitem();
		data2->_itemType = subs->getItemType()->getTypeID();
		data2->_amo = subs->getAmo();
		if(subs->getOwner().isShip())
			data2->_shipEnergy = subs->getOwner().isShip()->getEnergy();
		else
			data2->_shipEnergy = 0;
		data2->_statusField = 0;
		if(subs->online())
			data2->_statusField |= BitF_online;
		if(subs->recharge())
			data2->_statusField |= BitF_rechargin;
		if(subs->getTarget())
			data2->_statusField |= BitF_HaveTarget;
		
		//data2->_rechargin = 0; //TODO implement recharge
		data2->_targetGroup = subs->getTargetGroup();
		for(uint32_t i = 0; i != subs->Xitem(); i++){
			SerialShipSubIndu* data3 = (SerialShipSubIndu*)(message+sizeof(SerialShipSub)+(i * sizeof(SerialShipSubIndu)));
			data3->_durration =subs->cooldown(i);
			data3->_maxdurration = subs->maxcooldown(i);
			data3->_hp = 1; //TODO implement hp
		}
		//cerr<<sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*subs->Xitem())<<endl;
		sendtoC(cli,message,sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*subs->Xitem()));
	}
}



void SGrid::SendAstoroidFull(Client* cli, SAstoroid* astoroid){
	//NETWORK*********
	char message[sizeof(SerialAstoroidFullUpdate)];
	memset(message,0,sizeof(SerialAstoroidFullUpdate));

	SerialAstoroidFullUpdate* data = (SerialAstoroidFullUpdate*)(message);
	data->_type = SerialType::SerialAstoroidFullUpdate;
	data->_size = sizeof(SerialAstoroidFullUpdate);
	data->_Id = astoroid->getId();
	data->_astoroidType = astoroid->getAstoroidType()->getId();
	data->_Pos_x = astoroid->getPos().x;
	data->_Pos_y = astoroid->getPos().y;
	data->_Pos_d = astoroid->getPos().d;
	sendtoC(cli,message,sizeof(SerialAstoroidFullUpdate));

}


void SGrid::SendCargoUpdate(SSubAble* obj, SItemType* item, uint32_t quan){

		//NETWORK*********
		char message[sizeof(SerialCargoItem)];
		memset(message,0,sizeof(SerialCargoItem));

		SerialCargoItem* data = (SerialCargoItem*)(message);
		data->_type = SerialType::SerialCargoItem;
		data->_size = sizeof(SerialCargoItem);
		data->_Id = obj->obj()->getId();
		data->_itemid = item->getTypeID();
		data->_quantity = quan;


		//pthread_mutex_lock(&locksubscriber);
		for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
			sendtoC(*it,message,sizeof(SerialCargoItem));
		}
		//pthread_mutex_unlock(&locksubscriber);
}


void SGrid::ReportCharge(SSubSystem* subs,bool ToAll){
	
	if (subs){
		pthread_mutex_lock(&this->locksubscriber);
		if(!ToAll){
			list<Client*> tempcli;
			for (ClientI it = subscriber.begin(); it != subscriber.end(); it++){
				pthread_mutex_lock(&(*it)->getlocksubscriber());
				SObjI obit = (*it)->getsubscribes().find(subs->getOwner().getId());
				if (obit != (*it)->getsubscribes().end())
					tempcli.push_back((*it));
				pthread_mutex_unlock(&(*it)->getlocksubscriber());
			}

			if (tempcli.size() > 0){
				for(ClientI it = tempcli.begin(); it != tempcli.end(); it++){
					SendShipSubsystem(*it,subs);
				}
			}
		}else{
			for(ClientI it = subscriber.begin(); it != subscriber.end(); it++){
				SendShipSubsystem(*it,subs);
			}
		}
		
		pthread_mutex_unlock(&this->locksubscriber);
	}
	
}
void SGrid::BroadCastReportObjHpUdate(SObj* obj){
	pthread_mutex_lock(&this->locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		ReportObjHpUdate(*it,obj);
	}
	pthread_mutex_unlock(&this->locksubscriber);
}

void SGrid::ReportObjHpUdate(Client* cli, SObj* obj){
	if (obj->isShip()){
		//NETWORK*********
		char message[sizeof(SerialObjHpUpdate)];
		memset(message,0,sizeof(SerialObjHpUpdate));

		SerialObjHpUpdate* data = (SerialObjHpUpdate*)(message);
		data->_type = SerialType::SerialObjHpUpdate;
		data->_size = sizeof(SerialObjHpUpdate);
		data->_Id = obj->getId();
		for(int i = 0; i < 6;i++)
			data->_shield[i] = obj->isShip()->getShield(i);
		data->_deflector= obj->isShip()->getDeflector();
		data->_armor= obj->isShip()->getArmor();
		data->_hull= obj->isShip()->getHull();

		sendtoC(cli,message,sizeof(SerialObjHpUpdate));

	}


}

void SGrid::ReportHit(STargetable* target, SShot* shot,ParticalTex::Enum tex, int32_t x, int32_t y){
		//***************
		char message2[sizeof(SerialShotHitTarget)];
		memset(message2,0,sizeof(SerialShotHitTarget));

		SerialShotHitTarget* data2 = (SerialShotHitTarget*)(message2);
		data2->_type = SerialType::SerialShotHitTarget;
		data2->_size = sizeof(SerialShotHitTarget);
		data2->_Id = shot->getId();
		data2->_targetId = target->obj()->getId();
		data2->_hitPos_x = x;
		data2->_hitPos_y = y;
		data2->_hitPos_d = 0;
		data2->_textype = (uint32_t)tex;
		pthread_mutex_lock(&locksubscriber);
		for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
			sendtoC(*it,message2,sizeof(SerialShotHitTarget));
			this->ReportObjHpUdate(*it,target->obj());
		}
		pthread_mutex_unlock(&locksubscriber);

	
}

void SGrid::ReportShipDestroyd(SShip* ship ){
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		this->SendShipShipDestroyd(*it,ship,DestroyMode::Destroy);
	}
	pthread_mutex_unlock(&locksubscriber);
}

void SGrid::ReportAstoroidDepleted(SAstoroid* asto){
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		this->SendAstoroidDestroyd(*it,asto,DestroyMode::Depleted);
	}
	pthread_mutex_unlock(&locksubscriber);
}


SGrid::~SGrid() {
}

