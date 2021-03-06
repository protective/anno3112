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
	CommandEnterGrid(uint32_t time, uint32_t grid, uint32_t obj);
	virtual uint32_t execute();
	virtual ~CommandEnterGrid();
private:
	uint32_t _grid;
	uint32_t _obj;
	
};

#endif	/* COMMANDENTERGRID_H */

