/* 
 * File:   MethodNode.h
 * Author: karsten
 *
 * Created on 19. september 2014, 18:20
 */

#ifndef NODEMETHOD_H
#define	NODEMETHOD_H

#include "SOrderNodeExpr.h"
#include "NodeTop.h"
#include "SOrderNodeStmt.h"
#include "NodeParam.h"
namespace anl {
class NodeMethod : public NodeTop {
public:
	NodeMethod(TypeDenoter* type, SOrderIdentifier* id, NodeParam* param,  SOrderNodeStmt* block):
	NodeTop(){
		_block = block;
		_id = id;
		_type = type;
		_param = param;
	}
	SOrderIdentifier* variable(){
		return this->_id;
	}
	SOrderNodeStmt* block(){
		return this->_block;
	}
	NodeParam* param(){
		return this->_param;
	}
	virtual void accept(SOrderVisitor* v);
	virtual TypeDenoter* getType(){return _type;}
	virtual void setType(TypeDenoter* type){_type = type;}
	virtual ~NodeMethod(){}
private:
	SOrderNodeStmt* _block;
	NodeParam* _param;
	SOrderIdentifier* _id;
	TypeDenoter* _type;
};
}

#endif	/* NODEMETHOD_H */

