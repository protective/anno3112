/* 
 * File:   SOrderVisitor.cpp
 * Author: karsten
 * 
 * Created on 9. september 2014, 21:21
 */

#include "SOrderVisitor.h"

void  SOrderVisitor::visit(SOrderNodeAssignExpr* node){};
void  SOrderVisitor::visit(SOrderNodeExpr* node){};
void  SOrderVisitor::visit(SOrderNodeExprStmt* node){};
void  SOrderVisitor::visit(SOrderNodeIfStmt* node){};
void  SOrderVisitor::visit(SOrderNodeWhileStmt* node){};
void  SOrderVisitor::visit(SOrderNodeLiteralExpr* node){};
void  SOrderVisitor::visit(SOrderNodeStmt* node){};
void  SOrderVisitor::visit(SOrderNodeVardeclStmt* node){};
void  SOrderVisitor::visit(SOrderNodeVariable* node){};
void  SOrderVisitor::visit(SOrderNodeVariableExpr* node){};
void  SOrderVisitor::visit(SOrderIdentifier* node){};
void  SOrderVisitor::visit(SOrderIntegerLiteral* node){};
void  SOrderVisitor::visit(SOrderBinaryOperatorExpr* node){};
