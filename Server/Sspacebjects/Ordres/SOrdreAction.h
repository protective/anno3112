/* 
 * File:   SOrdreAction.h
 * Author: karsten
 *
 * Created on 17. februar 2012, 13:09
 */

#ifndef SORDREACTION_H
#define	SORDREACTION_H
#include "../../SFunctions.h"
class SObj;
class SGrid;
class SOrdreAction  {
public:
	SOrdreAction();
	virtual void execute(SObj* callUnit);
	virtual void execute(SObj* callUnit, SObj* triggerUnit);
	virtual void execute(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);
	virtual ~SOrdreAction();
private:

};

#endif	/* SORDREACTION_H */

