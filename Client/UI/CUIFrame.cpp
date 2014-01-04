/* 
 * File:   CUIFrame.cpp
 * Author: karsten
 * 
 * Created on 20. juli 2011, 18:35
 */

#include "CUIFrame.h"

CUIFrame::CUIFrame(CUIBaseFrame* parrent) :
CUIBaseFrame(parrent){
	this->_MCbar = NULL;
}

void CUIFrame::Draw(){
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		(*it)->Draw();
	}
}

CUIFrame::~CUIFrame() {
}

