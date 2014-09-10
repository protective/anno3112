/* 
 * File:   CommandSignalFighter.cpp
 * Author: karsten
 * 
 * Created on 28. august 2014, 22:13
 */

#include "CommandSignalFighter.h"
#include "Processable.h"
#include "Processor.h"
#include "../Sspacebjects/SFighter.h"
#include "../Sspacebjects/SShip.h"

CommandSignalFighter::CommandSignalFighter(OBJID toId, OBJID fighter, FighterSignal::Enum signal, uint32_t signalParam) :
Command(0){
	_toId = toId;
	_fighterId = fighter;
	_signal = signal;
	_signalParam = signalParam;	
}


uint32_t CommandSignalFighter::execute(){
	cerr<<"execute CommandSignalFighter toid="<<_toId<<endl;
	Processable* temp = _processor->getLocalProcssables()[_toId];
	
	if(!temp )
		return COMMAND_FINAL;
	
	if(temp->isFighter()){
		temp->isFighter()->setFighterSignal(_signal);
		switch (_signal){
			case FighterSignal::target :{
				temp->isFighter()->setMotherShipTarget(_signalParam);
				break;}

			case FighterSignal::returnToShip :{
				temp->isFighter()->setMotherShipTarget(0);	
				break;}
			default:{

			}
		}
	}else if(temp->isShip()){
		cerr<<"is ship signal="<<_signal<<endl;
		switch (_signal){
		case FighterSignal::haveReturned :{
			cerr<<"signal dock"<<endl;
			SSlotNode* tempSN = NULL;
			if(temp->isShip()->getSlots().find(_signalParam) != temp->isShip()->getSlots().end())
				tempSN = temp->isShip()->getSlots().find(_signalParam)->second;
			if(tempSN && tempSN->getSS() && tempSN->getSS()->isFighter())
				tempSN->getSS()->isFighter()->recoverFighter(_fighterId);
			break;}
		default:{

			}
		}
		
	}

	return COMMAND_FINAL;
}



CommandSignalFighter::~CommandSignalFighter() {
	
	
}

