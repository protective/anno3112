/* 
 * File:   SShot.cpp
 * Author: karsten
 * 
 * Created on 2. juli 2011, 14:23
 */

//#include <math.h>
//#include <c++/4.3/cmath>

#include <sys/types.h>

#include "SShot.h"
#include "SSubAble.h"
#include "SMetaObj.h"
#include "../World/SGrid.h"
#include "../World/SWorld.h"
#include "../NetworkLayer/SShotNetworkLayer.h"

#include "../Commands/CommandRemove.h"
#include "../Commands/CommandEnterGrid.h"
#include "../Commands/CommandHit.h"
#include "../Commands/CommandMetaHit.h"

SShot::SShot(uint32_t id, SPos& pos, SSubAble* owner, uint32_t target, SSubTypeWep* type, Processor* creator):
SObj(id, pos,owner->obj()->getTeam(),owner->obj()->getPlayerId()), SMovable(this,0,0), STargetable(this), Processable()
{

	this->_owner = owner->obj()->getId();
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
	_maxFlightTime = (((type->getRange() / type->getSpeed())) + 1) * 4;
	_size = 2000;
	
	SMetaObj* metaTarget;
	Destiny* destiny = pos.grid->getDestiny();
	if(metaTarget = pos.grid->getMetaInGrid(this->_target)){
		//cerr<<"target found"<<endl;
		SPos deltaPos;
		destiny->getPos(deltaPos, this->_target);

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
		//_maxFlightTime = expFlightTime;
		//TODO HMM problem
		
		if(metaTarget->isMoveable()){
			//int32_t td = metaTarget->getPos().d;  
			//int32_t tspeed = metaTarget->isMovable()->getSpeed() * expFlightTime;
			//preX += (metaTarget->vecX * expFlightTime) / 1;
			//preY += (metaTarget->vecY * expFlightTime) / 1;
			
			double v = type->getSpeed();
			double tx = (deltaPos.x - this->_pos.x) / 1000,
			ty = (deltaPos.y - this->_pos.y)/ 1000,
			tvx = metaTarget->vecX,
			tvy = metaTarget->vecY;
			// Get quadratic equation components
			double a = tvx*tvx + tvy*tvy - v*v;
			double b = 2 * (tvx * tx + tvy * ty);
			double c = tx*tx + ty*ty; 
			bool solf = false; 
			double sol[2];
			sol[0] = deltaPos.x;
			sol[1] = deltaPos.y;			
			if (abs(a) < 0.000000f) {
				if (abs(b) < 0.000000f) {
					if(c == 0){
						sol[0] = 0;
						sol[1] = 0;
						solf = true;
					}
				} else {
					sol[0] = -c/b;
					sol[1] = -c/b;
					solf = true;
				}
			} else {
				double disc = b*b - 4*a*c;
				if (disc >= 0) {
					disc = sqrt(disc);
					a = 2*a;
					sol[0] = (-b-disc)/a;
					sol[1] = (-b+disc)/a;
					solf = true;
				}
			}

			if (solf) {
				double t0 = sol[0], t1 = sol[1];
				double t = min(t0, t1);
				if (t < 0)
					t = max(t0, t1);    
				if (t > 0) {
					sol[0] = (deltaPos.x) + (t*metaTarget->vecX*1000);
					sol[1] = (deltaPos.y) + (t*metaTarget->vecY*1000);
				}
			}
			this->_targetPos.x = (int32_t)sol[0] + rx;
			this->_targetPos.y = (int32_t)sol[1] + ry;
		}else{
			this->_targetPos.x = rx + preX;
			this->_targetPos.y = ry + preY;
		}
		
		this->_targetPos.z = 0;
		this->_targetPos.grid = deltaPos.grid;
		this->_pos.d = 100 * Direction(this->_pos, this->_targetPos);
		this->_targetPos.d = this->_pos.d;
		
				//(100 * Deg(shot->_targetPos.x-shot->_pos.x,shot->_targetPos.y-shot->_pos.y));
		this->_moveZ = Deg(r*100, rz);
	
	}
	//this->addCommand(new CommandInitShot(id));
	SGrid* tempgrid =  world->getGrids().begin()->second;
	SMetaObj* meta = new SMetaObj(id, this->getTeam(), this->getSize(), this->getTargetType(), this->_owner);
	this->addCommand(new CommandEnterGrid(0,tempgrid->getId(), meta));
					
}

void SShot::proces(uint32_t delta, Processor* processor){
	//cerr<<"proces shot delta="<<delta<<endl;
	this->Move(delta);
	
	list<OBJID> tmp = this->_pos.grid->getDestiny()->inRange(this, this->getSize() / 2);
	
	if (tmp.size() > 0 ) {
		//cerr<<"HIT size "<<tmp.size()<<endl;
		this->checkCollisions(tmp);
		
	}
	if(canBeRemoved())
		this->addCommand(new CommandRemove(0,this));
}

void SShot::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){
	_subscriptions[level].push_back(clientId);
	this->sendFull(level);
	
}


void SShot::Move(uint32_t deltaT){

	if(_trackingTime){
		int32_t targetDir = 0;
		int32_t b;
		Destiny* destiny = this->getPos().grid->getDestiny();
		SPos targetPos;
		if (destiny->getPos(targetPos, _target)){
			targetDir = 100* Direction(this->_pos, targetPos);
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
	}
	this->MovePos((VektorUnitX(this->_pos.d/100) * _speed * deltaT)/40,-(VektorUnitY(this->_pos.d/100)* _speed* deltaT)/40,(VektorUnitY(this->_moveZ)*_speed*deltaT)/40);
	_flightTime+=deltaT;
	this->_pos.grid->getDestiny()->update(this);
	//if(deltaT)
		//this->TestHit();
}

bool SShot::canBeRemoved(){
	
	if (_hasHit || _flightTime >= _maxFlightTime){
		return true;
	}else
		return false;
}

void SShot::useDamage(uint32_t damage){
	//cerr<<"use min="<<_dmgMin<<" damage="<<damage <<endl;
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
	map<uint32_t, SMetaObj*>::iterator found = this->getPos().grid->getMetaInGrid().find(target);
	if(found == this->getPos().grid->getMetaInGrid().end())
		return;
	SMetaObj* obj = found->second;
	uint32_t tarRes = obj->getTargetSize()/100;
	double mod = 1;
	if(_resolution > tarRes){
		mod =  (double)tarRes / _resolution;
	}
	
	CommandHit* cmd = new CommandHit(target, this->getId(), _owner, mod * myrandom(_dmgMin, _dmgMax), _dmgType, shield, x, y);
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

void SShot::checkCollisions(list<OBJID> objs){

	SGrid* grid = this->getPos().grid;
	Destiny* destiny = grid->getDestiny();
	//cerr<<"HIT "<<endl;
	for (list<OBJID>::iterator it = objs.begin(); it != objs.end(); it++) {
		SMetaObj* target = grid->getMetaInGrid(*it);
		SPos targetPos;


		if(!target || target->getTeam() == this->getTeam()){
			continue;
		}
		bool found = false;
		for (list<OBJID>::iterator it2 = _hitlist.begin(); it2 != _hitlist.end(); it2++) {
			if(*it2 == *it){
				found = true;
				break;
			}
		}
		if (found)
			continue;
		
		destiny->getPos(targetPos, *it);
		int32_t negsize = 0-target->getTargetSize();
		int32_t possize = target->getTargetSize();
		if (this->getPos().z > (negsize)/2 && this->getPos().z < possize/2) {
			
			int32_t size = (target->getTargetSize()/2);
			//cerr<<"size="<<size<<endl;
			//cerr<<"oobj->getPos().x="<<oobj->getPos().x<<"oobj->getPos().y="<<oobj->getPos().y<<endl;
			//cerr<<"temppos.x="<<temppos.x<<"temppos.y="<<temppos.y<<endl;
			if (!(targetPos.x > this->getPos().x - size && targetPos.x < this->getPos().x + size
			&& targetPos.y > this->getPos().y - size && targetPos.y < this->getPos().y + size)) {
				//cerr<<"cont"<<endl;
				continue;
			}
			
			double a = 100 * Rangeobj(this->getPos(), this->getPos());
			if (target->getTargetType() == TargetType::Invalid) {
				continue;
			}
			if (a >= target->getTargetSize() / 2) {
				continue;
			}
			double movementX = 0; //this->vecX; //(VektorUnitX(this->pos.d/100) * this->getSpeed());
			double movementY = 0; //this->vecY; // (-(VektorUnitY(this->pos.d/100) * this->getSpeed()));
			int32_t x1 = this->getPos().x - targetPos.x;
			int32_t y1 = this->getPos().y - targetPos.y;
			int32_t x2 = this->getPos().x + movementX - targetPos.x;
			int32_t y2 = this->getPos().y + movementY - targetPos.y;
			int32_t dx = x2 - x1;
			int32_t dy = y2 - y1;
			double dr = sqrt((dx*dx)+(dy*dy));
			double D = x1*y2 - x2*y1;
			double dis = ((target->getTargetSize() / 2)*  (target->getTargetSize() / 2)) * (dr * dr) - (D * D);

			if (dis >= 0 ) {// || _flightTime <= 1){//hit
				double hitx = ((D *dy -dx * (sqrt(pow((target->getTargetSize()/2),2) * pow(dr,2)- pow(D,2))))/ pow(dr,2));
				double hity = ((-D *dx -dy * (sqrt(pow((target->getTargetSize()/2),2) * pow(dr,2)- pow(D,2))))/ pow(dr,2));
				double H_x = (target->getTargetSize()/2);
				double H_y = 0;

				double P_x = hitx;
				double P_y = hity;

				double ph = Rangecord(H_x,H_y,P_x,P_y);
				double ch =(target->getTargetSize()/2);
				double cp = Rangecord(0,0,P_x,P_y);
				double rad = 0;
				if (2*cp*ch)
					rad = acos(((ch*ch)+(cp*cp)-(ph*ph))/(2*cp*ch));
				double V = (rad/3.14)*180;

				if( P_y > H_y)
					V = 360 - V;

				double V2 = V - (targetPos.d / 100);

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
				cerr<<"hit i="<<i<<endl;
				//cerr<<"meta shot hit"<<endl;
				_hitlist.push_back(*it);
				networkControl->addCommandToProcesable(new CommandMetaHit(_id, *it,(Shields::Enum)i,0,0), _id);
				//Hit(it->first, (Shields::Enum)i,0,0);
			}
		}	
	}
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

