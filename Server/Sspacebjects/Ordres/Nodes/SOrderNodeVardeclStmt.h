/* 
 * File:   SOrderNodeVardecl.h
 * Author: karsten
 *
 * Created on 4. september 2014, 22:48
 */

#ifndef SORDERNODEVARDECLSTMT_H
#define	SORDERNODEVARDECLSTMT_H

#include "SOrderNodeStmt.h"
#include "SOrderNodeExpr.h"

class SOrderNodeVardeclStmt : public SOrderNodeStmt {
public:
	SOrderNodeVardeclStmt(TypeDenoter* type, SOrderIdentifier* id, SOrderNodeExpr* expr, SOrderNodeStmt* next):
	SOrderNodeStmt(next){
		_expr = expr;
		_id = id;
		_type = type;
	}
	SOrderIdentifier* variable(){
		return this->_id;
	}
	/** Getter for the expr */
	SOrderNodeExpr* expr(){
		return this->_expr;
	}
	virtual void accept(SOrderVisitor* v);
	virtual TypeDenoter* getType(){return _type;}
	virtual void setType(TypeDenoter* type){_type = type;}
	virtual ~SOrderNodeVardeclStmt(){}
private:
	SOrderNodeExpr* _expr;
	SOrderIdentifier* _id;
	TypeDenoter* _type;
};

#endif	/* SORDERNODEVARDECLSTMT_H */

