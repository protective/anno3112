/* 
 * File:   CShot.h
 * Author: karsten
 *
 * Created on 2. juli 2011, 14:37
 */

#ifndef CSHOT_H
#define	CSHOT_H

#include "CTargetable.h"
#include "CMovable.h"
#include "CObj.h"
#include "../Grafic/CPartical.h"
#include "../UI/CUIBaseFrame.h"
class CShot : public CObj , public CMovable , public CUIBaseFrame{
public:
	CShot(uint32_t id, uint32_t playerId, CPos& pos, CPos& target, uint32_t texId, uint32_t speed);
	virtual void Draw();
	virtual void Move(uint32_t deltaT);
	virtual void Proces(uint32_t DTime);
	virtual void setFlightTime(uint32_t value){this->_flightTime = value;}
	virtual void setMaxFlightTime(uint32_t value){this->_maxFlightTime = value;}
	virtual void setTracking(uint32_t value){this->_tracking = value;}
	virtual void setTrackingTime(uint32_t value){this->_trackingTime = value;}
	void finishMe();
	virtual void setTarget(CTargetable* value){
		this->_target = value;
	}
	virtual void announceRemovalOf(CObj* obj){if(this->_target){
													if(this->_target->obj() == obj)
														this->_target = NULL;
											}
	}

	virtual CShot* isShot(){return this;}
	virtual bool canBeRemoved();
	virtual ~CShot();
private:
	uint32_t _texId;
	CTargetable* _target;
	uint32_t _tracking;
	uint32_t _trackingTime;
	uint32_t _flightTime;
	uint32_t _maxFlightTime;
	uint32_t _movedis;
	uint32_t _finalmovedis;
	uint32_t _length;
	bool _ending;
};

typedef map<uint32_t,CShot*>::iterator CShotI;


#endif	/* CSHOT_H */

