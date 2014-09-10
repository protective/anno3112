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
	SOrderNodeVardeclStmt(SOrderIdentifier* id, SOrderNodeExpr* expr, SOrderNodeStmt* next):
	SOrderNodeStmt(next){
		_expr = expr;
		_id = id;
	}
	SOrderIdentifier* variable(){
		return this->_id;
	}
	/** Getter for the expr */
	SOrderNodeExpr* expr(){
		return this->_expr;
	}
	virtual void accept(SOrderVisitor* v);

	virtual ~SOrderNodeVardeclStmt(){}
private:
SOrderNodeExpr* _expr;
SOrderIdentifier* _id;
};

#endif	/* SORDERNODEVARDECLSTMT_H */

