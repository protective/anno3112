/* 
 * File:   CUIButtonChangeTG.cpp
 * Author: karsten
 * 
 * Created on 9. oktober 2011, 11:01
 */

#include "CUIButtonChangeTG.h"
#include "../CUIMainFrame.h"
#include "../../spaceobjects/CShip.h"
#include "../../spaceobjects/CSubAble.h"
CUIButtonChangeTG::CUIButtonChangeTG(CUIBaseFrame* parrent, TargetGroup::Enum changeTo):
CUIButton(parrent,0,0,40,14){
	this->_changeTo = changeTo;
	
}

void CUIButtonChangeTG::Click(SDL_Event event,int32_t x, int32_t y){
		cerr<<"click CUIButtonChangeTG"<<endl;
		for (list<CSlotNode*>::iterator it =  mainFrame->GetSelSlotList().begin(); it != mainFrame->GetSelSlotList().end();it++){
			if (playerSels && playerSels->isShip()){
				for(list<CObj*>::iterator it2 = playerMultiSels.begin(); it2 != playerMultiSels.end(); it2++){
					if((*it2)->isShip() && (*it2)->isShip()->getShipType() == playerSels->isShip()->getShipType())
						playerObj->ServerRequestChangeSubTG((*it2)->issubable(),(*it)->getId(),this->_changeTo);
				}
			}
		}
}

void CUIButtonChangeTG::Draw(){

	glLoadIdentity();
	font.FaceSize(16);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(_x+_parrent->getX(), _y+_parrent->getY()+13);
	stringstream s;
	s<<getTargetGroupstring(_changeTo);
	font.Render(s.str().c_str());

}

CUIButtonChangeTG::~CUIButtonChangeTG() {
}

