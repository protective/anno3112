/* 
 * File:   CUIButtonCreateFit.h
 * Author: karsten
 *
 * Created on 2. marts 2012, 23:47
 */

#ifndef CUIBUTTONCREATEFIT_H
#define	CUIBUTTONCREATEFIT_H
#include "../CUIButton.h"
class CUIButtonCreateFit : public CUIButton {
public:
	CUIButtonCreateFit(CUIBaseFrame* parrent, uint32_t x, uint32_t y,uint32_t wight, uint32_t hight);
	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual ~CUIButtonCreateFit();
private:

};

#endif	/* CUIBUTTONCREATEFIT_H */

