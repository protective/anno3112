/* 
 * File:   CSubSystemBoost.cpp
 * Author: karsten
 * 
 * Created on 25. december 2011, 18:46
 */

#include "CSubSystemBoost.h"

CSubSystemBoost::CSubSystemBoost(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item,uint32_t Xitem):
CSubSystemBonus(owner,slotnode,id,item,Xitem){

}



void CSubSystemBoost::proces(uint32_t DTime){
	_graficCounter+= DTime;
	if(this->_cooldown > 0){
		//cerr<<"tt"<<(40*DTime)/100<<endl;
		this->_cooldown -= (DTime); //TODO add dmg here
		if (this->_cooldown < 0)
			this->_cooldown = 0;
	}
}

CSubSystemBoost::~CSubSystemBoost() {
}

