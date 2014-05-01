/* 
 * File:   CommandEnterGrid.cpp
 * Author: karsten
 * 
 * Created on 18. april 2014, 20:57
 */

#include "CommandEnterGrid.h"
#include "../World/SGrid.h"
CommandEnterGrid::CommandEnterGrid(uint32_t time, SGrid* grid, SUnit* unit): 	
Command(time){
	_grid = grid;
	_unit = unit;
}

uint32_t CommandEnterGrid::execute(){
	_grid->addUnit(_unit);
	return COMMAND_FINAL;
}

CommandEnterGrid::~CommandEnterGrid() {
}

