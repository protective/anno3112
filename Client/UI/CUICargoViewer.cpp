/* 
 * File:   CUICargoViewer.cpp
 * Author: karsten
 * 
 * Created on 20. september 2011, 20:44
 */

#include "CUICargoViewer.h"
#include "Buttons/CUIButtonItem.h"
#include "RightClickMenus/CUIRCMenuLoadout.h"

CUICargoViewer::CUICargoViewer(CUIBaseFrame* parrent, uint32_t x,uint32_t y,uint32_t wight,uint32_t hight, CCargoBay* cargobay):
CUIButtonFrame(parrent,x,y,wight,hight,0,2){
	this->_cargobay = cargobay;
	this->_cargobay->setChange();
	this->_MCbar = new CUIMoveCloseBar(this);
	this->add(*this->_MCbar);
	//_vscroll =  new CUIVScroll(this,0,5,1,_wight-15,this->_MCbar->getHight()+2,15,hight-(this->_MCbar->getHight()+2));
	_vscroll = NULL;
	//map<CItemType*,uint32_t>::iterator it;
	//for (it = cargobay->getContent().begin();it != cargobay->getContent().end();it++){
	//	this->AddButton(*(new CUIButtonItem(this,0,0,40,40,it->first,it->second)));
	//}
}
void CUICargoViewer::setCanberemoved(bool b){
	this->_canBeRemoved = b;
	mainFrame->getOpenCargoList().remove(this->_cargobay);
}
void CUICargoViewer::Draw(){
	if (this->_cargobay->getChange()){
		this->updateButtons();
		this->_cargobay->resetChange();
	}

	Drawbox(this->getX(),this->getY(),this->getWight(),this->getHight(),0,0.5,0.1,1);

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		(*it)->Draw();
	}
	uint32_t mcbarh = 0;
	if(_MCbar)
		mcbarh = _MCbar->getHight();
	Drawbox(this->getX(),this->getY()+mcbarh,this->getWight(),2,0.1,0.1,0.1,1);
	if(_cargobay->getmaxCargo())
		Drawbox(this->getX(),this->getY()+mcbarh,(this->getWight() * _cargobay->getcurCargo()) /_cargobay->getmaxCargo(),2,1,1,1,1);

	if(_vscroll)
		_vscroll->Draw(this->getX(),this->getY());
}


void CUICargoViewer::Click(SDL_Event event, int32_t x, int32_t y){
	

	if(_MCbar && y < _MCbar->getHight()){
		_MCbar->Click(event,x,y - _MCbar->getHight());
	}else{
		uint32_t qx = floor(_wight/_spreadX);
		for (map<uint32_t, CUIButton*>::iterator it = this->_buttons.begin(); it != this->_buttons.end(); it++){
			if (x >= it->second->getX() && x <= it->second->getX() +it->second->getWight() && y >=  it->second->getY() && y <= it->second->getY()+it->second->getHight())
				it->second->Click(event,x- it->second->getX() ,y- it->second->getY());
		}
	}
	if(event.button.button == SDL_BUTTON_RIGHT){
		mainFrame->add(*new CUIRCMenuLoadout(mainFrame,event.button.x-10,event.button.y-10,20+(20*globalLoadout.size()), _cargobay));
	}else
		this->_toBeDrawnFront = true;
	if(_vscroll && x >= _vscroll->getX() && x <= _vscroll->getX() +_vscroll->getWight() &&  y >= _vscroll->getY() && y <= _vscroll->getY() +_vscroll->getHight()){
		uint32_t t = _vscroll->getValue();
		_vscroll->Click(event, x- _vscroll->getX(), y- _vscroll->getY());
		if(t != _vscroll->getValue()){
			updateButtonsPos();

		}
	}
}

void CUICargoViewer::updateScrolls(){
	uint32_t vscrollmax = ceil((double)_buttons.size()/getElementX())-getElementY();

	if(_vscroll){
		_vscroll->setMax(vscrollmax);
		if(this->_buttons.size() <= getElementX()*getElementY()){
			delete _vscroll;
			_vscroll = NULL;
		}
	}else{
		if(this->_buttons.size() > getElementX()*getElementY() ){
			if(_MCbar){
				_vscroll = new CUIVScroll(this,0,vscrollmax,1,_wight-15,this->_MCbar->getHight()+2,15,_hight-(this->_MCbar->getHight()+2));
			}else{
				_vscroll = new CUIVScroll(this,0,vscrollmax,1,_wight-15,0,15,_hight);
			}
		}
	}
}

void CUICargoViewer::OnDrop(CUIButtonItem* frame){
	if(!frame->getSlot())
		playerObj->ServerRequsetTransfere(frame->getCargoBay()->getOwner(),this->_cargobay->getOwner(),frame->getItem(),frame->getQuan());
	else
		playerObj->ServerRequsetUnFit(frame->getSlot(), this->_cargobay, frame->getQuan());
	
}



void CUICargoViewer::updateButtons(){

	map<CItemType*,uint32_t>::iterator it;
	map<uint32_t, CUIButton*>::iterator it2;
	bool sus = false;
	for (it = _cargobay->getContent().begin();it != _cargobay->getContent().end();it++){
		sus = false;
		for (it2 = this->_buttons.begin(); it2 != this->_buttons.end();it2++){
			if(it->first == ((CUIButtonItem*)it2->second)->getItem()){
				if(it->second){
					((CUIButtonItem*)it2->second)->updateQuan(it->second);
					
				}else{
					((CUIButtonItem*)it2->second)->setCanberemoved(true);
					this->RemoveButton(it2->first);
				
				}
				sus = true;
				break;
			}
		}
		if(!sus && it->second)
			this->AddButton(*(new CUIButtonItem(this,0,0,40,40,_cargobay,it->first,it->second)));
	}


	updateButtonsPos();
}


CUICargoViewer::~CUICargoViewer() {
}

