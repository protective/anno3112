/* 
 * File:   SCargoBayNetworkLayer.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 13:50
 */

#ifndef SCARGOBAYNETWORKLAYER_H
#define	SCARGOBAYNETWORKLAYER_H
#include <list>

inline void SendCargoUpdate(list<Client*>& clients, SSubAble* obj, SItemType* item, uint32_t quan){

	//NETWORK*********
	char message[sizeof(SerialCargoItem)];
	memset(message,0,sizeof(SerialCargoItem));

	SerialCargoItem* data = (SerialCargoItem*)(message);
	data->_type = SerialType::SerialCargoItem;
	data->_size = sizeof(SerialCargoItem);
	data->_Id = obj->obj()->getId();
	data->_itemid = item->getTypeID();
	data->_quantity = quan;

	for(list<Client*>::iterator it = clients.begin(); it != clients.end();it++  ){
		sendtoC(*it,message,sizeof(SerialCargoItem));
	}

}

#endif	/* SCARGOBAYNETWORKLAYER_H */

