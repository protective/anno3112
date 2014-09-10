/* 
 * File:   SOrderTerminal.h
 * Author: karsten
 *
 * Created on 7. september 2014, 15:04
 */

#ifndef SORDERTERMINAL_H
#define	SORDERTERMINAL_H

#include "../Nodes/SOrderNode.h"
#include "../Utils/SOrderSourcePosition.h"
#include "../Generated/Parser.h"

/** A simple terminal with any data associated */
class SOrderTerminal : public SOrderNode{
public:
	/** Create a new instance of Terminal */
	SOrderTerminal(Token token, SOrderSourcePosition pos) : _pos(pos){
		this->_token = token;
	}
	/** Gets the token of this Terminal */
	Token token() const{
		return this->_token;
	}
	
		/** Gets the source position of this Terminal */
	SOrderSourcePosition pos() const{
		return this->_pos;
	}
	
	virtual void visit(CommandCompiler* compiler){
	
	}

private:
	Token _token;
	SOrderSourcePosition _pos;
};


#endif	/* SORDERTERMINAL_H */

