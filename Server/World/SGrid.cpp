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
#include "../Commands/CommandClientSubscription.h"
#include "../NetworkLayer/SShipNetworkLayer.h"
#include "../NetworkLayer/SGridNetworkLayer.h"
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


void SGrid::sendFull(SubscriptionLevel::Enum level){
	//sendGridFull(subscriber, this); //HMM
	cerr<<"WARNING grid::sendfull not implemented"<<endl;
}

void SGrid::sendFull(Client* cli){
	cerr<<"grid send full"<<endl;
	list<uint32_t> temp;
	temp.push_back(cli->getId());
	sendGridFull(temp, this);
}

/*

void SGrid::add(SObj* obj){
	cerr<<"add wrong"<<endl;
	
	if(obj->isUnit())
		this->addUnit(obj->isUnit());
	if(obj->isAstoroid())
		this->addAsto(obj->isAstoroid());
	if(obj->isShot())
		this->addShot(obj->isShot());
	
	cerr<<"done add"<<endl;
	//if(obj->isFighter())
	//	this->add(obj->isFighter());
}



void SGrid::addAsto(SAstoroid* asto){
		//TODO
	/*
	this->addObj((SObj*)asto);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		asto->getSubscribers()[SubscriptionLevel::lowFreq].push_back(*it);
	}
	asto->sendFull(SubscriptionLevel::lowFreq);
	

}

void SGrid::addShot(SShot* shot){
	cerr<<"grid add shot"<<endl;
	
	this->addObj(shot);
	for(list<Client*>::iterator it =  subscriber.begin(); it != subscriber.end();it++){
		shot->addCommand(new CommandClientSubscription(0,(*it)->getId(),shot,SubscriptionLevel::lowFreq));
	}
	//TODO
	
	this->addObj((SObj*)shot);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		shot->getSubscribers()[SubscriptionLevel::lowFreq].push_back(*it);
	}
	

}

void SGrid::addUnit(SUnit* unit){
	
	this->addObj((SObj*)unit);
	for(list<Client*>::iterator it =  subscriber.begin(); it != subscriber.end();it++){
		unit->addCommand(new CommandClientSubscription(0,(*it)->getId(),unit,SubscriptionLevel::lowFreq));
	
	}
		//TODO
	/*
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		unit->getSubscribers()[SubscriptionLevel::lowFreq].push_back(*it);
	}
	unit->sendFull(SubscriptionLevel::lowFreq);

}	
	*/

void SGrid::addObj(uint32_t obj){
	cerr<<"SGrid::addObj"<<obj<<endl;
	this->objInGrid[obj] = obj;
	
	
	for(map<uint32_t, SubscriptionLevel::Enum>::iterator it = _clientSubscriptions.begin(); it != _clientSubscriptions.end(); it++){
		CommandClientSubscription* temp = new CommandClientSubscription(0,it->first, obj, it->second);
		if(networkControl->addCommandToProcesable(temp,it->first)){
			cerr<<"SGrid::addobj warning processer not found"<<endl;
			delete temp;
		}
	}
}

void SGrid::removeObj(uint32_t obj){
	this->objInGrid.erase(obj);
}

void SGrid::UnSubscribe(Client* cli){
	pthread_mutex_lock(&locksubscriber);
	this->subscriber.remove(cli);
	pthread_mutex_unlock(&locksubscriber);
}

void SGrid::Subscribe(Client* cli)
{
	world->getProcessor();
	
	//TODO SUBSCR
	/*
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
	 * */
}

//command call thread safe
void SGrid::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){
	cerr<<"grid subscribe cli="<<clientId<<endl;
	_clientSubscriptions[clientId] = level;
	sendGridFull(clientId, this);
	
	for(map<uint32_t, uint32_t>::iterator it = objInGrid.begin(); it != objInGrid.end(); it++){
		if (it->second){
			
			CommandClientSubscription* temp = new CommandClientSubscription(0,clientId, it->second, SubscriptionLevel::lowFreq);
			if(networkControl->addCommandToProcesable(temp,it->second)){
				cerr<<"SGrid::subscribeClient warning processer not found"<<endl;
				delete temp;
			}
		}
	}
	
}

//command call thread safe
void SGrid::proces(uint32_t delta, Processor* processor ){
	/*
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
			if (it->second->isUnit())
				it->second->isUnit()->sendRemoved(SubscriptionLevel::lowFreq, DestroyMode::Destroy);
			if (it->second->isAstoroid())
				it->second->isAstoroid()->sendDepleted(SubscriptionLevel::lowFreq);
			this->objInGrid.erase(it++);
			world->getObjs().erase(oldid->second->getId());
			for (SObjI it2 = this->objInGrid.begin() ; it2 != this->objInGrid.end();it2++){
				it2->second->announceRemovalOf(oldid->second);
			}
			delete oldid->second;
		}else
			 it++;
	}
	 * */
}

void SGrid::SendObjInfoToClients(){
	bool gosend = false;
	pthread_mutex_lock(&locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		if((*it)->getProcesCount() == 0){
			gosend = true;
		}
	}
	/*
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
							//TODO SUBSCR
							/*
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
	*/
	pthread_mutex_unlock(&locksubscriber);
}

/*
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

*/

/*
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

*/

/*

void SGrid::BroadCastReportObjHpUdate(SObj* obj){
	//TODO SUBSCR
	/*
	pthread_mutex_lock(&this->locksubscriber);
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		ReportObjHpUdate(*it,obj);
	}
	pthread_mutex_unlock(&this->locksubscriber);
	
}
*/

/*

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
		//TODO SUBSCR
		/*
		pthread_mutex_lock(&locksubscriber);
		for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
			sendtoC(*it,message2,sizeof(SerialShotHitTarget));
			this->ReportObjHpUdate(*it,target->obj());
		}
		pthread_mutex_unlock(&locksubscriber);
		
	
}
*/

/*
void SGrid::ReportShipDestroyd(SShip* ship ){
	pthread_mutex_lock(&locksubscriber);
	
	for(ClientI it = this->subscriber.begin(); it != this->subscriber.end(); it++){
		this->SendShipShipDestroyd(*it,ship,DestroyMode::Destroy);
	}
	pthread_mutex_unlock(&locksubscriber);
}
*/


SGrid::~SGrid() {
}

