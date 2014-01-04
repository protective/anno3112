/* 
 * File:   SOrdres.h
 * Author: karsten
 *
 * Created on 8. oktober 2011, 21:05
 */

#ifndef SORDRES_H
#define	SORDRES_H
#include "../SFunctions.h"
#include "Ordres/SOrdreRule.h"
class SObj;
class SGrid;
class SOrdres {
public:
	SOrdres(string name, uint32_t id);
	uint32_t getId(){return this->_id;}
	virtual ~SOrdres();
	list<TargetType::Enum>& getPrimary(){return _primary;}
	list<TargetType::Enum>& getLight(){return _light;}
	list<TargetType::Enum>& getMedium(){return _medium;}
	list<TargetType::Enum>& getHeavy(){return _heavy;}
	list<TargetType::Enum>& getSpecial(){return _special;}
	OrdresTactice::Enum getPrimeOrdre(){return this->_primeOrdre;}
	void setPrimeOrdre(OrdresTactice::Enum value){this->_primeOrdre = value;}

	void addRule(SOrdreRule* rule){this->_rules.push_back(rule);}
	
	void proces(OrdreEvent::Enum event, SObj* callUnit){
		for(list<SOrdreRule*>::iterator it = _rules.begin(); it != _rules.end();it++){
			(*it)->proces(event,callUnit);
		}
	}
	void procesRangeChange(SObj* callUnit, SObj* triggerUnit, uint32_t newrange, uint32_t oldrange){
		for(list<SOrdreRule*>::iterator it = _rules.begin(); it != _rules.end();it++){
			(*it)->procesRangeChange(callUnit,triggerUnit, newrange, oldrange);
		}
	}
	void proces(OrdreEvent::Enum event, SObj* callUnit, SObj* triggerUnit){
		for(list<SOrdreRule*>::iterator it = _rules.begin(); it != _rules.end();it++){
			(*it)->proces(event,callUnit,triggerUnit);
		}
	}
	void proces(OrdreEvent::Enum event, SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid){
		for(list<SOrdreRule*>::iterator it = _rules.begin(); it != _rules.end();it++){
			(*it)->proces(event,callUnit,triggerUnit,triggerGrid);
		}
	}

	map<uint32_t,bool>& getunitSet(){return this->_unitSet;}
	map<uint32_t,bool>& getPosSet(){return this->_PosSet;}

	uint32_t getAutoMoveRange(){return this->_automoveRange;}
	void setAutoMoveRange(uint32_t value){this->_automoveRange = value;}
	string getName(){return this->_name;}
private:
	string _name;
	uint32_t _id;
	list<TargetType::Enum> _primary;
	list<TargetType::Enum> _light;
	list<TargetType::Enum> _medium;
	list<TargetType::Enum> _heavy;
	list<TargetType::Enum> _special;
	OrdresTactice::Enum _primeOrdre;
	list<SOrdreRule*> _rules;
	map<uint32_t,bool> _unitSet;
	map<uint32_t,bool> _PosSet;

	uint32_t _automoveRange;
};

#endif	/* SORDRES_H */

