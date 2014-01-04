/* 
 * File:   CUIButton.h
 * Author: karsten
 *
 * Created on 3. august 2011, 16:30
 */

#ifndef CUIBUTTON_H
#define	CUIBUTTON_H

#include "CUIFrame.h"



class CUIButton : public CUIFrame {
public:
	CUIButton(CUIBaseFrame* parrent);
	CUIButton(CUIBaseFrame* parrent,uint32_t x, uint32_t y, uint32_t wight, uint32_t hight);
	void SetX(uint32_t x){this->_x = x;}
	void SetY(uint32_t y){this->_y = y;}
	virtual void Draw();
	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual ~CUIButton();
protected:
	Icontex::Enum _icon;
};

#endif	/* CUIBUTTON_H */

