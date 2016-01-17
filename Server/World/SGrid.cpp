/* 
 * File:   SGrid.cpp
 * Author: karsten
 * 
 * Created on 22. maj 2011, 16:42
 */

#include "SGrid.h"
#include "../Sspacebjects/SShip.h"
#include "../Sspacebjects/SAstoroid.h"
#include "../Sspacebjects/SMetaObj.h"

#include "SWorld.h"
#include "../Client.h"
#include "../Commands/CommandClientSubscription.h"
#include "../NetworkLayer/SShipNetworkLayer.h"
#include "../NetworkLayer/SGridNetworkLayer.h"
SGrid::SGrid(uint32_t id) {
	this->_id = id;
	
	_spaceHight = 10;
	_spaceWight = 10;
	_destiny = new Destiny();
	pthread_mutex_init(&this->locksubscriber, NULL);
	pthread_mutex_init(&this->lockgrid, NULL);
	cerr<<"init grid"<<endl;
}

SGrid::SGrid(uint32_t id, uint32_t spaceWight, uint32_t spaceHight) {
	this->_id = id;
	_spaceHight = spaceHight;
	_spaceWight = spaceWight;
	_destiny = new Destiny();
	pthread_mutex_init(&this->locksubscriber, NULL);
	pthread_mutex_init(&this->lockgrid, NULL);
	cerr<<"init grid"<<endl;
}

SMetaObj* SGrid::getMetaInGrid(uint32_t id){
	return  _metaInGrid.find(id) != _metaInGrid.end() ? _metaInGrid[id] : NULL;
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


void SGrid::addObj(SMetaObj* meta){
	//cerr<<"SGrid::addObj"<<obj<<endl;
	uint32_t obj = meta->_id;
	this->objInGrid[obj] = obj;
	
	this->_metaInGrid[obj] = meta;
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
	delete this->_metaInGrid[obj];
	this->_metaInGrid.erase(obj);
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

	pthread_mutex_unlock(&locksubscriber);
}



SGrid::~SGrid() {
}

