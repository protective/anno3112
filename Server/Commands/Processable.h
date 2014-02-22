/* 
 * File:   Processable.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 22:25
 */

#ifndef PROCESSABLE_H
#define	PROCESSABLE_H
#include "Command.h"
class Processable {
public:
	Processable();
	uint32_t addCommand(Command* cmd);
	uint32_t removeCommand(Command* cmd);

	virtual ~Processable();
private:
	Processor* _processor;

};

#endif	/* PROCESSABLE_H */

