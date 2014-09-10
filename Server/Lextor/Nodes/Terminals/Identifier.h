#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "Terminal.h"
#include <string>

using namespace std;

class Identifier : public Terminal{
public:
	/** Create an instance of identifier */
	Identifier(char* name, unsigned int length, SourcePosition pos) : 
		Terminal(TOKEN_id, pos),
		_name(name, length)
	{}

	/** Gets the name of this identifier */
	const string& name() const{
		return this->_name;
	}

	/** Accept a visitor */
	void accept(Visitor* v);
private:
	string _name;
};

#endif /* IDENTIFIER_H */
