/* 
 * File:   SOrderVisitor.h
 * Author: karsten
 *
 * Created on 9. september 2014, 21:21
 */

#ifndef SORDERVISITOR_H
#define	SORDERVISITOR_H




#include "../Nodes/SOrderNodes.h"
#include "../Terminals/SOrderTerminals.h"

class SOrderVisitor{
public:
	virtual void visit(SOrderTerminal* node) = 0;
	virtual void visit(SOrderNode* node) = 0;
	virtual void visit(SOrderNodeAssignExpr* node) = 0;
	virtual void visit(SOrderNodeExpr* node) = 0;
	virtual void visit(SOrderNodeExprStmt* node) = 0;
	virtual void visit(SOrderNodeIfStmt* node) = 0;
	virtual void visit(SOrderNodeWhileStmt* node) = 0;
	virtual void visit(SOrderNodeLiteralExpr* node) = 0;
	virtual void visit(SOrderNodeStmt* node) = 0;
	virtual void visit(SOrderNodeVardeclStmt* node) = 0;
	virtual void visit(SOrderNodeVariable* node) = 0;
	virtual void visit(SOrderNodeVariableExpr* node) = 0;
	virtual void visit(SOrderIdentifier* node) = 0;
	virtual void visit(SOrderIntegerLiteral* node) = 0;
	virtual void visit(SOrderBinaryOperatorExpr* node) = 0;
	virtual void visit(SOrderNodeArg* node) = 0;
	virtual void visit(SOrderNodeCallExpr* node) = 0;
};


#endif	/* SORDERVISITOR_H */

