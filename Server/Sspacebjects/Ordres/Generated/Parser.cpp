#include <stdio.h>
#include "Lexer.h"

#include "../Nodes/SOrderNodes.h"
#include "../Terminals/SOrderTerminals.h"
using namespace anl;
#define BinOp(a,b,c)		new SOrderBinaryOperatorExpr((SOrderNodeExpr*)a, (SOrderTerminal*)b, (SOrderNodeExpr*)c)

//Generated code:
#include <stack>
#include "Parser.h"
using namespace std;

/* Enumeration for all non-terminals */
enum Symbol{
	SYMBOL_error,
	SYMBOL_root,
	SYMBOL_program,
	SYMBOL_top_defs,
	SYMBOL_top_def,
	SYMBOL_topvardecl,
	SYMBOL_method,
	SYMBOL_type,
	SYMBOL_paramsblock,
	SYMBOL_block,
	SYMBOL_expr,
	SYMBOL_stmts,
	SYMBOL_stmt,
	SYMBOL_closedStmt,
	SYMBOL_varDecl,
	SYMBOL_params,
	SYMBOL_param,
	SYMBOL_varexpr,
	SYMBOL_argblock,
	SYMBOL_args,
	SYMBOL_arg
};


/* The following auto generated code expects the function lexer->nextToken() to return a Terminal
 * object pointer (e.g. Terminal*). The terminal object is assumed to have a token() method
 * returning a Token (the enum defined in the header file). The Terminal class must also
 * derivate from a class called Node, which must also be defined.
 * 
 * At last but not least a subclass of Terminal called ErrorTerminal must exist. This class
 * must have a constructor that takes a Terminal pointer as single argument. It must also
 * have a method called discard(Terminal* terminal), which will be called whenever a terminal
 * following an error is discarded.
 */

/** Function for parsing input read from lexer->nextToken() */
SOrderNode* parse(Lexer* lexer){
	stack<SOrderNode*> symbols = stack<SOrderNode*>();
	stack<void*> states = stack<void*>();
	Symbol top_non_terminal;
	SOrderTerminal* current_terminal = lexer->nextToken();
	SOrderNode* result, *arg0, *arg1, *arg2, *arg3;
	goto START;
	/*** States ****/
Shift0:
/*
{root -> ~ program, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
START:
State0:
	states.push(&&Goto0);
	switch(current_terminal->token()){
		case TOKEN_newline: goto Shift65;
		case TOKEN_var: goto Shift55;
		case TOKEN_id: goto Shift1;
		default: goto ERROR;
	}

Goto0:
	switch(top_non_terminal){
		case SYMBOL_program: goto State67;
		case SYMBOL_top_defs: goto State64;
		case SYMBOL_top_def: goto State61;
		case SYMBOL_method: goto State54;
		case SYMBOL_type: goto State2;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift1:
/*
{type -> [id] ~, [id]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State1:
	states.push(&&Goto1);
	switch(current_terminal->token()){
		case TOKEN_id: goto Reduce27;
		default: goto ERROR;
	}

Goto1:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift2:
/*
{method -> type ~ [id] paramsblock block, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State2:
	states.push(&&Goto2);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift3;
		default: goto ERROR;
	}

Goto2:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift3:
/*
{method -> type [id] ~ paramsblock block, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State3:
	states.push(&&Goto3);
	switch(current_terminal->token()){
		case TOKEN_left_p: goto Shift4;
		default: goto ERROR;
	}

Goto3:
	switch(top_non_terminal){
		case SYMBOL_paramsblock: goto State13;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift4:
/*
{paramsblock -> [left_p] ~ params [right_p], [left_c]}
{paramsblock -> [left_p] ~ [right_p], [left_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State4:
	states.push(&&Goto4);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Shift8;
		case TOKEN_id: goto Shift1;
		default: goto ERROR;
	}

Goto4:
	switch(top_non_terminal){
		case SYMBOL_type: goto State11;
		case SYMBOL_params: goto State9;
		case SYMBOL_param: goto State5;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift5:
/*
{params -> param ~ [comma] params, [right_p]}
{params -> param ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State5:
	states.push(&&Goto5);
	switch(current_terminal->token()){
		case TOKEN_comma: goto Shift6;
		case TOKEN_right_p: goto Reduce19;
		default: goto ERROR;
	}

Goto5:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift6:
/*
{params -> param [comma] ~ params, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State6:
	states.push(&&Goto6);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift1;
		default: goto ERROR;
	}

Goto6:
	switch(top_non_terminal){
		case SYMBOL_type: goto State11;
		case SYMBOL_params: goto State7;
		case SYMBOL_param: goto State5;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift7:
/*
{params -> param [comma] params ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State7:
	states.push(&&Goto7);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce18;
		default: goto ERROR;
	}

Goto7:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift8:
/*
{paramsblock -> [left_p] [right_p] ~, [left_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State8:
	states.push(&&Goto8);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce17;
		default: goto ERROR;
	}

Goto8:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift9:
/*
{paramsblock -> [left_p] params ~ [right_p], [left_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State9:
	states.push(&&Goto9);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Shift10;
		default: goto ERROR;
	}

Goto9:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift10:
/*
{paramsblock -> [left_p] params [right_p] ~, [left_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State10:
	states.push(&&Goto10);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce16;
		default: goto ERROR;
	}

Goto10:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift11:
/*
{param -> type ~ [id], [right_p]}
{param -> type ~ [id], [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State11:
	states.push(&&Goto11);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift12;
		default: goto ERROR;
	}

Goto11:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift12:
/*
{param -> type [id] ~, [right_p]}
{param -> type [id] ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State12:
	states.push(&&Goto12);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce20;
		case TOKEN_comma: goto Reduce20;
		default: goto ERROR;
	}

Goto12:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift13:
/*
{method -> type [id] paramsblock ~ block, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State13:
	states.push(&&Goto13);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Shift14;
		default: goto ERROR;
	}

Goto13:
	switch(top_non_terminal){
		case SYMBOL_block: goto State53;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift14:
/*
{block -> [left_c] ~ stmts [right_c], [semicolon]}
{block -> [left_c] ~ stmts [right_c], [right_c]}
{block -> [left_c] ~ stmts [right_c], [int]}
{block -> [left_c] ~ stmts [right_c], [id]}
{block -> [left_c] ~ stmts [right_c], [var]}
{block -> [left_c] ~ stmts [right_c], [if]}
{block -> [left_c] ~ stmts [right_c], [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State14:
	states.push(&&Goto14);
	switch(current_terminal->token()){
		case TOKEN_if: goto Shift23;
		case TOKEN_while: goto Shift16;
		case TOKEN_var: goto Shift47;
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto14:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State45;
		case SYMBOL_stmts: goto State43;
		case SYMBOL_stmt: goto State40;
		case SYMBOL_closedStmt: goto State38;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift15:
/*
{expr -> [int] ~, [semicolon]}
{expr -> [int] ~, [plus]}
{expr -> [int] ~, [minus]}
{expr -> [int] ~, [left_c]}
{expr -> [int] ~, [right_p]}
{expr -> [int] ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State15:
	states.push(&&Goto15);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce35;
		case TOKEN_plus: goto Reduce35;
		case TOKEN_minus: goto Reduce35;
		case TOKEN_left_c: goto Reduce35;
		case TOKEN_right_p: goto Reduce35;
		case TOKEN_comma: goto Reduce35;
		default: goto ERROR;
	}

Goto15:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift16:
/*
{closedStmt -> [while] ~ expr block, [right_c]}
{closedStmt -> [while] ~ expr block, [int]}
{closedStmt -> [while] ~ expr block, [id]}
{closedStmt -> [while] ~ expr block, [var]}
{closedStmt -> [while] ~ expr block, [if]}
{closedStmt -> [while] ~ expr block, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State16:
	states.push(&&Goto16);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto16:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State17;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift17:
/*
{closedStmt -> [while] expr ~ block, [right_c]}
{closedStmt -> [while] expr ~ block, [int]}
{closedStmt -> [while] expr ~ block, [id]}
{closedStmt -> [while] expr ~ block, [var]}
{closedStmt -> [while] expr ~ block, [if]}
{closedStmt -> [while] expr ~ block, [while]}
{expr -> expr ~ [minus] expr, [left_c]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [plus] expr, [left_c]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State17:
	states.push(&&Goto17);
	switch(current_terminal->token()){
		case TOKEN_minus: goto Shift20;
		case TOKEN_plus: goto Shift18;
		case TOKEN_left_c: goto Shift14;
		default: goto ERROR;
	}

Goto17:
	switch(top_non_terminal){
		case SYMBOL_block: goto State22;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift18:
/*
{expr -> expr [plus] ~ expr, [left_c]}
{expr -> expr [plus] ~ expr, [plus]}
{expr -> expr [plus] ~ expr, [minus]}
{expr -> expr [plus] ~ expr, [right_p]}
{expr -> expr [plus] ~ expr, [comma]}
{expr -> expr [plus] ~ expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State18:
	states.push(&&Goto18);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto18:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State19;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift19:
/*
{expr -> expr [plus] expr ~, [left_c]}
{expr -> expr [plus] expr ~, [plus]}
{expr -> expr [plus] expr ~, [minus]}
{expr -> expr [plus] expr ~, [right_p]}
{expr -> expr [plus] expr ~, [comma]}
{expr -> expr [plus] expr ~, [semicolon]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [minus] expr, [left_c]}
{expr -> expr ~ [minus] expr, [right_p]}
{expr -> expr ~ [minus] expr, [comma]}
{expr -> expr ~ [minus] expr, [semicolon]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
{expr -> expr ~ [plus] expr, [left_c]}
{expr -> expr ~ [plus] expr, [right_p]}
{expr -> expr ~ [plus] expr, [comma]}
{expr -> expr ~ [plus] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State19:
	states.push(&&Goto19);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce34;
		case TOKEN_plus: goto Reduce34;
		case TOKEN_right_p: goto Reduce34;
		case TOKEN_comma: goto Reduce34;
		case TOKEN_semicolon: goto Reduce34;
		case TOKEN_minus: goto Shift20;
		default: goto ERROR;
	}

Goto19:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift20:
/*
{expr -> expr [minus] ~ expr, [left_c]}
{expr -> expr [minus] ~ expr, [plus]}
{expr -> expr [minus] ~ expr, [minus]}
{expr -> expr [minus] ~ expr, [right_p]}
{expr -> expr [minus] ~ expr, [comma]}
{expr -> expr [minus] ~ expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State20:
	states.push(&&Goto20);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto20:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State21;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift21:
/*
{expr -> expr [minus] expr ~, [left_c]}
{expr -> expr [minus] expr ~, [plus]}
{expr -> expr [minus] expr ~, [minus]}
{expr -> expr [minus] expr ~, [right_p]}
{expr -> expr [minus] expr ~, [comma]}
{expr -> expr [minus] expr ~, [semicolon]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [minus] expr, [left_c]}
{expr -> expr ~ [minus] expr, [right_p]}
{expr -> expr ~ [minus] expr, [comma]}
{expr -> expr ~ [minus] expr, [semicolon]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
{expr -> expr ~ [plus] expr, [left_c]}
{expr -> expr ~ [plus] expr, [right_p]}
{expr -> expr ~ [plus] expr, [comma]}
{expr -> expr ~ [plus] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State21:
	states.push(&&Goto21);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce33;
		case TOKEN_plus: goto Reduce33;
		case TOKEN_minus: goto Reduce33;
		case TOKEN_right_p: goto Reduce33;
		case TOKEN_comma: goto Reduce33;
		case TOKEN_semicolon: goto Reduce33;
		default: goto ERROR;
	}

Goto21:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift22:
/*
{closedStmt -> [while] expr block ~, [right_c]}
{closedStmt -> [while] expr block ~, [int]}
{closedStmt -> [while] expr block ~, [id]}
{closedStmt -> [while] expr block ~, [var]}
{closedStmt -> [while] expr block ~, [if]}
{closedStmt -> [while] expr block ~, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State22:
	states.push(&&Goto22);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce26;
		case TOKEN_int: goto Reduce26;
		case TOKEN_id: goto Reduce26;
		case TOKEN_var: goto Reduce26;
		case TOKEN_if: goto Reduce26;
		case TOKEN_while: goto Reduce26;
		default: goto ERROR;
	}

Goto22:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift23:
/*
{closedStmt -> [if] ~ expr block, [right_c]}
{closedStmt -> [if] ~ expr block, [int]}
{closedStmt -> [if] ~ expr block, [id]}
{closedStmt -> [if] ~ expr block, [var]}
{closedStmt -> [if] ~ expr block, [if]}
{closedStmt -> [if] ~ expr block, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State23:
	states.push(&&Goto23);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto23:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State24;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift24:
/*
{closedStmt -> [if] expr ~ block, [right_c]}
{closedStmt -> [if] expr ~ block, [int]}
{closedStmt -> [if] expr ~ block, [id]}
{closedStmt -> [if] expr ~ block, [var]}
{closedStmt -> [if] expr ~ block, [if]}
{closedStmt -> [if] expr ~ block, [while]}
{expr -> expr ~ [minus] expr, [left_c]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [plus] expr, [left_c]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State24:
	states.push(&&Goto24);
	switch(current_terminal->token()){
		case TOKEN_minus: goto Shift20;
		case TOKEN_plus: goto Shift18;
		case TOKEN_left_c: goto Shift14;
		default: goto ERROR;
	}

Goto24:
	switch(top_non_terminal){
		case SYMBOL_block: goto State25;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift25:
/*
{closedStmt -> [if] expr block ~, [right_c]}
{closedStmt -> [if] expr block ~, [int]}
{closedStmt -> [if] expr block ~, [id]}
{closedStmt -> [if] expr block ~, [var]}
{closedStmt -> [if] expr block ~, [if]}
{closedStmt -> [if] expr block ~, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State25:
	states.push(&&Goto25);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce25;
		case TOKEN_int: goto Reduce25;
		case TOKEN_id: goto Reduce25;
		case TOKEN_var: goto Reduce25;
		case TOKEN_if: goto Reduce25;
		case TOKEN_while: goto Reduce25;
		default: goto ERROR;
	}

Goto25:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift26:
/*
{expr -> varexpr ~ argblock, [semicolon]}
{expr -> varexpr ~ argblock, [plus]}
{expr -> varexpr ~ argblock, [minus]}
{expr -> varexpr ~ argblock, [left_c]}
{expr -> varexpr ~ argblock, [right_p]}
{expr -> varexpr ~ argblock, [comma]}
{expr -> varexpr ~, [semicolon]}
{expr -> varexpr ~, [plus]}
{expr -> varexpr ~, [minus]}
{expr -> varexpr ~, [left_c]}
{expr -> varexpr ~, [right_p]}
{expr -> varexpr ~, [comma]}
{expr -> varexpr ~ [assignment] expr, [semicolon]}
{expr -> varexpr ~ [assignment] expr, [plus]}
{expr -> varexpr ~ [assignment] expr, [minus]}
{expr -> varexpr ~ [assignment] expr, [left_c]}
{expr -> varexpr ~ [assignment] expr, [right_p]}
{expr -> varexpr ~ [assignment] expr, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State26:
	states.push(&&Goto26);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce37;
		case TOKEN_plus: goto Reduce37;
		case TOKEN_minus: goto Reduce37;
		case TOKEN_left_c: goto Reduce37;
		case TOKEN_right_p: goto Reduce37;
		case TOKEN_comma: goto Reduce37;
		case TOKEN_assignment: goto Shift36;
		case TOKEN_left_p: goto Shift28;
		default: goto ERROR;
	}

Goto26:
	switch(top_non_terminal){
		case SYMBOL_argblock: goto State27;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift27:
/*
{expr -> varexpr argblock ~, [semicolon]}
{expr -> varexpr argblock ~, [plus]}
{expr -> varexpr argblock ~, [minus]}
{expr -> varexpr argblock ~, [left_c]}
{expr -> varexpr argblock ~, [right_p]}
{expr -> varexpr argblock ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State27:
	states.push(&&Goto27);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce36;
		case TOKEN_plus: goto Reduce36;
		case TOKEN_minus: goto Reduce36;
		case TOKEN_left_c: goto Reduce36;
		case TOKEN_right_p: goto Reduce36;
		case TOKEN_comma: goto Reduce36;
		default: goto ERROR;
	}

Goto27:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift28:
/*
{argblock -> [left_p] ~ args [right_p], [semicolon]}
{argblock -> [left_p] ~ args [right_p], [plus]}
{argblock -> [left_p] ~ args [right_p], [minus]}
{argblock -> [left_p] ~ args [right_p], [left_c]}
{argblock -> [left_p] ~ args [right_p], [right_p]}
{argblock -> [left_p] ~ args [right_p], [comma]}
{argblock -> [left_p] ~ [right_p], [semicolon]}
{argblock -> [left_p] ~ [right_p], [plus]}
{argblock -> [left_p] ~ [right_p], [minus]}
{argblock -> [left_p] ~ [right_p], [left_c]}
{argblock -> [left_p] ~ [right_p], [right_p]}
{argblock -> [left_p] ~ [right_p], [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State28:
	states.push(&&Goto28);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Shift34;
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto28:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State35;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_args: goto State32;
		case SYMBOL_arg: goto State29;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift29:
/*
{args -> arg ~ [comma] args, [right_p]}
{args -> arg ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State29:
	states.push(&&Goto29);
	switch(current_terminal->token()){
		case TOKEN_comma: goto Shift30;
		case TOKEN_right_p: goto Reduce31;
		default: goto ERROR;
	}

Goto29:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift30:
/*
{args -> arg [comma] ~ args, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State30:
	states.push(&&Goto30);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto30:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State35;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_args: goto State31;
		case SYMBOL_arg: goto State29;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift31:
/*
{args -> arg [comma] args ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State31:
	states.push(&&Goto31);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce30;
		default: goto ERROR;
	}

Goto31:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift32:
/*
{argblock -> [left_p] args ~ [right_p], [semicolon]}
{argblock -> [left_p] args ~ [right_p], [plus]}
{argblock -> [left_p] args ~ [right_p], [minus]}
{argblock -> [left_p] args ~ [right_p], [left_c]}
{argblock -> [left_p] args ~ [right_p], [right_p]}
{argblock -> [left_p] args ~ [right_p], [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State32:
	states.push(&&Goto32);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Shift33;
		default: goto ERROR;
	}

Goto32:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift33:
/*
{argblock -> [left_p] args [right_p] ~, [semicolon]}
{argblock -> [left_p] args [right_p] ~, [plus]}
{argblock -> [left_p] args [right_p] ~, [minus]}
{argblock -> [left_p] args [right_p] ~, [left_c]}
{argblock -> [left_p] args [right_p] ~, [right_p]}
{argblock -> [left_p] args [right_p] ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State33:
	states.push(&&Goto33);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce28;
		case TOKEN_plus: goto Reduce28;
		case TOKEN_minus: goto Reduce28;
		case TOKEN_left_c: goto Reduce28;
		case TOKEN_right_p: goto Reduce28;
		case TOKEN_comma: goto Reduce28;
		default: goto ERROR;
	}

Goto33:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift34:
/*
{argblock -> [left_p] [right_p] ~, [semicolon]}
{argblock -> [left_p] [right_p] ~, [plus]}
{argblock -> [left_p] [right_p] ~, [minus]}
{argblock -> [left_p] [right_p] ~, [left_c]}
{argblock -> [left_p] [right_p] ~, [right_p]}
{argblock -> [left_p] [right_p] ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State34:
	states.push(&&Goto34);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce29;
		case TOKEN_plus: goto Reduce29;
		case TOKEN_minus: goto Reduce29;
		case TOKEN_left_c: goto Reduce29;
		case TOKEN_right_p: goto Reduce29;
		case TOKEN_comma: goto Reduce29;
		default: goto ERROR;
	}

Goto34:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift35:
/*
{arg -> expr ~, [right_p]}
{arg -> expr ~, [comma]}
{expr -> expr ~ [minus] expr, [right_p]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [minus] expr, [comma]}
{expr -> expr ~ [plus] expr, [right_p]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
{expr -> expr ~ [plus] expr, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State35:
	states.push(&&Goto35);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce32;
		case TOKEN_comma: goto Reduce32;
		case TOKEN_minus: goto Shift20;
		case TOKEN_plus: goto Shift18;
		default: goto ERROR;
	}

Goto35:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift36:
/*
{expr -> varexpr [assignment] ~ expr, [semicolon]}
{expr -> varexpr [assignment] ~ expr, [plus]}
{expr -> varexpr [assignment] ~ expr, [minus]}
{expr -> varexpr [assignment] ~ expr, [left_c]}
{expr -> varexpr [assignment] ~ expr, [right_p]}
{expr -> varexpr [assignment] ~ expr, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State36:
	states.push(&&Goto36);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto36:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State37;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift37:
/*
{expr -> varexpr [assignment] expr ~, [semicolon]}
{expr -> varexpr [assignment] expr ~, [plus]}
{expr -> varexpr [assignment] expr ~, [minus]}
{expr -> varexpr [assignment] expr ~, [left_c]}
{expr -> varexpr [assignment] expr ~, [right_p]}
{expr -> varexpr [assignment] expr ~, [comma]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [minus] expr, [semicolon]}
{expr -> expr ~ [minus] expr, [left_c]}
{expr -> expr ~ [minus] expr, [right_p]}
{expr -> expr ~ [minus] expr, [comma]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
{expr -> expr ~ [plus] expr, [semicolon]}
{expr -> expr ~ [plus] expr, [left_c]}
{expr -> expr ~ [plus] expr, [right_p]}
{expr -> expr ~ [plus] expr, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State37:
	states.push(&&Goto37);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce38;
		case TOKEN_left_c: goto Reduce38;
		case TOKEN_right_p: goto Reduce38;
		case TOKEN_comma: goto Reduce38;
		case TOKEN_minus: goto Shift20;
		case TOKEN_plus: goto Shift18;
		default: goto ERROR;
	}

Goto37:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift38:
/*
{stmts -> closedStmt ~ stmts, [right_c]}
{stmts -> closedStmt ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State38:
	states.push(&&Goto38);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce13;
		case TOKEN_if: goto Shift23;
		case TOKEN_while: goto Shift16;
		case TOKEN_var: goto Shift47;
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto38:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State45;
		case SYMBOL_stmts: goto State39;
		case SYMBOL_stmt: goto State40;
		case SYMBOL_closedStmt: goto State38;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift39:
/*
{stmts -> closedStmt stmts ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State39:
	states.push(&&Goto39);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce11;
		default: goto ERROR;
	}

Goto39:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift40:
/*
{stmts -> stmt ~ [semicolon] stmts, [right_c]}
{stmts -> stmt ~ [semicolon], [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State40:
	states.push(&&Goto40);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Shift41;
		default: goto ERROR;
	}

Goto40:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift41:
/*
{stmts -> stmt [semicolon] ~ stmts, [right_c]}
{stmts -> stmt [semicolon] ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State41:
	states.push(&&Goto41);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce12;
		case TOKEN_if: goto Shift23;
		case TOKEN_while: goto Shift16;
		case TOKEN_var: goto Shift47;
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto41:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State45;
		case SYMBOL_stmts: goto State42;
		case SYMBOL_stmt: goto State40;
		case SYMBOL_closedStmt: goto State38;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift42:
/*
{stmts -> stmt [semicolon] stmts ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State42:
	states.push(&&Goto42);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce10;
		default: goto ERROR;
	}

Goto42:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift43:
/*
{block -> [left_c] stmts ~ [right_c], [semicolon]}
{block -> [left_c] stmts ~ [right_c], [right_c]}
{block -> [left_c] stmts ~ [right_c], [int]}
{block -> [left_c] stmts ~ [right_c], [id]}
{block -> [left_c] stmts ~ [right_c], [var]}
{block -> [left_c] stmts ~ [right_c], [if]}
{block -> [left_c] stmts ~ [right_c], [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State43:
	states.push(&&Goto43);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Shift44;
		default: goto ERROR;
	}

Goto43:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift44:
/*
{block -> [left_c] stmts [right_c] ~, [semicolon]}
{block -> [left_c] stmts [right_c] ~, [right_c]}
{block -> [left_c] stmts [right_c] ~, [int]}
{block -> [left_c] stmts [right_c] ~, [id]}
{block -> [left_c] stmts [right_c] ~, [var]}
{block -> [left_c] stmts [right_c] ~, [if]}
{block -> [left_c] stmts [right_c] ~, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State44:
	states.push(&&Goto44);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce24;
		case TOKEN_right_c: goto Reduce24;
		case TOKEN_int: goto Reduce24;
		case TOKEN_id: goto Reduce24;
		case TOKEN_var: goto Reduce24;
		case TOKEN_if: goto Reduce24;
		case TOKEN_while: goto Reduce24;
		default: goto ERROR;
	}

Goto44:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift45:
/*
{stmt -> expr ~, [semicolon]}
{expr -> expr ~ [minus] expr, [semicolon]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [plus] expr, [semicolon]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State45:
	states.push(&&Goto45);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce14;
		case TOKEN_minus: goto Shift20;
		case TOKEN_plus: goto Shift18;
		default: goto ERROR;
	}

Goto45:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift46:
/*
{varexpr -> [id] ~, [assignment]}
{varexpr -> [id] ~, [semicolon]}
{varexpr -> [id] ~, [left_p]}
{varexpr -> [id] ~, [plus]}
{varexpr -> [id] ~, [minus]}
{varexpr -> [id] ~, [left_c]}
{varexpr -> [id] ~, [right_p]}
{varexpr -> [id] ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State46:
	states.push(&&Goto46);
	switch(current_terminal->token()){
		case TOKEN_assignment: goto Reduce23;
		case TOKEN_semicolon: goto Reduce23;
		case TOKEN_left_p: goto Reduce23;
		case TOKEN_plus: goto Reduce23;
		case TOKEN_minus: goto Reduce23;
		case TOKEN_left_c: goto Reduce23;
		case TOKEN_right_p: goto Reduce23;
		case TOKEN_comma: goto Reduce23;
		default: goto ERROR;
	}

Goto46:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift47:
/*
{stmt -> [var] ~ varDecl, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State47:
	states.push(&&Goto47);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift1;
		default: goto ERROR;
	}

Goto47:
	switch(top_non_terminal){
		case SYMBOL_type: goto State49;
		case SYMBOL_varDecl: goto State48;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift48:
/*
{stmt -> [var] varDecl ~, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State48:
	states.push(&&Goto48);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce15;
		default: goto ERROR;
	}

Goto48:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift49:
/*
{varDecl -> type ~ [id], [semicolon]}
{varDecl -> type ~ [id] [assignment] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State49:
	states.push(&&Goto49);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift50;
		default: goto ERROR;
	}

Goto49:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift50:
/*
{varDecl -> type [id] ~, [semicolon]}
{varDecl -> type [id] ~ [assignment] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State50:
	states.push(&&Goto50);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce21;
		case TOKEN_assignment: goto Shift51;
		default: goto ERROR;
	}

Goto50:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift51:
/*
{varDecl -> type [id] [assignment] ~ expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State51:
	states.push(&&Goto51);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto51:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State52;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift52:
/*
{varDecl -> type [id] [assignment] expr ~, [semicolon]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [minus] expr, [semicolon]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
{expr -> expr ~ [plus] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State52:
	states.push(&&Goto52);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce22;
		case TOKEN_minus: goto Shift20;
		case TOKEN_plus: goto Shift18;
		default: goto ERROR;
	}

Goto52:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift53:
/*
{method -> type [id] paramsblock block ~, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State53:
	states.push(&&Goto53);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce7;
		default: goto ERROR;
	}

Goto53:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift54:
/*
{top_def -> method ~, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State54:
	states.push(&&Goto54);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce6;
		default: goto ERROR;
	}

Goto54:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift55:
/*
{top_def -> [var] ~ topvardecl, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State55:
	states.push(&&Goto55);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift1;
		default: goto ERROR;
	}

Goto55:
	switch(top_non_terminal){
		case SYMBOL_topvardecl: goto State60;
		case SYMBOL_type: goto State56;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift56:
/*
{topvardecl -> type ~ [id], [semicolon]}
{topvardecl -> type ~ [id] [assignment] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State56:
	states.push(&&Goto56);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift57;
		default: goto ERROR;
	}

Goto56:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift57:
/*
{topvardecl -> type [id] ~, [semicolon]}
{topvardecl -> type [id] ~ [assignment] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State57:
	states.push(&&Goto57);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce8;
		case TOKEN_assignment: goto Shift58;
		default: goto ERROR;
	}

Goto57:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift58:
/*
{topvardecl -> type [id] [assignment] ~ expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State58:
	states.push(&&Goto58);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift15;
		case TOKEN_id: goto Shift46;
		default: goto ERROR;
	}

Goto58:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State59;
		case SYMBOL_varexpr: goto State26;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift59:
/*
{topvardecl -> type [id] [assignment] expr ~, [semicolon]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [minus] expr, [semicolon]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
{expr -> expr ~ [plus] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State59:
	states.push(&&Goto59);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce9;
		case TOKEN_minus: goto Shift20;
		case TOKEN_plus: goto Shift18;
		default: goto ERROR;
	}

Goto59:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift60:
/*
{top_def -> [var] topvardecl ~, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State60:
	states.push(&&Goto60);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce5;
		default: goto ERROR;
	}

Goto60:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift61:
/*
{top_defs -> top_def ~ [semicolon] top_defs, [EOF]}
{top_defs -> top_def ~ [semicolon], [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State61:
	states.push(&&Goto61);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Shift62;
		default: goto ERROR;
	}

Goto61:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift62:
/*
{top_defs -> top_def [semicolon] ~ top_defs, [EOF]}
{top_defs -> top_def [semicolon] ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State62:
	states.push(&&Goto62);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce4;
		case TOKEN_var: goto Shift55;
		case TOKEN_id: goto Shift1;
		default: goto ERROR;
	}

Goto62:
	switch(top_non_terminal){
		case SYMBOL_top_defs: goto State63;
		case SYMBOL_top_def: goto State61;
		case SYMBOL_method: goto State54;
		case SYMBOL_type: goto State2;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift63:
/*
{top_defs -> top_def [semicolon] top_defs ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State63:
	states.push(&&Goto63);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce3;
		default: goto ERROR;
	}

Goto63:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift64:
/*
{program -> top_defs ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State64:
	states.push(&&Goto64);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce2;
		default: goto ERROR;
	}

Goto64:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift65:
/*
{program -> [newline] ~ top_defs, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State65:
	states.push(&&Goto65);
	switch(current_terminal->token()){
		case TOKEN_var: goto Shift55;
		case TOKEN_id: goto Shift1;
		default: goto ERROR;
	}

Goto65:
	switch(top_non_terminal){
		case SYMBOL_top_defs: goto State66;
		case SYMBOL_top_def: goto State61;
		case SYMBOL_method: goto State54;
		case SYMBOL_type: goto State2;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift66:
/*
{program -> [newline] top_defs ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State66:
	states.push(&&Goto66);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce1;
		default: goto ERROR;
	}

Goto66:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift67:
/*
{root -> program ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State67:
	states.push(&&Goto67);
	switch(current_terminal->token()){
		case TOKEN_EOF: return symbols.top();
		default: goto ERROR;
	}

Goto67:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

	/*** Reductions ****/
Reduce0: //root -> program
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_root;
	goto *states.top();

Reduce1: //program -> [newline] top_defs
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg1;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_program;
	goto *states.top();

Reduce2: //program -> top_defs
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_program;
	goto *states.top();

Reduce3: //top_defs -> top_def [semicolon] top_defs
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	((NodeTop*)arg0)->setNext((NodeTop*)arg2); result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_top_defs;
	goto *states.top();

Reduce4: //top_defs -> top_def [semicolon]
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_top_defs;
	goto *states.top();

Reduce5: //top_def -> [var] topvardecl
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg1;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_top_def;
	goto *states.top();

Reduce6: //top_def -> method
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_top_def;
	goto *states.top();

Reduce7: //method -> type [id] paramsblock block
	arg3 = symbols.top();
	symbols.pop();
	states.pop();
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE method"<<endl;result = new NodeMethod((TypeDenoter*)arg0, (SOrderIdentifier*)arg1, (NodeParam*)arg2, (SOrderNodeStmt*)arg3);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_method;
	goto *states.top();

Reduce8: //topvardecl -> type [id]
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE top id"<<endl;result = new NodeVardecTop(((TypeDenoter*)arg0),(SOrderIdentifier*)arg1, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_topvardecl;
	goto *states.top();

Reduce9: //topvardecl -> type [id] [assignment] expr
	arg3 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE top id assignment expr"<<endl;result = new NodeVardecTop(((TypeDenoter*)arg0), (SOrderIdentifier*)arg1,(SOrderNodeExpr*)arg3);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_topvardecl;
	goto *states.top();

Reduce10: //stmts -> stmt [semicolon] stmts
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE stmt semicolon stmts"<<endl;((SOrderNodeStmt*)arg0)->setNext((SOrderNodeStmt*)arg2); result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_stmts;
	goto *states.top();

Reduce11: //stmts -> closedStmt stmts
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE stmt semicolon stmts"<<endl;((SOrderNodeStmt*)arg0)->setNext((SOrderNodeStmt*)arg1); result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_stmts;
	goto *states.top();

Reduce12: //stmts -> stmt [semicolon]
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE stmt"<<endl;result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_stmts;
	goto *states.top();

Reduce13: //stmts -> closedStmt
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE stmt semicolon stmts"<<endl; result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_stmts;
	goto *states.top();

Reduce14: //stmt -> expr
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE expr"<<endl; result = new SOrderNodeExprStmt((SOrderNodeExpr*)arg0);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_stmt;
	goto *states.top();

Reduce15: //stmt -> [var] varDecl
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE var varDecl"<<endl;result = arg1;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_stmt;
	goto *states.top();

Reduce16: //paramsblock -> [left_p] params [right_p]
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg1;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_paramsblock;
	goto *states.top();

Reduce17: //paramsblock -> [left_p] [right_p]
	delete symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = NULL;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_paramsblock;
	goto *states.top();

Reduce18: //params -> param [comma] params
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	((NodeParam*)arg0)->setNext((NodeParam*)arg2); result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_params;
	goto *states.top();

Reduce19: //params -> param
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_params;
	goto *states.top();

Reduce20: //param -> type [id]
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = new NodeParam((TypeDenoter*)arg0, (SOrderIdentifier*)arg1);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_param;
	goto *states.top();

Reduce21: //varDecl -> type [id]
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE id"<<endl;result = new SOrderNodeVardeclStmt(((TypeDenoter*)arg0),(SOrderIdentifier*)arg1, NULL, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_varDecl;
	goto *states.top();

Reduce22: //varDecl -> type [id] [assignment] expr
	arg3 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE id assignment expr"<<endl;result = new SOrderNodeVardeclStmt(((TypeDenoter*)arg0), (SOrderIdentifier*)arg1,(SOrderNodeExpr*)arg3, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_varDecl;
	goto *states.top();

Reduce23: //varexpr -> [id]
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE id"<<endl;result = new SOrderNodeVariable((SOrderIdentifier*)arg0);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_varexpr;
	goto *states.top();

Reduce24: //block -> [left_c] stmts [right_c]
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE block"<<endl;result = arg1;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_block;
	goto *states.top();

Reduce25: //closedStmt -> [if] expr block
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE closedStmt"<<endl; result = new SOrderNodeIfStmt((SOrderNodeExpr*)arg1, (SOrderNodeStmt*)arg2, NULL, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_closedStmt;
	goto *states.top();

Reduce26: //closedStmt -> [while] expr block
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE closedStmt"<<endl; result = new SOrderNodeWhileStmt((SOrderNodeExpr*)arg1, (SOrderNodeStmt*)arg2, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_closedStmt;
	goto *states.top();

Reduce27: //type -> [id]
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = new TypeDenoter((SOrderIdentifier*)arg0);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_type;
	goto *states.top();

Reduce28: //argblock -> [left_p] args [right_p]
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE argblock"<<endl; result = arg1;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_argblock;
	goto *states.top();

Reduce29: //argblock -> [left_p] [right_p]
	delete symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE argblock"<<endl; result = NULL;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_argblock;
	goto *states.top();

Reduce30: //args -> arg [comma] args
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE args"<<endl; ((SOrderNodeArg*)arg0)->setNext((SOrderNodeArg*)arg2); result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_args;
	goto *states.top();

Reduce31: //args -> arg
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE args"<<endl; result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_args;
	goto *states.top();

Reduce32: //arg -> expr
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE arg"<<endl; result = new SOrderNodeArg((SOrderNodeExpr*)arg0);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_arg;
	goto *states.top();

Reduce33: //expr -> expr [minus] expr
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE minus"<<endl; result = BinOp(arg0, arg1, arg2);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_expr;
	goto *states.top();

Reduce34: //expr -> expr [plus] expr
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE plus"<<endl; result = BinOp(arg0, arg1, arg2);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_expr;
	goto *states.top();

Reduce35: //expr -> [int]
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE int"<<endl;result = new SOrderNodeLiteralExpr((SOrderIntegerLiteral*)arg0);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_expr;
	goto *states.top();

Reduce36: //expr -> varexpr argblock
	arg1 = symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE call"<<endl; result = new SOrderNodeCallExpr(new SOrderNodeVariableExpr((SOrderNodeVariable*)arg0), (SOrderNodeArg*)arg1);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_expr;
	goto *states.top();

Reduce37: //expr -> varexpr
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE varexpr"<<endl;result = new SOrderNodeVariableExpr((SOrderNodeVariable*)arg0);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_expr;
	goto *states.top();

Reduce38: //expr -> varexpr [assignment] expr
	arg2 = symbols.top();
	symbols.pop();
	states.pop();
	delete symbols.top();
	symbols.pop();
	states.pop();
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE varexpr assignment expr"<<endl;result = new SOrderNodeAssignExpr((SOrderNodeVariable*)arg0, (SOrderNodeExpr*)arg2);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_expr;
	goto *states.top();


ERROR:
	current_terminal = new SOrderErrorTerminal(current_terminal);
	top_non_terminal = SYMBOL_error;
	goto *states.top();
FATAL_ERROR:
	fprintf(stderr, "Fatal error occured, this shouldn't be possible!");
	exit(9);
}

string TokenToString(Token token){
	switch(token){
		case TOKEN_EOF: return "EOF";
		case TOKEN_newline: return "newline";
		case TOKEN_semicolon: return "semicolon";
		case TOKEN_var: return "var";
		case TOKEN_id: return "id";
		case TOKEN_assignment: return "assignment";
		case TOKEN_left_p: return "left_p";
		case TOKEN_right_p: return "right_p";
		case TOKEN_comma: return "comma";
		case TOKEN_left_c: return "left_c";
		case TOKEN_right_c: return "right_c";
		case TOKEN_if: return "if";
		case TOKEN_while: return "while";
		case TOKEN_minus: return "minus";
		case TOKEN_plus: return "plus";
		case TOKEN_int: return "int";
		default: return "Unknown token";
	}
}


