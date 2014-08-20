/* 
 * File:   SUnitNetworkLayer.h
 * Author: karsten
 *
 * Created on 15. februar 2014, 12:23
 */

#ifndef SUNITNETWORKLAYER_H
#define	SUNITNETWORKLAYER_H
#include <list>
#include "SSubSystemNetworkLayer.h"
using namespace std;

inline void networkSendUnitHpUdate(list<uint32_t>& clients, SUnit* unit){
	//NETWORK*********
	char message[sizeof(SerialObjHpUpdate)];
	memset(message,0,sizeof(SerialObjHpUpdate));

	SerialObjHpUpdate* data = (SerialObjHpUpdate*)(message);
	data->_type = SerialType::SerialObjHpUpdate;
	data->_size = sizeof(SerialObjHpUpdate);
	data->_Id = unit->getId();
	for(int i = 0; i < 6;i++)
		data->_shield[i] = unit->getShield(i);
	data->_deflector= unit->getDeflector();
	data->_armor= unit->getArmor();
	data->_hull= unit->getHull();
	
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end();it++  ){
		networkControl->sendToC(*it,message,sizeof(SerialObjHpUpdate));
	}
	
}

inline void sendUnitFull(list<uint32_t>& clients, SUnit* unit){
	cerr<<"send unit full"<<endl;
	//NETWORK*********
	char message[sizeof(SerialShipFullUpdate)];
	memset(message,0,sizeof(SerialShipFullUpdate));

	SerialShipFullUpdate* data = (SerialShipFullUpdate*)(message);
	data->_type = SerialType::SerialShipFullUpdate;
	data->_size = sizeof(SerialShipFullUpdate);
	data->_Id = unit->getId();
	data->_playerOwner = unit->getPlayerId();
	data->_ShipType = unit->getUnitType()->getId();
	data->_Pos_x = unit->getPos().x;
	data->_Pos_y = unit->getPos().y;
	data->_Pos_d = unit->getPos().d;

	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end();it++  ){
		networkControl->sendToC(*it,message,sizeof(SerialShipFullUpdate));
	}
	for(SSlotNodeI it = unit->getSlots().begin(); it != unit->getSlots().end(); it++){
		SSubSystem* subs = it->second->getSS();
		SendSubsystem(clients,subs);
	}
	cerr<<"cargobay ="<<unit->getCargoBay()<<endl;
	if(unit->getCargoBay())
		unit->getCargoBay()->sendCargoBay(clients);
	networkSendUnitHpUdate(clients,unit);
}

inline void sendUnitPosUpdate(list<uint32_t>& clients, SUnit* unit){
	char message[sizeof(SerialShipTargetPosUpdate)];
	memset(message,0,sizeof(SerialShipTargetPosUpdate));
	SerialShipTargetPosUpdate* data = (SerialShipTargetPosUpdate*)(message);
	data->_type = SerialType::SerialShipTargetPosUpdate;
	data->_size = sizeof(SerialShipTargetPosUpdate);
	data->_Id = unit->getId();
	data->_Pos_x = unit->getPos().x;
	data->_Pos_y = unit->getPos().y;
	data->_Pos_d = unit->getPos().d;
	data->_TargetPos_x = unit->getTargetPos().x;
	data->_TargetPos_y = unit->getTargetPos().y;
	data->_TargetPos_d = unit->getTargetPos().d;
	data->_MovementStatus = unit->getMovementStatus();
	data->_Speed = unit->getSpeed();
	
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end();it++  ){

		networkControl->sendToC(*it,message,sizeof(SerialShipTargetPosUpdate));
	}

}

inline void sendUnitRemoved(list<uint32_t>& clients, SUnit* unit, DestroyMode::Enum mode){

	//NETWORK*********
	char message[sizeof(SerialShipDestroy)];
	memset(message,0,sizeof(SerialShipDestroy));

	SerialShipDestroy* data = (SerialShipDestroy*)(message);
	data->_type = SerialType::SerialShipDestroy;
	data->_size = sizeof(SerialShipDestroy);
	data->_Id = unit->getId();
	data->_mode = (uint32_t)mode;
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end();it++  ){
		networkControl->sendToC(*it, message,sizeof(SerialShipDestroy));
	}
}
	
#endif	/* SUNITNETWORKLAYER_H */

