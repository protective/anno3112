#ifndef INTEGERLITERAL_H
#define INTEGERLITERAL_H

#include "Terminal.h"

class IntegerLiteral : public Terminal{
public:
	/** Create an instance of IntegerLiteral value */
	IntegerLiteral(unsigned long long int value, bool negative, SourcePosition pos);
	/** Accept a visitor */
	void accept(Visitor* v);
	/** Gets the unsigned value of this IntegerLiteral */
	unsigned long long int value() const{
		return this->_value;
	}
	/** Gets true if this IntegerLiteral is negative */
	bool negative() const{
		return this->_negative;
	}
private:
	unsigned long long int _value;
	bool _negative;
};

/** Create an instance of IntegerLiteral from a decimal string */
IntegerLiteral* IntegerFromDecimalString(char* value, int length, SourcePosition pos);

#endif /* INTEGERLITERAL_H */
