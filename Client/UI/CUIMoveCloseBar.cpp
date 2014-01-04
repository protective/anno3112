/* 
 * File:   CUIMoveCloseBar.cpp
 * Author: karsten
 * 
 * Created on 22. september 2011, 11:29
 */

#include "CUIMoveCloseBar.h"

CUIMoveCloseBar::CUIMoveCloseBar(CUIBaseFrame* parrent):
CUIBaseFrame(parrent){
	this->_hight = 12;
	this->_wight = parrent->getWight();
	this->_x = 0;
	this->_y = 0;
	
}

void CUIMoveCloseBar::Click(SDL_Event event, int32_t x, int32_t y){
	cerr<<"select"<<endl;
	if (x < this->_wight-15)
		selectedFrame = _parrent;
	else{

		_parrent->setCanberemoved(true) ;
		cerr<<"ok remove"<<endl;
	}
}

void CUIMoveCloseBar::Draw(){

	Drawbox(_parrent->getX(),_parrent->getY(),this->getWight(),this->getHight(),0.7,0.8,0.1,1);
}

CUIMoveCloseBar::~CUIMoveCloseBar() {
}

