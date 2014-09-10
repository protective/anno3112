/* 
 * File:   SOrderErrorTerminal.h
 * Author: karsten
 *
 * Created on 7. september 2014, 21:59
 */

#ifndef SORDERERRORTERMINAL_H
#define	SORDERERRORTERMINAL_H

#include "SOrderTerminal.h"

/** Error terminal in the AST*/
class SOrderErrorTerminal : public SOrderTerminal{
public:
	/** Create new error terminal.
	  * This constructor is used by the parser. */
	SOrderErrorTerminal(SOrderTerminal* unexpected) : SOrderTerminal(TOKEN_error, unexpected->pos()){
		this->_unexpected = unexpected;
	}
	/** Discard an error terminal.
	  * Used by the parser if the next terminal is unusable.*/
	void discard(SOrderTerminal* terminal){
		this->_discarded.push_back(terminal);
	}
	/** Returns the unexpected terminal which caused the error*/
	SOrderTerminal* unexpected(){
		return this->_unexpected;
	}
private:
	list<SOrderTerminal*> _discarded;
	SOrderTerminal* _unexpected; 
};


#endif	/* SORDERERRORTERMINAL_H */

