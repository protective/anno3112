/* 
 * File:   CUIButtonOK.cpp
 * Author: karsten
 * 
 * Created on 15. marts 2012, 20:04
 */

#include "CUIButtonOK.h"

CUIButtonOK::CUIButtonOK(CUIBaseFrame* parrent, uint32_t x, uint32_t y,uint32_t wight, uint32_t hight):
CUIButton(parrent,x,y,wight,hight){
_icon = Icontex::ok;
}



CUIButtonOK::~CUIButtonOK() {
}

