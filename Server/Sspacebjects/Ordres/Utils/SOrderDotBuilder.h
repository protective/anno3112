/* 
 * File:   SOrderDotBuilder.h
 * Author: karsten
 *
 * Created on 9. september 2014, 21:54
 */

#ifndef SORDERDOTBUILDER_H
#define	SORDERDOTBUILDER_H

class DotBuilder;

#include "SOrderVisitor.h"
#include <iostream>
#include <string>

using namespace std;
using namespace anl;
class SOrderDotBuilder : public SOrderVisitor {
public:
	SOrderDotBuilder(ostream& output = cout) : out(output){
		//Print graph header
		out<<"graph \"\""<<endl;
		out<<"{"<<endl;
		out<<"#   node [fontsize=10,width=\".2\", height=\".2\", margin=0];"<<endl;
		out<<"#   graph[fontsize=8];"<<endl;
		out<<"label=\"test Graf\""<<endl;
		
		//Setup Id's
		int myId;
		nextId = 0;
		myId = nextId++;
		parentId = myId;
		//Print root
		out<<"n"<<myId<<" ;"<<endl; // Create my parent node
		out<<"n"<<myId<<" [label=\"Root\"] ;"<<endl; // Create my node
	}
	void visit(SOrderNode* node);
	void visit(SOrderTerminal* node);
	void visit(SOrderNodeAssignExpr* node);
	void visit(SOrderNodeExpr* node);
	void visit(SOrderNodeExprStmt* node);
	void visit(SOrderNodeIfStmt* node);
	void visit(SOrderNodeWhileStmt* node);
	void visit(SOrderNodeLiteralExpr* node);
	void visit(SOrderNodeStmt* node);
	void visit(SOrderNodeVardeclStmt* node);
	void visit(SOrderNodeVariable* node);
	void visit(SOrderNodeVariableExpr* node);
	void visit(SOrderIdentifier* node);
	void visit(SOrderIntegerLiteral* node);
	void visit(SOrderBinaryOperatorExpr* node);
	void visit(SOrderNodeArg* node);
	void visit(SOrderNodeCallExpr* node);
	void visit(TypeDenoter* node);
	void visit(anl::NodeMethod* node);
	void visit(anl::NodeParam* node);
	void visit(anl::NodeTop* node);
	void visit(anl::NodeVardecTop* node);
	void finalise(){
		out<<"}"<<endl;
	}
private:
	ostream& out;
	int nextId;
	int parentId;
	int printNode(const string& label){
		int myId = nextId++;
		out<<"n"<<parentId<<" -- n"<<myId<<" ;"<<endl;
		out<<"n"<<myId<<" [label=\""<<label<<"\"] ;"<<endl;
		return myId;
	}
};


#endif	/* SORDERDOTBUILDER_H */

