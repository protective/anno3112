#ifndef REALLITERAL_H
#define REALLITERAL_H

#include "Terminal.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

class RealLiteral : public Terminal{
public:
	RealLiteral(char* value, unsigned int length, SourcePosition pos) : Terminal(TOKEN_real, pos){
		assert(length > 0);
		char buf[length+1];
		memcpy(buf, value, length);
		buf[length] = '\0'; //NULL terminating the string
		_value = atof(buf); //Now we can be sure the string is null terminated.
	}

	void accept(Visitor* v);

	double value() const{
		return this->_value;
	}
private:
	double _value;
};

#endif /* REALLITERAL_H */
