/* 
 * File:   CUIRightClickMenu.h
 * Author: karsten
 *
 * Created on 1. marts 2012, 21:21
 */

#ifndef CUIRIGHTCLICKMENU_H
#define	CUIRIGHTCLICKMENU_H

#include "CUIButtonFrame.h"
class CUIRightClickMenu  : public CUIButtonFrame {
public:
	CUIRightClickMenu(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual ~CUIRightClickMenu();
private:
	bool _mouseOk;
};

#endif	/* CUIRIGHTCLICKMENU_H */

