/* 
 * File:   AOrdreSet.cpp
 * Author: karsten
 * 
 * Created on 20. juni 2012, 18:41
 */

#include "AOrdreSet.h"

AOrdreSet::AOrdreSet() {
	_moveCost = 0;
	_utility = 0;
}

void AOrdreSet::execute(){
	for(list<AOrdre*>::iterator it = _ordres.begin() ; it != _ordres.end(); it++){
		usleep(1000);
		(*it)->Execute();
	}
}

AOrdreSet::~AOrdreSet() {
	for(list<AOrdre*>::iterator it = _ordresDelete.begin() ; it != _ordresDelete.end(); it++){
		delete (*it);
	}
	for(list<AObjGroup*>::iterator it = _todelete.begin() ; it != _todelete.end(); it++){
		delete (*it);
	}	
		
}

