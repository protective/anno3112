/* 
 * File:   SOrdreConditionUnitEqTo.h
 * Author: karsten
 *
 * Created on 20. februar 2012, 18:28
 */

#ifndef SORDRECONDITIONUNITEQTO_H
#define	SORDRECONDITIONUNITEQTO_H
#include "SOrdreCondition.h"

class SOrdreConditionUnitEqTo : public SOrdreCondition {
public:
	SOrdreConditionUnitEqTo(OrdresConditionUnits::Enum conditionUnit, uint32_t oindexUnit);
	virtual bool sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);
	virtual ~SOrdreConditionUnitEqTo();
private:
	OrdresConditionUnits::Enum _conditionUnit;
	uint32_t _oindexUnit;
};

#endif	/* SORDRECONDITIONUNITEQTO_H */

