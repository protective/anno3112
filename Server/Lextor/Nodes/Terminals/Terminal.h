#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal;

#include "../../Utils/SourcePosition.h"
#include "../../Parser.h"

/** A simple terminal with any data associated */
class Terminal{
public:
	/** Create a new instance of Terminal */
	Terminal(Token token, SourcePosition pos){
		this->_token = token;
	}
	/** Gets the token of this Terminal */
	Token token() const{
		return this->_token;
	}
	/** Gets the source position of this Terminal */
	SourcePosition pos() const{
		return this->_pos;
	}
	/** Accept a visitor */
	//void accept(Visitor* v);

	/** Convert the token of this Terminal to string */
	string toString() const {
		return TokenToString(token());
	}
private:
	Token _token;
	SourcePosition _pos;
};

#endif /* TERMINAL_H */
