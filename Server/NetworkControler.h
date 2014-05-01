/* 
 * File:   NetworkControler.h
 * Author: karsten
 *
 * Created on 22. februar 2014, 23:13
 */

#ifndef NETWORKCONTROLER_H
#define	NETWORKCONTROLER_H
#include "SFunctions.h"
#include "Client.h"

class Processor;
class NetworkControler {
public:
	NetworkControler();
	
	void addClient(Client* client);
	void removeClient(Client* client);
	void registerObj(uint32_t objId, Processor* processor);
	void deRegisterObj(uint32_t objId);
	Processor* getProcessor(uint32_t objId);
	void readBuffers();
	uint32_t sendToC(uint32_t id, void* block, uint32_t len);
	virtual ~NetworkControler();
private:

	map<uint32_t, Client*> _connections;
	pthread_mutex_t _clientLock;
	pthread_mutex_t _objRegistrationListLock;
	map<uint32_t, Processor*> _objRegistration;
};

#endif	/* NETWORKCONTROLER_H */

