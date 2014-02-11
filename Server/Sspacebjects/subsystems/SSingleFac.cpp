/* 
 * File:   SSingleFac.cpp
 * Author: karsten
 * 
 * Created on 15. september 2011, 09:46
 */

#include "SSingleFac.h"
#include "SSubSystemW.h"
#include "SSubSystemFac.h"
#include "../SShip.h"
#include "../../World/SWorld.h"
#include "../cargo/SCargoBay.h"
SSingleFac::SSingleFac(SSubSystemFac* subsys) {
	this->subsys = subsys;
	this->_cur = -1;
	this->_charge = 0;
}

void SSingleFac::proces(){

	if (this->subsys->getOwner().getsubable() == NULL){
		cerr<<"WARNING SSingleFac::proces Not Subable"<<endl;
		return;
	}
	if(this->_cur == 0){
		this->_charge = 1;
		this->_cur = -1;
	}
	if(this->_charge > 0){
		SPos* temppos =  &this->subsys->getOwner().getPos();
		if (this->subsys->getCurBuild()){
			if (!this->subsys->getCurBuild()->getShipType()){
				if (this->subsys->getOwner().getsubable()){
					if (this->subsys->getOwner().getsubable()->getCargoBay()){
						SCargoBay* temp = this->subsys->getOwner().getsubable()->getCargoBay();
						if (temp->AddReturn(this->subsys->getCurBuild(),this->subsys->getCurBuild()->getBatch()) < this->subsys->getCurBuild()->getBatch()){
							cerr<<"INFO SSingleFac::proces no more room in cargobay"<<endl;
						}
					}else
						cerr<<"WARNING SSingleFac::proces owner have no cargobay"<<endl;
				}else
					cerr<<"WARNING SSingleFac::proces owner not subable and have no cargobay"<<endl;
			}else if(this->subsys->getCurBuild()->getShipType()){
				cerr<<"INFO SSingleFac::proces we are building ship"<<endl;
				SShip* ship = new SShip(getFreeID(), *temppos, *this->subsys->getCurBuild()->getShipType(),this->subsys->getOwner().getPlayerId());
				world->getGrids()[1]->addUnit(ship);
			}
		}else
			cerr<<"WARNING SSingleFac::proces we are not building anything?"<<endl;
		this->_charge-=1;
	}
	
	if(this->_cur <= 0 && this->_charge == 0 && this->subsys->getCurBuild() ){
		if (this->subsys->online()){
			if(this->subsys->getQueue().size() >0 && this->subsys->getCurBuild() == this->subsys->getQueue().front()._item){
				if (this->subsys->getQueue().front()._quantity > 0){
					this->subsys->getQueue().front()._quantity -=1;
					
					this->_cur = this->subsys->getCurBuild()->getBuildTime();
					this->subsys->getOwner().getPos().grid->ReportCharge(this->subsys,false);
				}else{
				this->subsys->getQueue().pop_front();
				}
			}
		}
	}else if(this->_cur > 0){

		this->_cur -= 1000/FRAMERATE; //TODO add dmg here
		if (this->_cur < 0)
			this->_cur = 0;
	}
}



SSingleFac::~SSingleFac() {
}

