/* 
 * File:   CommandExitGrid.h
 * Author: karsten
 *
 * Created on 10. maj 2014, 13:53
 */

#ifndef COMMANDEXITGRID_H
#define	COMMANDEXITGRID_H
#include "Command.h"

class CommandExitGrid : public Command {
public:
	CommandExitGrid(uint32_t time, uint32_t grid, uint32_t obj);
	virtual uint32_t execute();
	virtual ~CommandExitGrid();
private:
	uint32_t _grid;
	uint32_t _obj;
};

#endif	/* COMMANDEXITGRID_H */

