#ifndef STRINGLITERAL_H
#define STRINGLITERAL_H

#include "Terminal.h"

#include <string>

using namespace std;

class StringLiteral : public Terminal{
public:
	/** Create an instance of string literal */
	StringLiteral(char* data, unsigned int length, SourcePosition pos) : 
		Terminal(TOKEN_string, pos)
		//Removing quotations by incrementing pointer and decrementing length
		//_data(data+1, length-2)
	{
        char* temp;
        temp =(char*)malloc(length);
        char* start = temp;
        int removedchars = 0;
        unsigned int i = 0;
            while (i++ < length){
                   
               if (*data == '\\'){
                   data++;
                   removedchars++;
                   if (*data == 'n'){
                       *temp = 10;
                       temp++;
                       data++;
                   }else if(*data == 't'){
                       *temp = 9;
                       temp++;
                       data++;
                   }else if(*data == 'r'){
                       *temp = 13;
                       temp++;
                       data++;
                   }else if(*data == 34){ // double quotes
                       *temp = 34;
                       temp++;
                       data++;
                   }else if(*data == 39){ // single quotes
                       *temp = 39;
                       temp++;
                       data++;
                   }else if(*data == '\\'){
                       *temp = '\\';
                       temp++;
                       data++;       
                   }
               }else{
                    *temp = *data;
                    temp++;
                    data++;
               }
            }
        _data.assign(start+1,length-(2+removedchars));
        }

	/** Gets the string held by this literal */
	const string& data() const{
		return this->_data;
	}

	/** Accept a visitor */
	void accept(Visitor* v);
private:
	string _data;
};


#endif /* STRINGLITERAL_H */
