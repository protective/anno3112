/* 
 * File:   SOrderNodeAssingExpr.h
 * Author: karsten
 *
 * Created on 6. september 2014, 00:43
 */

#ifndef SORDERNODEASSIGNEXPR_H
#define	SORDERNODEASSIGNEXPR_H

#include "SOrderNodeExpr.h"
#include "SOrderNodeVariable.h"


class SOrderNodeAssignExpr : public SOrderNodeExpr {
public:
	SOrderNodeAssignExpr(SOrderNodeVariable* assignee, SOrderNodeExpr* expresion) : SOrderNodeExpr(assignee->id()->pos()) {
		_assignee = assignee;
		_expresion = expresion;
	}
	SOrderNodeExpr* value(){return _expresion;}
	virtual TypeDenoter* getType(){return _expresion->getType();}
	
	SOrderNodeVariable* assignee(){return _assignee;}
	virtual void accept(SOrderVisitor* v);
	virtual ~SOrderNodeAssignExpr(){}
private:
	SOrderNodeVariable* _assignee;
	SOrderNodeExpr* _expresion;
};


#endif	/* SORDERNODEASSIGNEXPR_H */

