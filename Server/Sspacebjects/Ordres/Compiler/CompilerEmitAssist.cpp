#include "CommandCompiler.h"



void CommandCompiler::emitNOP(){
	program().push_back(inst::NOP);
}

void CommandCompiler::emitEOP(){
	program().push_back(inst::EOP);
}
void CommandCompiler::emitPopStack(uint32_t size){
	if(size){
		//coppy top stack to the rel loc 
		program().push_back(inst::popN | size);
		this->_scopeRef.back() -= size;
	}
}
void CommandCompiler::emitPopStackIgnore(uint32_t size){
	if(size){
		//coppy top stack to the rel loc 
		program().push_back(inst::popN | size);
	}
}

void CommandCompiler::emitPopTopStackToLoc(uint32_t pos, uint32_t size){
    //coppy top stack to the rel loc
    program().push_back(inst::cpN_DS2 | size);
    program().push_back(relpos(pos)); //copy to
    program().push_back(0x00); //copy from
    
    //pop top of stack
    program().push_back(inst::popN | size);
    this->_scopeRef.back() -= size;
}

void CommandCompiler::emitTopStackToLoc(uint32_t pos, bool rel, uint32_t size){

    //coppy top stack to the rel loc 
    program().push_back((rel ? inst::cpN_DS2: inst::cpN_DRS2) | size);
    program().push_back(rel ? relpos(pos): pos); //copy to
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
void CommandCompiler::emitCall(string name){
	program().push_back(inst::jmpA_1);
	program().push_back(0);
	_lables[program().size() -1] = name;
	return;

}

void CommandCompiler::emitPushPC(){
	program().push_back(inst::pushPC);
	return;
}
uint32_t CommandCompiler::emitPushRPC(){
	program().push_back(inst::pushRPC);
	program().push_back(0x00);
    return program().size() - 1;
}
void CommandCompiler::emitReturn(){
	/*
	 
	 */
	_scopeRef.back()-= 1; //push old pc
	program().push_back(inst::popPC);


}

void CommandCompiler::emitSysCall(uint32_t pos, uint32_t functionId){
	program().push_back(inst::sysCall | functionId);
	program().push_back(relpos(pos));
}

void CommandCompiler::emitPushLocToTopStack(uint32_t pos, uint32_t size, bool rel){
    
    //coppy loc to top stact
    program().push_back(inst::pushN | size);
    _scopeRef.back() += size;
    program().push_back( (rel ? inst::cpN_DS2 : inst::cpN_RDS2)  | size);
    program().push_back(size - 1); //copy to
    program().push_back(rel ? relpos(pos) : pos); //copy from
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