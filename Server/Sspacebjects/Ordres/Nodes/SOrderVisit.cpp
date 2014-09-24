
#include "../Utils/SOrderVisitor.h"
void SOrderTerminal::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNode::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeAssignExpr::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeExpr::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeExprStmt::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeIfStmt::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeLiteralExpr::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeStmt::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeVardeclStmt::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeVariable::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderNodeVariableExpr::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderIdentifier::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderIntegerLiteral::accept(SOrderVisitor* v){
	v->visit(this);
}
void SOrderBinaryOperatorExpr::accept(SOrderVisitor* v){
	v->visit(this);
}

void SOrderNodeWhileStmt::accept(SOrderVisitor* v){
	v->visit(this);
}

void SOrderNodeArg::accept(SOrderVisitor* v){
	v->visit(this);
}

void SOrderNodeCallExpr::accept(SOrderVisitor* v){
	v->visit(this);
}

void TypeDenoter::accept(SOrderVisitor* v){
	v->visit(this);
}

void anl::NodeTop::accept(SOrderVisitor* v){
	v->visit(this);
}

void anl::NodeVardecTop::accept(SOrderVisitor* v){
	v->visit(this);
}

void anl::NodeParam::accept(SOrderVisitor* v){
	v->visit(this);
}

void anl::NodeMethod::accept(SOrderVisitor* v){
	v->visit(this);
}