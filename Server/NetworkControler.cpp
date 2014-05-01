/* 
 * File:   NetworkControler.cpp
 * Author: karsten
 * 
 * Created on 22. februar 2014, 23:13
 */

#include "NetworkControler.h"
#include "Client.h"
#include "Sspacebjects/SSubAble.h"

NetworkControler::NetworkControler() {
	
	pthread_mutex_init(&_clientLock ,NULL);
}

void NetworkControler::readBuffers(){
	for (map<uint32_t, Client*>::iterator ci = _connections.begin(); ci != _connections.end(); ci++){
		ReadBuffer(ci->second);
		ci->second->proces();
	}
}

void NetworkControler::registerObj(uint32_t objId, Processor* processor){
	pthread_mutex_lock(&_objRegistrationListLock);
		_objRegistration[objId] = processor;
		
		//TODO GET all processores dealing with the active grid here
		processor->addCommand(new CommandAddSubscriptions(processor,1,objId));
	pthread_mutex_unlock(&_objRegistrationListLock);
}

void NetworkControler::deRegisterObj(uint32_t objId){
	pthread_mutex_lock(&_objRegistrationListLock);
		_objRegistration.erase(objId);
	pthread_mutex_unlock(&_objRegistrationListLock);
}

Processor* NetworkControler::getProcessor(uint32_t objId){
	Processor* temp;
	map<uint32_t, Processor*>::iterator it;
	pthread_mutex_lock(&_objRegistrationListLock);
	it = _objRegistration.find(objId);
	temp = it != _objRegistration.end() ? it->second : NULL;
	pthread_mutex_unlock(&_objRegistrationListLock);
	return temp;
}

uint32_t NetworkControler::sendToC(uint32_t id, void* block, uint32_t len){
	bool sendt = false;
	//cerr<<"send to c= "<<id<<endl;
	pthread_mutex_lock(&_clientLock);
	map<uint32_t, Client*>::iterator it = _connections.find(id);
	if (it!= _connections.end()){
		//cerr<<"network send len ="<<len<<endl;
		send(it->second->getSocket(),block, len,MSG_NOSIGNAL);
		sendt = true;
	}else
		cerr<<"ERROR CLIENT NOT FOUND"<<endl;
	pthread_mutex_unlock(&_clientLock);
	if(sendt)
		return 0;
	else
		return 1;
}

void NetworkControler::addClient(Client* client){
	cerr<<"add cli before lock"<<endl;
	pthread_mutex_lock(&_clientLock);
	cerr<<"add cli ="<<client->getId()<<endl;
	_connections[client->getId()] = client;
	pthread_mutex_unlock(&_clientLock);
}
void NetworkControler::removeClient(Client* client){
	_connections.erase(client->getId());
}

NetworkControler::~NetworkControler() {
}

