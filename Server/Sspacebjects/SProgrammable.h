/* 
 * File:   SProgrammable.h
 * Author: karsten
 *
 * Created on 24. september 2014, 19:34
 */

#ifndef SPROGRAMMABLE_H
#define	SPROGRAMMABLE_H
#include "../SFunctions.h"
#include "SObj.h"

namespace registerFlags{
	enum Enum{
		Yeld = 0x00000001
	};
}

class SOrdreProgram;
class SProgrammable  {
public:
	SProgrammable(OBJID obj);
	
	virtual uint32_t execute(Command* cmd);
	virtual uint32_t getId() = 0;
	virtual SUnit* isUnit() = 0;
	uint32_t segfault();
	void setProgram(SOrdreProgram* program){_program = program;}
	void dumpStack();
	virtual void interrupt(uint32_t programId, uint32_t handlerId, uint32_t* payload, uint32_t payloadLen);
	void yeld(){_registerFlags |= registerFlags::Yeld;}
protected:
	SOrdreProgram* getProgram(){return _program;}

	void loadProgram(SOrdreProgram* program);
private:
	uint32_t _registerFlags;
	uint32_t _mipsCredit;
	TIME _lastExeTime;
	OBJID _obj;
	
	SOrdreProgram* _program;
	uint32_t _programCounter;
	uint32_t _stackTop;

	uint32_t* _stack;
	uint32_t _stackMax;

};

#endif	/* SPROGRAMMABLE_H */

