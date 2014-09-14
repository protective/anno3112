/* 
 * File:   SOrderNodeWhileStmt.h
 * Author: karsten
 *
 * Created on 14. september 2014, 11:53
 */

#ifndef SORDERNODEWHILESTMT_H
#define	SORDERNODEWHILESTMT_H


#include "SOrderNodeStmt.h"

class SOrderNodeWhileStmt : public SOrderNodeStmt {
public:
	SOrderNodeWhileStmt(SOrderNodeExpr* condition, SOrderNodeStmt* body, SOrderNodeStmt* next):
	SOrderNodeStmt(next){
		_condition = condition;
		_body = body;
	}
	SOrderNodeExpr* condition(){return _condition;}
	/** Get the body */
	SOrderNodeStmt* body(){
	    return _body;
	}
	virtual void accept(SOrderVisitor* v);
	virtual ~SOrderNodeWhileStmt(){}
private:
    SOrderNodeExpr* _condition;
    SOrderNodeStmt* _body;
};


#endif	/* SORDERNODEWHILESTMT_H */

