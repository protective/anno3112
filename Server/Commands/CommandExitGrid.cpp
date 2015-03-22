/* 
 * File:   CommandExitGrid.cpp
 * Author: karsten
 * 
 * Created on 10. maj 2014, 13:53
 */

#include "CommandExitGrid.h"
#include "../World/SGrid.h"
#include "../World/SWorld.h"
CommandExitGrid::CommandExitGrid(uint32_t time, uint32_t grid, uint32_t obj): 	
Command(world->getTime()){
	_grid = grid;
	_obj = obj;
}

uint32_t CommandExitGrid::execute(){
	Processable* temp = _processor->getLocalProcssable(_grid);
	if (!temp || !temp->getGrid())
		return COMMAND_FINAL;
	temp->getGrid()->removeObj(_obj);
	return COMMAND_FINAL;
}

CommandExitGrid::~CommandExitGrid() {
}

