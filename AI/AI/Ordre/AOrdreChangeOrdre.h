/* 
 * File:   AOrdreChangeOrdre.h
 * Author: karsten
 *
 * Created on 25. juli 2012, 15:37
 */

#ifndef AORDRECHANGEORDRE_H
#define	AORDRECHANGEORDRE_H
#include "AOrdre.h"
class AOrdreChangeOrdre : public AOrdre {
public:
	AOrdreChangeOrdre(AObjGroup* units, uint32_t ordreIndex);
	virtual void Execute();
	virtual ~AOrdreChangeOrdre();
private:
	AObjGroup* _units;
	uint32_t _ordreIndex;
};

#endif	/* AORDRECHANGEORDRE_H */

