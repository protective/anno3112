/* 
 * File:   SOrdreActionMoveTo.h
 * Author: karsten
 *
 * Created on 17. februar 2012, 13:26
 */

#ifndef SORDREACTIONMOVETO_H
#define	SORDREACTIONMOVETO_H
#include "SOrdreAction.h"
class SOrdreActionMoveTo : public SOrdreAction {
public:
	SOrdreActionMoveTo(bool isUnit, uint32_t oindex);
	virtual void execute(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid);
	virtual ~SOrdreActionMoveTo();
private:
	bool _isUnit;
	uint32_t _oindex;
};

#endif	/* SORDREACTIONMOVETO_H */

