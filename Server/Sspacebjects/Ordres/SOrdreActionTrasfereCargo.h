/* 
 * File:   SOrdreActionTrasfereCargo.h
 * Author: karsten
 *
 * Created on 21. februar 2012, 20:07
 */

#ifndef SORDREACTIONTRASFERECARGO_H
#define	SORDREACTIONTRASFERECARGO_H
#include "SOrdreAction.h"
class SOrdreActionTrasfereCargo : public SOrdreAction {
public:
	SOrdreActionTrasfereCargo(uint32_t transfereTo_oindex);
	virtual void execute(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);
	virtual ~SOrdreActionTrasfereCargo();
private:
	uint32_t _oindex;
};

#endif	/* SORDREACTIONTRASFERECARGO_H */

