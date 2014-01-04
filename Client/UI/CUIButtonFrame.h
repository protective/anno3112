/* 
 * File:   CUIButtonFrame.h
 * Author: karsten
 *
 * Created on 18. september 2011, 15:51
 */

#ifndef CUIBUTTONFRAME_H
#define	CUIBUTTONFRAME_H

#include "CUIFrame.h"
#include "CUIButton.h"

#include "Scrolls/CUIVScroll.h"
class CUIButtonFrame : public CUIFrame {
public:
	CUIButtonFrame(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight);
	CUIButtonFrame(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight, int32_t ajustX, int32_t ajustY);
	void AddButton(CUIButton& button, uint32_t pos);
	void AddButton(CUIButton& button);
	virtual void updateButtonsPos();
	virtual void updateScrolls();
	void RemoveButton(uint32_t pos);
	virtual void Move(SDL_Event event,int32_t x, int32_t y);
	virtual uint32_t getElementX(){return floor(_wight/_spreadX);}
	virtual uint32_t getElementY(){	if(this->getMCbar())
		return floor((_hight- this->getMCbar()->getHight() - _ajustY)/_spreadY);
	else
		return floor((_hight - _ajustY)/_spreadY);
	}
	virtual void Draw();
	
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual ~CUIButtonFrame();
protected:
	map<uint32_t, CUIButton*> _buttons;

	uint32_t _spreadX;
	uint32_t _spreadY;
	int32_t _ajustX;
	int32_t _ajustY;
	CUIVScroll* _vscroll;
};

#endif	/* CUIBUTTONFRAME_H */

