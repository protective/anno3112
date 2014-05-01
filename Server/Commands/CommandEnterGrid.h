/* 
 * File:   CommandEnterGrid.h
 * Author: karsten
 *
 * Created on 18. april 2014, 20:57
 */

#ifndef COMMANDENTERGRID_H
#define	COMMANDENTERGRID_H

#include "Command.h"

class SGrid;
class SUnit;
class CommandEnterGrid : public Command {
public:
	CommandEnterGrid(uint32_t time, SGrid* grid, SUnit* unit);
	virtual uint32_t execute();
	virtual ~CommandEnterGrid();
private:
	SGrid* _grid;
	SUnit* _unit;
	
};

#endif	/* COMMANDENTERGRID_H */

