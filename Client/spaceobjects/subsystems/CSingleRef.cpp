/* 
 * File:   CSingleRef.cpp
 * Author: karsten
 * 
 * Created on 24. marts 2012, 18:54
 */

#include "CSingleRef.h"
#include "CSubSystemRef.h"
CSingleRef::CSingleRef(CSubSystemRef* subsys) {
		this->subsys = subsys;
}


void CSingleRef::proces(uint32_t DTime){

	if(this->_cur > 0){
		//cerr<<"tt"<<(40*DTime)/100<<endl;
		this->_cur -= (DTime); //TODO add dmg here
		if (this->_cur < 0)
			this->_cur = 0;
	}

}

CSingleRef::~CSingleRef() {
}

