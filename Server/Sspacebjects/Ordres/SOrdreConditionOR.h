/* 
 * File:   SOrdreConditionOR.h
 * Author: karsten
 *
 * Created on 20. februar 2012, 18:35
 */

#ifndef SORDRECONDITIONOR_H
#define	SORDRECONDITIONOR_H
#include "SOrdreCondition.h"
class SOrdreConditionOR : public SOrdreCondition  {
public:
	SOrdreConditionOR(SOrdreCondition* left, SOrdreCondition* right);
	virtual bool sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);
	virtual ~SOrdreConditionOR();
private:
	SOrdreCondition* _left;
	SOrdreCondition* _right;

};

#endif	/* SORDRECONDITIONOR_H */

