/* 
 * File:   SOrderNodeExpr.h
 * Author: karsten
 *
 * Created on 4. september 2014, 23:31
 */

#ifndef SORDERNODEEXPR_H
#define	SORDERNODEEXPR_H

#include "SOrderNode.h"
#include "../Utils/SOrderSourcePosition.h"
#include "../Types/TypeDenoter.h"
class SOrderNodeExpr : public SOrderNode {
public:
	SOrderNodeExpr(SOrderSourcePosition pos) : _pos(pos){
	}
    	/** Get the position of the expression */
	SOrderSourcePosition pos(){
		return _pos;
	}
    
	virtual TypeDenoter* getType(){return NULL;}
	//virtual void setType(TypeDenoter* type){_type = type;}	
	virtual void accept(SOrderVisitor* v);
	virtual ~SOrderNodeExpr(){}
private:
	SOrderSourcePosition _pos;
	//TypeDenoter* _type;
};

#endif	/* SORDERNODEEXPR_H */

