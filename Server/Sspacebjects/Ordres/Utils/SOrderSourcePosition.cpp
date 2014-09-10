#include "SOrderSourcePosition.h"

ostream& operator<<(ostream &stream, const SOrderSourcePosition &position){
	stream<<"Line "<<position.line()<<":"<<position.col();
	return stream;
}

