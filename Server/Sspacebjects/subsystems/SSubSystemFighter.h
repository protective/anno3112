/* 
 * File:   SSubSystemFighter.h
 * Author: karsten
 *
 * Created on 4. februar 2014, 19:57
 */

#ifndef SSUBSYSTEMFIGHTER_H
#define	SSUBSYSTEMFIGHTER_H
#include "SSubSystem.h"
#include "SSubType.h"
#include "SSubTypeFighter.h"
#include "SSubSystemTargetingI.h"
class SSubTypeFighter;
class SFighter;
class SSubSystemFighter : public SSubSystem , public SSubSystemTargetingI  {
public:
	SSubSystemFighter(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem);
	SSubTypeFighter* getTypeFighter(){return this->_type->getSubType()->isFighter();}
	virtual SSubSystemFighter* isFighter(){return this;}
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual void proces(Processor* processor);
	virtual int32_t cooldown(uint16_t index){return 0;}
	virtual int32_t maxcooldown(uint16_t index){return 0;}
	virtual uint32_t getTarget(){return _target;}
	virtual void setTarget(uint32_t target){_target = target;}
	uint32_t getRange(){return 10000000;}//getTypeFighter()->getRange();}
	
	virtual TargetGroup::Enum getTargetGroup(){return this->_targetGroup;}
	virtual void setTargetGroup(TargetGroup::Enum tg){this->_targetGroup = tg;}
	
	virtual uint32_t getAmo(){return _fightersLunchTImer.size();}
	virtual uint32_t getMaxAmo(){return this->getTypeFighter()->getBayCount() *_xItems;}
	virtual void setAmo(uint32_t amo){}
	
	void launchFighter();
	void recoverFighter(OBJID id);
	void signalFighterReturn(uint32_t id);
	void resetLockPower();
	virtual ~SSubSystemFighter();
private:
	map<uint32_t, uint32_t> _fightersLunchTImer;
	map<uint32_t, OBJID> _fightersId;
	map<uint32_t, FighterSignal::Enum> _fightersSignal;
    int32_t _cur;
	uint32_t _charge;
	int32_t _lockingPower;
	uint32_t _target;
};


#endif	/* SSUBSYSTEMFIGHTER_H */

