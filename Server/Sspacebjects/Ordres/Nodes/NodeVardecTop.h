/* 
 * File:   VardecTop.h
 * Author: karsten
 *
 * Created on 19. september 2014, 18:39
 */

#ifndef VARDECTOP_H
#define	VARDECTOP_H

#include "SOrderNodeExpr.h"
#include "NodeTop.h"
namespace anl {
class NodeVardecTop : public NodeTop {
public:
	NodeVardecTop(TypeDenoter* type, SOrderIdentifier* id, SOrderNodeExpr* expr)
	{
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
	virtual ~NodeVardecTop(){}
private:
	SOrderNodeExpr* _expr;
	SOrderIdentifier* _id;
	TypeDenoter* _type;
};
}
#endif	/* VARDECTOP_H */

