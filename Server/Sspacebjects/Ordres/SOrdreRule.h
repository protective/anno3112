/* 
 * File:   SOrdreRule.h
 * Author: karsten
 *
 * Created on 2. januar 2012, 16:30
 */

#ifndef SORDRERULE_H
#define	SORDRERULE_H
#include "../../SFunctions.h"
#include "SOrdreAction.h"
class SObj;
class SGrid;
class SOrdreCondition;
struct SEvent{
	SEvent(OrdreEvent::Enum event, uint32_t value){
		_event = event;
		_value = value;
	}
	OrdreEvent::Enum _event;
	uint32_t _value;
};

class SOrdreRule {
public:
	SOrdreRule();
	
	void proces(OrdreEvent::Enum event, SObj* callUnit);

	void procesRangeChange(SObj* callUnit, SObj* triggerUnit, uint32_t newrange, uint32_t oldrange);

	void proces(OrdreEvent::Enum event, SObj* callUnit, SObj* triggerUnit);
	void proces(OrdreEvent::Enum event, SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);

	void addAction(SOrdreAction* action){this->_actions.push_back(action);}
	void addEvent(OrdreEvent::Enum event){this->_events.push_back(new SEvent(event,0));}
	void addCondition(SOrdreCondition* condi){_condition = condi;}
	void addEvent(OrdreEvent::Enum event, uint32_t value){this->_events.push_back(new SEvent(event,value));}
	virtual ~SOrdreRule();
private:
	list<SEvent*> _events;
	SOrdreCondition* _condition;
	list<SOrdreAction*> _actions;
};

#endif	/* SORDRERULE_H */

