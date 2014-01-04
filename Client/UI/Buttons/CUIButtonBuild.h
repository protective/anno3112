/* 
 * File:   CUIButtonBuild.h
 * Author: karsten
 *
 * Created on 20. september 2011, 10:36
 */

#ifndef CUIBUTTONBUILD_H
#define	CUIBUTTONBUILD_H

#include "../CUIButton.h"
#include "../../Items/CItemType.h"

class CUIButtonBuild : public CUIButton {
public:
	CUIButtonBuild(CUIBaseFrame* parrent,CSubSystemFac* fac,CItemType* item);
	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual void Move(SDL_Event event,int32_t x, int32_t y);
	virtual string getHoverMsg(){if(_item)return _item->getName();else return "";}
	virtual void Draw(int32_t x, int32_t y);
	virtual CItemType* getFrameItemTypeRep(){return _item;}

	virtual ~CUIButtonBuild();
private:
CSubSystemFac* _fac;
CItemType* _item;
};

#endif	/* CUIBUTTONBUILD_H */

