/* 
 * File:   CUIComboBox.h
 * Author: karsten
 *
 * Created on 9. oktober 2011, 10:12
 */

#ifndef CUICOMBOBOX_H
#define	CUICOMBOBOX_H

#include "CUIFrame.h"
#include "CUIButton.h"

class CUIComboBox : public CUIFrame {
public:
	CUIComboBox(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight);
	void AddButton(CUIButton& button);
	void AddButton(CUIButton& button, uint32_t pos);
	void RemoveButton(uint32_t pos);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual ~CUIComboBox();
protected:
	map<uint32_t, CUIButton*> _buttons;
	bool _active;
		uint32_t _spreadY;
};

#endif	/* CUICOMBOBOX_H */

