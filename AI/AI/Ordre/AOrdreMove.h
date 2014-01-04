/* 
 * File:   AOrdreMove.h
 * Author: karsten
 *
 * Created on 20. juni 2012, 18:42
 */

#ifndef AORDREMOVE_H
#define	AORDREMOVE_H

#include "AOrdre.h"
class AOrdreMove : public AOrdre {
public:
	AOrdreMove(AObjGroup* units, CPos moveto);
	virtual void Execute();
	virtual ~AOrdreMove();
private:
	AObjGroup* _units;
	CPos _moveto;
};

#endif	/* AORDREMOVE_H */

