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
#include "../Utils/SOrderVisitor.h"

#include "../SOrdersSystemCalls.h"
using namespace anl;
typedef struct vTableEntry{
    vTableEntry(string p_name, uint32_t p_pos, bool p_rel){
		name = p_name;
		pos = p_pos;
		rel = p_rel;
		size = 1;
		systemCall = 0;
    }
    vTableEntry(string p_name, uint32_t p_pos, bool p_rel, uint32_t p_size){
		name = p_name;
		pos = p_pos;
		rel = p_rel;
		size = p_size;
		systemCall = 0;
    }
	vTableEntry(string p_name, uint32_t p_pos, bool p_rel, uint32_t p_size, systemCallFunc p_systemCall){
		name = p_name;
		pos = p_pos;
		rel = p_rel;
		size = p_size;
		systemCall = p_systemCall;
    }
    vTableEntry(const vTableEntry& v){
		name = v.name;
		pos = v.pos;
		rel = v.rel;
		size = v.size;
		systemCall = v.systemCall;
    }
    string name;
    uint32_t pos;
	bool rel;
    uint32_t size;
	systemCallFunc systemCall; //pointer to systemcall Function
}vTableEntry;

namespace Step{
	enum Enum{
		allocation = 1,
		main = 2
	};
}

class CommandCompiler : public Command, public SOrderVisitor {
public: 
	CommandCompiler(string programPath);
	virtual uint32_t execute();
	PROGRAM& program(){return _program;}
    //list<systemCallFunc> getGlobalSystemCallLibs();
	virtual void visit(SOrderNode* node){};
	virtual void visit(SOrderTerminal* node){};
	virtual void visit(SOrderNodeAssignExpr* node);
	virtual void visit(SOrderNodeExpr* node){};
	virtual void visit(SOrderNodeExprStmt* node);
	virtual void visit(SOrderNodeIfStmt* node);
	virtual void visit(SOrderNodeWhileStmt* node);
	virtual void visit(SOrderNodeLiteralExpr* node);
	virtual void visit(SOrderNodeStmt* node){};
	virtual void visit(SOrderNodeVardeclStmt* node);
	virtual void visit(SOrderNodeVariable* node);
	virtual void visit(SOrderNodeVariableExpr* node);
	virtual void visit(SOrderIdentifier* node){};
	virtual void visit(SOrderIntegerLiteral* node);
	virtual void visit(SOrderBinaryOperatorExpr* node);
	virtual void visit(SOrderNodeArg* node);
	virtual void visit(SOrderNodeCallExpr* node);
	virtual void visit(TypeDenoter* node){}
	virtual void visit(NodeTop* node){}
	virtual void visit(NodeVardecTop* node);
	virtual void visit(NodeParam* node);
	virtual void visit(NodeMethod* node);
	void finalize();
	virtual ~CommandCompiler();
private:
	uint32_t _mainFunctionPC;
	Step::Enum _step;
	bool _inStatic;
	vTableEntry* vtableFind(string id);
	string _programPath;
	PROGRAM _program;

	uint32_t relpos(uint32_t pos){
		//stack location start at 1
		return _scopeRef.back() - pos;
	}
	list<uint32_t> _scopeRef;
	list<vTableEntry> _vtable;
	//  codepoint, jmppoint
	map<uint32_t, string> _lables;
	map<uint32_t, uint32_t> _interruptHandlers;
	void emitPopStack(uint32_t size);
	void emitPopStackIgnore(uint32_t size);

	void emitPushStack(uint32_t value, uint32_t size);
	void emitPopTopStackToLoc(uint32_t pos, uint32_t size);
	void emitTopStackToLoc(uint32_t pos, bool rel, uint32_t size);
	void emitPushLocToTopStack(uint32_t pos, uint32_t size, bool rel);
	void emitPushTopStackNtimesToStack(uint32_t size);
	void emitCall(string name);
	void emitPushPC();
	uint32_t emitPushRPC();
	void emitNOP();
	void emitEOP();
	void emitReturn();
	void emitBOAddPush();
	void emitBOMinusPush();
	void emitBOAddPop();
	void emitBOMinusPop();
	void emitSysCall(uint32_t pos, uint32_t functionId);
	uint32_t emitJumpToRef();
    uint32_t emitCondJumpToRef();
	uint32_t emitJumpToRef(uint32_t ref);
    uint32_t emitCondJumpToRef(uint32_t ref);	
};

#endif	/* COMMANDCOMPILER_H */

