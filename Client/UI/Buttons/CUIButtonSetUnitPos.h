/* 
 * File:   CUIButtonSetUnitPos.h
 * Author: karsten
 *
 * Created on 27. februar 2012, 08:35
 */

#ifndef CUIBUTTONSETUNITPOS_H
#define	CUIBUTTONSETUNITPOS_H
#include "../CUIButton.h"
class CUIButtonSetUnitPos : public CUIButton{
public:
	CUIButtonSetUnitPos(CUIBaseFrame* parrent, int32_t setUnit, int32_t setPos);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual ~CUIButtonSetUnitPos();
private:
	int32_t _setUnit;
	int32_t _setPos;
};

#endif	/* CUIBUTTONSETUNITPOS_H */

