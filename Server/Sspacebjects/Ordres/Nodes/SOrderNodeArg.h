/* 
 * File:   SOrderNodeArg.h
 * Author: karsten
 *
 * Created on 14. september 2014, 14:21
 */

#ifndef SORDERNODEARG_H
#define	SORDERNODEARG_H

#include "SOrderNodeExpr.h"


class SOrderNodeArg : public SOrderNode{
public:
	SOrderNodeArg(SOrderNodeExpr* expr, SOrderNodeArg* next = NULL) {
	    _expr = expr;
	    _next = next;
	}
	/** Get the expression for this argument */
	SOrderNodeExpr* expr(){
	    return _expr;
	}
	SOrderNodeArg* next(){return _next;}
	void setNext(SOrderNodeArg* next){_next = next;}
	void accept(SOrderVisitor* v);
private:
	SOrderNodeExpr* _expr;
	SOrderNodeArg* _next;
};

#endif	/* SORDERNODEARG_H */

