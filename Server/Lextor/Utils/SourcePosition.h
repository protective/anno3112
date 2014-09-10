#ifndef SOURCEPOSITION_H
#define SOURCEPOSITION_H

class SourcePosition;

#include <iostream>
using namespace std;

/** Representation of a position in a source file */
class SourcePosition{
public:
	/** Create a new instance of source position */
	SourcePosition(unsigned int line, unsigned int col){
		this->_line = line;
		this->_col = col;
	}
	SourcePosition(const SourcePosition& pos){
		//Hack to handle negative col offsets used in the lexer after newline
		this->_line = pos.line();
		this->_col = pos.col();		
	}
	/** Gets line offset in the file, starts at 1 */
	unsigned int line() const{
		return this->_line;
	}
	/** Gets col offset in the line, starts at 0 */
	unsigned int col() const{
		return this->_col;
	}
	/** Can be modified by Lexer */
	friend class Lexer;
private:
	unsigned int _line;
	unsigned int _col;
};

ostream& operator<<(ostream &stream, const SourcePosition &position);

#endif /* SOURCEPOSITION_H */
