/* 
 * File:   SOrderNodeStmt.h
 * Author: karsten
 *
 * Created on 4. september 2014, 23:21
 */

#ifndef SORDERNODESTMT_H
#define	SORDERNODESTMT_H

#include "SOrderNode.h"


class SOrderNodeStmt : public SOrderNode {
public:
	SOrderNodeStmt(SOrderNodeStmt* next){
		_next = next;
	}

	virtual void accept(SOrderVisitor* v);
	void setNext(SOrderNodeStmt* next){
		_next = next;
	}
	
	SOrderNodeStmt* next(){return _next;}
	
	virtual ~SOrderNodeStmt(){}
protected:
	SOrderNodeStmt* _next;
};

#endif	/* SORDERNODESTMT_H */

