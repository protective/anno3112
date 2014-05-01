/* 
 * File:   SSingleWep.h
 * Author: karsten
 *
 * Created on 1. juli 2011, 21:26
 */

#ifndef SSINGLEWEP_H
#define	SSINGLEWEP_H
#include "../../SFunctions.h"
#include "../../Commands/Processor.h"
class SSubSystemW;
class SSingleWep {
public:
	SSingleWep(SSubSystemW* subsys);
	void proces(Processor* processor);
	//bool InAngle(int32_t angle, FireDir::Enum fd);
	int32_t getDuration(){return _cur;}
	void resetLockPower(){_lockingPower = 0;}
	uint32_t getLockPower(){return _lockingPower;}
	virtual ~SSingleWep();
private:
	SSubSystemW* subsys;
	int32_t _cur;
	list<uint32_t> _tempseq;
	int32_t _charge;
	uint32_t _lockingPower;
};
typedef map<uint32_t,SSingleWep*>::iterator SSingleWI;
#endif	/* SSINGLEWEP_H */

