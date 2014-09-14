#include <stdio.h>
#include "Lexer.h"

#include "../Nodes/SOrderNodes.h"
#include "../Terminals/SOrderTerminals.h"
#define BinOp(a,b,c)		new BinaryOperatorExpr((ExprNode*)a, (Terminal*)b, (ExprNode*)c)

//Generated code:
#include <stack>
#include ".h"
using namespace std;

/* Enumeration for all non-terminals */
enum Symbol{
	SYMBOL_error,
	SYMBOL_root,
	SYMBOL_program,
	SYMBOL_stmts,
	SYMBOL_stmt,
	SYMBOL_closedStmt,
	SYMBOL_expr,
	SYMBOL_varDecl,
	SYMBOL_varexpr,
	SYMBOL_block,
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
	SOrderNode* result, *arg0, *arg2, *arg1;
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
		case TOKEN_var: goto Shift21;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		case TOKEN_if: goto Shift2;
		default: goto ERROR;
	}

Goto0:
	switch(top_non_terminal){
		case SYMBOL_program: goto State33;
		case SYMBOL_stmts: goto State32;
		case SYMBOL_stmt: goto State29;
		case SYMBOL_closedStmt: goto State27;
		case SYMBOL_expr: goto State26;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift1:
/*
{expr -> [int] ~, [semicolon]}
{expr -> [int] ~, [left_p]}
{expr -> [int] ~, [left_c]}
{expr -> [int] ~, [right_p]}
{expr -> [int] ~, [comma]}
{expr -> [int] ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State1:
	states.push(&&Goto1);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce17;
		case TOKEN_left_p: goto Reduce17;
		case TOKEN_left_c: goto Reduce17;
		case TOKEN_right_p: goto Reduce17;
		case TOKEN_comma: goto Reduce17;
		case TOKEN_right_c: goto Reduce17;
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
{closedStmt -> [if] ~ expr block, [int]}
{closedStmt -> [if] ~ expr block, [id]}
{closedStmt -> [if] ~ expr block, [var]}
{closedStmt -> [if] ~ expr block, [if]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State2:
	states.push(&&Goto2);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		default: goto ERROR;
	}

Goto2:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State3;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift3:
/*
{closedStmt -> [if] expr ~ block, [int]}
{closedStmt -> [if] expr ~ block, [id]}
{closedStmt -> [if] expr ~ block, [var]}
{closedStmt -> [if] expr ~ block, [if]}
{expr -> expr ~ argblock, [left_c]}
{expr -> expr ~ argblock, [left_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State3:
	states.push(&&Goto3);
	switch(current_terminal->token()){
		case TOKEN_left_p: goto Shift4;
		case TOKEN_left_c: goto Shift13;
		default: goto ERROR;
	}

Goto3:
	switch(top_non_terminal){
		case SYMBOL_block: goto State16;
		case SYMBOL_argblock: goto State12;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift4:
/*
{argblock -> [left_p] ~ args [right_p], [left_c]}
{argblock -> [left_p] ~ args [right_p], [left_p]}
{argblock -> [left_p] ~ args [right_p], [right_p]}
{argblock -> [left_p] ~ args [right_p], [comma]}
{argblock -> [left_p] ~ args [right_p], [semicolon]}
{argblock -> [left_p] ~ args [right_p], [right_c]}
{argblock -> [left_p] ~ [right_p], [left_c]}
{argblock -> [left_p] ~ [right_p], [left_p]}
{argblock -> [left_p] ~ [right_p], [right_p]}
{argblock -> [left_p] ~ [right_p], [comma]}
{argblock -> [left_p] ~ [right_p], [semicolon]}
{argblock -> [left_p] ~ [right_p], [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State4:
	states.push(&&Goto4);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Shift8;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		default: goto ERROR;
	}

Goto4:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State11;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_args: goto State9;
		case SYMBOL_arg: goto State5;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift5:
/*
{args -> arg ~ [comma] args, [right_p]}
{args -> arg ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State5:
	states.push(&&Goto5);
	switch(current_terminal->token()){
		case TOKEN_comma: goto Shift6;
		case TOKEN_right_p: goto Reduce15;
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
{args -> arg [comma] ~ args, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State6:
	states.push(&&Goto6);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		default: goto ERROR;
	}

Goto6:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State11;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_args: goto State7;
		case SYMBOL_arg: goto State5;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift7:
/*
{args -> arg [comma] args ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State7:
	states.push(&&Goto7);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce14;
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
{argblock -> [left_p] [right_p] ~, [left_c]}
{argblock -> [left_p] [right_p] ~, [left_p]}
{argblock -> [left_p] [right_p] ~, [right_p]}
{argblock -> [left_p] [right_p] ~, [comma]}
{argblock -> [left_p] [right_p] ~, [semicolon]}
{argblock -> [left_p] [right_p] ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State8:
	states.push(&&Goto8);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce13;
		case TOKEN_left_p: goto Reduce13;
		case TOKEN_right_p: goto Reduce13;
		case TOKEN_comma: goto Reduce13;
		case TOKEN_semicolon: goto Reduce13;
		case TOKEN_right_c: goto Reduce13;
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
{argblock -> [left_p] args ~ [right_p], [left_c]}
{argblock -> [left_p] args ~ [right_p], [left_p]}
{argblock -> [left_p] args ~ [right_p], [right_p]}
{argblock -> [left_p] args ~ [right_p], [comma]}
{argblock -> [left_p] args ~ [right_p], [semicolon]}
{argblock -> [left_p] args ~ [right_p], [right_c]}
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
{argblock -> [left_p] args [right_p] ~, [left_c]}
{argblock -> [left_p] args [right_p] ~, [left_p]}
{argblock -> [left_p] args [right_p] ~, [right_p]}
{argblock -> [left_p] args [right_p] ~, [comma]}
{argblock -> [left_p] args [right_p] ~, [semicolon]}
{argblock -> [left_p] args [right_p] ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State10:
	states.push(&&Goto10);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce12;
		case TOKEN_left_p: goto Reduce12;
		case TOKEN_right_p: goto Reduce12;
		case TOKEN_comma: goto Reduce12;
		case TOKEN_semicolon: goto Reduce12;
		case TOKEN_right_c: goto Reduce12;
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
{arg -> expr ~, [right_p]}
{arg -> expr ~, [comma]}
{expr -> expr ~ argblock, [right_p]}
{expr -> expr ~ argblock, [left_p]}
{expr -> expr ~ argblock, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State11:
	states.push(&&Goto11);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce16;
		case TOKEN_comma: goto Reduce16;
		case TOKEN_left_p: goto Shift4;
		default: goto ERROR;
	}

Goto11:
	switch(top_non_terminal){
		case SYMBOL_argblock: goto State12;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift12:
/*
{expr -> expr argblock ~, [left_c]}
{expr -> expr argblock ~, [left_p]}
{expr -> expr argblock ~, [right_p]}
{expr -> expr argblock ~, [comma]}
{expr -> expr argblock ~, [semicolon]}
{expr -> expr argblock ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State12:
	states.push(&&Goto12);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce20;
		case TOKEN_left_p: goto Reduce20;
		case TOKEN_right_p: goto Reduce20;
		case TOKEN_comma: goto Reduce20;
		case TOKEN_semicolon: goto Reduce20;
		case TOKEN_right_c: goto Reduce20;
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
{block -> [left_c] ~ stmt [right_c], [int]}
{block -> [left_c] ~ stmt [right_c], [id]}
{block -> [left_c] ~ stmt [right_c], [var]}
{block -> [left_c] ~ stmt [right_c], [if]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State13:
	states.push(&&Goto13);
	switch(current_terminal->token()){
		case TOKEN_var: goto Shift21;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		default: goto ERROR;
	}

Goto13:
	switch(top_non_terminal){
		case SYMBOL_stmt: goto State14;
		case SYMBOL_expr: goto State26;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift14:
/*
{block -> [left_c] stmt ~ [right_c], [int]}
{block -> [left_c] stmt ~ [right_c], [id]}
{block -> [left_c] stmt ~ [right_c], [var]}
{block -> [left_c] stmt ~ [right_c], [if]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State14:
	states.push(&&Goto14);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Shift15;
		default: goto ERROR;
	}

Goto14:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift15:
/*
{block -> [left_c] stmt [right_c] ~, [int]}
{block -> [left_c] stmt [right_c] ~, [id]}
{block -> [left_c] stmt [right_c] ~, [var]}
{block -> [left_c] stmt [right_c] ~, [if]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State15:
	states.push(&&Goto15);
	switch(current_terminal->token()){
		case TOKEN_int: goto Reduce10;
		case TOKEN_id: goto Reduce10;
		case TOKEN_var: goto Reduce10;
		case TOKEN_if: goto Reduce10;
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
{closedStmt -> [if] expr block ~, [int]}
{closedStmt -> [if] expr block ~, [id]}
{closedStmt -> [if] expr block ~, [var]}
{closedStmt -> [if] expr block ~, [if]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State16:
	states.push(&&Goto16);
	switch(current_terminal->token()){
		case TOKEN_int: goto Reduce11;
		case TOKEN_id: goto Reduce11;
		case TOKEN_var: goto Reduce11;
		case TOKEN_if: goto Reduce11;
		default: goto ERROR;
	}

Goto16:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift17:
/*
{expr -> varexpr ~, [semicolon]}
{expr -> varexpr ~, [left_p]}
{expr -> varexpr ~, [left_c]}
{expr -> varexpr ~, [right_p]}
{expr -> varexpr ~, [comma]}
{expr -> varexpr ~, [right_c]}
{expr -> varexpr ~ [assignment] expr, [semicolon]}
{expr -> varexpr ~ [assignment] expr, [left_p]}
{expr -> varexpr ~ [assignment] expr, [left_c]}
{expr -> varexpr ~ [assignment] expr, [right_p]}
{expr -> varexpr ~ [assignment] expr, [comma]}
{expr -> varexpr ~ [assignment] expr, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State17:
	states.push(&&Goto17);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce18;
		case TOKEN_left_p: goto Reduce18;
		case TOKEN_left_c: goto Reduce18;
		case TOKEN_right_p: goto Reduce18;
		case TOKEN_comma: goto Reduce18;
		case TOKEN_right_c: goto Reduce18;
		case TOKEN_assignment: goto Shift18;
		default: goto ERROR;
	}

Goto17:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift18:
/*
{expr -> varexpr [assignment] ~ expr, [semicolon]}
{expr -> varexpr [assignment] ~ expr, [left_p]}
{expr -> varexpr [assignment] ~ expr, [left_c]}
{expr -> varexpr [assignment] ~ expr, [right_p]}
{expr -> varexpr [assignment] ~ expr, [comma]}
{expr -> varexpr [assignment] ~ expr, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State18:
	states.push(&&Goto18);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		default: goto ERROR;
	}

Goto18:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State19;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift19:
/*
{expr -> varexpr [assignment] expr ~, [semicolon]}
{expr -> varexpr [assignment] expr ~, [left_p]}
{expr -> varexpr [assignment] expr ~, [left_c]}
{expr -> varexpr [assignment] expr ~, [right_p]}
{expr -> varexpr [assignment] expr ~, [comma]}
{expr -> varexpr [assignment] expr ~, [right_c]}
{expr -> expr ~ argblock, [left_p]}
{expr -> expr ~ argblock, [semicolon]}
{expr -> expr ~ argblock, [left_c]}
{expr -> expr ~ argblock, [right_p]}
{expr -> expr ~ argblock, [comma]}
{expr -> expr ~ argblock, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State19:
	states.push(&&Goto19);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce19;
		case TOKEN_left_c: goto Reduce19;
		case TOKEN_right_p: goto Reduce19;
		case TOKEN_comma: goto Reduce19;
		case TOKEN_right_c: goto Reduce19;
		case TOKEN_left_p: goto Shift4;
		default: goto ERROR;
	}

Goto19:
	switch(top_non_terminal){
		case SYMBOL_argblock: goto State12;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift20:
/*
{varexpr -> [id] ~, [assignment]}
{varexpr -> [id] ~, [left_p]}
{varexpr -> [id] ~, [semicolon]}
{varexpr -> [id] ~, [left_c]}
{varexpr -> [id] ~, [right_p]}
{varexpr -> [id] ~, [comma]}
{varexpr -> [id] ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State20:
	states.push(&&Goto20);
	switch(current_terminal->token()){
		case TOKEN_assignment: goto Reduce9;
		case TOKEN_left_p: goto Reduce9;
		case TOKEN_semicolon: goto Reduce9;
		case TOKEN_left_c: goto Reduce9;
		case TOKEN_right_p: goto Reduce9;
		case TOKEN_comma: goto Reduce9;
		case TOKEN_right_c: goto Reduce9;
		default: goto ERROR;
	}

Goto20:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift21:
/*
{stmt -> [var] ~ varDecl, [semicolon]}
{stmt -> [var] ~ varDecl, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State21:
	states.push(&&Goto21);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift22;
		default: goto ERROR;
	}

Goto21:
	switch(top_non_terminal){
		case SYMBOL_varDecl: goto State25;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift22:
/*
{varDecl -> [id] ~, [semicolon]}
{varDecl -> [id] ~, [right_c]}
{varDecl -> [id] ~ [assignment] expr, [semicolon]}
{varDecl -> [id] ~ [assignment] expr, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State22:
	states.push(&&Goto22);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce7;
		case TOKEN_right_c: goto Reduce7;
		case TOKEN_assignment: goto Shift23;
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
{varDecl -> [id] [assignment] ~ expr, [semicolon]}
{varDecl -> [id] [assignment] ~ expr, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State23:
	states.push(&&Goto23);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		default: goto ERROR;
	}

Goto23:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State24;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift24:
/*
{varDecl -> [id] [assignment] expr ~, [semicolon]}
{varDecl -> [id] [assignment] expr ~, [right_c]}
{expr -> expr ~ argblock, [left_p]}
{expr -> expr ~ argblock, [semicolon]}
{expr -> expr ~ argblock, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State24:
	states.push(&&Goto24);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce8;
		case TOKEN_right_c: goto Reduce8;
		case TOKEN_left_p: goto Shift4;
		default: goto ERROR;
	}

Goto24:
	switch(top_non_terminal){
		case SYMBOL_argblock: goto State12;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift25:
/*
{stmt -> [var] varDecl ~, [semicolon]}
{stmt -> [var] varDecl ~, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State25:
	states.push(&&Goto25);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce6;
		case TOKEN_right_c: goto Reduce6;
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
{stmt -> expr ~, [semicolon]}
{stmt -> expr ~, [right_c]}
{expr -> expr ~ argblock, [semicolon]}
{expr -> expr ~ argblock, [left_p]}
{expr -> expr ~ argblock, [right_c]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State26:
	states.push(&&Goto26);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce5;
		case TOKEN_right_c: goto Reduce5;
		case TOKEN_left_p: goto Shift4;
		default: goto ERROR;
	}

Goto26:
	switch(top_non_terminal){
		case SYMBOL_argblock: goto State12;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift27:
/*
{stmts -> closedStmt ~ stmts, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State27:
	states.push(&&Goto27);
	switch(current_terminal->token()){
		case TOKEN_var: goto Shift21;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		case TOKEN_if: goto Shift2;
		default: goto ERROR;
	}

Goto27:
	switch(top_non_terminal){
		case SYMBOL_stmts: goto State28;
		case SYMBOL_stmt: goto State29;
		case SYMBOL_closedStmt: goto State27;
		case SYMBOL_expr: goto State26;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift28:
/*
{stmts -> closedStmt stmts ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State28:
	states.push(&&Goto28);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce3;
		default: goto ERROR;
	}

Goto28:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift29:
/*
{stmts -> stmt ~ [semicolon] stmts, [EOF]}
{stmts -> stmt ~ [semicolon], [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State29:
	states.push(&&Goto29);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Shift30;
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
{stmts -> stmt [semicolon] ~ stmts, [EOF]}
{stmts -> stmt [semicolon] ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State30:
	states.push(&&Goto30);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce4;
		case TOKEN_var: goto Shift21;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift20;
		case TOKEN_if: goto Shift2;
		default: goto ERROR;
	}

Goto30:
	switch(top_non_terminal){
		case SYMBOL_stmts: goto State31;
		case SYMBOL_stmt: goto State29;
		case SYMBOL_closedStmt: goto State27;
		case SYMBOL_expr: goto State26;
		case SYMBOL_varexpr: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift31:
/*
{stmts -> stmt [semicolon] stmts ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State31:
	states.push(&&Goto31);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce2;
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
{program -> stmts ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State32:
	states.push(&&Goto32);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce1;
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
{root -> program ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State33:
	states.push(&&Goto33);
	switch(current_terminal->token()){
		case TOKEN_EOF: return symbols.top();
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

Reduce1: //program -> stmts
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE stmts"<<endl;result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_program;
	goto *states.top();

Reduce2: //stmts -> stmt [semicolon] stmts
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

Reduce3: //stmts -> closedStmt stmts
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

Reduce4: //stmts -> stmt [semicolon]
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

Reduce5: //stmt -> expr
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

Reduce6: //stmt -> [var] varDecl
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

Reduce7: //varDecl -> [id]
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	cerr<<"PARSE id"<<endl;result = new SOrderNodeVardeclStmt((SOrderIdentifier*)arg0, NULL, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_varDecl;
	goto *states.top();

Reduce8: //varDecl -> [id] [assignment] expr
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
	cerr<<"PARSE id assignment expr"<<endl;result = new SOrderNodeVardeclStmt((SOrderIdentifier*)arg0,(SOrderNodeExpr*)arg2, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_varDecl;
	goto *states.top();

Reduce9: //varexpr -> [id]
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

Reduce10: //block -> [left_c] stmt [right_c]
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
	top_non_terminal = SYMBOL_block;
	goto *states.top();

Reduce11: //closedStmt -> [if] expr block
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
	result = new IfStmt((ExprNode*)arg1, (StmtNode*)arg2);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_closedStmt;
	goto *states.top();

Reduce12: //argblock -> [left_p] args [right_p]
	delete symbols.top();
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
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_argblock;
	goto *states.top();

Reduce13: //argblock -> [left_p] [right_p]
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
	top_non_terminal = SYMBOL_argblock;
	goto *states.top();

Reduce14: //args -> arg [comma] args
	delete symbols.top();
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
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_args;
	goto *states.top();

Reduce15: //args -> arg
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_args;
	goto *states.top();

Reduce16: //arg -> expr
	arg0 = symbols.top();
	symbols.pop();
	states.pop();
	result = NULL;
	{
	result = arg0;
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_arg;
	goto *states.top();

Reduce17: //expr -> [int]
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

Reduce18: //expr -> varexpr
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

Reduce19: //expr -> varexpr [assignment] expr
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

Reduce20: //expr -> expr argblock
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
		case TOKEN_semicolon: return "semicolon";
		case TOKEN_var: return "var";
		case TOKEN_id: return "id";
		case TOKEN_assignment: return "assignment";
		case TOKEN_left_c: return "left_c";
		case TOKEN_right_c: return "right_c";
		case TOKEN_if: return "if";
		case TOKEN_left_p: return "left_p";
		case TOKEN_right_p: return "right_p";
		case TOKEN_comma: return "comma";
		case TOKEN_int: return "int";
		default: return "Unknown token";
	}
}


