/* 
 * File:   NetworkControler.h
 * Author: karsten
 *
 * Created on 22. februar 2014, 23:13
 */

#ifndef NETWORKCONTROLER_H
#define	NETWORKCONTROLER_H
#include "SFunctions.h"
#include "Sspacebjects/SObj.h"

class NetworkControler {
public:
	NetworkControler();
	
	void addClient(Client* client);
	void removeClient(Client* client);
	uint32_t sendToC(uint32_t id);
	virtual ~NetworkControler();
private:

	map<uint32_t, Client*> _connections;
	pthread_mutex_t _clientLock;
};

#endif	/* NETWORKCONTROLER_H */

