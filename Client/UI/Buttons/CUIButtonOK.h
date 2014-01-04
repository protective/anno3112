/* 
 * File:   CUIButtonOK.h
 * Author: karsten
 *
 * Created on 15. marts 2012, 20:04
 */

#ifndef CUIBUTTONOK_H
#define	CUIBUTTONOK_H
#include "../CUIButton.h"
class CUIButtonOK : public CUIButton {
public:
	CUIButtonOK(CUIBaseFrame* parrent, uint32_t x, uint32_t y,uint32_t wight, uint32_t hight);
	virtual ~CUIButtonOK();
private:

};

#endif	/* CUIBUTTONOK_H */

