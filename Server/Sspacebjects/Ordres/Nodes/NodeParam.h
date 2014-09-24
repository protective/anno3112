/* 
 * File:   ParamNode.h
 * Author: karsten
 *
 * Created on 19. september 2014, 18:21
 */

#ifndef NODEPARAM_H
#define	NODEPARAM_H

#include "../Terminals/SOrderIdentifier.h"
#include "../Types/TypeDenoter.h"

namespace anl {
class NodeParam : public SOrderNode{
public:
	NodeParam(TypeDenoter* type, SOrderIdentifier* id) {
		_type = type;
		_id = id;
		_next = NULL;
	}
	NodeParam(TypeDenoter* type, SOrderIdentifier* id, anl::NodeParam* next) {
		_type = type;
		_id = id;
		_next = next;
	}
	TypeDenoter* type(){
		return _type;
	}
	SOrderIdentifier* id(){
		return _id;
	}
	NodeParam* next(){return _next;}
	void setNext(NodeParam* next){_next = next;}
	void accept(SOrderVisitor* v);
	virtual ~NodeParam(){}
private:
	TypeDenoter* _type;
	SOrderIdentifier* _id;
	NodeParam* _next;
};
}
#endif	/* NODEPARAM_H */

