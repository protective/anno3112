/* 
 * File:   CUIVScroll.cpp
 * Author: karsten
 * 
 * Created on 22. marts 2012, 20:32
 */

#include "CUIVScroll.h"

CUIVScroll::CUIVScroll(CUIBaseFrame* parrent, uint32_t min, uint32_t max, uint32_t step, uint32_t x, uint32_t y, uint32_t wight, uint32_t hight):
CUIBaseFrame(parrent){
	_min = min;
	_max = max;
	_step = step;
	_x = x;
	_y = y;
	_wight = wight;
	_hight = hight;

	_value = min;
}




void CUIVScroll::Draw(int32_t x, int32_t y){
	Drawbox(this->getX()+ x, this->getY() + y ,this->getWight(),this->getHight(),1,1,1,1);

}


void CUIVScroll::Click(SDL_Event event, int32_t x, int32_t y){
	cerr<<"click VSCROOL"<<endl;
	if(y < 20){
		cerr<<"--"<<_value<<endl;
		if(_min + _step <= _value  )
			_value -= _step;
	}
	if(y > _hight - 20){
		cerr<<"++"<<_value<<endl;
		if(_max >= _value + _step )
			_value += _step;
	}
	cerr<<"_value"<<_value<<endl;
}


CUIVScroll::~CUIVScroll() {
}

