/* 
 * File:   SOrdreProgram.h
 * Author: karsten
 *
 * Created on 5. september 2014, 17:48
 */

#ifndef SORDREPROGRAM_H
#define	SORDREPROGRAM_H


#include "SOrdreInstructionSet.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <inttypes.h>
using namespace std;
typedef uint32_t INSTRUCTION;
#define OPCODE(X) (X & 0x00FF0000)
#define ARG(X) X & 0x0000FFFF
typedef vector<INSTRUCTION> PROGRAM;
class SOrdreProgram {
public:
    
	SOrdreProgram();
	PROGRAM& program(){return _program;}
	string name(){return _name;}
	virtual ~SOrdreProgram();
private:
	string _name;
	PROGRAM _program;
};

#endif	/* SORDREPROGRAM_H */

