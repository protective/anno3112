#include "SOrderIntegerLiteral.h"
#include <assert.h>

SOrderIntegerLiteral::SOrderIntegerLiteral(unsigned long long int value, bool negative, SOrderSourcePosition pos) : SOrderTerminal(TOKEN_int, pos){
	this->_value = value;
	this->_negative = negative;
}

SOrderIntegerLiteral* IntegerFromDecimalString(char* value, int len, SOrderSourcePosition pos){
	//We can't have length less than 1
	assert(len > 0);
	//Read the sign value
	bool negative = false;
	if(value[0] == '-'){
		negative = true;
		value++;
		len--;
	}
	//Set value to 0 and add stuff
	unsigned long long int data = 0;
	for(int i = 0; i < len; i++){
		data *= 10;
		data += value[i] - '0';
	}
	return new SOrderIntegerLiteral(data, negative, pos);
}
