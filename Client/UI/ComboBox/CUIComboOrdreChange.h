/* 
 * File:   CUIComboOrdreChange.h
 * Author: karsten
 *
 * Created on 14. januar 2012, 00:40
 */

#ifndef CUICOMBOORDRECHANGE_H
#define	CUICOMBOORDRECHANGE_H
#include "../CUIComboBox.h"

class CUIComboOrdreChange : public CUIComboBox{
public:
	CUIComboOrdreChange(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight);
	virtual void Draw();
	void Click(SDL_Event event, int32_t x, int32_t y);
	virtual ~CUIComboOrdreChange();
private:

};

#endif	/* CUICOMBOORDRECHANGE_H */

