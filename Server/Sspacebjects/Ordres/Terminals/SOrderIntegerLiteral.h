/* 
 * File:   SOrderIntegerLiteral.h
 * Author: karsten
 *
 * Created on 7. september 2014, 17:54
 */

#ifndef SORDERINTEGERLITERAL_H
#define	SORDERINTEGERLITERAL_H

#include "SOrderTerminal.h"

class SOrderIntegerLiteral : public SOrderTerminal{
public:
	/** Create an instance of IntegerLiteral value */
	SOrderIntegerLiteral(unsigned long long int value, bool negative, SOrderSourcePosition pos);
	
	virtual void accept(SOrderVisitor* v);	
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
SOrderIntegerLiteral* IntegerFromDecimalString(char* value, int length, SOrderSourcePosition pos);

#endif	/* SORDERINTEGERLITERAL_H */

