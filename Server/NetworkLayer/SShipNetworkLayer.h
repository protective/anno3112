/* 
 * File:   SShipNetworkLayer.h
 * Author: karsten
 *
 * Created on 15. februar 2014, 11:58
 */

#ifndef SSHIPNETWORKLAYER_H
#define	SSHIPNETWORKLAYER_H
#include <list>
#include "SUnitNetworkLayer.h"
using namespace std;
inline void sendShipFull(list<Client*>& clients, SShip* ship){
	sendUnitFull(clients,ship);
	//TODO SUBSCR
	/*	for (map<SItemType*,uint32_t>::iterator it = ship->getCargoBay()->getContent().begin(); it != ship->getCargoBay()->getContent().end();it++){
		SendCargoUpdate(ship,it->first,it->second);
	}

	SendObjTargetPrio(cli,ship);
	this->ReportObjHpUdate(cli,ship);
	*/

}



#endif	/* SSHIPNETWORKLAYER_H */

