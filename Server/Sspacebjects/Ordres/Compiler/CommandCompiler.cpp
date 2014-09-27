/* 
 * File:   CommandCompiler.cpp
 * Author: karsten
 * 
 * Created on 5. september 2014, 17:47
 */

#include "CommandCompiler.h"
#include <fstream>
#include <vector>
#include "../Generated/Lexer.h"
#include "../Generated/Parser.h"
#include "../Nodes/SOrderNode.h"
#include "../Utils/SOrderDotBuilder.h"
#include "../Utils/SOrderVisitor.h"
#include "SOrderProgramPrinter.h"
#include "../CommandOrderThread.h"
#include "../../../Commands/Processor.h"
#include "TypeChecker.h"
CommandCompiler::CommandCompiler(string programPath) :
Command(0){
	_programPath = programPath;
	_inStatic = true;
	_step = Step::allocation;
	for(int i = 0; GlobalSystemCallLib[i]._systemCallFunc; i++){
		vTableEntry temp(GlobalSystemCallLib[i]._name, i,0,false, GlobalSystemCallLib[i]._systemCallFunc);
		_vtable.push_back(temp);
	}

}

uint32_t CommandCompiler::execute(){
	cerr<<"execute Compiler"<<endl;
	ifstream is(_programPath.c_str());
	Lexer lexer(&is);
	
	SOrderNode* result = parse(&lexer);

	//TypeChecker typecheck;
	
	//result->accept(&typecheck);
	
	ofstream dotfile(_programPath.append(".dot").c_str());
	SOrderDotBuilder dot(dotfile);
	dot.visit(result);
	result->accept(&dot);
	dot.finalise();

	_scopeRef.push_back(1);
	result->accept(this);
	_step = Step::main;
	emitPushStack(0xAAAA,1);
	emitPushPC();
	emitCall("main");
	emitEOP();	
	result->accept(this);
	this->finalize();
	
	ofstream asmPrinter(_programPath.append(".asm").c_str());
	printProgram(asmPrinter,_program);
	SOrdreProgram* p = new SOrdreProgram("test",_program, _interruptHandlers);
	_processor->getPrograms()["test"] = p;
	return COMMAND_FINAL;
}
vTableEntry* CommandCompiler::vtableFind(string id){
    for(list<vTableEntry>::reverse_iterator it = _vtable.rbegin(); it != _vtable.rend(); it++){
        if((*it).name == id){
            return &(*it);
        }
    }
	cerr<<"vtable error looking for ("<<id<<")"<<endl;
	return NULL;
}

void CommandCompiler::finalize(){
	for(map<uint32_t, string>::iterator it = _lables.begin(); it != _lables.end(); it++){
		if(vtableFind(it->second))
			_program[it->first] = vtableFind(it->second)->pos;
		else
			cerr<<"undeclared function>>"<<it->second<<endl;
	}
}

void CommandCompiler::visit(SOrderNodeIfStmt* node){
    
    /*
     * 
     *   eval E
     *   conjump <h>
	 *	 pop E
     *   jump <g>
     *-h
	 *	 pop E
     *   ifblock   
     *   pop
     *-g 
     * 
     *   eval E
     *   conjump <h>
     *   elseblock
     *   pop
     *   jump <g>
     *-h
     *   ifblock   
     *   pop
     *-g
     */
    _scopeRef.push_back(0);
    if(node->condition()){
        node->condition()->accept(this);
    }
	_scopeRef.pop_back();
    uint32_t h = emitCondJumpToRef();
	emitPopStackIgnore(1);
    if(node->elseBlock()){
        _scopeRef.push_back(0);
        node->elseBlock()->accept(this);
		emitPopStack(_scopeRef.back());
        _scopeRef.pop_back();
        

    }
    uint32_t g = emitJumpToRef();
    program().at(h) = program().size();
	emitPopStackIgnore(1);
    if(node->ifBlock()){
        _scopeRef.push_back(0);
		node->ifBlock()->accept(this);
		emitPopStack(_scopeRef.back());
        _scopeRef.pop_back();

    }
	program().at(g) = program().size();
	if(node->next()){
		node->next()->accept(this);
	}
}


void CommandCompiler::visit(SOrderNodeWhileStmt* node){
   /*
     *   jump <g>
     *-h
	 *   pop E
     *   block   
     *   pop
     *-g 
     *   eval E
     *   conjump <h>
	 *	 pop E
     */
    
	uint32_t g = emitJumpToRef();
	uint32_t h = program().size();
	emitPopStackIgnore(1);
	if(node->body()){
		_scopeRef.push_back(_scopeRef.back());
		 node->body()->accept(this);
		uint32_t oldRef = _scopeRef.back();
		_scopeRef.pop_back();
		emitPopStack(oldRef - _scopeRef.back());	
    }
	program().at(g) = program().size();
	_scopeRef.push_back(0);
	if(node->condition()){
        node->condition()->accept(this);
    }
	_scopeRef.pop_back();
    emitCondJumpToRef(h);
	emitPopStackIgnore(1);
	if(node->next()){
		node->next()->accept(this);
	}
}

void CommandCompiler::visit(NodeMethod* node){
	if(_step == Step::main){
		emitNOP();
		if(node->variable()->name() == "main"){
			_mainFunctionPC = program().size();
		}
		vTableEntry v(node->variable()->name(),program().size(),false);
		_vtable.push_back(v);
		
		for(int i = 0 ; GlobalSystemCallBackLib[i]._id; i++){
			if (GlobalSystemCallBackLib[i]._name == node->variable()->name()){
				cerr<<"found interrupt handler"<<endl;
				_interruptHandlers[GlobalSystemCallBackLib[i]._id] = program().size();
			}
		}
		if(node->block()){
			_scopeRef.push_back(0);
			if(node->param())
				node->param()->accept(this);
			node->block()->accept(this);
			emitPopStack(_scopeRef.back());
			_scopeRef.pop_back();
			emitReturn();
		}
	}
	if(node->next())
		node->next()->accept(this);
	
}

 void CommandCompiler::visit(NodeVardecTop* node){
	if(_step == Step::allocation){
		_inStatic = true;
		if(node->expr()){
			node->expr()->accept(this);
		}
		if(!node->expr()){
			emitPushStack(0x00, 1);
		}
		vTableEntry v(node->variable()->name(),_scopeRef.back()-1,false);
		_vtable.push_back(v);
	}
	if(node->next())
		node->next()->accept(this);
	
}

void CommandCompiler::visit(SOrderNodeVardeclStmt* node){
    
    if(node->expr()){
        node->expr()->accept(this);
    }
    if(!node->expr()){
        emitPushStack(0x00, 1);
    }
    vTableEntry v(node->variable()->name(),_scopeRef.back(), true);
    _vtable.push_back(v);
    if(node->next())
        node->next()->accept(this);
}

void CommandCompiler::visit(NodeParam* node){
	_scopeRef.back()+=1;
	vTableEntry v(node->id()->name(),_scopeRef.back(), true);
    _vtable.push_back(v);
	cerr<<"paramnode "<<node->id()->name() <<" ref "<< _scopeRef.back()<<endl;
	if(node->next())
        node->next()->accept(this);
}

void CommandCompiler::visit(SOrderNodeExprStmt* node){

    if(node->expr()){

        node->expr()->accept(this);
    }
    emitPopStack(1);
    
    if(node->next())
        node->next()->accept(this);
}


void CommandCompiler::visit(SOrderNodeAssignExpr* node){
    
    node->value()->accept(this);
    
    vTableEntry* ve = NULL;
    ve = this->vtableFind(node->assignee()->id()->name());
    if(!ve){
        return;
    }
    emitTopStackToLoc(ve->pos, ve->rel, 1);

}

void CommandCompiler::visit(SOrderNodeLiteralExpr* node){
    //not much to do
    node->literal()->accept(this);
};

void CommandCompiler::visit(SOrderIntegerLiteral* node){
    emitPushStack(node->value(),1);
}

void CommandCompiler::visit(SOrderBinaryOperatorExpr* node){
	node->firstOperand()->accept(this);
	node->secondOperand()->accept(this);
	switch(node->appliedOperator()->token()){
		case TOKEN_plus:{
			emitBOAddPop();
			break;
		}
		case TOKEN_minus:{
			emitBOMinusPop();
			break;
		}
	}
}

void CommandCompiler::visit(SOrderNodeVariableExpr* node){

	node->var()->accept(this);
}

void CommandCompiler::visit(SOrderNodeVariable* node){

    vTableEntry* ve = NULL;
    ve = this->vtableFind(node->id()->name());
    if(!ve){
        cerr<<"ERROR visit SOrderNodeVariable"<<endl;
        return;
    }
	
	emitPushLocToTopStack(ve->pos,1, ve->rel);


}

void CommandCompiler::visit(SOrderNodeArg* node){
	node->expr()->accept(this);
	if(node->next())
		node->next()->accept(this);
}

void CommandCompiler::visit(SOrderNodeCallExpr* node){

	vTableEntry* ve = NULL;

	ve = this->vtableFind(node->callee()->var()->id()->name());
		
	if(!ve){
        return;
    }

	if(ve->systemCall){
		uint32_t s = _scopeRef.back();
		emitPushStack(0xEEEE,1);
		uint32_t oldref = _scopeRef.back();
		_scopeRef.push_back(_scopeRef.back());
		node->args()->accept(this);
		emitSysCall(s, ve->pos);
		
		emitPopStack(_scopeRef.back() - oldref);
		_scopeRef.pop_back();
		
	}else{
		emitPushStack(0x00FF,1);
		uint32_t h = emitPushRPC();
		
		_scopeRef.push_back(_scopeRef.back());
		if(node->args())
			node->args()->accept(this);
		_scopeRef.pop_back();
		emitCall(ve->name);
		program().at(h) = program().size();
		//emitPopStack(_scopeRef.back());
		
	}
		
	
}



CommandCompiler::~CommandCompiler() {
}

