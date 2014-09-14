#include "CommandCompiler.h"


void CommandCompiler::emitPopStack(uint32_t size){
	if(size){
		//coppy top stack to the rel loc 
		program().push_back(inst::popN | size);
		this->_scopeRef.back() -= size;
	}
}

void CommandCompiler::emitPopTopStackToLoc(uint32_t pos, uint32_t size){
    //coppy top stack to the rel loc
    program().push_back(inst::cpN_FT2 | size);
    program().push_back(relpos(pos)); //copy to
    program().push_back(0x00); //copy from
    
    //pop top of stack
    program().push_back(inst::popN | size);
    this->_scopeRef.back() -= size;
}

void CommandCompiler::emitTopStackToLoc(uint32_t pos, uint32_t size){

    //coppy top stack to the rel loc 
    program().push_back(inst::cpN_FT2 | size);
    program().push_back(relpos(pos)); //copy to
    program().push_back(0x00); //copy from
}


void CommandCompiler::emitPushStack(uint32_t value, uint32_t size){
    program().push_back(inst::pushN_1 | size);
    program().push_back(value); //value to push
    _scopeRef.back()+= size;
}

void CommandCompiler::emitPushTopStackNtimesToStack( uint32_t size){
    program().push_back(inst::pushS0N | size);
    _scopeRef.back()+= size;
}

void CommandCompiler::emitSysCall(uint32_t pos){
	program().push_back(inst::sysCall);
	program().push_back(relpos(pos));
}

void CommandCompiler::emitPushLocToTopStack(uint32_t pos, uint32_t size){
    
    //coppy loc to top stact
    program().push_back(inst::pushN | size);
    _scopeRef.back() += size;
    program().push_back(inst::cpN_FT2 | size);
    program().push_back(size - 1); //copy to
    program().push_back(relpos(pos)); //copy from
}

uint32_t CommandCompiler::emitJumpToRef(){
    program().push_back(inst::jmpA_1);
    program().push_back(0x00);
    return program().size() - 1;
}

uint32_t CommandCompiler::emitCondJumpToRef(){
    program().push_back(inst::cjmpA_1);
    program().push_back(0x00);
    return program().size() - 1;
}

uint32_t CommandCompiler::emitJumpToRef(uint32_t ref){
    program().push_back(inst::jmpA_1);
    program().push_back(ref);
    return ref;
}

uint32_t CommandCompiler::emitCondJumpToRef(uint32_t ref){
    program().push_back(inst::cjmpA_1);
    program().push_back(ref);
    return ref;
}

void CommandCompiler::emitBOAddPush(){
	program().push_back(inst::addS01);
	_scopeRef.back() += 1;
}

void CommandCompiler::emitBOMinusPush(){
	program().push_back(inst::minusS01);
	_scopeRef.back() += 1;
}

void CommandCompiler::emitBOAddPop(){
	program().push_back(inst::addS01dS1);
	_scopeRef.back() -= 1;
}

void CommandCompiler::emitBOMinusPop(){
	program().push_back(inst::minusS01dS1);
	_scopeRef.back() -= 1;
}