/* 
 * File:   SSingleRef.cpp
 * Author: karsten
 * 
 * Created on 23. marts 2012, 23:51
 */

#include "SSingleRef.h"
#include "SSubSystem.h"
#include "SSubSystemRef.h"
#include "SSubType.h"
#include "SSubTypeRef.h"
#include "../../SItems/SItemType.h"
#include "../../Sspacebjects/SSubAble.h"
#include "../../World/SGrid.h"
SSingleRef::SSingleRef(SSubSystemRef* subsys) {
	this->subsys = subsys;
	this->_cur = -1;
	this->_charge = 0;
	this->_curitem = NULL;
}


void SSingleRef::proces(){

	if (this->subsys->getOwner().getsubable() == NULL){
		cerr<<"WARNING SSingleFac::proces Not Subable"<<endl;
		return;
	}
	if(this->_cur == 0){
		this->_charge = 1;
		this->_cur = -1;
	}
	if(this->_charge > 0){
		if (this->_curitem){
			if (!this->_curitem->getShipType()){
				if (this->subsys->getOwner().getsubable()){
					if (this->subsys->getOwner().getsubable()->getCargoBay()){
						SCargoBay* temp = this->subsys->getOwner().getsubable()->getCargoBay();
						for(map<uint32_t,bmaterial>::iterator it = this->_curitem->getRefineTo().begin(); it != this->_curitem->getRefineTo().end(); it++){
							SItemType* titem = it->second._item;
							uint32_t tquan = it->second._quan;
							if (temp->AddReturn(titem,tquan) <= tquan){
								cerr<<"INFO SSingleFac::proces no more room in cargobay"<<endl;
							}
						}
						_curitem = NULL;
					}else
						cerr<<"WARNING SSingleFac::proces owner have no cargobay"<<endl;
				}else
					cerr<<"WARNING SSingleFac::proces owner not subable and have no cargobay"<<endl;
			}
		}else
			cerr<<"WARNING SSingleFac::proces we are not building anything?"<<endl;
		this->_charge-=1;
	}

	 if(this->_cur > 0){

		this->_cur -= 1000/FRAMERATE; //TODO add dmg here
		if (this->_cur < 0)
			this->_cur = 0;
	}
}


void SSingleRef::Refine(SItemType* item){
	if(this->_cur <= 0 && this->_charge == 0 ){
		this->_cur = this->subsys->getItemType()->getSubType()->isRef()->getCooldown();
		this->_curitem = item;
		this->subsys->reportCharge(SubscriptionLevel::details);
	}
}

SSingleRef::~SSingleRef() {
}

