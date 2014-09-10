#ifndef ERRORTERMINAL_H
#define ERRORTERMINAL_H

#include "Terminal.h"
#include <list>
using namespace std;

/** Error terminal in the AST*/
class ErrorTerminal : public Terminal{
public:
	/** Create new error terminal.
	  * This constructor is used by the parser. */
	ErrorTerminal(Terminal* unexpected) : Terminal(TOKEN_error, unexpected->pos()){
		this->_unexpected = unexpected;
	}
	/** Discard an error terminal.
	  * Used by the parser if the next terminal is unusable.*/
	void discard(Terminal* terminal){
		this->_discarded.push_back(terminal);
	}
	/** Returns the unexpected terminal which caused the error*/
	Terminal* unexpected(){
		return this->_unexpected;
	}
	/** Accept a visitor*/
	void accept(Visitor* v);
private:
	list<Terminal*> _discarded;
	Terminal* _unexpected; 
};

#endif /* ERRORTERMINAL_H */
