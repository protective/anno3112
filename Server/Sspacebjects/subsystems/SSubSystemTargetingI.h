/* 
 * File:   SSubSystemTargetingI.h
 * Author: karsten
 *
 * Created on 16. august 2014, 14:04
 */

#ifndef SSUBSYSTEMTARGETINGI_H
#define	SSUBSYSTEMTARGETINGI_H

class SSubSystemTargetingI{
public:
	virtual uint32_t getTarget() = 0;
	virtual void setTarget(uint32_t target) = 0;
	virtual TargetGroup::Enum getTargetGroup() = 0;
	virtual void setTargetGroup(TargetGroup::Enum tg) = 0;
	virtual uint32_t getRange() = 0;
	virtual void resetLockPower() = 0;
};


#endif	/* SSUBSYSTEMTARGETINGI_H */

