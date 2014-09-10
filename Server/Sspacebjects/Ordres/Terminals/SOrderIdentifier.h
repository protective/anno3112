/* 
 * File:   SOrderTokenIdentifier.h
 * Author: karsten
 *
 * Created on 6. september 2014, 13:31
 */

#ifndef SORDERIDENTIFIER_H
#define	SORDERIDENTIFIER_H

#include "../Terminals/SOrderTerminal.h"

class SOrderIdentifier : public SOrderTerminal{
public:
	/** Create an instance of identifier */
	SOrderIdentifier(char* name, unsigned int length, SOrderSourcePosition pos) : 
		SOrderTerminal(TOKEN_id, pos),
		_name(name, length)
	{}
	virtual void accept(SOrderVisitor* v);
	/** Gets the name of this identifier */
	const string& name() const{
		return this->_name;
	}

private:
	string _name;
};

#endif	/* SORDERIDENTIFIER_H */

