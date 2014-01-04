/* 
 * File:   SOrdreAction.cpp
 * Author: karsten
 * 
 * Created on 17. februar 2012, 13:09
 */

#include "SOrdreAction.h"

SOrdreAction::SOrdreAction() {
}

void SOrdreAction::execute(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid) {
	cerr<<"action exe hm should not happen virtual error ? "<<endl;
}

void SOrdreAction::execute(SObj* callUnit, SObj* triggerUnit) {
	this->execute(callUnit,triggerUnit, NULL);
}

void SOrdreAction::execute(SObj* callUnit) {
	this->execute(callUnit,NULL,NULL);
}

SOrdreAction::~SOrdreAction() {
}

