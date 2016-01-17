/* 
 * File:   CommandEnterGrid.cpp
 * Author: karsten
 * 
 * Created on 18. april 2014, 20:57
 */

#include "CommandEnterGrid.h"
#include "../World/SGrid.h"
#include "../World/SWorld.h"

CommandEnterGrid::CommandEnterGrid(uint32_t time, uint32_t grid, SMetaObj* meta): 	
Command(world->getTime()){
	_grid = grid;
	_meta = meta;
}

uint32_t CommandEnterGrid::execute(){
	//cerr<<"execute enter grid"<<endl;
	Processable* temp = _processor->getLocalProcssable(_grid);
	if (!temp || !temp->getGrid())
		return COMMAND_FINAL;
	temp->getGrid()->addObj(_meta);
	return COMMAND_FINAL;
}

CommandEnterGrid::~CommandEnterGrid() {
}

