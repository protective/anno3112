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
SObj(id, pos,owner->obj()->getTeam(),owner->obj()->getPlayerId()), SMovable(this,0,0), STargetable(this), Processable()
{

	//this->_owner = owner;
	this->_target = target;
	this->_texId = type->getTexId();
	this->_resolution = type->getResolution(owner->getBonusList());
	
	_type = type;
	_hasHit = false;
	_dmgMin = type->getDmgMin(owner->getBonusList());
	_dmgMax = type->getDmgMax(owner->getBonusList());
	_hp = type->getHp();
	_speed = type->getSpeed();
	_dmgType = type->getDmgTypes();
	_tracking = type->getTracking();
	_trackingTime = type->getTrackingTime();
	_flightTime = 0;
	_maxFlightTime = (((type->getRange()/type->getSpeed()))+1)*4;
	_size = 2000;
	
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
		int32_t expFlightTime = (((r*100)/type->getSpeed())) - (((r*100)/10000));
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

void SShot::useDamage(uint32_t damage){
	cerr<<"use min="<<_dmgMin<<" damage="<<damage <<endl;
	if(damage == 0){
		_hasHit = true;
	}else if(damage < _dmgMin){
		_dmgMin -= damage;
		_dmgMax -= damage;
	}else{
		ParticalTex::Enum tex;
		tex= ParticalTex::Invalid;
		sendTargetHit(SubscriptionLevel::lowFreq, _id, tex, 0, 0);

		_hasHit = true;
	}
}

void SShot::applyDamage(uint32_t target, Shields::Enum shield, int32_t x, int32_t y){
	SMetaObj* obj = _processor->getLocalMetas()[target];
	uint32_t tarRes = obj->getTargetSize()/100;
	double mod = 1;
	if(_resolution > tarRes){
		mod =  (double)tarRes / _resolution;
	}
	CommandHit* cmd = new CommandHit(target, this->getId(), 0, mod * myrandom(_dmgMin, _dmgMax), _dmgType, shield, x, y);
	if(networkControl->addCommandToProcesable(cmd, target))
		delete cmd;
	//obj->Hit(this, );
}

uint32_t SShot::hit(uint32_t shot, OBJID owner, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y) {
	//TODO fix report hit

	if(dmg > _hp){
		_hasHit = true;
		ParticalTex::Enum tex;
		tex= ParticalTex::eks7l;
		sendTargetHit(SubscriptionLevel::lowFreq, _id, tex, x, y);
	}else{
		_hp -= dmg;
	}
	return min(dmg,_hp);
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

