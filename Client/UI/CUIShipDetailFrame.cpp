/* 
 * File:   CUIShipDetailFrame.cpp
 * Author: karsten
 * 
 * Created on 31. juli 2011, 23:18
 */

#include "CUIShipDetailFrame.h"
#include "../spaceobjects/CShip.h"
#include "../spaceobjects/subsystems/CSlotNode.h"
#include "../spaceobjects/subsystems/CSubTypeFac.h"
#include "CUIButton.h"
#include "CUISubSystem.h"
#include "CUIMainFrame.h"
#include "CUIButtonFrame.h"
#include "CUICargoViewer.h"
#include "Build/CUIBuildFrame.h"
CUIShipDetailFrame::CUIShipDetailFrame() :
CUIBaseFrame(NULL){
	_UIlevel = 2;
	_x = 0;
	_y = 0;
	_wight =450;
	_hight = Basehight;
	this->_buildFrame = NULL;
	this->_changeOrdre = NULL;
	this->_changeSubTargetGroup = NULL;
	_createFitForm = NULL;
	_opencargobut = new CUIButtonOpenCargo(this,5,170,60,36);
	_buttonFit = new CUIButtonCreateFit(this,70,170,60,36);
	this->_setUnits[0] = new CUIButtonSetUnitPos(this,0,-1);
	this->_setUnits[1] = new CUIButtonSetUnitPos(this,1,-1);
	this->_setPoses[0] = new CUIButtonSetUnitPos(this,-1,0);

}
void CUIShipDetailFrame::Move(SDL_Event event,int32_t x, int32_t y){

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->Move(event,x-(*it)->getX(),y-(*it)->getY());
	}
}


void CUIShipDetailFrame::UpdateSelvSubsystemChange(){
	if(mainFrame->GetSelSlot()){
		if (_buildFrame){
			cerr<<"remove build"<<endl;
			this->remove(*_buildFrame);
			delete _buildFrame;
			_buildFrame = NULL;
		}
		if(mainFrame->GetSelSlot()->getSS()){
			if (mainFrame->GetSelSlot()->getSS()->isFac()){
				if(mainFrame->GetSelSlot()->getSS()->isFac()->getItemType()){
					if(mainFrame->GetSelSlot()->getSS()->isFac()->getItemType()->getSubType()){
						CSubTypeFac* temp2 = mainFrame->GetSelSlot()->getSS()->isFac()->getItemType()->getSubType()->isFac();
						if (temp2){
							_buildFrame = new CUIBuildFrame(this,mainFrame->GetSelSlot()->getOwner()->getCargoBay());
							this->add(*_buildFrame);
							for (map<uint32_t,CItemType*>::iterator it = temp2->getCanBuildList().begin(); it!=temp2->getCanBuildList().end(); it++){
								this->_buildFrame->addCanBuild(mainFrame->GetSelSlot()->getSS()->isFac(),it->second);
							}
						}
					}
				}
			}
		}
	}

}
void CUIShipDetailFrame::updateLateShip(){

	for (map<uint32_t,CUIButtonSetUnitPos*>::iterator it = this->_setUnits.begin(); it != this->_setUnits.end(); it++){
		if(it->second){
			this->remove(*this->_setUnits[it->first]);

		}
	}
	for (map<uint32_t,CUIButtonSetUnitPos*>::iterator it = this->_setPoses.begin(); it != this->_setPoses.end(); it++){
		if(it->second){
			this->remove(*this->_setPoses[it->first]);
		}
	}

	if(playerSels && playerSels->isShip() && playerSels->isShip()->getOrdres()){
		for (map<uint32_t,bool>::iterator it = playerSels->isShip()->getOrdres()->getunitSet().begin(); it != playerSels->isShip()->getOrdres()->getunitSet().end(); it++){
			if(it->second){
				this->add(*this->_setUnits[it->first]);
				this->_setUnits[it->first]->SetX(100*it->first);
			}
		}
		for (map<uint32_t,bool>::iterator it = playerSels->isShip()->getOrdres()->getPosSet().begin(); it != playerSels->isShip()->getOrdres()->getPosSet().end(); it++){
			if(it->second){
				this->add(*this->_setPoses[it->first]);
				this->_setPoses[it->first]->SetX(100*it->first);
				this->_setPoses[it->first]->SetY(570);
			}
		}
	}
}

void CUIShipDetailFrame::updateShip(){
	if(!this->_changeOrdre)
		this->_changeOrdre = new CUIComboOrdreChange(this,10,500,80,14*(globalOrders.size()+1));
	this->remove(*_opencargobut);
	this->_buildFrame = NULL;
	this->_changeSubTargetGroup = NULL;
	this->remove(*_changeOrdre);
	this->remove(*_buttonFit);

	for (map<uint32_t,CUIButtonSetUnitPos*>::iterator it = this->_setUnits.begin(); it != this->_setUnits.end(); it++){
		if(it->second){
			this->remove(*this->_setUnits[it->first]);
		}
	}
	for (map<uint32_t,CUIButtonSetUnitPos*>::iterator it = this->_setPoses.begin(); it != this->_setPoses.end(); it++){
		if(it->second){
			this->remove(*this->_setPoses[it->first]);
		}
	}
	this->clear();
	if (playerSels){
		if(playerSels->isShip()){
			CShip* ss = playerSels->isShip();
			//cerr<<ss->getSlots().empty()<<endl;
			this->add(*this->_opencargobut);
			this->add(*this->_changeOrdre);
			this->add(*this->_buttonFit);
			this->updateLateShip();

			for (CslotI it = ss->getSlots().begin(); it != ss->getSlots().end();it++){
				CUISubSystem* subs = new CUISubSystem((CUIBaseFrame*)this,*it->second);
				this->add(*subs);
			}
		}
	}
		

}

void CUIShipDetailFrame::Click(SDL_Event event,int32_t x, int32_t y){
	cerr<<"click shipdetailframe"<<endl;
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() )
			(*it)->Click(event,x-(*it)->getX(),y-(*it)->getY());
	}
}

void CUIShipDetailFrame::MouseUp(SDL_Event event, int32_t x, int32_t y){
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() ){
			if(selectedFrame){
				if(selectedFrame->DragDropable()){
					selectedFrame->DragDropable()->drop((*it));
					selectedFrame = NULL;
				}

			}
		}
	}
	
}

void CUIShipDetailFrame::Draw(){

	int32_t uvx1;
	int32_t uvy1;
	uint32_t sheetsize;
	sheetsize = 1024;
	
	Drawbox(0,0,450,Basehight,0,0.00,0.12,1);
	
	if(playerSels){
		if(playerSels->isShip()){
			switch (playerSels->isShip()->getShipType()->getTexture()){

				//*****************************************
				//file generated by python spritesheet
				#include "../Textures/obj/Owcords.txt"

				//**************************************************
				default:{
				glBindTexture( GL_TEXTURE_2D, textures[Textures::OwObjSheet]);

				uvx1 = 0;
				uvy1 = 0;
				cerr<<"Warning subitemsheed tex"<<endl;
				break;
				}
			}
			glLoadIdentity();
			glTranslated((GLfloat)(220),(GLfloat)(318),0);

			uint32_t tsize = 200;
			uint32_t tnsize = 200;

				glBegin( GL_QUADS );
				//Bottom-left vertex (corner)
				glTexCoord2f((((double)1)/sheetsize)*(uvx1), (((double)1)/sheetsize)*(uvy1) );
				glVertex3i(-tsize, -tsize, 0.0f);

				//Bottom-right vertex (corner)
				glTexCoord2f((((double)1)/sheetsize)*(uvx1+tnsize), (((double)1)/sheetsize)*(uvy1) );
				glVertex3i(tsize, -tsize, 0.f);

				//Top-right vertex (corner)
				glTexCoord2f((((double)1)/sheetsize)*(uvx1+tnsize), (((double)1)/sheetsize)*(uvy1+tnsize) );
				glVertex3i(tsize, tsize, 0.f);

				//Top-left vertex (corner)
				glTexCoord2f((((double)1)/sheetsize)*(uvx1), (((double)1)/sheetsize)*(uvy1+tnsize) );
				glVertex3i(-tsize, tsize, 0.f);
			glEnd();


			//Draw energy bar
			Drawbox(5,250,15,150,1,0,0,1);
			if(playerSels->isShip()->getMaxEnergy() > 0){
				int32_t t =  (playerSels->isShip()->getEnergy()*150)/playerSels->isShip()->getMaxEnergy();
				Drawbox(5,250 + (150- t) ,15,t,0,1,0,1);
			}

		}
	}


	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		(*it)->Draw();
	}

	//hover box
	if(hoverFrame){
		glLoadIdentity();
		font.FaceSize(16);
		glColor3f(1.0, 1.0, 1.0);

		glRasterPos2f(280, 15);
		stringstream s;
		s<<hoverFrame->getHoverMsg();
		font.Render(s.str().c_str());
	}
}

CUIShipDetailFrame::~CUIShipDetailFrame() {
	this->clear();
}

