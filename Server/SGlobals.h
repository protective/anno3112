/* 
 * File:   SGlobals.h
 * Author: karsten
 *
 * Created on 23. april 2011, 09:41
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <SDL/SDL.h>
#include <list>
#include <map>
//#include "Sspacebjects/subsystems/SSubType.h"

#define NRTHREADS 1


#ifndef SGLOBALS_H
#define	SGLOBALS_H
using namespace std;
class Client;
class SWorld;
class SSubType;
class SItemType;
class SShipType;
class SAstoroidType;
class SOrdres;
class SLoadout;
extern SWorld* world;
extern list<Client*> clients;
extern pthread_mutex_t lockNetInput;
extern pthread_mutex_t lockClientList;
extern uint32_t freeIdCount;
extern pthread_mutex_t lockFreeID;
extern pthread_barrier_t  procesBar;
extern map<uint32_t,SItemType*> itemlist;
extern map<string,uint32_t> itemlistFileNames;
extern map<uint32_t, SShipType*> shipTypes;
extern map<uint32_t, SAstoroidType*> astoroidTypes;
extern map<uint32_t,map<uint32_t,SOrdres*> > globalOrders;
extern map<uint32_t,map<uint32_t,SLoadout*> > globalLoadout;
extern map<uint32_t,uint8_t> teamlist;
extern list<uint8_t> allteams;
#endif	/* SGLOBALS_H */

