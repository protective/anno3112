/* 
 * File:   SSubSystemNetworkLayer.h
 * Author: karsten
 *
 * Created on 15. februar 2014, 19:12
 */

#ifndef SSUBSYSTEMNETWORKLAYER_H
#define	SSUBSYSTEMNETWORKLAYER_H
#include <list>

inline void SendSubsystem(list<Client*>& clients, SSubSystem* subs){
	if (subs){
		char message[sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*subs->Xitem())];
		memset(message,0,sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*subs->Xitem()));
		SerialShipSub* data2 = (SerialShipSub*)(message);
		data2->_type = SerialType::SerialShipSub;
		data2->_size = sizeof(SerialShipSub) + sizeof(SerialShipSubIndu)*subs->Xitem();
		data2->_Id = subs->getOwner().getId();
		data2->_subId = subs->getId();
		data2->_xitem = subs->Xitem();
		data2->_itemType = subs->getItemType()->getTypeID();
		data2->_amo = subs->getAmo();
		if(subs->getOwner().isUnit())
			data2->_shipEnergy = subs->getOwner().isUnit()->getEnergy();
		else
			data2->_shipEnergy = 0;
		data2->_statusField = 0;
		if(subs->online())
			data2->_statusField |= BitF_online;
		if(subs->recharge())
			data2->_statusField |= BitF_rechargin;
		if(subs->getTarget())
			data2->_statusField |= BitF_HaveTarget;
		
		//data2->_rechargin = 0; //TODO implement recharge
		data2->_targetGroup = subs->getTargetGroup();
		for(uint32_t i = 0; i != subs->Xitem(); i++){
			SerialShipSubIndu* data3 = (SerialShipSubIndu*)(message+sizeof(SerialShipSub)+(i * sizeof(SerialShipSubIndu)));
			data3->_durration =subs->cooldown(i);
			data3->_maxdurration = subs->maxcooldown(i);
			data3->_hp = 1; //TODO implement hp
		}
		for(list<Client*>::iterator it = clients.begin(); it != clients.end();it++  ){
			sendtoC(*it, message,sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*subs->Xitem()));
		}
	}
}

#endif	/* SSUBSYSTEMNETWORKLAYER_H */

