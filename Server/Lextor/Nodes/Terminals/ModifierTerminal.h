#ifndef MODIFIER_H
#define MODIFIER_H

#include "Terminal.h"
#include <string>
using namespace std;

#include "../LinkedNode.h"

/** Modifiers */
enum Modifier{
	MOD_private,
	MOD_public,
	MOD_protected,
	MOD_internal
	//TODO: Add modifiers
};

class ModifierTerminal : public Terminal, public LinkedNode<ModifierTerminal>{
public:
	/** Create a new ModifierTerminal */
	ModifierTerminal(Modifier modifier, SourcePosition pos, ModifierTerminal* next = NULL)
		 : Terminal(TOKEN_EOF, pos), LinkedNode<ModifierTerminal>(next) {
		this->_modifier = modifier;
	}

	/** Gets the modifier value */
	Modifier modifier() const{
		return this->_modifier;
	}

	/** Accept a visitor */
	void accept(Visitor* v);

	/** Convert modifier to string
	  * Note you must manually handle the next modifier
	  */
	const string& toString() const;
private:
	Modifier _modifier;
};

#endif /* MODIFIER_H */
