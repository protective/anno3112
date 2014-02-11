/* 
 * File:   SShipType.h
 * Author: karsten
 *
 * Created on 25. juni 2011, 00:22
 */

#ifndef SSHIPTYPE_H
#define	SSHIPTYPE_H

#include "SUnitType.h"

class SShipType : public SUnitType {
public:
	SShipType(uint32_t id);
	virtual SUnitType* getUnitType(){return this;}
	virtual ~SShipType();
private:

};

#endif	/* SSHIPTYPE_H */

