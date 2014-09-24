/* 
 * File:   SOrderNodeLiteralExpr.h
 * Author: karsten
 *
 * Created on 8. september 2014, 21:55
 */

#ifndef SORDERNODELITERALEXPR_H
#define	SORDERNODELITERALEXPR_H

#include "SOrderNodeExpr.h"
#include "../Terminals/SOrderTerminal.h"
class SOrderNodeLiteralExpr : public SOrderNodeExpr {
public:
	SOrderNodeLiteralExpr(SOrderTerminal* literal) : SOrderNodeExpr(literal->pos()) {
		this->_literal = literal;
	}
	virtual void accept(SOrderVisitor* v);
	SOrderTerminal* literal(){
		return this->_literal;
	}
	virtual TypeDenoter* getType(){return _type;}
	void setType(TypeDenoter* type){
		_type = type;
	}
	virtual ~SOrderNodeLiteralExpr(){}
private:
	SOrderTerminal* _literal;
	SOrderNodeExpr* _expr;
	TypeDenoter* _type;	
};

#endif	/* SORDERNODELITERALEXPR_H */

