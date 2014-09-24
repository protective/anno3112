
#include "SProgrammable.h"

#include "Ordres/SOrdreProgram.h"

#include "Ordres/SOrdersSystemCalls.h"
#include "../World/SWorld.h"

namespace registerFlags{
	enum Enum{
		Yeld = 0x00000001
	};
}

SProgrammable::SProgrammable(OBJID obj){
	_registerFlags = 0;
	_mipsCredit = 0;
	_lastExeTime = 0;
	_obj = obj;
	_program = NULL;
	_programCounter = 0;
	_stackTop = 0;
	_stack = (uint32_t*)malloc(sizeof(uint32_t)* 100);
	_stackMax = 100;
}

void SProgrammable::interrupt(uint32_t programId, uint32_t handlerId, uint32_t* payload, uint32_t payloadLen){
	if(_program->getInterruptHandlers().find(handlerId) == _program->getInterruptHandlers().end()){
		cerr<<"SProgrammable::interrupt ERROR handler not found "<<endl;
		return;
	}	
	memcpy(_stack + _stackTop+1, payload, payloadLen);
	_stackTop+= payloadLen;

	_stackTop +=1;
	_stack[_stackTop] = _programCounter;
	_programCounter = _program->getInterruptHandlers()[handlerId];
}

uint32_t SProgrammable::segfault(){
	cerr<<"SEGFAULT PC ="<<_programCounter<<" stack top ="<<_stackTop<<endl;
	cerr<<"stack"<<endl;
	dumpStack();
	free(_stack);
	return COMMAND_FINAL;
}

void SProgrammable::dumpStack(){
	for(int i = 0; i <= _stackTop ; i++){
		cerr<<_stack[i]<<endl;;
	}
	cerr<<"stack end"<<endl;
}

uint32_t SProgrammable::execute(Command* cmd){
	cerr<<"execure CommandOrderThread"<<endl;
	_mipsCredit = 10;

	
	while(_mipsCredit && _program){
		
		_mipsCredit--;
		if((_registerFlags & registerFlags::Yeld) > 0){
			_registerFlags &= ~registerFlags::Yeld;
			cerr<<"yeld"<<endl;
			return COMMAND_REPEAT;
		}
		
		uint32_t ins = _program->program()[_programCounter];
		cerr<<"exe line "<<std::hex<<_programCounter<<std::dec<<" stack top "<<_stackTop<<endl;
		dumpStack();
		switch(OPCODE(ins)){
			case inst::pushN_1:{
				for(int i = 0 ; i < ARG(ins);i++){
					if(_stackTop++ >= _stackMax)
						return segfault();
					_stack[_stackTop] = _program->program()[_programCounter+1];
				}
				_programCounter += 2;
				break;
			}
			case inst::jmpA_1:{
				if(_program->program()[_programCounter+1] >= _program->program().size())
					return segfault();
				_programCounter = _program->program()[_programCounter+1];
				cerr<<"program counter ="<<_programCounter<<endl;
				break;
			}
			case inst::pushPC:{
				if(_stackTop++ >= _stackMax)
					return segfault();			
				_stack[_stackTop] = _programCounter + 3; //skip next jump
	
				_programCounter += 1;
				break;
			}
			case inst::popPC:{
				if(_stackTop == 0)
					return segfault();
				_programCounter = _stack[_stackTop--];
				break;
			}
			case inst::cjmpA_1:{
				if (_stack[_stackTop]){
					if(_program->program()[_programCounter+1] >= _program->program().size())
						return segfault();
					_programCounter =  _program->program()[_programCounter+1];
				}else{
					_programCounter += 2;
				}
				break;
			}
			case inst::popN:{
				if(_stackTop < ARG(ins))
					return segfault();
				_stackTop-= ARG(ins);
				_programCounter += 1;
				break;
			}
			case inst::pushN:{
				_stackTop += ARG(ins);
				if(_stackTop >= _stackMax)
					return segfault();
				_programCounter += 1;
				break;
			}
			case inst::sysCall:{
				uint32_t stackArg = _program->program()[_programCounter+1];
				GlobalSystemCallLib[ARG(ins)]._systemCallFunc(cmd->getProcessor(),cmd,_obj,(void*)(&_stack[_stackTop - stackArg + 1]));
				_programCounter += 2;
				break;
			}
			
			case inst::addS01dS1:{
				if(_stackTop == 0)
					return segfault();
				_stack[_stackTop-1] = _stack[_stackTop-1] + _stack[_stackTop];
				_stackTop--;
				_programCounter += 1;
				break;
			}
			case inst::cpN_DS2:{
				uint32_t dest = _stackTop - _program->program()[_programCounter+1];
				uint32_t src = _stackTop - _program->program()[_programCounter+2];
				for(int i = 0 ; i< ARG(ins); i++){
					if(dest + i < _stackMax && src + i < _stackMax)
						_stack[dest + i] = _stack[src + i];
					else{
						return segfault();
					}
				}
				_programCounter += 3;
				break;
			}
			case inst::cpN_DRS2:{
				uint32_t dest =  _program->program()[_programCounter+1];
				uint32_t src = _stackTop - _program->program()[_programCounter+2];
				for(int i = 0 ; i< ARG(ins); i++){
					if(dest + i < _stackMax && src + i < _stackMax)
						_stack[dest + i] = _stack[src + i];
					else{
						return segfault();
					}
				}
				_programCounter += 3;
				break;
			}
			case inst::cpN_RDS2:{
				uint32_t dest = _stackTop - _program->program()[_programCounter+1];
				uint32_t src = _program->program()[_programCounter+2];
				for(int i = 0 ; i< ARG(ins); i++){
					if(dest + i < _stackMax && src + i < _stackMax)
						_stack[dest + i] = _stack[src + i];
					else{
						return segfault();
					}
				}
				_programCounter += 3;
				break;
			}
			case inst::NOP:{
				_programCounter += 1;
				break;
			}
			case inst::EOP:{
				cerr<<"EOP exit OK"<<endl;
				free(_stack);
				return COMMAND_FINAL;
				break;
			}
			default:{
				cerr<<"ERROR UNKNOW INSTRUCTION opcode "<<OPCODE(ins)<<endl;
				free(_stack);
				return COMMAND_FINAL;
			}
		}
	}
	cmd->setTime(world->getTime() +20 );
	return COMMAND_REPEAT;
}
