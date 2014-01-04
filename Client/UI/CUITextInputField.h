/* 
 * File:   CUITextInputField.h
 * Author: karsten
 *
 * Created on 2. marts 2012, 21:16
 */

#ifndef CUITEXTINPUTFIELD_H
#define	CUITEXTINPUTFIELD_H
#include "CUIFrame.h"
class CUITextInputField  : public CUIFrame {
public:
	CUITextInputField(CUIBaseFrame* parrent,uint32_t x, uint32_t y, uint32_t wight, uint32_t hight);

	virtual void Draw();
	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual void KeyDown(SDL_Event event);
	string getTextField(){return _textField;}
	virtual ~CUITextInputField();
private:
	string _textField;
	uint32_t _pos;
	uint32_t _deltaBlink;
};

#endif	/* CUITEXTINPUTFIELD_H */

