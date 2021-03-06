/* 
 * File:   SGlobals.cpp
 * Author: karsten
 * 
 * Created on 23. april 2011, 09:41
 */
#include "SGlobals.h"
#include "Client.h"
#include "World/SWorld.h"
#include "SFunctions.h"

NetworkControler* networkControl;
pthread_mutex_t lockNetInput  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockClientList= PTHREAD_MUTEX_INITIALIZER;

SWorld* world = NULL;

map<uint32_t,SItemType*> itemlist;
map<string,uint32_t> itemlistFileNames;
map<uint32_t, SUnitType*> unitTypes;
map<uint32_t, SAstoroidType*> astoroidTypes;
map<uint32_t,map<uint32_t,SOrdres*> > globalOrders;
map<uint32_t,map<uint32_t,SLoadout*> > globalLoadout;
map<uint32_t,uint8_t> teamlist;
list<uint8_t> allteams;