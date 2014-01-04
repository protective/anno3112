/* 
 * File:   CUIMainFrame.cpp
 * Author: karsten
 * 
 * Created on 20. juli 2011, 21:36
 */

#include "CUIMainFrame.h"
#include "../spaceobjects/subsystems/CSlotNode.h"
#include "../spaceobjects/subsystems/CSubTypeFac.h"
#include "../spaceobjects/subsystems/CSubSystemFac.h"
#include "../Items/CItemType.h"
#include "CUIButton.h"
#include "CUISubSystem.h"
#include "CUIButtonFrame.h"
#include "Buttons/CUIButtonBuild.h"
#include "Build/CUIBuildFrame.h"
#include "../spaceobjects/CSubAble.h"
#include "../spaceobjects/CShip.h"
#include "../world/CGrid.h"
#include <SDL/SDL.h>
///usr/share/fonts/truetype/msttcorefonts

CUIMainFrame::CUIMainFrame(CUIBaseFrame* parrent):
CUIBaseFrame(parrent){
	Vx = 0;
	Vy = 0;
	_setOrdreUnit = -1;
	_setOrdrePos= -1;
	_shipDetail = new CUIShipDetailFrame();
	this->add(*_shipDetail);
	
}

void CUIMainFrame::preAdd(){
	for(list<CUIBaseFrame*>::iterator it = _toBeAdded.begin(); it != _toBeAdded.end();it++){
		this->_frames.push_back(*it);
	}
	_toBeAdded.clear();

}

void CUIMainFrame::SetSelSlot(CSlotNode* subsys,bool add){
	this->_selslot = subsys;
	this->_shipDetail->UpdateSelvSubsystemChange();
	if(subsys){
		if (add){
			_selslotList.remove(subsys);
			_selslotList.push_back(subsys);
		}else{
			_selslotList.clear();
			_selslotList.push_back(subsys);
		}
	}else{
		_selslotList.clear();
	}
}

void CUIMainFrame::Draw(){

	for (uint32_t i = 0; i < 2 ; i++){
		for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
			(*it)->predraw(i);
		}
	}
	if(viewPos && viewPos->grid){
		//cerr<<"draw"<<endl;
		int32_t tx = ((((int32_t)0-((int32_t)viewPos->grid->getWight()/2))-viewPos->x)*viewZoom)/100;
		int32_t ty = ((((int32_t)0-((int32_t)viewPos->grid->getHight()/2))-viewPos->y)*viewZoom)/100;

		Drawbox(tx,ty,(viewPos->grid->getWight()*viewZoom)/100,1,1,1,1,1);
		Drawbox(tx,ty,1,(viewPos->grid->getHight()*viewZoom)/100,1,1,1,1);

		Drawbox(tx,ty+((viewPos->grid->getHight()*viewZoom)/100),(viewPos->grid->getWight()*viewZoom)/100,1,1,1,1,1);
		Drawbox(tx+((viewPos->grid->getWight()*viewZoom)/100),ty,1,(viewPos->grid->getHight()*viewZoom)/100,1,1,1,1);
	}
	for(uint16_t i = 0; i < 5; i++){
		for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
			if ((*it)->getUILevel() == i){
				(*it)->Draw();
			}
		}
		if (i == 1){
			for(list<CPartical*>::iterator it = particals.begin(); it != particals.end();it++){
				(*it)->Draw();
			}
		}
	}


	
}

void CUIMainFrame::Click(SDL_Event event,int32_t x, int32_t y){
	//cerr<<"click mainframe"<<endl;
	bool clickhit = false;

	if(mainFrame->getsetOrdrePos() >= 0){
		for(list<CObj*>::iterator it = playerMultiSels.begin(); it != playerMultiSels.end(); it++){
			int32_t mx = event.button.x*100;
			int32_t my = event.button.y*100;
			CPos temppos((mx* viewRZoom)+viewPos->x,(my* viewRZoom)+viewPos->y,0);

			playerObj->ServerRequestSetOrdrePos(*it,&temppos, mainFrame->getsetOrdrePos());
		}
		mainFrame->setsetOrdrePos(-1);
		return;
	}

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() ){
			(*it)->Click(event,x-(*it)->getX(),y-(*it)->getY());

			if((*it)->getUILevel()>= 3)
				clickhit = true;
		}
	}
	if (x > _shipDetail->getX() + _shipDetail->getWight() && !clickhit){
		if (!(SDL_GetModState() & KMOD_LSHIFT) && !(SDL_GetModState() & KMOD_LCTRL) && event.button.button == SDL_BUTTON_RIGHT){

			if(playerMultiSels.size()> 0 && _setOrdrePos == -1 && _setOrdreUnit == -1){
				int32_t tx = 0;
				int32_t ty = 0;
				for(list<CObj*>::iterator it = playerMultiSels.begin(); it != playerMultiSels.end(); it++){
					if((*it)->isMovable()){
						tx += (*it)->getPos().x;
						ty += (*it)->getPos().y;
					}
				}
				//cerr<<"tx "<<tx<<" ty "<<ty<<" "<<playerMultiSels.size()<<endl;
				tx = (double)tx / playerMultiSels.size();
				ty = (double)ty / playerMultiSels.size();
				//cerr<<"tx "<<tx<<" ty "<<ty<<endl;
				for(list<CObj*>::iterator it = playerMultiSels.begin(); it != playerMultiSels.end(); it++){
					if((*it)->isMovable() && (*it)->getTeam() == teamlist[playerId]){
						CMovable* tobj = (*it)->isMovable();
						int32_t mx = event.button.x*100;
						int32_t my = event.button.y*100;		
						if(!(*it)->isMovable()->getMovementStatus() & MoveBitF::TargetPosLock){
							tobj->getTargetPos().x = ((mx* viewRZoom)+viewPos->x) - (tx - (*it)->getPos().x);
							tobj->getTargetPos().y = ((my* viewRZoom)+viewPos->y) - (ty - (*it)->getPos().y);

							playerObj->ServerNotisTargetPosChange(*(*it));
						}
					}
				}
			}
		}
	}


}

void CUIMainFrame::MouseUp(SDL_Event event,int32_t x, int32_t y){

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->MouseUp(event,x-(*it)->getX(),y-(*it)->getY());
	}

	selectedFrame = NULL;
}


void CUIMainFrame::Move(SDL_Event event,int32_t x, int32_t y){
	if (selectedFrame){
		selectedFrame->moveX(event.motion.xrel);
		selectedFrame->moveY(event.motion.yrel);
	}
	if((SDL_GetModState() & KMOD_LSHIFT ) && event.button.button == 4){//SHIFT
		viewPos->x -= event.motion.xrel*100*(viewRZoom);
		viewPos->y -= event.motion.yrel*100*(viewRZoom);

	}
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){

		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->Move(event,x-(*it)->getX(),y-(*it)->getY());
	}

}



CUIMainFrame::~CUIMainFrame() {
}

