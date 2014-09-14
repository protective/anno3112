/* 
 * File:   CommandCompiler.cpp
 * Author: karsten
 * 
 * Created on 5. september 2014, 17:47
 */

#include "CommandCompiler.h"
#include <fstream>
#include "../Generated/Lexer.h"
#include "../Generated/Parser.h"
#include "../Nodes/SOrderNode.h"
#include "../Utils/SOrderDotBuilder.h"
#include "../Utils/SOrderVisitor.h"
#include "SOrderProgramPrinter.h"

CommandCompiler::CommandCompiler(string programPath) :
Command(0){
	_programPath = programPath;
}

uint32_t CommandCompiler::execute(){
	cerr<<"execute Compiler"<<endl;
	ifstream is(_programPath.c_str());
	Lexer lexer(&is);
	
	SOrderNode* result = parse(&lexer);
	ofstream dotfile(_programPath.append(".dot").c_str());
	SOrderDotBuilder dot(dotfile);
	//dot.visit(result);
	result->accept(&dot);
	dot.finalise();
        
 
	_scopeRef.push_back(0);
        result->accept(this);
        ofstream asmPrinter(_programPath.append(".asm").c_str());
        printProgram(asmPrinter,_program);
	return COMMAND_FINAL;
}
vTableEntry* CommandCompiler::vtableFind(string id){
    for(list<vTableEntry>::reverse_iterator it = _vtable.rbegin(); it != _vtable.rend(); it++){
        if((*it).name == id){
            return &(*it);
        }
    }
	cerr<<"vtable error looking for "<<id<<endl;
	return NULL;
}
void CommandCompiler::visit(SOrderNodeIfStmt* node){
    
    /*
     * 
     *   eval E
     *   conjump <h>
     *   jump <g>
     *-h
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
    
    if(node->condition()){
        node->condition()->accept(this);
    }
    uint32_t h = emitCondJumpToRef();
  
    if(node->elseBlock()){
        _scopeRef.push_back(_scopeRef.back());
        node->elseBlock()->accept(this);
        uint32_t oldRef = _scopeRef.back();
        _scopeRef.pop_back();
        emitPopStack(oldRef - _scopeRef.back());

    }
    uint32_t g = emitJumpToRef();
    program().at(h) = program().size();
    if(node->ifBlock()){
       _scopeRef.push_back(_scopeRef.back());
		node->ifBlock()->accept(this);
       uint32_t oldRef = _scopeRef.back();
	   _scopeRef.pop_back();
       emitPopStack(oldRef - _scopeRef.back());

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
     *   block   
     *   pop
     *-g 
     *   eval E
     *   conjump <h>
     */
    
	uint32_t g = emitJumpToRef();
	uint32_t h = program().size();
	if(node->body()){
		_scopeRef.push_back(_scopeRef.back());
		 node->body()->accept(this);
		uint32_t oldRef = _scopeRef.back();
		_scopeRef.pop_back();
		emitPopStack(oldRef - _scopeRef.back());	
    }
	program().at(g) = program().size();
	if(node->condition()){
        node->condition()->accept(this);
    }
    emitCondJumpToRef(h);
  	
	if(node->next()){
		node->next()->accept(this);
	}
}

void CommandCompiler::visit(SOrderNodeVardeclStmt* node){
    
    if(node->expr()){
        node->expr()->accept(this);
    }
    if(!node->expr()){
        emitPushStack(0x00, 1);
    }
    vTableEntry v(node->variable()->name(),_scopeRef.back());
    _vtable.push_back(v);
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
        cerr<<"ERROR visit SOrderNodeAssignExpr"<<endl;
        return;
    }
    emitTopStackToLoc(ve->pos,1);

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
    emitPushLocToTopStack(ve->pos,1);

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
        cerr<<"ERROR visit SOrderNodeCallExpr"<<endl;
        return;
    }

	if(node->callee()){
		_scopeRef.push_back(_scopeRef.back());
		node->args()->accept(this);
		emitSysCall();
		uint32_t oldRef = _scopeRef.back();
		_scopeRef.pop_back();
		emitPopStack(oldRef - _scopeRef.back());
	}
	
}

CommandCompiler::~CommandCompiler() {
}

