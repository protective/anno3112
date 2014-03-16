/* 
 * File:   Processable.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 22:25
 */

#ifndef PROCESSABLE_H
#define	PROCESSABLE_H
#include "../SFunctions.h"

class Command;
class SMetaObj;

class Processable {
public:
	Processable(uint32_t id);
	uint32_t addCommand(Command* cmd);
	uint32_t removeCommand(Command* cmd);
	Processor* getProcessor(){return _processor;}
	virtual bool isMetable(){return false;}
	virtual void getMetaObj(SMetaObj* metaobj){}
	virtual void proces(uint32_t delta){}
	uint32_t getId();
	virtual ~Processable();
protected:
	uint32_t _id;
	Processor* _processor;

};

#endif	/* PROCESSABLE_H */

