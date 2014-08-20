/* 
 * File:   STargetableNetworkLayer.h
 * Author: karsten
 *
 * Created on 2. juni 2014, 22:46
 */

#ifndef STARGETABLENETWORKLAYER_H
#define	STARGETABLENETWORKLAYER_H

#include <list>
using namespace std;

inline void networkSendTargetHit(list<uint32_t>& clients, STargetable* target, uint32_t shot, ParticalTex::Enum tex, int32_t x, int32_t y){
	char message2[sizeof(SerialShotHitTarget)];
	memset(message2,0,sizeof(SerialShotHitTarget));

	SerialShotHitTarget* data2 = (SerialShotHitTarget*)(message2);
	data2->_type = SerialType::SerialShotHitTarget;
	data2->_size = sizeof(SerialShotHitTarget);
	data2->_Id = shot;
	data2->_targetId = target->obj()->getId();
	data2->_hitPos_x = x;
	data2->_hitPos_y = y;
	data2->_hitPos_d = 0;
	data2->_textype = (uint32_t)tex;
	
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end();it++  ){
		networkControl->sendToC(*it,message2,sizeof(SerialShotHitTarget));
	}

}

#endif	/* STARGETABLENETWORKLAYER_H */

