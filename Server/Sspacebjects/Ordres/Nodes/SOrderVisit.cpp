
#include "../Utils/SOrderVisitor.h"
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