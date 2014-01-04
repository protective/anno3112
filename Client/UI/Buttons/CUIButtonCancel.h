/* 
 * File:   CUIButtonCancel.h
 * Author: karsten
 *
 * Created on 15. marts 2012, 20:50
 */

#ifndef CUIBUTTONCANCEL_H
#define	CUIBUTTONCANCEL_H
#include "../CUIButton.h"
class CUIButtonCancel : public CUIButton {
public:
	CUIButtonCancel(CUIBaseFrame* parrent, uint32_t x, uint32_t y,uint32_t wight, uint32_t hight);
	virtual ~CUIButtonCancel();
private:

};

#endif	/* CUIBUTTONCANCEL_H */

