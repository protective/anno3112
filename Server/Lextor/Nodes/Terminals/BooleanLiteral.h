#ifndef _BOOLEANLITERAL_H
#define	_BOOLEANLITERAL_H

#include <string>
#include "Terminal.h"

/**Boolean AST-node*/
class BooleanLiteral : public Terminal{
public:
	/**Create a BooleanLiteral*/
	BooleanLiteral(bool value, SourcePosition pos) : Terminal(TOKEN_bool, pos){
		this->_value = value;
	}
	/**Return a string representation of the BooleanLiteral*/
	string toString(){
		if(this->_value)
			return "true";
		return "false";
	}
	/**Visit the BooleanLiteral*/
	void accept(Visitor* v);

	/**Getter for the boolean value*/
	bool value(){
		return this->_value;
	}
private:
	bool _value;
};
#endif	/* _BOOLEANLITERAL_H */

