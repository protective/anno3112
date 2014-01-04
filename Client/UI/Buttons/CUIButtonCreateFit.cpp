/* 
 * File:   CUIButtonCreateFit.cpp
 * Author: karsten
 * 
 * Created on 2. marts 2012, 23:47
 */

#include "CUIButtonCreateFit.h"
#include "../Forms/CUICreateFitForm.h"
#include "../CUIMainFrame.h"
#include "../../spaceobjects/CSubAble.h"
CUIButtonCreateFit::CUIButtonCreateFit(CUIBaseFrame* parrent, uint32_t x, uint32_t y,uint32_t wight, uint32_t hight) :
CUIButton(parrent,x,y,wight,hight){
	_icon = Icontex::CreateLoadOut;
}

void CUIButtonCreateFit::Click(SDL_Event event,int32_t x, int32_t y){
	if(mainFrame->shipDetail()->getCreateFitForm()){
		mainFrame->shipDetail()->getCreateFitForm()->setCanberemoved(true);
	}

	CUICreateFitForm* temp = new CUICreateFitForm(mainFrame,135,100);
	mainFrame->add(*temp);
	mainFrame->shipDetail()->setCreateFitForm(temp);

}


CUIButtonCreateFit::~CUIButtonCreateFit() {
}

