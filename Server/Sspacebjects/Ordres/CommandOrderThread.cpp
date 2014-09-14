/* 
 * File:   CommandOrderThread.cpp
 * Author: karsten
 * 
 * Created on 4. september 2014, 22:14
 */

#include "CommandOrderThread.h"
#include "SOrdreProgram.h"
#include "Compiler/CommandCompiler.h"
#include "../../World/SWorld.h"
CommandOrderThread::CommandOrderThread(SOrdreProgram* program, OBJID obj):
Command(0){
	_program = program;
	_obj = obj;
	cerr<<"_obj"<<obj<<endl;
	_programCounter = 0;
	_stackTop = 0;
	_mipsCredit = 0;
	_stack = (uint32_t*)malloc(sizeof(uint32_t) * 100);
}


uint32_t CommandOrderThread::execute(){
	cerr<<"execure CommandOrderThread"<<endl;
	_mipsCredit = 5;
	
	while(_mipsCredit){
		
		_mipsCredit--;
		uint32_t ins = _program->program()[_programCounter];
		switch(OPCODE(ins)){
			case inst::pushN_1:{
				for(int i = 0 ; i < ARG(ins);i++){
					_stack[_stackTop] = _program->program()[_programCounter+1];
					_stackTop++;
				}
				_programCounter += 2;
				break;
			}
			case inst::popN:{
				_stackTop-= ARG(ins);
				_programCounter += 1;
				break;
			}
			case inst::sysCall:{
				uint32_t stackArg = _program->program()[_programCounter+1];
				GlobalSystemCallLib[ARG(ins)]._systemCallFunc(_processor,_obj,(void*)(&_stack[_stackTop - stackArg]));
				_programCounter += 2;
				break;
			}
			
			case inst::addS01dS1:{
				_stackTop--;
				_stack[_stackTop-1] = _stack[_stackTop-1] + _stack[_stackTop];
				_programCounter += 1;
				break;
			}
			case inst::EOP:{
				
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
	_time = world->getTime()+1000;
	return COMMAND_REPEAT;
}

//void CommandOrderThread::systemSetSubsystemFlags(void* arg){

//}
CommandOrderThread::~CommandOrderThread() {
}

