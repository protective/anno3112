/* 
 * File:   Client.h
 * Author: karsten
 *
 * Created on 23. april 2011, 10:00
 */

#ifndef CLIENT_H
#define	CLIENT_H
#include "SGlobals.h"
#include "Sspacebjects/SObj.h"

struct NetworkBuffer{
    uint32_t recived;
    char networkBuf[1024];
};

class Client {
public:
	Client(int socket);

	int getSocket(){return this->socket;}

	pthread_t listenThread;
	pthread_mutex_t networkBufLock;
	pthread_mutex_t networkSendLock;
	bool networkSendLockBool;
	void proces(){procescounter++; if(procescounter >= 25)procescounter = 0;}
	uint32_t getProcesCount(){return procescounter;}
	bool switchBuffer(){
       //active_buffer = (active_buffer+1)%2;
		if(outputnetworkBuf->recived + inputnetworkBuf->recived < 1024){
			memmove(outputnetworkBuf->networkBuf + outputnetworkBuf->recived, inputnetworkBuf->networkBuf, inputnetworkBuf->recived);
			outputnetworkBuf->recived += inputnetworkBuf->recived;
			inputnetworkBuf->recived = 0;
			return true;
		}else
			return false;

    }
	void setPlayerId(uint32_t id){this->playerID = id;this->_teamId = teamlist[id];}
	uint32_t getPlayerId(){return this->playerID;}
	uint8_t getTeamId(){return this->_teamId;}
	bool parsingoutput;
    NetworkBuffer* inputnetworkBuf;
    NetworkBuffer* outputnetworkBuf;
	map<uint32_t,SObj*>& getsubscribes(){return this->_subscribes;}
	void sendLoadout(uint32_t id);
	void initTransfere();
	virtual ~Client();
	pthread_mutex_t& getlocksubscriber() {return locksubscriber;}

private:
	void sendShipTypes();
	void sendAstoroidTypes();
	void sendItemTypes();
	void sendOrdres();
	void sendLoadOuts();
	void sendGrids();
	void sendTeams();
	uint32_t procescounter;
	uint32_t playerID;
	uint8_t _teamId;
	int socket;
    uint16_t active_buffer;
    NetworkBuffer networkBuf1;
    NetworkBuffer networkBuf2;
	map<uint32_t,SObj*> _subscribes;
	pthread_mutex_t locksubscriber;
};

#endif	/* CLIENT_H */

