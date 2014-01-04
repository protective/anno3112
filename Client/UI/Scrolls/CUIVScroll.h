/* 
 * File:   CUIVScroll.h
 * Author: karsten
 *
 * Created on 22. marts 2012, 20:32
 */

#ifndef CUIVSCROLL_H
#define	CUIVSCROLL_H
#include "../CUIBaseFrame.h"
class CUIVScroll : public CUIBaseFrame {
public:
	CUIVScroll(CUIBaseFrame* parrent, uint32_t min, uint32_t max, uint32_t step, uint32_t x, uint32_t y, uint32_t wight, uint32_t hight);
	virtual void Draw(int32_t x, int32_t y);
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	uint32_t getValue() {return _value;}
	void setMin(uint32_t min){_min = min;}
	void setMax(uint32_t max){_max = max;}

	virtual ~CUIVScroll();
private:
uint32_t _min;
uint32_t _max;
uint32_t _step;
uint32_t _value;
};

#endif	/* CUIVSCROLL_H */

