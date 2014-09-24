/* 
 * File:   TypeChecker.cpp
 * Author: karsten
 * 
 * Created on 16. september 2014, 22:01
 */

#include "TypeChecker.h"


void TypeChecker::visit(SOrderNode* node){
	
}

void TypeChecker::visit(SOrderNodeIfStmt* node){

    if(node->condition()){
        node->condition()->accept(this);
    }
    if(node->elseBlock()){
        node->elseBlock()->accept(this);
    }
    if(node->ifBlock()){
		node->ifBlock()->accept(this);
    }
	if(node->next()){
		node->next()->accept(this);
	}
}


void TypeChecker::visit(SOrderNodeWhileStmt* node){
	if(node->body()){
		 node->body()->accept(this);
    }
	if(node->condition()){
        node->condition()->accept(this);
    }
	if(node->next()){
		node->next()->accept(this);
	}
}
void TypeChecker::visit(SOrderNodeVardeclStmt* node){
    
	cerr<<"tc SOrderNodeVardeclStmt"<<endl;
    if(node->expr()){
        node->expr()->accept(this);
    }
	
	if (findType(node->getType()->toString())){

		typeTable_t temp;
		temp.name = node->variable()->name();
		temp.type = findType(node->getType()->toString());
		_ttable.push_back(temp);
		delete node->getType();
		node->setType(temp.type);
	}
    if(node->next())
        node->next()->accept(this);
}

void TypeChecker::visit(SOrderNodeExprStmt* node){
	cerr<<"tc SOrderNodeExprStmt"<<endl;
    if(node->expr()){
        node->expr()->accept(this);
    }
    
    if(node->next())
        node->next()->accept(this);
}


void TypeChecker::visit(SOrderNodeAssignExpr* node){
	//node->
	if(node->value())
		node->value()->accept(this);
}


void TypeChecker::visit(SOrderNodeLiteralExpr* node){
    //not much to do
    node->setType(findType("int"));

};

void TypeChecker::visit(SOrderNodeVariableExpr* node){
	cerr<<"tc SOrderNodeVariableExpr"<<endl;
	node->setType(findType(node->var()->id()->name()));
}

void TypeChecker::visit(SOrderIntegerLiteral* node){
    
	
}

void TypeChecker::visit(SOrderBinaryOperatorExpr* node){
	node->firstOperand()->accept(this);
	node->secondOperand()->accept(this);
	
}

void TypeChecker::visit(SOrderNodeVariable* node){
	node->accept(this);
}

void TypeChecker::visit(SOrderNodeArg* node){
	node->expr()->accept(this);
	if(node->next())
		node->next()->accept(this);
}

void TypeChecker::visit(SOrderNodeCallExpr* node){
	node->args()->accept(this);
}

TypeChecker::~TypeChecker() {
}

