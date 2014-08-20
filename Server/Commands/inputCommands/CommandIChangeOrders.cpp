/* 
 * File:   CommandIChangeOrders.cpp
 * Author: karsten
 * 
 * Created on 15. august 2014, 23:54
 */

#include "CommandIChangeOrders.h"
#include "../../Sspacebjects/SShip.h"

CommandIChangeOrders::CommandIChangeOrders(uint32_t shipId, uint32_t ordreId,  uint32_t clientId) :
Command(0){
	_shipId = shipId;
	_ordreId  = ordreId;
	_clientId = clientId;
}

uint32_t CommandIChangeOrders::execute(){
	
	cerr<<"execute CommandIChangeOrders"<<endl;

	Processable *tproc = _processor->getLocalProcssable(_shipId);
	if (!tproc)
		return COMMAND_FINAL;
	SShip* ship = tproc->isShip();
	if (!ship)
		return COMMAND_FINAL;
	
	//TODO CHECK TEAM
	//if(unit->getTeam() != _client->getTeamId())
	//	break;


	ship->setOrdres(globalOrders[1][_ordreId]);
	return COMMAND_FINAL;
}


CommandIChangeOrders::~CommandIChangeOrders() {
}

