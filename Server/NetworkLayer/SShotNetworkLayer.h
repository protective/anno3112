/* 
 * File:   SShotNetworkLayer.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 12:15
 */

#ifndef SSHOTNETWORKLAYER_H
#define	SSHOTNETWORKLAYER_H
#include <list>
using namespace std;
inline void sendShotFull(list<uint32_t>& clients, SShot* shot){

	//NETWORK*********
	char message[sizeof(SerialShotFullUpdate)];
	memset(message,0,sizeof(SerialShotFullUpdate));

	SerialShotFullUpdate* data = (SerialShotFullUpdate*)(message);
	data->_type = SerialType::SerialShotFullUpdate;
	data->_size = sizeof(SerialShotFullUpdate);
	data->_Id = shot->getId();
	if(shot->getTarget()){
		data->_targetId = shot->getTarget();
	}else
		data->_targetId = 0;
	data->_speed = shot->getSpeed();
	data->_texId = shot->getTexId();
	data->_Pos_x = shot->getPos().x;
	data->_Pos_y = shot->getPos().y;
	data->_Pos_d = shot->getPos().d;

	data->_TargetPos_x = shot->getTargetPos().x;
	data->_TargetPos_y = shot->getTargetPos().y;
	data->_TargetPos_d = shot->getTargetPos().d;
	
	data->_FlightTime = shot->getFlightTime();
	data->_maxFlightTime = shot->getMaxFlightTime();
	data->_tracking = shot->getTracking();
	data->_trackingTime = shot->getTrackingTime();

	
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end();it++  ){
		networkControl->sendToC(*it,message,sizeof(SerialShotFullUpdate));
		//sendtoC(*it,message,sizeof(SerialShotFullUpdate));
	}

}

#endif	/* SSHOTNETWORKLAYER_H */

