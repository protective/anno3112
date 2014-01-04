/* 
 * File:   CUIButtonOpenCargo.h
 * Author: karsten
 *
 * Created on 1. oktober 2011, 21:08
 */

#ifndef CUIBUTTONOPENCARGO_H
#define	CUIBUTTONOPENCARGO_H
#include "../CUIButton.h"
class CUIButtonOpenCargo : public CUIButton {
public:
	CUIButtonOpenCargo(CUIBaseFrame* parrent, uint32_t x, uint32_t y,uint32_t wight, uint32_t hight);

	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual ~CUIButtonOpenCargo();
private:

};

#endif	/* CUIBUTTONOPENCARGO_H */

