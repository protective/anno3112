/* 
 * File:   NetworkControler.cpp
 * Author: karsten
 * 
 * Created on 22. februar 2014, 23:13
 */

#include "NetworkControler.h"
#include "Client.h"

NetworkControler::NetworkControler() {
	
	pthread_mutex_init(&_clientLock ,NULL);
}


uint32_t NetworkControler::sendToC(uint32_t id, void* block, uint32_t len){
	bool sendt = false;
	pthread_mutex_lock(&_clientLock);
	map<uint32_t, Client*>::iterator it = _connections.find(id);
	if (it!= _connections.end()){
		send(it->second->getSocket(),block, len,MSG_NOSIGNAL);
		sendt = true;
	}
	pthread_mutex_unlock(&_clientLock);
	if(sendt)
		return 0;
	else
		return 1;
}

void NetworkControler::addClient(Client* client){

	pthread_mutex_lock(&_clientLock);
	
	pthread_mutex_unlock(&_clientLock);
}
void NetworkControler::removeClient(Client* client){

}

NetworkControler::~NetworkControler() {
}

