/* 
 * File:   SOrderNodeCallExpr.h
 * Author: karsten
 *
 * Created on 14. september 2014, 14:22
 */

#ifndef SORDERNODECALLEXPR_H
#define	SORDERNODECALLEXPR_H

#include "SOrderNodeExpr.h"
#include "SOrderNodeVariableExpr.h"


/** Call expression in the abstract syntax tree */
class SOrderNodeCallExpr : public SOrderNodeExpr{
public:
	SOrderNodeCallExpr(SOrderNodeVariableExpr* callee, SOrderNodeArg* args) : SOrderNodeExpr(callee->pos()){
		_callee = callee;
		_args = args;
	}
	/** Method or function being called */
	SOrderNodeVariableExpr* callee(){
		return _callee;
	}
	/** Arguments for the call 
 	 * Note that ArgNode forms a single linked list
	 */
	virtual TypeDenoter* getType(){return NULL;}

	
	SOrderNodeArg* args(){
		return _args;
	}
	void accept(SOrderVisitor* v);
private:
	SOrderNodeVariableExpr* _callee;
	SOrderNodeArg* _args;
};

#endif	/* SORDERNODECALLEXPR_H */

