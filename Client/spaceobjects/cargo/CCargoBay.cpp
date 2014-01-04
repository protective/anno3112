/* 
 * File:   CCargoBay.cpp
 * Author: karsten
 * 
 * Created on 20. september 2011, 19:44
 */

#include "CCargoBay.h"
#include "../../Items/CItemType.h"

CCargoBay::CCargoBay(CSubAble* owner, uint32_t Cargo) {
	this->_owner = owner;
	this->_maxCargo = Cargo;
	this->_curCargo = 0;
	_change = true;
}

void CCargoBay::updateCurCargo(){
	_curCargo = 0;
	for(map<CItemType*, uint32_t>::iterator it = _content.begin(); it != _content.end(); it++){
		_curCargo += it->first->getMass() * it->second;
	}
}

uint32_t CCargoBay::GetReturn(CItemType* item, uint32_t quan){
if (!item)
		cerr<<"ERROR CCargoBay::RemoveReturn unknown item"<<endl;
	//check that we have it
	CCargoI it = this->getContent().find(item);
	if(it != this->_content.end()){
		if (quan > it->second)
			quan = it->second;
	}else
		quan = 0;
	return quan;
}

CCargoBay::~CCargoBay() {
}

