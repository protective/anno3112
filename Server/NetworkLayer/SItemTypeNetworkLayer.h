/* 
 * File:   SItemTypesNetworkLayer.h
 * Author: karsten
 *
 * Created on 24. august 2014, 00:45
 */


#ifndef SITEMTYPESNETWORKLAYER_H
#define	SITEMTYPESNETWORKLAYER_H
#include <list>

using namespace std;

inline uint32_t packFighter(SItemType* itemType, char* message){
	if (itemType->getSubType()->isFighter()) {
		SSubTypeFighter * temp = itemType->getSubType()->isFighter();
		SerialTypeFighter* data = (SerialTypeFighter*) (message);
		data->_item._itemId = itemType->getTypeID();
		data->_item._itemtex = itemType->getTexId();
		data->_item._mass = itemType->getMass();
		data->_item._buildtime = itemType->getBuildTime();
		if (itemType->getName().size() <= 20){
			memcpy(data->_item._name, itemType->getName().c_str(), itemType->getName().size());
		}else
			cerr << "WARNING Client:senditemtype serial wep  Name to long" << endl;
		data->_item._matcount = itemType->getCost().size(); //TODO
		data->_cooldown = temp->getMaxCd();
		data->_fitClass = 0; //TODO;
		data->_mount = 0; //TODO;
	}
	return sizeof(SerialTypeFighter);
}

inline uint32_t packMaterials( SItemType* itemType, char *message){
	int i = 0;
	for (map<uint32_t,bmaterial>::iterator it = itemType->getCost().begin(); it != itemType->getCost().end(); it++) {
		SerialPartMat* data = (SerialPartMat*)(message + (sizeof(SerialPartMat) * i));
		data->_matid = it->second._item->getTypeID();
		data->_quantity = it->second._quan;
		i++;
	}
	return i * sizeof (SerialPartMat);
}

inline void SendItemType(list<uint32_t>& clients, SItemType* itemType){
	if(itemType->getSubType()){
		if(itemType->getSubType()->isFighter()){
			uint32_t xmats = itemType->getCost().size();
			char message[sizeof (SerialTypeFighter)+ (xmats * sizeof (SerialPartMat))];
			memset(message, 0, sizeof (SerialTypeFighter)+ (xmats * sizeof (SerialPartMat)));
			uint32_t packing=0;

			SerialTypeFighter* data = (SerialTypeFighter*) (message);
			data->_type = SerialType::SerialTypeFighter;
			data->_size = sizeof(SerialTypeFighter)+ (xmats * sizeof (SerialPartMat));

			packing = packFighter(itemType,message);
			packing = packMaterials(itemType, message + packing);

			for(list<uint32_t>::iterator it = clients.begin(); it != clients.end(); it++){
				networkControl->sendToC(*it,message, sizeof (SerialTypeFighter)+ (xmats * sizeof (SerialPartMat)));
			}
		}
	}
}

inline void SendItemType(Client* client, SItemType* itemType){
	if(!client)
		return;
	list<uint32_t> tlist;
	tlist.push_back(client->getId());
	SendItemType(tlist,itemType);
	
}



#endif	/* SITEMTYPESNETWORKLAYER_H */

