/* 
 * File:   SCargoBayNetworkLayer.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 13:50
 */

#ifndef SCARGOBAYNETWORKLAYER_H
#define	SCARGOBAYNETWORKLAYER_H
#include <list>
using namespace std;



inline void SendCargoUpdate(list<uint32_t>& clients, SSubAble* obj, SItemType* item, uint32_t quan){
	//NETWORK*********
	char message[sizeof(SerialCargoItem)];
	memset(message,0,sizeof(SerialCargoItem));

	SerialCargoItem* data = (SerialCargoItem*)(message);
	data->_type = SerialType::SerialCargoItem;
	data->_size = sizeof(SerialCargoItem);
	data->_Id = obj->obj()->getId();
	data->_itemid = item->getTypeID();
	data->_quantity = quan;

	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end(); it++){
		networkControl->sendToC(*it,message,sizeof(SerialCargoItem));
	}

}

inline void SendCargoUpdate(list<uint32_t>& clients, SCargoBay* cargobay){
	for(map<SItemType*, uint32_t>::iterator it = cargobay->getContent().begin(); it != cargobay->getContent().end();it++){
		SendCargoUpdate(clients,cargobay->getOwner(),it->first,it->second);
	} 
}

#endif	/* SCARGOBAYNETWORKLAYER_H */

