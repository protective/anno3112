#include <stdio.h>
#include "Lexer.h"

#include "../Nodes/SOrderNodes.h"
#include "../Terminals/SOrderTerminals.h"
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
		case TOKEN_var: goto Shift28;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		case TOKEN_if: goto Shift12;
		case TOKEN_while: goto Shift2;
		default: goto ERROR;
	}

Goto0:
	switch(top_non_terminal){
		case SYMBOL_program: goto State40;
		case SYMBOL_stmts: goto State39;
		case SYMBOL_stmt: goto State36;
		case SYMBOL_closedStmt: goto State34;
		case SYMBOL_expr: goto State33;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift1:
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
State1:
	states.push(&&Goto1);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce20;
		case TOKEN_plus: goto Reduce20;
		case TOKEN_minus: goto Reduce20;
		case TOKEN_left_c: goto Reduce20;
		case TOKEN_right_p: goto Reduce20;
		case TOKEN_comma: goto Reduce20;
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
{closedStmt -> [while] ~ expr block, [int]}
{closedStmt -> [while] ~ expr block, [id]}
{closedStmt -> [while] ~ expr block, [var]}
{closedStmt -> [while] ~ expr block, [if]}
{closedStmt -> [while] ~ expr block, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State2:
	states.push(&&Goto2);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto2:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State3;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift3:
/*
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
State3:
	states.push(&&Goto3);
	switch(current_terminal->token()){
		case TOKEN_minus: goto Shift6;
		case TOKEN_plus: goto Shift4;
		case TOKEN_left_c: goto Shift8;
		default: goto ERROR;
	}

Goto3:
	switch(top_non_terminal){
		case SYMBOL_block: goto State11;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift4:
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
State4:
	states.push(&&Goto4);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto4:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State5;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift5:
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
State5:
	states.push(&&Goto5);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce19;
		case TOKEN_plus: goto Reduce19;
		case TOKEN_right_p: goto Reduce19;
		case TOKEN_comma: goto Reduce19;
		case TOKEN_semicolon: goto Reduce19;
		case TOKEN_minus: goto Shift6;
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
{expr -> expr [minus] ~ expr, [left_c]}
{expr -> expr [minus] ~ expr, [plus]}
{expr -> expr [minus] ~ expr, [minus]}
{expr -> expr [minus] ~ expr, [right_p]}
{expr -> expr [minus] ~ expr, [comma]}
{expr -> expr [minus] ~ expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State6:
	states.push(&&Goto6);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto6:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State7;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift7:
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
State7:
	states.push(&&Goto7);
	switch(current_terminal->token()){
		case TOKEN_left_c: goto Reduce18;
		case TOKEN_plus: goto Reduce18;
		case TOKEN_minus: goto Reduce18;
		case TOKEN_right_p: goto Reduce18;
		case TOKEN_comma: goto Reduce18;
		case TOKEN_semicolon: goto Reduce18;
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
{block -> [left_c] ~ stmts [right_c], [int]}
{block -> [left_c] ~ stmts [right_c], [id]}
{block -> [left_c] ~ stmts [right_c], [var]}
{block -> [left_c] ~ stmts [right_c], [if]}
{block -> [left_c] ~ stmts [right_c], [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State8:
	states.push(&&Goto8);
	switch(current_terminal->token()){
		case TOKEN_var: goto Shift28;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		case TOKEN_if: goto Shift12;
		case TOKEN_while: goto Shift2;
		default: goto ERROR;
	}

Goto8:
	switch(top_non_terminal){
		case SYMBOL_stmts: goto State9;
		case SYMBOL_stmt: goto State36;
		case SYMBOL_closedStmt: goto State34;
		case SYMBOL_expr: goto State33;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift9:
/*
{block -> [left_c] stmts ~ [right_c], [int]}
{block -> [left_c] stmts ~ [right_c], [id]}
{block -> [left_c] stmts ~ [right_c], [var]}
{block -> [left_c] stmts ~ [right_c], [if]}
{block -> [left_c] stmts ~ [right_c], [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State9:
	states.push(&&Goto9);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Shift10;
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
{block -> [left_c] stmts [right_c] ~, [int]}
{block -> [left_c] stmts [right_c] ~, [id]}
{block -> [left_c] stmts [right_c] ~, [var]}
{block -> [left_c] stmts [right_c] ~, [if]}
{block -> [left_c] stmts [right_c] ~, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State10:
	states.push(&&Goto10);
	switch(current_terminal->token()){
		case TOKEN_int: goto Reduce10;
		case TOKEN_id: goto Reduce10;
		case TOKEN_var: goto Reduce10;
		case TOKEN_if: goto Reduce10;
		case TOKEN_while: goto Reduce10;
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
{closedStmt -> [while] expr block ~, [int]}
{closedStmt -> [while] expr block ~, [id]}
{closedStmt -> [while] expr block ~, [var]}
{closedStmt -> [while] expr block ~, [if]}
{closedStmt -> [while] expr block ~, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State11:
	states.push(&&Goto11);
	switch(current_terminal->token()){
		case TOKEN_int: goto Reduce12;
		case TOKEN_id: goto Reduce12;
		case TOKEN_var: goto Reduce12;
		case TOKEN_if: goto Reduce12;
		case TOKEN_while: goto Reduce12;
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
{closedStmt -> [if] ~ expr block, [int]}
{closedStmt -> [if] ~ expr block, [id]}
{closedStmt -> [if] ~ expr block, [var]}
{closedStmt -> [if] ~ expr block, [if]}
{closedStmt -> [if] ~ expr block, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State12:
	states.push(&&Goto12);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto12:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State13;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift13:
/*
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
State13:
	states.push(&&Goto13);
	switch(current_terminal->token()){
		case TOKEN_minus: goto Shift6;
		case TOKEN_plus: goto Shift4;
		case TOKEN_left_c: goto Shift8;
		default: goto ERROR;
	}

Goto13:
	switch(top_non_terminal){
		case SYMBOL_block: goto State14;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift14:
/*
{closedStmt -> [if] expr block ~, [int]}
{closedStmt -> [if] expr block ~, [id]}
{closedStmt -> [if] expr block ~, [var]}
{closedStmt -> [if] expr block ~, [if]}
{closedStmt -> [if] expr block ~, [while]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State14:
	states.push(&&Goto14);
	switch(current_terminal->token()){
		case TOKEN_int: goto Reduce11;
		case TOKEN_id: goto Reduce11;
		case TOKEN_var: goto Reduce11;
		case TOKEN_if: goto Reduce11;
		case TOKEN_while: goto Reduce11;
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
State15:
	states.push(&&Goto15);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce22;
		case TOKEN_plus: goto Reduce22;
		case TOKEN_minus: goto Reduce22;
		case TOKEN_left_c: goto Reduce22;
		case TOKEN_right_p: goto Reduce22;
		case TOKEN_comma: goto Reduce22;
		case TOKEN_assignment: goto Shift25;
		case TOKEN_left_p: goto Shift16;
		default: goto ERROR;
	}

Goto15:
	switch(top_non_terminal){
		case SYMBOL_argblock: goto State24;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift16:
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
State16:
	states.push(&&Goto16);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Shift20;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto16:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State23;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_args: goto State21;
		case SYMBOL_arg: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift17:
/*
{args -> arg ~ [comma] args, [right_p]}
{args -> arg ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State17:
	states.push(&&Goto17);
	switch(current_terminal->token()){
		case TOKEN_comma: goto Shift18;
		case TOKEN_right_p: goto Reduce16;
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
{args -> arg [comma] ~ args, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State18:
	states.push(&&Goto18);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto18:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State23;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_args: goto State19;
		case SYMBOL_arg: goto State17;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift19:
/*
{args -> arg [comma] args ~, [right_p]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State19:
	states.push(&&Goto19);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce15;
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
{argblock -> [left_p] [right_p] ~, [semicolon]}
{argblock -> [left_p] [right_p] ~, [plus]}
{argblock -> [left_p] [right_p] ~, [minus]}
{argblock -> [left_p] [right_p] ~, [left_c]}
{argblock -> [left_p] [right_p] ~, [right_p]}
{argblock -> [left_p] [right_p] ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State20:
	states.push(&&Goto20);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce14;
		case TOKEN_plus: goto Reduce14;
		case TOKEN_minus: goto Reduce14;
		case TOKEN_left_c: goto Reduce14;
		case TOKEN_right_p: goto Reduce14;
		case TOKEN_comma: goto Reduce14;
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
{argblock -> [left_p] args ~ [right_p], [semicolon]}
{argblock -> [left_p] args ~ [right_p], [plus]}
{argblock -> [left_p] args ~ [right_p], [minus]}
{argblock -> [left_p] args ~ [right_p], [left_c]}
{argblock -> [left_p] args ~ [right_p], [right_p]}
{argblock -> [left_p] args ~ [right_p], [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State21:
	states.push(&&Goto21);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Shift22;
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
{argblock -> [left_p] args [right_p] ~, [semicolon]}
{argblock -> [left_p] args [right_p] ~, [plus]}
{argblock -> [left_p] args [right_p] ~, [minus]}
{argblock -> [left_p] args [right_p] ~, [left_c]}
{argblock -> [left_p] args [right_p] ~, [right_p]}
{argblock -> [left_p] args [right_p] ~, [comma]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State22:
	states.push(&&Goto22);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce13;
		case TOKEN_plus: goto Reduce13;
		case TOKEN_minus: goto Reduce13;
		case TOKEN_left_c: goto Reduce13;
		case TOKEN_right_p: goto Reduce13;
		case TOKEN_comma: goto Reduce13;
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
State23:
	states.push(&&Goto23);
	switch(current_terminal->token()){
		case TOKEN_right_p: goto Reduce17;
		case TOKEN_comma: goto Reduce17;
		case TOKEN_minus: goto Shift6;
		case TOKEN_plus: goto Shift4;
		default: goto ERROR;
	}

Goto23:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift24:
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
State24:
	states.push(&&Goto24);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce21;
		case TOKEN_plus: goto Reduce21;
		case TOKEN_minus: goto Reduce21;
		case TOKEN_left_c: goto Reduce21;
		case TOKEN_right_p: goto Reduce21;
		case TOKEN_comma: goto Reduce21;
		default: goto ERROR;
	}

Goto24:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift25:
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
State25:
	states.push(&&Goto25);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto25:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State26;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift26:
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
State26:
	states.push(&&Goto26);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce23;
		case TOKEN_left_c: goto Reduce23;
		case TOKEN_right_p: goto Reduce23;
		case TOKEN_comma: goto Reduce23;
		case TOKEN_minus: goto Shift6;
		case TOKEN_plus: goto Shift4;
		default: goto ERROR;
	}

Goto26:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift27:
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
State27:
	states.push(&&Goto27);
	switch(current_terminal->token()){
		case TOKEN_assignment: goto Reduce9;
		case TOKEN_semicolon: goto Reduce9;
		case TOKEN_left_p: goto Reduce9;
		case TOKEN_plus: goto Reduce9;
		case TOKEN_minus: goto Reduce9;
		case TOKEN_left_c: goto Reduce9;
		case TOKEN_right_p: goto Reduce9;
		case TOKEN_comma: goto Reduce9;
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
{stmt -> [var] ~ varDecl, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State28:
	states.push(&&Goto28);
	switch(current_terminal->token()){
		case TOKEN_id: goto Shift29;
		default: goto ERROR;
	}

Goto28:
	switch(top_non_terminal){
		case SYMBOL_varDecl: goto State32;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift29:
/*
{varDecl -> [id] ~, [semicolon]}
{varDecl -> [id] ~ [assignment] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State29:
	states.push(&&Goto29);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce7;
		case TOKEN_assignment: goto Shift30;
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
{varDecl -> [id] [assignment] ~ expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State30:
	states.push(&&Goto30);
	switch(current_terminal->token()){
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		default: goto ERROR;
	}

Goto30:
	switch(top_non_terminal){
		case SYMBOL_expr: goto State31;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift31:
/*
{varDecl -> [id] [assignment] expr ~, [semicolon]}
{expr -> expr ~ [minus] expr, [plus]}
{expr -> expr ~ [minus] expr, [minus]}
{expr -> expr ~ [minus] expr, [semicolon]}
{expr -> expr ~ [plus] expr, [plus]}
{expr -> expr ~ [plus] expr, [minus]}
{expr -> expr ~ [plus] expr, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State31:
	states.push(&&Goto31);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce8;
		case TOKEN_minus: goto Shift6;
		case TOKEN_plus: goto Shift4;
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
{stmt -> [var] varDecl ~, [semicolon]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State32:
	states.push(&&Goto32);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce6;
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
State33:
	states.push(&&Goto33);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Reduce5;
		case TOKEN_minus: goto Shift6;
		case TOKEN_plus: goto Shift4;
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
{stmts -> closedStmt ~ stmts, [right_c]}
{stmts -> closedStmt ~ stmts, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State34:
	states.push(&&Goto34);
	switch(current_terminal->token()){
		case TOKEN_var: goto Shift28;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		case TOKEN_if: goto Shift12;
		case TOKEN_while: goto Shift2;
		default: goto ERROR;
	}

Goto34:
	switch(top_non_terminal){
		case SYMBOL_stmts: goto State35;
		case SYMBOL_stmt: goto State36;
		case SYMBOL_closedStmt: goto State34;
		case SYMBOL_expr: goto State33;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift35:
/*
{stmts -> closedStmt stmts ~, [right_c]}
{stmts -> closedStmt stmts ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State35:
	states.push(&&Goto35);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce3;
		case TOKEN_EOF: goto Reduce3;
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
{stmts -> stmt ~ [semicolon] stmts, [right_c]}
{stmts -> stmt ~ [semicolon] stmts, [EOF]}
{stmts -> stmt ~ [semicolon], [right_c]}
{stmts -> stmt ~ [semicolon], [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State36:
	states.push(&&Goto36);
	switch(current_terminal->token()){
		case TOKEN_semicolon: goto Shift37;
		default: goto ERROR;
	}

Goto36:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift37:
/*
{stmts -> stmt [semicolon] ~ stmts, [right_c]}
{stmts -> stmt [semicolon] ~ stmts, [EOF]}
{stmts -> stmt [semicolon] ~, [right_c]}
{stmts -> stmt [semicolon] ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State37:
	states.push(&&Goto37);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce4;
		case TOKEN_EOF: goto Reduce4;
		case TOKEN_var: goto Shift28;
		case TOKEN_int: goto Shift1;
		case TOKEN_id: goto Shift27;
		case TOKEN_if: goto Shift12;
		case TOKEN_while: goto Shift2;
		default: goto ERROR;
	}

Goto37:
	switch(top_non_terminal){
		case SYMBOL_stmts: goto State38;
		case SYMBOL_stmt: goto State36;
		case SYMBOL_closedStmt: goto State34;
		case SYMBOL_expr: goto State33;
		case SYMBOL_varexpr: goto State15;
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift38:
/*
{stmts -> stmt [semicolon] stmts ~, [right_c]}
{stmts -> stmt [semicolon] stmts ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State38:
	states.push(&&Goto38);
	switch(current_terminal->token()){
		case TOKEN_right_c: goto Reduce2;
		case TOKEN_EOF: goto Reduce2;
		default: goto ERROR;
	}

Goto38:
	switch(top_non_terminal){
		case SYMBOL_error:
			states.pop();
			symbols.pop();
			goto *states.top();
		default: goto FATAL_ERROR;
	}

Shift39:
/*
{program -> stmts ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State39:
	states.push(&&Goto39);
	switch(current_terminal->token()){
		case TOKEN_EOF: goto Reduce1;
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
{root -> program ~, [EOF]}
*/
	symbols.push(current_terminal);
	current_terminal = lexer->nextToken();
State40:
	states.push(&&Goto40);
	switch(current_terminal->token()){
		case TOKEN_EOF: return symbols.top();
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

Reduce10: //block -> [left_c] stmts [right_c]
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
	cerr<<"PARSE closedStmt"<<endl; result = new SOrderNodeIfStmt((SOrderNodeExpr*)arg1, (SOrderNodeStmt*)arg2, NULL, NULL);
	}
	symbols.push(result);
	top_non_terminal = SYMBOL_closedStmt;
	goto *states.top();

Reduce12: //closedStmt -> [while] expr block
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

Reduce13: //argblock -> [left_p] args [right_p]
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

Reduce14: //argblock -> [left_p] [right_p]
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

Reduce15: //args -> arg [comma] args
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

Reduce16: //args -> arg
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

Reduce17: //arg -> expr
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

Reduce18: //expr -> expr [minus] expr
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

Reduce19: //expr -> expr [plus] expr
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

Reduce20: //expr -> [int]
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

Reduce21: //expr -> varexpr argblock
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

Reduce22: //expr -> varexpr
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

Reduce23: //expr -> varexpr [assignment] expr
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
		case TOKEN_semicolon: return "semicolon";
		case TOKEN_var: return "var";
		case TOKEN_id: return "id";
		case TOKEN_assignment: return "assignment";
		case TOKEN_left_c: return "left_c";
		case TOKEN_right_c: return "right_c";
		case TOKEN_if: return "if";
		case TOKEN_while: return "while";
		case TOKEN_left_p: return "left_p";
		case TOKEN_right_p: return "right_p";
		case TOKEN_comma: return "comma";
		case TOKEN_minus: return "minus";
		case TOKEN_plus: return "plus";
		case TOKEN_int: return "int";
		default: return "Unknown token";
	}
}


