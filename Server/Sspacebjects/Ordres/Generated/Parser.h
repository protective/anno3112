#ifndef PARSER_H
#define PARSER_H
#include "../../../SFunctions.h"
class Lexer;
class SOrderNode;

SOrderNode* parse(Lexer* lex);

enum Token{
	TOKEN_error,
	TOKEN_EOF,
	TOKEN_newline,
	TOKEN_semicolon,
	TOKEN_var,
	TOKEN_id,
	TOKEN_assignment,
	TOKEN_left_p,
	TOKEN_right_p,
	TOKEN_comma,
	TOKEN_left_c,
	TOKEN_right_c,
	TOKEN_if,
	TOKEN_while,
	TOKEN_minus,
	TOKEN_plus,
	TOKEN_int
};


string TokenToString(Token token);

#endif /* PARSER_H */
