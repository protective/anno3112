/* 
 * File:   GShip.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:34
 */

#include "CShip.h"
#include "subsystems/CSubSystemW.h"
#include "subsystems/CSubSystemBonus.h"
#include "subsystems/CSubSystemBoost.h"
#include "../UI/CUIShipDetailFrame.h"
#include "../UI/CUIMainFrame.h"
#include "CShipType.h"
CShip::CShip(uint32_t id, uint32_t playerId, CPos& pos, CShipType& stype) :
CObj(id,playerId,pos),CTargetable(this),CSubAble(this,stype.getEnergy(), stype.getScanRange(),stype.getScanPRange(),stype.getCargo()),CUIBaseFrame((CUIBaseFrame*)mainFrame),CMovable(this,stype.getTopSpeed(),stype.getAgility()) {

	_graficCounterPrio = 0;
	this->_order = NULL;
	this->_toBeRemoved = false;
	this->_targetPos.x = pos.x;
	this->_targetPos.y = pos.y;
	this->_targetPos.d = pos.d;

	this->_maxarmor = stype.getArmor()*1000;
	this->_maxhull = stype.getHull()*1000;
	this->_armor = stype.getArmor()*1000;
	this->_hull = stype.getHull()*1000;
	this->_maxdeflector = stype.getDeflector()*1000;
	this->_deflector = stype.getDeflector()*1000;

	for (int i = 0; i< 6; i++){
		this->_maxshield[i] = stype.getShield(i) * stype.getShieldStr() * 10;
		this->_shield[i] = this->_maxshield[i];
	}

	
	this->_shiptype = &stype;
	for(map<uint32_t, CShipTypeSlotData*>::iterator it = stype.getSlots().begin(); it != stype.getSlots().end(); it++){
		this->slots[it->first] = new CSlotNode(this,it->first,it->second);
	}

	_UIlevel = 1;
}

void CShip::ResivePosUpdate(CPos& pos){
	//this->_pos.x = pos.x;
	//this->_pos.y = pos.y;

	this->_ofsetX =  pos.x - this->_pos.x;
	this->_ofsetY =  pos.y - this->_pos.y;

	this->_pos.d = pos.d;
	this->_lastUpdate = getTime();
	this->_procedTime = getTime();
}

bool CShip::canBeRemoved(){
	if (this->_toBeRemoved  && _fadetimer == 0){
		
		return true;
	}else
		return false;
}


bool CShip::isDead(){
	if (this->_hull <= 0)
		return true;
	else
		return false;
}

void CShip::predraw(uint32_t level){
	/*
	if(level == 0){
		if(this->_scanRange && this->_team == teamlist[playerId]){
			uint32_t actualRange = this->_scanRange/100;
			glLoadIdentity();
			glTranslated((GLfloat)(((this->_pos.x-viewPos->x)*viewZoom)/100),(GLfloat)(((this->_pos.y-viewPos->y)*viewZoom)/100),0);

			glDisable(GL_TEXTURE_2D);
			glColor4f(0.08, 0.08, 0.08, 1);
			glBegin(GL_TRIANGLE_FAN);
				for(int angle = 0 ; angle < 360; angle+=5){
					glVertex2f(0 + MySin[angle] * (actualRange*viewZoom), 0 + MyCos[angle] * (actualRange*viewZoom));
				}
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glColor4f(1, 1, 1, 1);
		}
	}else if(level == 1){
		if(this->_scanPRange && this->_team == teamlist[playerId]){
			uint32_t actualRange = this->_scanPRange/100;
			glLoadIdentity();
			glTranslated((GLfloat)(((this->_pos.x-viewPos->x)*viewZoom)/100),(GLfloat)(((this->_pos.y-viewPos->y)*viewZoom)/100),0);

			glDisable(GL_TEXTURE_2D);
			glColor4f(0.11, 0.11, 0.11, 1);
			glBegin(GL_TRIANGLE_FAN);
				for(int angle = 0 ; angle < 360; angle+=5){
					glVertex2f(0 + MySin[angle] * (actualRange*viewZoom), 0 + MyCos[angle] * (actualRange*viewZoom));
				}
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glColor4f(1, 1, 1, 1);

			
		}
	}
	 * */
}

void CShip::Draw(){

	int32_t uvx1;
	int32_t uvy1;
	uint32_t sheetsize;

			sheetsize = 1024;

	double a = 1;
	if(_maxfadetimer != 0){
		if (_maxfadetimer > 0){
			a = 1-(((double)_fadetimer / _maxfadetimer));
		}
		if (_maxfadetimer < 0){
			a = (((double)_fadetimer / _maxfadetimer));
		}
		
	}

		switch (this->_shiptype->getTexture()){

		//*****************************************
		//file generated by python spritesheet
		#include "../Textures/obj/cords.txt"

		//**************************************************
			default:{
			glBindTexture( GL_TEXTURE_2D, textures[Textures::ObjSheet]);

			uvx1 = 0;
			uvy1 = 0;
			cerr<<"Warning objsheed tex"<<endl;
			break;
			}
		}


	glBindTexture( GL_TEXTURE_2D, textures[Textures::ObjSheet]);

	glLoadIdentity();
	glTranslated((GLfloat)(((this->_pos.x-viewPos->x)*viewZoom)/100),(GLfloat)(((this->_pos.y-viewPos->y)*viewZoom)/100),0);
	glColor4f(1, 1, 1, a);
	glRotatef((GLfloat)(180-(this->_pos.d/100)),0,0,0.1);
	uint32_t tsize = (this->getSize() /2);
	uint32_t tnsize =this->getSize();
	uint32_t tzsize = tsize*viewZoom;
	uint32_t tznsize =tnsize*viewZoom;
		glBegin( GL_QUADS );
		//Bottom-left vertex (corner)
		glTexCoord2f((((double)1)/sheetsize)*(uvx1), (((double)1)/sheetsize)*(uvy1) );
		glVertex3i(-tzsize, -tzsize, 0.0f);

		//Bottom-right vertex (corner)
		glTexCoord2f((((double)1)/sheetsize)*(uvx1+tnsize), (((double)1)/sheetsize)*(uvy1) );
		glVertex3i(tzsize, -tzsize, 0.f);

		//Top-right vertex (corner)
		glTexCoord2f((((double)1)/sheetsize)*(uvx1+tnsize), (((double)1)/sheetsize)*(uvy1+tnsize) );
		glVertex3i(tzsize, tzsize, 0.f);

		//Top-left vertex (corner)
		glTexCoord2f((((double)1)/sheetsize)*(uvx1), (((double)1)/sheetsize)*(uvy1+tnsize) );
		glVertex3i(-tzsize, tzsize, 0.f);
	glEnd();
	
	glColor4f(1, 1, 1, 1);

	//begin hpstatus
	int32_t tx = ((_pos.x-viewPos->x)*viewZoom)/100;
	int32_t ty = ((_pos.y-viewPos->y)*viewZoom)/100;

	for(list<CObj*>::iterator it = playerMultiSels.begin(); it != playerMultiSels.end(); it++){
		if(*it == this){
			Drawbox((tx)-(tznsize/2)-4,(ty)-(tznsize/2), (tznsize)+8,5,0.5,1,0.5,1);
		}
	}
	if(this->getPrio() > 0){
		if (_graficCounterPrio< 400){
			Drawbox(tx+(((tznsize*_graficCounterPrio)/400)/2)-tznsize/2,(ty)-(tznsize/2)+6, 2,2,1,1,0,1);
			Drawbox(tx-(((tznsize*_graficCounterPrio)/400)/2)+tznsize/2,(ty)-(tznsize/2)+6, 2,2,1,1,0,1);

		}
	}
	
	if(playerSels == this)
		Drawbox((tx)-(tznsize/2)-4,(ty)-(tznsize/2), (tznsize)+8,5,255,255,255,255);



	Drawbox((tx)-(tznsize/2),(ty)-(tznsize/2),(tznsize),6,255,0,0,255);



	//team
	Drawbox((tx)-(tznsize/2),(ty)-(tznsize/2)+8, (tznsize),1,playercolour[this->_playerId]._r,playercolour[this->_playerId]._g,playercolour[this->_playerId]._b,1);
	glColor4f(1,1,1,1);
	//hull
	if(_maxhull)
		Drawbox((tx)-(tznsize/2),(ty)-(tznsize/2), ((tznsize)*_hull)/_maxhull,6,255,255,0,255);

	//armor
	if(_maxarmor)
		Drawbox((tx)-(tznsize/2),(ty)-(tznsize/2), ((tznsize)*_armor)/_maxarmor,2,0,255,0,255);

	//deflector
	glTranslated((GLfloat)(((this->_pos.x-viewPos->x)*viewZoom)/100),(GLfloat)(((this->_pos.y-viewPos->y)*viewZoom)/100),0);

	if (this->_deflector > 0){
		GLfloat r = 0;
		GLfloat g = 0;
		GLfloat b = 0;
		GLfloat a = 1;
		double p;
		if (this->_maxdeflector){
			p = ((double)this->_deflector) / this->_maxdeflector;
			if (p > 0.5){
				double p2 = (double)1 - (p*2);
				r = p2;
				g = 1;
			}else{
				double p2 = (p*2);
				a = p2;
				r = 1;
				g = p2;
			}
			glColor4f(r, g, b, a);
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_LINE_LOOP);
			for(int angle = 0 ; angle < 360; angle+=5){
				glVertex2f(0 + MySin[angle] * (this->getSize()*viewZoom)/2.2, 0 + MyCos[angle] * (this->getSize()*viewZoom)/2.2);
			}
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
	}


	//Shield
	glRotatef((GLfloat)(180-(this->_pos.d/100)),0,0,0.1);

	//glRotatef((GLfloat)(180-(this->_pos.d/100)),0,0,0.1);
	glDisable(GL_TEXTURE_2D);
	for (int i = 0 ; i< 6 ; i++){
		int32_t d1;
		int32_t d2;
		switch(i){
			case 0:d1 = 30;d2 = 330;break;
			case 2:d1 = 90;d2 = 30;break;
			case 5:d1 = 150;d2 = 90;break;
			case 3:d1 = 210;d2 = 150;break;
			case 4:d1 = 270;d2 = 210;break;
			case 1:d1 = 330;d2 = 270;break;
		}
	int32_t x1 = (-VektorUnitX(d1) * (tzsize))*1.1;
	int32_t y1 = (-VektorUnitY(d1) * (tzsize))*1.1;
	int32_t x2 = (-VektorUnitX(d2) * (tzsize))*1.1;
	int32_t y2 = (-VektorUnitY(d2) * (tzsize))*1.1;
	if (this->_shield[i] > 0){
		GLfloat r = 0;
		GLfloat g = 0;
		GLfloat b = 0;
		GLfloat a = 1;
		double p;
		if (this->_maxshield[i]){
			p = ((double)this->_shield[i]) / this->_maxshield[i];
			if (p > 0.5){
				double p2 = (double)1 - (p*2);
				r = p2;
				g = 1;
			}else{
				double p2 = (p*2);
				a = p2;
				r = 1;
				g = p2;
			}
		}


		glColor4f(r, g, b, a);
		glBegin(GL_LINES);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		glEnd();
		glColor4f(1,1,1,1);
	}

	}
	glEnable(GL_TEXTURE_2D);
	//Drawbox(0,0, ((_size)*_armor)/_maxarmor,2,0,255,0,255);

	//DrawLine(_pos.x/100,_pos.y/100,_pos.x/100+80,_pos.y/100+80,2,0,255,0,255);

}

void CShip::Click(SDL_Event event, int32_t x, int32_t y){
	if( Rangeobj((this->_pos.x-viewPos->x)*viewZoom, (this->_pos.y-viewPos->y)*viewZoom,x*100,y*100) <= this->_shiptype->getSize()*viewZoom/2){
		if(!_toBeRemoved){

			if(mainFrame->getsetOrdreUnit() >= 0){
				for(list<CObj*>::iterator it = playerMultiSels.begin(); it != playerMultiSels.end(); it++){
					playerObj->ServerRequestSetOrdreUnit(*it,this, mainFrame->getsetOrdreUnit());
				}
				mainFrame->setsetOrdreUnit(-1);
				return;
			}

			if(playerSels && playerSels != this)
				playerObj->ServerNotisUnSubscribe(*playerSels);

			playerObj->ServerNotisSubscribe(*this);
			if (event.button.button == SDL_BUTTON_RIGHT && SDL_GetModState() & KMOD_SHIFT){
				if(this->getPrio() == 0)
					playerObj->ServerRequestChangePrio(this,1);
				else
					playerObj->ServerRequestChangePrio(this,0);

			}
			if (event.button.button == SDL_BUTTON_LEFT && SDL_GetModState() & KMOD_SHIFT ){
				if(_team == teamlist[playerId] && ((playerMultiSels.size() > 0 && playerMultiSels.back()->getTeam() == teamlist[playerId]) || playerMultiSels.size() == 0)){
					playerMultiSels.remove(this);
					playerMultiSels.push_back(this);
					playerSels = this;
				}
			}else if(event.button.button == SDL_BUTTON_LEFT){
				playerMultiSels.clear();
				playerMultiSels.remove(this);
				playerMultiSels.push_back(this);
				playerSels = this;
			}


			mainFrame->SetSelSlot(NULL,false);
			mainFrame->shipDetail()->updateShip();
		}
	}
}

void CShip::Proces(uint32_t DTime){
	for(CSlotNodeI it = this->slots.begin(); it != this->slots.end(); it++){
		if (it->second->getSS())
			it->second->getSS()->proces(DTime);
	}
	_graficCounterPrio += DTime;
	if(_graficCounterPrio > 1000)
		_graficCounterPrio = _graficCounterPrio - 1000;
	while(this->_procedTime<= getTime()){
		this->_procedTime += 1000/25;
		if(_fadetimer > 0)
			_fadetimer--;
		else if(_fadetimer < 0)
			_fadetimer++;
		if(_fadetimer == 0)
			_maxfadetimer = 0;
	//turn code************
		uint32_t r = Rangeobj(this->getPos(),this->getTargetPos());
		int32_t targetDir = 0;
		//if(this->_targetPos.d >= 0){
			targetDir = this->_targetPos.d;
		//}else
		//	targetDir = (100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y));

		int32_t b;
		int32_t a; //amount to turn
		double acc = _agility;
		double turnVal;

		//speed up or down
		if (r < _topSpeed/acc)
			_maxSpeed = r * 100;

		if(r > 20){
			if(_speed < _maxSpeed)
				_speed += acc*2;
		}else if (r > 10){
			if (_maxSpeed/100 > r)
				_maxSpeed = (r+ 10)*100;
		}else{
			_maxSpeed = 0;
		}

		if(_speed > _maxSpeed){
			_speed -= acc;
			if(_speed < 0)
				_speed = 0;
			if(_speed < _maxSpeed)
				_speed = _maxSpeed;
		}

		//calk diff to turn
		if (targetDir >= this->_pos.d)
			b = targetDir - this->_pos.d;
		else
			b = targetDir + 36000 - this->_pos.d;

		//calk amount to turn
		if (b <= 18000)
			a = b;
		else if( b > 18000)
			a = 36000 - b;

		//reduce maxspeed if the turn is sharp
		if(a < 300 * 0.95)
			_maxSpeed = _topSpeed;
		else
			_maxSpeed= _topSpeed * (1 - ((double)a / 8000));

		//turnval reduces by the speed
		if(_speed > 0){
			if(_speed < _topSpeed * 0.75)
				turnVal = 300 * (1 - ((double)_speed / (double)_topSpeed));
			else
				turnVal = 300 * 0.25;
		}else
			turnVal = 300;

		turnVal = turnVal * (((double)_agility / 100) / 2);
		if (a < turnVal)
			turnVal = a;
		if (b > 18000)
			this->_pos.turn((int32_t)-turnVal);
		else
			this->_pos.turn((int32_t)turnVal);


		//Update stats

		_targetUpdateCounter++;
		if (_targetUpdateCounter % 25 == 0){
			this->_bonuslist.clear();
			for(CSlotNodeI it = this->slots.begin(); it != this->slots.end(); it++){
				if (it->second->getSS()){
					if (it->second->getSS()->isBonus()){
						it->second->getSS()->isBonus()->procesBonus(this);
					}
				}

			}
			this->_maxEnergy = _shiptype->getEnergy() * 1000;
			this->_maxdeflector = _shiptype->getDeflector()*1000;
			//this->_deflector = stype.getDeflector()*1000;
			for (int i = 0; i< 6; i++){
				this->_maxshield[i] = _shiptype->getShield(i) * _shiptype->getShieldStr() * 10;
			}
			this->_maxarmor = _shiptype->getArmor()*1000;
			this->_maxhull = _shiptype->getHull()*1000;

			this->_scanRange = _shiptype->getScanRange() * 100;
			this->_scanPRange = _shiptype->getScanPRange() * 100;
			_topSpeed = _shiptype->getTopSpeed() * 100;
			_agility = _shiptype->getAgility();

			for (map<BonusTypes::Enum, int32_t>::iterator it = this->_bonuslist.begin(); it != this->_bonuslist.end();it++){
				switch(it->first){
					case BonusTypes::Armor:{this->_maxarmor+= it->second;break;}
					case BonusTypes::Deflector:{this->_maxdeflector+= it->second;break;}
					case BonusTypes::Hull:{this->_maxhull+= it->second;break;}
					case BonusTypes::ShieldStr:{
						for(uint32_t i = 0; i < 6 ; i++){
							this->_maxshield[i] += (this->getShipType()->getShield(i) * it->second)/100;
						}
						break;
					}
					case BonusTypes::Energy:{this->_maxEnergy+= it->second;break;}
					case BonusTypes::ScanRange:{this->_scanRange+= (it->second/10);break;}
					case BonusTypes::ScanPRange:{this->_scanPRange+= (it->second/10);break;}
					case BonusTypes::SpeedThruster:{this->_topSpeed+= (it->second/(_shiptype->getMass()/10));break;}
					case BonusTypes::ManuvereThruster:{this->_agility+= (it->second/(_shiptype->getMass()*10));break;}

				}
			}
		}
		if (_targetUpdateCounter == 25)
			_targetUpdateCounter = 0;


		}
		//Move TDtime - procestime
		this->Move(DTime);
		//this->Move(getTime() - this->_lastUpdate);
		this->_lastUpdate = getTime();
}

uint32_t CShip::AddSub(CItemType* type, uint32_t slot, uint32_t Xitem){
	if (this->slots[slot]){
		if(this->slots[slot]->getSS()){
			if(this->slots[slot]->getSS()->getItemType()->getTypeID() != type->getTypeID() ){
				return 0;
			}
		}else{
			//if(type->getSubType()->getClass() == SubSystemClass::Wep){
			//	this->slots[slot]->setSS(new CSubSystemW(*((CObj*)this),type,Xitem));
			//	return this->slots[slot]->getSS()->Xitem();
			//}
		}
		if (this->slots[slot]->getSS())
			return this->slots[slot]->getSS()->AddItem(Xitem);
		else{
			cerr<<"WARNING Ship::ADDSub no subsystem created"<<endl;
			return 0;
		}
	}
	cerr<<"WARNING Ship::ADDSub slot not found"<<endl;
	return 0;

}


uint32_t CShip::RemoveSub(uint32_t slot, uint32_t Xitem){
	if (this->slots[slot]){
		if (this->slots[slot]->getSS()){
			uint32_t t = this->slots[slot]->getSS()->RemoveItem(Xitem);
			if (this->slots[slot]->getSS()->Xitem() == 0 ){
				delete this->slots[slot]->getSS();
				this->slots[slot]->setSS(NULL);
			}
			return t;
		}else{
			cerr<<"WARNING Ship::RemoveSub no subsystem to remove"<<endl;
			return 0;
		}
	}
	cerr<<"WARNING Ship::RemoveSub slot not found"<<endl;
	return 0;

}

void CShip::Move(uint32_t deltaT){
	if (deltaT > 10000)
		cerr<<"WARNING CShip::Move delta is wrong "<<deltaT<<endl;
	if (_speed < 0)
		cerr<<"WARNING CShip::Move speed is negative "<<deltaT<<endl;

	int32_t speed = 0;
	speed = (_speed * deltaT)/(1000/25);
	//cerr<<"d>"<<deltaT<<endl;
	if(_ofsetX > 5 || _ofsetX < -5){
		_pos.x += _ofsetX / 5;
		_ofsetX -= _ofsetX / 5;
	}else{
		_pos.x += _ofsetX;
		_ofsetX = 0;
	}

	if(_ofsetY > 5 || _ofsetY < -5){
		_pos.y += _ofsetY / 5;
		_ofsetY -= _ofsetY / 5;
	}else{
		_pos.y += _ofsetY;
		_ofsetY = 0;
	}

	this->MovePos((VektorUnitX(this->_pos.d/100) * speed)/100 ,-((VektorUnitY(this->_pos.d/100)* speed )/100));

}

CShip::~CShip() {
}

