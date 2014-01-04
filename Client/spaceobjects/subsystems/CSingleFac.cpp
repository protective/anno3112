/* 
 * File:   CSingleFac.cpp
 * Author: karsten
 * 
 * Created on 16. september 2011, 21:38
 */

#include "CSingleFac.h"
#include "CSubSystemFac.h"

CSingleFac::CSingleFac(CSubSystemFac* subsys) {
	this->subsys = subsys;
}

void CSingleFac::proces(uint32_t DTime){

	if(this->_cur > 0){
		//cerr<<"tt"<<(40*DTime)/100<<endl;
		this->_cur -= (DTime); //TODO add dmg here
		if (this->_cur < 0)
			this->_cur = 0;
	}

}

CSingleFac::~CSingleFac() {
}

