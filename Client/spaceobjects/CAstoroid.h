/* 
 * File:   CAstoroid.h
 * Author: karsten
 *
 * Created on 21. oktober 2011, 19:14
 */

#ifndef CASTOROID_H
#define	CASTOROID_H
#include "CObj.h"
#include "CSubAble.h"
#include "../UI/CUIBaseFrame.h"
#include "CAstoroidType.h"
class CAstoroid : public CObj, public CTargetable , public CUIBaseFrame  {
public:
	CAstoroid(uint32_t id,uint32_t playerId, CPos& pos, CAstoroidType& atype);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual int32_t getX(){return 0;}
	virtual int32_t getY(){return 0;}
	virtual int32_t getWight(){return 30000;}
	virtual int32_t getHight(){return 30000;}
	virtual uint32_t getSize(){return this->_astoroidtype->getSize();}
	virtual CAstoroid* isAstoroid(){return this;}
	void setToBeRemoved(bool b){this->_toBeRemoved = b;}
	bool getToBeRemoved(){return this->_toBeRemoved;}
	virtual CAstoroidType* getAstoroidType(){return _astoroidtype;}
	virtual bool canBeRemoved();
	virtual ~CAstoroid();
private:
	bool _toBeRemoved;
	CAstoroidType* _astoroidtype;
};

#endif	/* CASTOROID_H */

