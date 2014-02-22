/* 
 * File:   SFighterNetworkLayer.h
 * Author: karsten
 *
 * Created on 15. februar 2014, 12:25
 */

#ifndef SFIGHTERNETWORKLAYER_H
#define	SFIGHTERNETWORKLAYER_H

#include "SUnitNetworkLayer.h"
using namespace std;
inline void sendFighterFull(list<Client*>& clients, SFighter* fighter){
	sendUnitFull(clients,fighter);
	//TODO SUBSCR
	/*	for (map<SItemType*,uint32_t>::iterator it = ship->getCargoBay()->getContent().begin(); it != ship->getCargoBay()->getContent().end();it++){
		SendCargoUpdate(ship,it->first,it->second);
	}
	for(SSlotNodeI it = ship->getSlots().begin(); it != ship->getSlots().end(); it++){
		SSubSystem* subs = it->second->getSS();
		SendShipSubsystem(cli,subs);
	}
	SendObjTargetPrio(cli,ship);
	this->ReportObjHpUdate(cli,ship);
	*/

}

#endif	/* SFIGHTERNETWORKLAYER_H */

