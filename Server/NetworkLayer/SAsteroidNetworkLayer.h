/* 
 * File:   SAsteroidNetworkLayer.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 11:49
 */

#ifndef SASTEROIDNETWORKLAYER_H
#define	SASTEROIDNETWORKLAYER_H
#include <list>
using namespace std;
inline void SendAstoroidDestroyd(list<uint32_t>& clients, SAstoroid* asto, DestroyMode::Enum mode){

	//NETWORK*********
	char message[sizeof(SerialAstoroidDestroy)];
	memset(message,0,sizeof(SerialAstoroidDestroy));

	SerialAstoroidDestroy* data = (SerialAstoroidDestroy*)(message);
	data->_type = SerialType::SerialAstoroidDestroy;
	data->_size = sizeof(SerialAstoroidDestroy);
	data->_Id = asto->getId();
	data->_mode = (uint32_t)mode;
	
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end(); it++){
		networkControl->sendToC(*it,message,sizeof(SerialAstoroidDestroy));
	}
}

inline void SendAstoroidFull(list<uint32_t>& clients, SAstoroid* astoroid){
	//NETWORK*********
	char message[sizeof(SerialAstoroidFullUpdate)];
	memset(message,0,sizeof(SerialAstoroidFullUpdate));

	SerialAstoroidFullUpdate* data = (SerialAstoroidFullUpdate*)(message);
	data->_type = SerialType::SerialAstoroidFullUpdate;
	data->_size = sizeof(SerialAstoroidFullUpdate);
	data->_Id = astoroid->getId();
	data->_astoroidType = astoroid->getAstoroidType()->getId();
	data->_Pos_x = astoroid->getPos().x;
	data->_Pos_y = astoroid->getPos().y;
	data->_Pos_d = astoroid->getPos().d;
	
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end(); it++){
		networkControl->sendToC(*it, message,sizeof(SerialAstoroidFullUpdate));
	}
}


#endif	/* SASTEROIDNETWORKLAYER_H */

