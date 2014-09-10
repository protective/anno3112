/* 
 * File:   SOrderNodeVariable.h
 * Author: karsten
 *
 * Created on 6. september 2014, 00:50
 */

#ifndef SORDERNODEVARIABLE_H
#define	SORDERNODEVARIABLE_H

#include "SOrderNode.h"
#include "../Terminals/SOrderIdentifier.h"

class SOrderNodeVariable : public SOrderNode {
public:
	SOrderNodeVariable(SOrderIdentifier* id){
		_id = id;
	}
	virtual void accept(SOrderVisitor* v);
	SOrderIdentifier* id(){
		return _id;
	}

	virtual ~SOrderNodeVariable(){}
private:
SOrderIdentifier* _id;
};

#endif	/* SORDERNODEVARIABLE_H */

