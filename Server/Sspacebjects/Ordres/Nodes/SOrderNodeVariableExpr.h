/* 
 * File:   SOrderNodeVariableExpr.h
 * Author: karsten
 *
 * Created on 8. september 2014, 22:07
 */

#ifndef SORDERNODEVARIABLEEXPR_H
#define	SORDERNODEVARIABLEEXPR_H

#include "SOrderNodeExpr.h"
#include "SOrderNodeVariable.h"

class SOrderNodeVariableExpr : public SOrderNodeExpr{
public:
	SOrderNodeVariableExpr(SOrderNodeVariable* var) : SOrderNodeExpr(var->id()->pos()) {
		_var = var;
		_type = NULL;
	}
	
	virtual void accept(SOrderVisitor* v);
	SOrderNodeVariable* var(){
		return _var;
	}
	TypeDenoter* getType(){
		return _type;
	}
	void setType(TypeDenoter* type){
		_type = type;
	}
private:
	SOrderNodeVariable* _var;
	TypeDenoter* _type;
};

#endif	/* SORDERNODEVARIABLEEXPR_H */

