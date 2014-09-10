/* 
 * File:   SFighter.cpp
 * Author: karsten
 * 
 * Created on 25. januar 2014, 22:33
 */

#include "SFighter.h"
#include "../World/SGrid.h"
#include "../Commands/CommandEnterGrid.h"
#include "../Commands/CommandExitGrid.h"
#include "../Commands/CommandSignalFighter.h"
#include "SMetaObj.h"

SFighter::SFighter(uint32_t id, SPos& pos, SFighterType& stype, uint32_t playerId, uint32_t mothership, uint32_t motherShipSub):
SUnit(id,pos, stype, playerId){
	_fType = &stype;
	_order = globalOrders[playerId][1];
	_motherShip = mothership;
	_motherShipSub = motherShipSub;
	_motherShipTarget = 0;
	_curSignal = FighterSignal::target;
	this->addCommand(new CommandEnterGrid(0,pos.grid->getId(),id));
}

void SFighter::setFighterSignal(FighterSignal::Enum signal){
	this->_curSignal = signal;
	if(this->_curSignal == FighterSignal::returnToShip){
		cerr<<"set signal id ="<<this->_id<<" signal return"<<endl;
		this->setOrdres(globalOrders[this->_playerId][0]);
		
		SMetaObj* mothership = NULL;
		mothership = _processor->getMeta(_motherShip);
	}
}

void SFighter::proces(uint32_t delta, Processor* processor){
	SUnit::proces(delta,processor);
	
	if(_targetUpdateCounter % 25 == 0 && _curSignal == FighterSignal::returnToShip){
		SMetaObj* mothership = NULL;
		mothership = processor->getMeta(_motherShip);
		if(mothership){
		
			if(this->_curSignal == FighterSignal::returnToShip){
				this->setTargetPos(mothership->getPos()->x,mothership->getPos()->y );
			}
			if(Rangeobj(*mothership->getPos(), this->_pos) < 50){
				CommandSignalFighter* cmd = new CommandSignalFighter(_motherShip,_id, FighterSignal::haveReturned,_motherShipSub);
				if(networkControl->addCommandToProcesable(cmd,_motherShip))
					delete cmd;
				this->_hull = 0;
				
				cerr<<"fighter dock id="<<_id<<" subid ="<<_motherShipSub<<endl;
				sendRemoved(SubscriptionLevel::lowFreq, DestroyMode::Vanish);
				
				this->addCommand(new CommandExitGrid(0,this->_pos.grid->getId(),_id));
				this->_pos.grid = NULL;
				this->addCommand(new CommandRemove(0,this));
			}
		}
	}
}

void SFighter::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){
	cerr<<"subscribe fighter clid ="<<clientId<<endl;
	this->sendFull(clientId);
	_subscriptions[level].push_back(clientId);
}

SFighter::~SFighter() {
}

