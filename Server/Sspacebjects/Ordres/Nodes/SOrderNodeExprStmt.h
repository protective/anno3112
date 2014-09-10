/* 
 * File:   SOrderNodeExprStmt.h
 * Author: karsten
 *
 * Created on 7. september 2014, 19:25
 */

#ifndef SORDERNODEEXPRSTMT_H
#define	SORDERNODEEXPRSTMT_H

#include "SOrderNodeStmt.h"

class SOrderNodeExprStmt : public SOrderNodeStmt {
public:
	SOrderNodeExprStmt(SOrderNodeExpr* expr):
	SOrderNodeStmt(NULL){
		_expr = expr;

	}
	SOrderNodeExpr* expr(){return _expr;}

	virtual void accept(SOrderVisitor* v);
	virtual ~SOrderNodeExprStmt(){}
private:
SOrderNodeExpr* _expr;

};

#endif	/* SORDERNODEEXPRSTMT_H */

