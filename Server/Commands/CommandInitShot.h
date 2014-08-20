/* 
 * File:   CommandInitShot.h
 * Author: karsten
 *
 * Created on 18. maj 2014, 18:52
 */

#ifndef COMMANDINITSHOT_H
#define	COMMANDINITSHOT_H

#include "Command.h"


class CommandInitShot : public Command {
public:
	CommandInitShot(uint32_t shotid);
	virtual uint32_t execute();
	virtual ~CommandInitShot();
private:
	uint32_t _shot;
};

#endif	/* COMMANDINITSHOT_H */

