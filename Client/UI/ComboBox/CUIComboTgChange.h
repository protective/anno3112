/* 
 * File:   CUIComboTgChange.h
 * Author: karsten
 *
 * Created on 17. oktober 2011, 08:22
 */

#ifndef CUICOMBOTGCHANGE_H
#define	CUICOMBOTGCHANGE_H
#include "../CUIComboBox.h"
class CUIComboTgChange : public CUIComboBox {
public:
	CUIComboTgChange(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight);
	virtual void Draw();
	virtual ~CUIComboTgChange();
private:

};

#endif	/* CUICOMBOTGCHANGE_H */

