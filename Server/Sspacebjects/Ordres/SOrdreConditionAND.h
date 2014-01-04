/* 
 * File:   SOrdreConditionAND.h
 * Author: karsten
 *
 * Created on 20. februar 2012, 18:34
 */

#ifndef SORDRECONDITIONAND_H
#define	SORDRECONDITIONAND_H
#include "SOrdreCondition.h"
class SOrdreConditionAND  : public SOrdreCondition {
public:
	SOrdreConditionAND(SOrdreCondition* left, SOrdreCondition* right);
	virtual bool sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);
	virtual ~SOrdreConditionAND();
private:
	SOrdreCondition* _left;
	SOrdreCondition* _right;
};

#endif	/* SORDRECONDITIONAND_H */

