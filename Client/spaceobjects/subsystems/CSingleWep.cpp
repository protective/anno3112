/* 
 * File:   CSingleWep.cpp
 * Author: karsten
 * 
 * Created on 31. juli 2011, 23:36
 */

#include "CSingleWep.h"
#include "CSubSystemW.h"
#include "../CSubAble.h"
#include "../CShot.h"

CSingleWep::CSingleWep(CSubSystemW* subsys) {
}

void CSingleWep::proces(uint32_t DTime){

	if(this->_cur > 0){
		//cerr<<"tt"<<(40*DTime)/100<<endl;
		this->_cur -= (DTime); //TODO add dmg here
		if (this->_cur < 0)
			this->_cur = 0;
	}
	
}

CSingleWep::~CSingleWep() {
}

