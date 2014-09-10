/* 
 * File:   CommandOrderThread.h
 * Author: karsten
 *
 * Created on 4. september 2014, 22:14
 */

#ifndef COMMANDORDERTHREAD_H
#define	COMMANDORDERTHREAD_H

#include "../../Commands/Command.h"
#include "SOrdreProgram.h"
#include "Utils/SOrderVar.h"
class CommandOrderThread : public Command {
public:
	CommandOrderThread(SOrdreProgram* program, OBJID obj);
	virtual Processable* getProcessable(){return NULL;} //TODO FIX
	virtual uint32_t execute();
	void pushStack(SOrderVar* var){
		_stack.push_back(var);
	}
	/*
	SOrderVar* popStack(){
		SOrderVar* t = _stack.back();
		_stack.pop_back();
		return t;
	}
	void pushProgramStack(SOrderNode* node){
		_programStack.push_back(node);
	}
	 * */
	virtual ~CommandOrderThread();
private:

	uint32_t _mipsCredit;
	TIME _lastExeTime;
	OBJID _obj;
	SOrdreProgram* _program;
	uint32_t _programCounter;
	//list<SOrderNode*> _programStack;
	vector<SOrderVar*> _stack;
	
};

#endif	/* COMMANDORDERTHREAD_H */

