/* 
 * File:   Processable.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 22:25
 */

#ifndef PROCESSABLE_H
#define	PROCESSABLE_H
#include "../SFunctions.h"
#include "Command.h"
#include "CommandAddSubscriptions.h"
#include "CommandUpdateMetas.h"
#include "CommandTimedSubscribeUpdate.h"
class SMetaObj;
class Processor;
class SUnit;
class Processable {
public:
	Processable();
	uint32_t addCommand(Command* cmd);
	uint32_t removeCommand(Command* cmd);
	Processor* getProcessor(){return _processor;}
	void setProcessor(Processor* processor){_processor = processor;}
	virtual bool isMetable(){return false;}
	virtual SUnit* isUnit(){return NULL;}
	virtual SObj* isObj(){return NULL;}
	virtual void getMetaObj(SMetaObj* metaobj){}
	virtual void proces(uint32_t delta, Processor* processor ) = 0;
	virtual void subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level) = 0;
	virtual uint32_t getId() = 0;
	virtual list<Command*>& getLocalQueue(){return _localQueue;}
	virtual ~Processable();
protected:
	Processor* _processor;
	list<Command*> _localQueue;
};

#endif	/* PROCESSABLE_H */

