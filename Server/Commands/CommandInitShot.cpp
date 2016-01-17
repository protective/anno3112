/* 
 * File:   CommandInitShot.cpp
 * Author: karsten
 * 
 * Created on 18. maj 2014, 18:52
 */

#include "CommandInitShot.h"
#include "../Sspacebjects/SShot.h"
#include "../Sspacebjects/subsystems/SSubTypeWep.h"
#include "CommandProcessor.h"
#include "../Sspacebjects/SMetaObj.h"
#include "../World/SWorld.h"


CommandInitShot::CommandInitShot(uint32_t shotid) :
Command(world->getTime()){
	_shot = shotid;
}

uint32_t CommandInitShot::execute(){
	cerr<<"execute init shot"<<endl;
	Processable* temp = _processor->getLocalProcssable(_shot);
	if (!temp || !temp->isShot())
		return COMMAND_FINAL;
	
	SShot* shot  = temp->isShot();
	SSubTypeWep* type = temp->isShot()->getType();
	SMetaObj* metaTarget;
	/*
	if(metaTarget = _processor->getMeta(shot->_target)){
		uint32_t r = Rangeobj(shot->_pos,*(metaTarget->getPos()));
		uint32_t m = (r * type->getSpread()*50)/(type->getRange()/1000);

		m = myrandom(0,m);
		uint32_t theta = myrandom(0,359);
		int32_t rx = m * MyCos[theta];
		int32_t ry =  m * MySin[theta];
		uint32_t gamma = myrandom(0,359);
		int32_t rz = m * MyCos[gamma];

		int32_t expFlightTime = (((r*100)/type->getSpeed()))+1;
		int32_t preX = metaTarget->getPos()->x; 
		int32_t preY = metaTarget->getPos()->y;
*/
		//TODO HMM problem
		/*
		if(metaTarget->isMovable()){
			int32_t td = metaTarget->getPos().d;  
			int32_t tspeed = metaTarget->isMovable()->getSpeed() * expFlightTime;
			preX += (VektorUnitX(td/100) * tspeed)/100;
			preY += -((VektorUnitY(td/100)* tspeed)/100);
		}
		

		shot->_targetPos.x = rx + preX;
		shot->_targetPos.y = ry + preY;
		
		shot->_targetPos.z = 0;
		cerr<<"rx "<<shot->_targetPos.x<<" ry "<<shot->_targetPos.y<<endl;
		shot->_targetPos.grid = metaTarget->getPos()->grid;
		shot->_pos.d = 100 * Direction(shot->_pos, shot->_targetPos);
		shot->_targetPos.d = shot->_pos.d;
		
				//(100 * Deg(shot->_targetPos.x-shot->_pos.x,shot->_targetPos.y-shot->_pos.y));
		shot->_moveZ = Deg(r*100,rz);

	}
		 * */
	return COMMAND_FINAL;
}

CommandInitShot::~CommandInitShot() {
}

