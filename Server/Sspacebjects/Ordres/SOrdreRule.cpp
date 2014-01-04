/* 
 * File:   SOrdreRule.cpp
 * Author: karsten
 * 
 * Created on 2. januar 2012, 16:30
 */

#include "SOrdreRule.h"
#include "SOrdreCondition.h"
#include "../../Sspacebjects/SObj.h"
#include "../../World/SGrid.h"
SOrdreRule::SOrdreRule() {
}


void SOrdreRule::proces(OrdreEvent::Enum event, SObj* callUnit){
	this->proces(event,callUnit,NULL,NULL);
}

void SOrdreRule::procesRangeChange(SObj* callUnit, SObj* triggerUnit, uint32_t newrange, uint32_t oldrange){
	bool evok = false;
	//cerr<<"procesRangeChange >"<< newrange<<" "<<oldrange<<endl;
	for(list<SEvent*>::iterator it = this->_events.begin(); it != this->_events.end(); it++){
		//cerr<<"event "<<event<<" it "<<(*it)<<endl;
		if((*it)->_event == OrdreEvent::UnitEnterRangeUnit){
			if(oldrange > (*it)->_value && newrange <= (*it)->_value)
				evok = true;
		}
		if((*it)->_event == OrdreEvent::UnitLeaveRangeUnit){
			if(oldrange <= (*it)->_value && newrange > (*it)->_value)
				evok = true;
		}
	}

	if(evok){
		if (_condition->sat(callUnit,triggerUnit,NULL)){
			for(list<SOrdreAction*>::iterator it = this->_actions.begin(); it != this->_actions.end(); it++){
				(*it)->execute(callUnit,triggerUnit,NULL);
			}
		}
	}
}

void SOrdreRule::proces(OrdreEvent::Enum event, SObj* callUnit, SObj* triggerUnit){
	this->proces(event,callUnit,triggerUnit,NULL);
}
void SOrdreRule::proces(OrdreEvent::Enum event, SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid){
	bool evok = false;
	//cerr<<"proces"<<endl;
	for(list<SEvent*>::iterator it = this->_events.begin(); it != this->_events.end(); it++){
		//cerr<<"event "<<event<<" it "<<(*it)<<endl;
		if(event == (*it)->_event)
			evok = true;
	}
	if(evok){
		if (_condition->sat(callUnit,triggerUnit,triggerGrid)){
			for(list<SOrdreAction*>::iterator it = this->_actions.begin(); it != this->_actions.end(); it++){
				(*it)->execute(callUnit,triggerUnit,triggerGrid);
			}
		}
	}
}


SOrdreRule::~SOrdreRule() {
}

