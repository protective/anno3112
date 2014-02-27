/* 
 * File:   SShot.cpp
 * Author: karsten
 * 
 * Created on 2. juli 2011, 14:23
 */

//#include <math.h>
//#include <c++/4.3/cmath>

#include "SShot.h"
#include "SSubAble.h"
#include "../World/SGrid.h"
#include "../NetworkLayer/SShotNetworkLayer.h"

SShot::SShot(uint32_t id, SPos& pos, SSubAble* owner, STargetable* target, SSubTypeWep* type):
SObj(pos,owner->obj()->getTeam(),owner->obj()->getPlayerId()), SMovable(this,0,0), Processable(id)
{

	this->_owner = owner;
	this->_target = target;
	this->_texId = type->getTexId();
	this->_resolution = type->getResolution(owner->getBonusList());

	uint32_t r = Rangeobj(this->_pos,target->obj()->getPos());
	uint32_t m = (r * type->getSpread()*50)/(type->getRange()/1000);

	m = myrandom(0,m);
	uint32_t theta = myrandom(0,359);
	int32_t rx = m * MyCos[theta];
	int32_t ry =  m * MySin[theta];
	uint32_t gamma = myrandom(0,359);
	int32_t rz = m * MyCos[gamma];

	int32_t expFlightTime = (((r*100)/type->getSpeed()))+1;
	int32_t preX = target->obj()->getPos().x; 
	int32_t preY = target->obj()->getPos().y;
	if(target->obj()->isMovable()){
		int32_t td = target->obj()->getPos().d;  
		int32_t tspeed = target->obj()->isMovable()->getSpeed() * expFlightTime;
		preX += (VektorUnitX(td/100) * tspeed)/100;
		preY += -((VektorUnitY(td/100)* tspeed)/100);
	}
	
	
	this->_targetPos.x = preX + rx;
	this->_targetPos.y = preY + ry;
	this->_targetPos.d = 0;
	this->_targetPos.z = 0;
	this->_targetPos.grid = target->obj()->getPos().grid;
	this->_pos.d = (100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y));
	this->_moveZ = Deg(r*100,rz);

	_hasHit = false;
	_dmgMin = type->getDmgMin(owner->getBonusList());
	_dmgMax = type->getDmgMax(owner->getBonusList());
	_speed = type->getSpeed();
	_dmgType = type->getDmgTypes();
	_tracking = type->getTracking();
	_trackingTime = type->getTrackingTime();
	_flightTime = 0;
	_maxFlightTime = ((type->getRange()/type->getSpeed())/10)+1;

}


void SShot::Move(uint32_t deltaT){
	if(_trackingTime && _target){
		int32_t targetDir = 0;
		int32_t b;
		targetDir = (100 * Deg(_target->obj()->getPos().x -this->_pos.x,_target->obj()->getPos().y -this->_pos.y));
		if (targetDir >= this->_pos.d)
			b = targetDir - this->_pos.d;
		else
			b = targetDir + 36000 - this->_pos.d;
		if (b > 18000)
			this->_pos.turn((int32_t)-this->_tracking);
		else
			this->_pos.turn((int32_t)this->_tracking);
		
	}
	this->MovePos(VektorUnitX(this->_pos.d/100) * _speed ,-(VektorUnitY(this->_pos.d/100)* _speed),VektorUnitY(this->_moveZ)*_speed);
	_flightTime++;
	
}

bool SShot::canBeRemoved(){

	if (_hasHit || _flightTime >= _maxFlightTime)
		return true;
	else
		return false;
}

void SShot::TestHit(){
	if (!_hasHit){
		
		for(SObjI it = this->_pos.grid->getObjInGrid().begin(); it != this->_pos.grid->getObjInGrid().end();it++){
			SObj* oobj = it->second;
			
			if(oobj->getTeam() != this->getTeam()){
				int32_t negsize = 0-oobj->getTargetSize();
				int32_t possize = oobj->getTargetSize();
				if(this->_pos.z > (negsize)/2 && this->_pos.z < possize/2){
					
					
					double a = 100 * Rangeobj(this->_pos,oobj->getPos());
					if(oobj->getTargetable()){
						if(a < oobj->getTargetSize()/2){
							double movementX = (VektorUnitX(this->_pos.d/100) * this->getSpeed());
							double movementY = (-(VektorUnitY(this->_pos.d/100) * this->getSpeed()));
							int32_t x1 = this->_pos.x - oobj->getPos().x;
							int32_t y1 = this->_pos.y - oobj->getPos().y;
							int32_t x2 = this->_pos.x+movementX - oobj->getPos().x;
							int32_t y2 = this->_pos.y+movementY - oobj->getPos().y;

							int32_t dx = x2 - x1;
							int32_t dy = y2 - y1;
							double dr = sqrt((dx*dx)+(dy*dy));
							double D = x1*y2 - x2*y1;
							double dis = ((oobj->getTargetSize()/2)*(oobj->getTargetSize()/2))*(dr*dr)-(D*D);

							if(dis >= 0 || _flightTime <= 1){//hit

								double hitx = ((D *dy -dx * (sqrt(pow((oobj->getTargetSize()/2),2) * pow(dr,2)- pow(D,2))))/ pow(dr,2));
								double hity = ((-D *dx -dy * (sqrt(pow((oobj->getTargetSize()/2),2) * pow(dr,2)- pow(D,2))))/ pow(dr,2));
								double H_x = (oobj->getTargetSize()/2);
								double H_y = 0;

								double P_x = hitx;
								double P_y = hity;

								double ph = Rangecord(H_x,H_y,P_x,P_y);
								double ch =(oobj->getTargetSize()/2);
								double cp = Rangecord(0,0,P_x,P_y);
								double rad = 0;
								if (2*cp*ch)
									rad = acos(((ch*ch)+(cp*cp)-(ph*ph))/(2*cp*ch));
								double V = (rad/3.14)*180;

								if( P_y > H_y)
									V = 360 - V;

								double V2 = V - (oobj->getPos().d/100);

								if(V2 < 0)
									V2 = V2 + 360;

								int i = 0;
								if ((V2 >= 0 && V2 <= 30) ||(V2 >= 330 && V2 <= 360)){
									i = 0;
								}else if(V2 >= 31 && V2 <= 90){
									i = 1;
								}else if(V2 >= 91 && V2 <= 150){
									i = 4;
								}else if(V2 >= 151 && V2 <= 209){
									i = 3;
								}else if(V2 >= 210 && V2 <= 269){
									i = 5;
								}else if(V2 >= 270 && V2 <= 329){
									i = 2;
								}

								
								Hit(oobj->getTargetable() , (Shields::Enum)i,0,0);
							}
						}
					}
				}
			}
		}
	}
}

void SShot::Hit(STargetable* target, Shields::Enum shield, int32_t x, int32_t y){
	_hasHit = true;
	uint32_t tarRes = target->obj()->getSize()/100;
	double mod = 1;
	if(_resolution > tarRes){
		mod =  (double)tarRes / _resolution;
	}
	target->Hit(this,mod * myrandom(_dmgMin,_dmgMax),_dmgType,shield,x,y);

}


void SShot::setTargetPos(SPos& pos){
	pthread_mutex_lock(&this->lockUnit);
	this->_targetPos.x = pos.x;
	this->_targetPos.y = pos.y;
	this->_targetPos.d = pos.d;
	pthread_mutex_unlock(&this->lockUnit);
}

void SShot::MovePos(int32_t x, int32_t y, int32_t z){
	this->_pos.x+= x;
	this->_pos.y+= y;
	this->_pos.z+= z;
}

void SShot::sendFull(SubscriptionLevel::Enum level){
	sendShotFull(_subscriptions[level],this);
}

SShot::~SShot() {
}

