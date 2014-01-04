/* 
 * File:   SOrdreCondition.h
 * Author: karsten
 *
 * Created on 17. februar 2012, 13:09
 */

#ifndef SORDRECONDITION_H
#define	SORDRECONDITION_H
#include "../../SFunctions.h"
#include "SOrdreRule.h"
class SOrdreCondition {
public:
	SOrdreCondition();
	virtual bool sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid){}
	virtual ~SOrdreCondition();
private:

};

#endif	/* SORDRECONDITION_H */

