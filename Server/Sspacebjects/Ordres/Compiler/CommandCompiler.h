/* 
 * File:   CommandCompiler.h
 * Author: karsten
 *
 * Created on 5. september 2014, 17:47
 */

#ifndef COMMANDCOMPILER_H
#define	COMMANDCOMPILER_H
#include "../../../Commands/Command.h"
#include "../SOrdreProgram.h"

class CommandCompiler : public Command {
public: 
	CommandCompiler(string programPath);
	virtual uint32_t execute();
	PROGRAM& program(){return _program;}
	virtual ~CommandCompiler();
private:
	string _programPath;
	PROGRAM _program;
	
};

#endif	/* COMMANDCOMPILER_H */

