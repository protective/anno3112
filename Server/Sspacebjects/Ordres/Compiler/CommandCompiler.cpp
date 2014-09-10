/* 
 * File:   CommandCompiler.cpp
 * Author: karsten
 * 
 * Created on 5. september 2014, 17:47
 */

#include "CommandCompiler.h"
#include <fstream>
#include "../Generated/Lexer.h"
#include "../Generated/Parser.h"
#include "../Nodes/SOrderNode.h"
#include "../Utils/SOrderDotBuilder.h"

CommandCompiler::CommandCompiler(string programPath) :
Command(0){
	_programPath = programPath;
}

uint32_t CommandCompiler::execute(){
	cerr<<"execute Compiler"<<endl;
	ifstream is(_programPath.c_str());
	Lexer lexer(&is);
	
	SOrderNode* result = parse(&lexer);
	ofstream dotfile(_programPath.append(".dot").c_str());
	SOrderDotBuilder dot(dotfile);
	//dot.visit(result);
	result->accept(&dot);
	dot.finalise();
	
	_processor;
	return COMMAND_FINAL;
}

CommandCompiler::~CommandCompiler() {
}

