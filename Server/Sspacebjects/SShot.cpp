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
#include "../World/SWorld.h"
#include "../NetworkLayer/SShotNetworkLayer.h"
#include "SMetaObj.h"
#include "../Commands/CommandRemove.h"
#include "../Commands/CommandEnterGrid.h"
#include "../Commands/CommandHit.h"


SShot::SShot(uint32_t id, SPos& pos, SSubAble* owner, uint32_t target, SSubTypeWep* type, Processor* creator):
SObj(id, pos,owner->obj()->getTeam(),owner->obj()->getPlayerId()), SMovable(this,0,0), Processable()
{

	this->_owner = owner;
	this->_target = target;
	this->_texId = type->getTexId();
	this->_resolution = type->getResolution(owner->getBonusList());
	
	_type = type;
	_hasHit = false;
	_dmgMin = type->getDmgMin(owner->getBonusList());
	_dmgMax = type->getDmgMax(owner->getBonusList());
	_speed = type->getSpeed();
	_dmgType = type->getDmgTypes();
	_tracking = type->getTracking();
	_trackingTime = type->getTrackingTime();
	_flightTime = 0;
	_maxFlightTime = (((type->getRange()/type->getSpeed()))+1)*4;
	SMetaObj* metaTarget;
	if(metaTarget = creator->getMeta(this->_target)){
		SPos deltaPos; deltaPos = metaTarget->getRPos();
		uint32_t r = Rangeobj(this->_pos, deltaPos);
		uint32_t m = (r * type->getSpread()*50)/(type->getRange()/1000);

		m = myrandom(0,m);
		uint32_t theta = myrandom(0,359);
		int32_t rx = m * MyCos[theta];
		int32_t ry =  m * MySin[theta];
		uint32_t gamma = myrandom(0,359);
		int32_t rz = m * MyCos[gamma];
		int32_t expFlightTime = (((r*100)/type->getSpeed()))+1;
		int32_t preX = deltaPos.x; 
		int32_t preY = deltaPos.y;

		//TODO HMM problem
		
		if(metaTarget->isMoveable()){
			//int32_t td = metaTarget->getPos().d;  
			//int32_t tspeed = metaTarget->isMovable()->getSpeed() * expFlightTime;
			preX += (metaTarget->vecX * expFlightTime) / 1;
			preY += (metaTarget->vecY * expFlightTime) / 1;
		}
		

		this->_targetPos.x = rx + preX;
		this->_targetPos.y = ry + preY;
		
		this->_targetPos.z = 0;
		this->_targetPos.grid = metaTarget->getPos()->grid;
		this->_pos.d = 100 * Direction(this->_pos, this->_targetPos);
		this->_targetPos.d = this->_pos.d;
		
				//(100 * Deg(shot->_targetPos.x-shot->_pos.x,shot->_targetPos.y-shot->_pos.y));
		this->_moveZ = Deg(r*100,rz);
	
	}
	
	//this->addCommand(new CommandInitShot(id));
	SGrid* tempgrid =  world->getGrids().begin()->second;
	this->addCommand(new CommandEnterGrid(0,tempgrid->getId(),id));
					
}

void SShot::proces(uint32_t delta, Processor* processor){
	//cerr<<"proces shot"<<endl;
	this->Move(delta);
	if(canBeRemoved())
		this->addCommand(new CommandRemove(0,this));
}

void SShot::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){
	_subscriptions[level].push_back(clientId);
	this->sendFull(level);
	
}


void SShot::Move(uint32_t deltaT){
	SMetaObj* targetMeta = NULL;
	if(_trackingTime && (targetMeta = _processor->getMeta(_target))){
		int32_t targetDir = 0;
		int32_t b;
		targetDir = 100* Direction(this->_pos,*targetMeta->getPos());
		//targetDir = (100 * Deg(targetMeta->getPos()->x - this->_pos.x, targetMeta->getPos()->y - this->_pos.y));
		if (targetDir >= this->_pos.d)
			b = targetDir - this->_pos.d;
		else
			b = targetDir + 36000 - this->_pos.d;
		if (b > 18000)
			this->_pos.turn((int32_t)-this->_tracking);
		else
			this->_pos.turn((int32_t)this->_tracking);
		
	}
	this->MovePos((VektorUnitX(this->_pos.d/100) * _speed * deltaT)/40,-(VektorUnitY(this->_pos.d/100)* _speed* deltaT)/40,(VektorUnitY(this->_moveZ)*_speed*deltaT)/40);
	_flightTime+=deltaT;
	//if(deltaT)
		//this->TestHit();
}

bool SShot::canBeRemoved(){

	if (_hasHit || _flightTime >= _maxFlightTime)
		return true;
	else
		return false;
}

void SShot::TestHit(){
	if (_hasHit){
		return;
	}
	
	for(map<uint32_t, SMetaObj*>::iterator it = _processor->getLocalMetas().begin(); it !=  _processor->getLocalMetas().end(); it++){
		SMetaObj* oobj = it->second;

		if(oobj->getTeam() == this->getTeam()){
			continue;
		}
		int32_t negsize = 0-oobj->getTargetSize();
		int32_t possize = oobj->getTargetSize();
		if(this->_pos.z > (negsize)/2 && this->_pos.z < possize/2){
			double a = 100 * Rangeobj(this->_pos,*oobj->getPos());
			if(oobj->getTargetType()==TargetType::Invalid){
				continue;
			}
			if(a >= oobj->getTargetSize()/2){
				continue;
			}
			double movementX = (VektorUnitX(this->_pos.d/100) * this->getSpeed());
			double movementY = (-(VektorUnitY(this->_pos.d/100) * this->getSpeed()));
			int32_t x1 = this->_pos.x - oobj->getPos()->x;
			int32_t y1 = this->_pos.y - oobj->getPos()->y;
			int32_t x2 = this->_pos.x+movementX - oobj->getPos()->x;
			int32_t y2 = this->_pos.y+movementY - oobj->getPos()->y;

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

				double V2 = V - (oobj->getPos()->d/100);

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

				Hit(it->first, (Shields::Enum)i,0,0);
			}
		}	
	}
}

void SShot::Hit(uint32_t target, Shields::Enum shield, int32_t x, int32_t y){
	SMetaObj* obj = _processor->getLocalMetas()[target];
	_hasHit = true;
	uint32_t tarRes = obj->getTargetSize()/100;
	double mod = 1;
	if(_resolution > tarRes){
		mod =  (double)tarRes / _resolution;
	}
	CommandHit* cmd = new CommandHit(target, this->getId(), mod * myrandom(_dmgMin, _dmgMax), _dmgType, shield, x, y);;
	if(networkControl->addCommandToProcesable(cmd, this->getId()))
		delete cmd;
	//obj->Hit(this, );
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

