/* 
 * File:   SOrderNodeIfStmt.h
 * Author: karsten
 *
 * Created on 4. september 2014, 23:29
 */

#ifndef SORDERNODEIFSTMT_H
#define	SORDERNODEIFSTMT_H

#include "SOrderNodeStmt.h"

class SOrderNodeIfStmt : public SOrderNodeStmt {
public:
	SOrderNodeIfStmt(SOrderNodeExpr* condition, SOrderNodeStmt* ifStmt, SOrderNodeStmt* elseStmt, SOrderNodeStmt* next):
	SOrderNodeStmt(next){
		_condition = condition;
		_ifStmt = ifStmt;
		_elseStmt = elseStmt;
	}
	SOrderNodeExpr* condition(){return _condition;}
	SOrderNodeStmt* ifBlock(){return _ifStmt;}
	SOrderNodeStmt* elseBlock(){return _elseStmt;}
	virtual void accept(SOrderVisitor* v);
	virtual ~SOrderNodeIfStmt(){}
private:
SOrderNodeExpr* _condition;
SOrderNodeStmt* _ifStmt;
SOrderNodeStmt* _elseStmt;
};

#endif	/* SORDERNODEIFSTMT_H */

