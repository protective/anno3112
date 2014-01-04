/* 
 * File:   CTargetable.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:32
 */

#ifndef CTARGETABLE_H
#define	CTARGETABLE_H
#include "CObj.h"
class CTargetable {
public:
	CTargetable(CObj* obj);
	CObj* obj(){return this->_obj;}
	void setPrio(uint8_t prio){this->_prio = prio;}
	uint8_t getPrio(){return this->_prio;}
	virtual ~CTargetable();
protected:
	uint8_t _prio;
private:
	CObj* _obj;
};

#endif	/* CTARGETABLE_H */

