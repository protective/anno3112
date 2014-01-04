/* 
 * File:   CUIBuildFrame.cpp
 * Author: karsten
 * 
 * Created on 26. oktober 2011, 09:19
 */

#include "CUIBuildFrame.h"
#include "../Buttons/CUIButtonBuild.h"
#include "../CUIButtonFrame.h"
CUIBuildFrame::CUIBuildFrame(CUIBaseFrame* parrent, CCargoBay* cargo):
CUIFrame(parrent){
	_UIlevel = 3;
	_cargo = cargo;
	this->_x = 10;
	this->_y = 10;
	this->_wight = 300;
	this->_hight = 200;
	this->_buildList = new CUIButtonFrame(this,0,0,300,150);
	this->_matList = new CUIListBox(this,0,100,200,12);
	this->add(*_buildList);
	//this->add(*_matList);
}

void CUIBuildFrame::addCanBuild(CSubSystemFac* fac, CItemType* item){
	this->_buildList->AddButton(*(new CUIButtonBuild(this->_buildList,fac,item)));
}

void CUIBuildFrame::Draw(){
	_matList->clearall();

	if(hoverFrame){
		if (hoverFrame->getFrameItemTypeRep()){
		    CItemType* itemType = hoverFrame->getFrameItemTypeRep();
		    this->_matList->setHight(itemType->getCost().size()*12);
		    this->_matList->setX(hoverFrame->getX());
		    this->_matList->setY(hoverFrame->getY()+hoverFrame->getHight());
			
			uint32_t i = 0;
			for (map<uint32_t,bmaterial>::iterator it = itemType->getCost().begin(); it != itemType->getCost().end(); it++){
				uint32_t have = 0;
				if (it->second._item){
					have = this->_cargo->GetReturn(it->second._item,0-1);
					stringstream s;
					s<<it->second._item->getName()<<" "<<it->second._quan<<"/"<<have;
					_matList->getStrings()[i][0] = s.str();
					if(have>= it->second._quan)
						_matList->getFlag()[i][0] = 1;
					else
						_matList->getFlag()[i][0] = 0;
					
				}
				i++;
			}
		}
	}
	

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		(*it)->Draw();
	}
	_matList->Draw();

}

void CUIBuildFrame::Click(SDL_Event event,int32_t x, int32_t y){
	cerr<<"click BuildFrame "<<x<<" "<<y<<endl;
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->Click(event,x-(*it)->getX(),y-(*it)->getY());
	}


}


void CUIBuildFrame::Move(SDL_Event event,int32_t x, int32_t y){
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->Move(event,x-(*it)->getX(),y-(*it)->getY());
	}
}

CUIBuildFrame::~CUIBuildFrame() {
	if(_buildList)
		delete _buildList; //TODO do not work yet
}

