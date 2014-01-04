/* 
 * File:   CUIBaseFrame.cpp
 * Author: karsten
 * 
 * Created on 20. juli 2011, 20:10
 */

#include "CUIBaseFrame.h"
#include "CUIMainFrame.h"

CUIBaseFrame::CUIBaseFrame(CUIBaseFrame* parrent) {
	_parrent = parrent;
	_UIlevel = 1;
	_canBeRemoved = false;
	_toBeDrawnFront = false;
}

void CUIBaseFrame::Move(SDL_Event event,int32_t x, int32_t y){
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->Move(event,x-(*it)->getX(),y-(*it)->getY());
	}
}

void CUIBaseFrame::KeyDown(SDL_Event event){
	cerr<<"wtf"<<endl;
	/*for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		cerr<<"keydown"<<endl;
		if((*it))
			(*it)->KeyDown(event);
		cerr<<"donekeydown"<<endl;
	}
	*/
}

void CUIBaseFrame::Click(SDL_Event event, int32_t x, int32_t y){
	//cerr<<"click Baseframe"<<endl;
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){

	}
}
void CUIBaseFrame::MouseUp(SDL_Event event,int32_t x, int32_t y){

	if(selectedFrame){
		if(selectedFrame->DragDropable()){
			selectedFrame->DragDropable()->drop(this);
		}
	}
	//selectedFrame = NULL;
}




void CUIBaseFrame::clear(){
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		delete (*it);
	}
	this->_frames.clear();
}


void CUIBaseFrame::finalRemove(){
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end();it++ ){

		(*it)->finalRemove();
	}


	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); ){
		if ((*it)->ToBeDrawFront()){
			CUIBaseFrame* temp = *it;
			_frames.remove((*it++));
			temp->setDrawFront(false);
			_frames.push_back((temp));
		}else
			it++;
	}
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); ){
		if ((*it)->getCanberemoved()){
			if ((*it) == selectedFrame)
				selectedFrame = NULL;
			_frames.remove(*it++);
		}else
			it++;
	}


}

int CUIBaseFrame::getUILevel(){
	if(this->_parrent){
		if (this->_parrent->getUILevel() > this->_UIlevel)
			return this->_parrent->getUILevel();
		else
			return this->_UIlevel;
	}else
		return this->_UIlevel;

}


void CUIBaseFrame::Draw(){
	for(uint16_t i = 0; i < 3; i++){
		for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
			if ((*it)->getUILevel() == i){
				(*it)->Draw();
			}
		}
	}
}


void CUIBaseFrame::add(CUIBaseFrame& frame){
	this->_frames.push_back(&frame);
}

void CUIBaseFrame::remove(CUIBaseFrame& frame){
	this->_frames.remove(&frame);
}


CUIBaseFrame::~CUIBaseFrame() {
}

