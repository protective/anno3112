/* 
 * File:   TypeChecker.h
 * Author: karsten
 *
 * Created on 16. september 2014, 22:01
 */

#ifndef TYPECHECKER_H
#define	TYPECHECKER_H
#include "CommandCompiler.h"
	
typedef struct typeTable_t{
	string name;
	TypeDenoter* type;
} typeTable_t;
class TypeChecker : public SOrderVisitor {
public:
	TypeChecker(){
		
	typeTable_t temp;
	temp.name = "int";
	temp.type = new TypeDenoter(PrimitiveType::P_int,4);
		_ttable.push_back(temp);
	
	temp.name = "pos";
	temp.type = new TypeDenoter(PrimitiveType::P_int,8);
		_ttable.push_back(temp);
	}	
	
	virtual void visit(SOrderNode* node);
	virtual void visit(SOrderTerminal* node){};
	virtual void visit(SOrderNodeAssignExpr* node);
	virtual void visit(SOrderNodeExpr* node){};
	virtual void visit(SOrderNodeExprStmt* node);
	virtual void visit(SOrderNodeIfStmt* node);
	virtual void visit(SOrderNodeWhileStmt* node);
	virtual void visit(SOrderNodeLiteralExpr* node);
	virtual void visit(SOrderNodeStmt* node){};
	virtual void visit(SOrderNodeVardeclStmt* node);
	virtual void visit(SOrderNodeVariable* node);
	virtual void visit(SOrderNodeVariableExpr* node);
	virtual void visit(SOrderIdentifier* node){};
	virtual void visit(SOrderIntegerLiteral* node);
	virtual void visit(SOrderBinaryOperatorExpr* node);
	virtual void visit(SOrderNodeArg* node);
	virtual void visit(SOrderNodeCallExpr* node);
	virtual void visit(TypeDenoter* node){}
	virtual void visit(NodeTop* node){}
	virtual void visit(NodeVardecTop* node){}
	virtual void visit(NodeParam* node){}
	virtual void visit(NodeMethod* node){}
	virtual ~TypeChecker();
private:
	list<typeTable_t> _ttable;
	
	TypeDenoter* findType(string type){
		cerr<<"look for "<<type<<endl;
		for(list<typeTable_t>::iterator it = _ttable.begin(); it != _ttable.end(); it++){
			cerr<<"find "<<(*it).name<<endl;
			if((*it).name == type){
				
				return (*it).type;
			}
		}
		cerr<<"found NULL"<<endl;
		return NULL;
	}
};

#endif	/* TYPECHECKER_H */

