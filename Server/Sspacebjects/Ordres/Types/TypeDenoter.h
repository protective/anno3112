/* 
 * File:   TypeDenoter.h
 * Author: karsten
 *
 * Created on 16. september 2014, 19:17
 */

#ifndef TYPEDENOTER_H
#define	TYPEDENOTER_H
#include <string>
#include "../Nodes/SOrderNode.h"
#include "../Terminals/SOrderIdentifier.h"
using namespace std;
	namespace PrimitiveType{
		enum Primitive{
			P_int = 0,
			P_float,
			P_string,
			P_void,
			P_bool,
			P_undefined
		};
	}

/** Abstract base class for all classes that can denote a type */
class TypeDenoter : public SOrderNode{
public:

	TypeDenoter(SOrderIdentifier* id){
		_id = id;
		_prim = PrimitiveType::P_undefined;
	}
	TypeDenoter(PrimitiveType::Primitive prim, uint32_t size){
		_id = NULL;
		_prim = prim;
		_size = size;
	}

	/** Accept a visitor */
	void accept(SOrderVisitor* v);
	uint32_t byteSize(){return _size;}
	string byteSizeToString(){stringstream s; s<<_size; return s.str();}
	const string toString(){
		if(_id)
			return _id->name();
		switch(_prim){
			case PrimitiveType::P_int:
				return "int";
			case PrimitiveType::P_float:
				return "float";
			case PrimitiveType::P_string:
				return "string";
			case PrimitiveType::P_void:
				return "void";
			case PrimitiveType::P_bool:
				return "bool";
			case PrimitiveType::P_undefined:
				return "prim undefined";
			default:
				return "error";
		}
	}
private:
	
	PrimitiveType::Primitive _prim;
	SOrderIdentifier* _id;
	uint32_t _size;
};

#endif	/* TYPEDENOTER_H */

