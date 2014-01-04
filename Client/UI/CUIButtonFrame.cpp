/* 
 * File:   CUIButtonFrame.cpp
 * Author: karsten
 * 
 * Created on 18. september 2011, 15:51
 */

#include "CUIButtonFrame.h"

CUIButtonFrame::CUIButtonFrame(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight) :
CUIFrame(parrent){
	_UIlevel = 3;
	this->_x = x;
	this->_y = y;
	this->_wight = wight;
	this->_hight = hight;
	this->_spreadX = 45;
	this->_spreadY = 45;
	this->_ajustX = 0;
	this->_ajustY = 0;
	_vscroll =  NULL;
	_MCbar = NULL;

}

CUIButtonFrame::CUIButtonFrame(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight, int32_t ajustX, int32_t ajustY) :
CUIFrame(parrent){
	_UIlevel = 3;
	this->_x = x;
	this->_y = y;
	this->_wight = wight;
	this->_hight = hight;
	this->_spreadX = 45;
	this->_spreadY = 45;
	this->_ajustX = ajustX;
	this->_ajustY = ajustY;
	_vscroll =  NULL;
	_MCbar = NULL;
}	


void CUIButtonFrame::Move(SDL_Event event,int32_t x, int32_t y){

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->Move(event,x-(*it)->getX(),y-(*it)->getY());
	}
}

void CUIButtonFrame::Draw(){

	Drawbox(this->getX() + _parrent->getX() ,this->getY() + _parrent->getY(),this->getWight(),this->getHight(),0,1,0.1,1);
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		(*it)->Draw(this->getX() + _parrent->getX(),this->getY() + _parrent->getY());
	}

	if(_vscroll)
		_vscroll->Draw(this->getX() + _parrent->getX(),this->getY() + _parrent->getY());

}

void CUIButtonFrame::Click(SDL_Event event, int32_t x, int32_t y){
	cerr<<"click CUIButtonFrame "<<x<<" "<<y<<endl;
	cerr<<"x "<<x<<" y "<<y<<endl;
	this->_toBeDrawnFront = true;
	
	if(_MCbar && y < _MCbar->getHight()){
		cerr<<"click mc"<<endl;
		_MCbar->Click(event,x,y - _MCbar->getHight());
	}else{
		uint32_t qx = floor(_wight/_spreadX);
		for (map<uint32_t, CUIButton*>::iterator it = this->_buttons.begin(); it != this->_buttons.end(); it++){
			if (x >= it->second->getX() && x <= it->second->getX() +it->second->getWight() && y >=  it->second->getY() && y <= it->second->getY()+it->second->getHight())
				it->second->Click(event,x- it->second->getX() ,y- it->second->getY());
		}
		
		if(_vscroll && x >= _vscroll->getX() && x <= _vscroll->getX() +_vscroll->getWight() &&  y >= _vscroll->getY() && y <= _vscroll->getY() +_vscroll->getHight()){
			uint32_t t = _vscroll->getValue();
			_vscroll->Click(event, x- _vscroll->getX(), y- _vscroll->getY());
			if(t != _vscroll->getValue()){
				updateButtonsPos();
				cerr<<"update"<<endl;
			}
		}
	}
	cerr<<"done click ButtonFrame"<<endl;
}

void CUIButtonFrame::updateScrolls(){
	uint32_t vscrollmax = ceil((double)_buttons.size()/getElementX())-getElementY();

	if(_vscroll){
		_vscroll->setMax(vscrollmax);
		if(this->_buttons.size() <= getElementX()*getElementY()){
			delete _vscroll;
			_vscroll = NULL;
		}
	}else{
		if(this->_buttons.size() > getElementX()*getElementY() ){
			_vscroll = new CUIVScroll(this,0,vscrollmax,1,_wight-15,0,15,_hight);
			
		}
	}
}
void CUIButtonFrame::updateButtonsPos(){

	this->updateScrolls();


uint32_t exray = 0;
uint32_t vvalue = 0;
	if(_vscroll){
		vvalue = _vscroll->getValue();
	}
	if(this->getMCbar()){
		exray = this->getMCbar()->getHight();
	}
	for(map<uint32_t,CUIButton*>::iterator it = _buttons.begin(); it != _buttons.end(); it++){
		this->remove(*it->second);
	}
	uint32_t i = 0;
	for(map<uint32_t,CUIButton*>::iterator it = _buttons.begin(); it != _buttons.end(); ){
		if(it->first != i){
			_buttons[i] = it->second;
			_buttons.erase(it++);
			
		}else
			it++;
		i++;
	}

	for(map<uint32_t,CUIButton*>::iterator it = _buttons.begin(); it != _buttons.end(); it++){
		uint32_t qx = floor(_wight/_spreadX);
		if(floor(it->first/qx) >= vvalue && floor(it->first/qx) < vvalue + floor((_hight- exray - _ajustY)/_spreadY)){
			this->add(*it->second);
		}
		
		it->second->SetX(((it->first%qx)*_spreadX)+ _ajustX);
		it->second->SetY(exray+ _ajustY -(_spreadY*vvalue)+(floor((it->first/qx)*_spreadY)));
	}
}

void CUIButtonFrame::AddButton(CUIButton& button, uint32_t pos){
	uint32_t exray = 0;
	if(this->getMCbar()){
		exray = this->getMCbar()->getHight();
	}
	while (true){
		if (this->_buttons.find(pos) == this->_buttons.end()){
			this->_buttons[pos] = &button;

			this->updateButtonsPos();
			break;
		}else{
			pos+=1;
		}
	}
}
void CUIButtonFrame::AddButton(CUIButton& button){
	uint32_t pos = 0;
	while (true){
		if (this->_buttons.find(pos) == this->_buttons.end()){
			this->AddButton(button, pos);
			break;
		}else{
			pos+=1;
		}
	}
}

void CUIButtonFrame::RemoveButton(uint32_t pos){
	if(hoverFrame == this->_buttons[pos])
		hoverFrame = NULL;
	delete this->_buttons[pos];
	this->remove(*this->_buttons[pos]);
	this->_buttons.erase(pos);
}

CUIButtonFrame::~CUIButtonFrame() {
}

