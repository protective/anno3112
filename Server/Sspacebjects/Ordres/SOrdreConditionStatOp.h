/* 
 * File:   SOrdreConditionStatOp.h
 * Author: karsten
 *
 * Created on 20. februar 2012, 18:29
 */

#ifndef SORDRECONDITIONSTATOP_H
#define	SORDRECONDITIONSTATOP_H
#include "SOrdreCondition.h"
class SOrdreConditionStatOp : public SOrdreCondition{
public:
	SOrdreConditionStatOp(OrdreConditionsStat::Enum conditionstat, int32_t value);
	virtual bool sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);
	virtual ~SOrdreConditionStatOp();
private:
	OrdreConditionsStat::Enum _conditionstat;
	int32_t _value;
};

#endif	/* SORDRECONDITIONSTATOP_H */

