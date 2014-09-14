/* 
 * File:   SOrderDotBuilder.cpp
 * Author: karsten
 * 
 * Created on 9. september 2014, 21:54
 */

#include "SOrderDotBuilder.h"


#include <sstream>


void SOrderDotBuilder::visit(SOrderNode* node){
	
}

void SOrderDotBuilder::visit(SOrderIdentifier* node) { 
	string msg("Id: " + node->name());
	printNode(msg);
}
void SOrderDotBuilder::visit(SOrderIntegerLiteral* node) {
	//Small hack to convert int to string
	stringstream sout;
	sout << node->value();
	
	string msg("Int: " + sout.str());
	printNode(msg);
}

void SOrderDotBuilder::visit(SOrderNodeLiteralExpr* node){
	node->literal()->accept(this);
}

void SOrderDotBuilder::visit(SOrderNodeVardeclStmt* node){
	int myId = printNode("VarDeclaration");
	//Visit next
	if(node->next() != NULL)
		node->next()->accept(this);
	//Visit children
	parentId = myId;
	node->variable()->accept(this);
	if(node->expr() != NULL){
		parentId = myId;
		node->expr()->accept(this);
	}
}

void SOrderDotBuilder::visit(SOrderNodeIfStmt* node) { 
	int myId = printNode("IfStmt");
	//Visit next
	if(node->next() != NULL)
		node->next()->accept(this);
	//Visit children
	parentId = myId;
	node->condition()->accept(this);
	parentId = myId;
	node->ifBlock()->accept(this);
	if(node->elseBlock() != NULL){
		parentId = myId;
		node->elseBlock()->accept(this);
	}
}

void SOrderDotBuilder::visit(SOrderNodeExprStmt* node) {
	int myId = printNode("ExprStmt");
	//Visit next
	if(node->next() != NULL)
		node->next()->accept(this);
	//Visit children
	parentId = myId;
	node->expr()->accept(this);
}

void SOrderDotBuilder::visit(SOrderNodeVariable* node) { 
	int myId = printNode("Variable");
	//Visit children
	parentId = myId;
	node->id()->accept(this);
}

void SOrderDotBuilder::visit(SOrderNodeAssignExpr* node) { 
	int myId = printNode("AssignmentExpr");
	//Visit children
	parentId = myId;
	node->assignee()->accept(this);
	parentId = myId;
	node->value()->accept(this);
}
void SOrderDotBuilder::visit(SOrderNodeVariableExpr* node) { 
	int myId = printNode("VariableExpr");
	//Visit children
	parentId = myId;
	node->var()->accept(this);
}

void SOrderDotBuilder::visit(SOrderTerminal* node) { 
	string msg("Terminal: " + node->toString());
	printNode(msg);
}

void SOrderDotBuilder::visit(SOrderNodeExpr* node) { 
	cerr<<"ERROR SOrderDotBuilder::visit(SOrderNodeExpr* node)"<<endl;
}
void SOrderDotBuilder::visit(SOrderNodeStmt* node) {
	cerr<<"ERROR SOrderDotBuilder::visit(SOrderNodeStmt* node)"<<endl;
}

void SOrderDotBuilder::visit(SOrderBinaryOperatorExpr* node) { 
	int myId = printNode("BinaryOperation");
	//Visit children
	parentId = myId;
	node->firstOperand()->accept(this);
	parentId = myId;
	node->appliedOperator()->accept(this);
	parentId = myId;
	node->secondOperand()->accept(this);
}


void SOrderDotBuilder::visit(SOrderNodeWhileStmt* node) { 
	int myId = printNode("WhileStmt");
	//Visit next
	if(node->next() != NULL)
		node->next()->accept(this);
	//Visit children
	parentId = myId;
	node->condition()->accept(this);
	parentId = myId;
	node->body()->accept(this);
}

void SOrderDotBuilder::visit(SOrderNodeArg* node) { 
	int myId = printNode("ArgNode");
	//Visit next
	if(node->next() != NULL)
		node->next()->accept(this);
	//Visit children
	parentId = myId;
	node->expr()->accept(this);
}

void SOrderDotBuilder::visit(SOrderNodeCallExpr* node) { 
	int myId = printNode("CallExpr");
	//Visit children
	parentId = myId;
	node->callee()->accept(this);
	if(node->args()){
		parentId = myId;
		node->args()->accept(this);
	}
}