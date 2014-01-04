/* 
 * File:   CDatabase.cpp
 * Author: karsten
 * 
 * Created on 17. september 2011, 19:27
 */

#include "CDatabase.h"
#include "Items/CItemType.h"
#include "spaceobjects/subsystems/CSubTypeFac.h"
CDatabase::CDatabase() {
}

void CDatabase::updateItemRefs(){
	for (map<uint32_t,CItemType*>::iterator it = itemlist.begin(); it != itemlist.end();it++){

		if(it->second){
			map<uint32_t,bmaterial>::iterator test = it->second->getCost().begin();

			for (map<uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin(); it2 != it->second->getCost().end();it2++){
				if(itemlist.find(it2->first) != itemlist.end())
					it2->second._item = itemlist[it2->first];
			}
		


			if (it->second->getSubType() && it->second->getSubType()->getClass() == SubSystemClass::Fac){
				CSubTypeFac* temp = it->second->getSubType()->isFac();
				for ( map<uint32_t,CItemType*>::iterator it2 = temp->getCanBuildList().begin(); it2 != temp->getCanBuildList().end();it2++){
					if (it2->second == NULL && itemlist.find(it2->first) != itemlist.end()){
						temp->getCanBuildList()[it2->first] = itemlist[it2->first];
					}
				}
			}
		}
	}
}


CDatabase::~CDatabase() {
}

