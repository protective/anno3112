/* 
 * File:   SLoadout.cpp
 * Author: karsten
 * 
 * Created on 1. marts 2012, 10:15
 */

#include "SLoadout.h"
#include "SSubSystem.h"
#include "SSlotNode.h"
#include "../SSubAble.h"
#include "../cargo/SCargoBay.h"
SLoadout::SLoadout(uint32_t id, string name, SShipType& shipType) {
	_id = id;
	_shipType = &shipType;
	_name = name;
}

void SLoadout::addItem(uint32_t slot, SItemType* type, uint32_t xitem, TargetGroup::Enum targetGroup){

	_items[slot]._type = type;
	_items[slot]._xitem = xitem;
	_items[slot]._targetGroup = targetGroup;

}


void SLoadout::fitTo(SSubAble* obj, SCargoBay* fromCargo){
	for(map<uint32_t,SSlotNode*>::iterator it = obj->getSlots().begin(); it != obj->getSlots().end();it++){
		obj->FitRemoveSub(it->first,4,fromCargo);
	}

	for(map<uint32_t,SSlotNode*>::iterator it = obj->getSlots().begin(); it != obj->getSlots().end();it++){
		if(this->_items.find(it->first) != this->_items.end()){
			if(obj->getSlots()[it->first]->getSS() && _items[it->first]._type != obj->getSlots()[it->first]->getSS()->getItemType())
				obj->FitRemoveSub(it->first,4,fromCargo);
			obj->FitAddSub(_items[it->first]._type,it->first,_items[it->first]._xitem,fromCargo);
			if(obj->getSlots()[it->first]->getSS())
				obj->getSlots()[it->first]->getSS()->setTargetGroup(_items[it->first]._targetGroup);
		}else
			obj->FitRemoveSub(it->first,4,fromCargo);
	}
}


SLoadout::~SLoadout() {
}

