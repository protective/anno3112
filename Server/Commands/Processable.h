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
	Processable(uint32_t id);
	uint32_t addCommand(Command* cmd);
	uint32_t removeCommand(Command* cmd);
	uint32_t getId();
	virtual ~Processable();
protected:
	uint32_t _id;
	Processor* _processor;

};

#endif	/* PROCESSABLE_H */

