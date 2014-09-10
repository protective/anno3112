#include "../Lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define token 	bufstart

Lexer::Lexer(istream* input)
	: pos(1, 0) {
	this->input = input;
	indent = 0;
	d_indent = 0;
	buffer = new char[BUF_SIZE];
	bufstart = buffer;
	cursor = buffer;
	limit = buffer;
	marker = buffer;
	toklen = 0;
	fill();
}

void Lexer::fill(){
	assert(cursor==limit);
	//TODO: Handle the case below by extending the buffer
	assert(!(buffer==bufstart && buffer + BUF_SIZE == limit));

	//Move memory in the buffer
	int relative = bufstart - buffer;
	memmove(buffer,bufstart,limit-bufstart);
	
	//Move pointers
	bufstart -= relative;
	marker -= relative;
	cursor -= relative;
	limit -= relative;

	//Read data
	int reqbyte =  buffer + BUF_SIZE - limit;
	input->read(limit, reqbyte);
	limit += input->gcount();

	//Handle EOF and possible errors
	if(input->eof()){
		*limit = 0x4; //eof
		limit++;
	}else if(input->fail()){
		//TODO: Handle IO error
		fprintf(stderr, "Error reading input file!\n");
		exit(1);		
	}
}

Terminal* Lexer::nextToken(){
	/*if(throwNewline){
		throwNewline = false;
		return new Terminal(TOKEN_newline, pos);
	}*/
	if(d_indent != 0)
		goto handle_indents;
BEGIN:
	//Add offset from last token
	this->pos._col += toklen;
	//The DFA:
	{
	bufstart = marker;
	int accept = -1;
	goto START;
final:
	if(accept == -1)
		marker++;
	cursor = marker;
	{
		toklen = marker - bufstart;
	}
	switch(accept){
	case 0:
		{
		return new Terminal(TOKEN_var, pos);
		}
		break;
	case 1:
		{
		return new Terminal(TOKEN_if, pos);
		}
		break;
	case 2:
		{
		return new Terminal(TOKEN_else, pos);
		}
		break;
	case 3:
		{
		return new Terminal(TOKEN_elseif, pos);
		}
		break;
	case 4:
		{
		return new Terminal(TOKEN_while, pos);
		}
		break;
	case 5:
		{
		return new Terminal(TOKEN_for, pos);
		}
		break;
	case 6:
		{
		return new Terminal(TOKEN_in, pos);
		}
		break;
	case 7:
		{
		return new Terminal(TOKEN_not, pos);
		}
		break;
	case 8:
		{
		return new Terminal(TOKEN_and, pos);
		}
		break;
	case 9:
		{
		return new Terminal(TOKEN_or, pos);
		}
		break;
	case 10:
		{
		return new Terminal(TOKEN_enum, pos);
		}
		break;
	case 11:
		{
		return new Terminal(TOKEN_class, pos);
		}
		break;
	case 12:
		{
		return new Terminal(TOKEN_extends, pos);
		}
		break;
	case 13:
		{
		return new Terminal(TOKEN_return, pos);
		}
		break;
	case 14:
		{
		return new Terminal(TOKEN_colon, pos);
		}
		break;
	case 15:
		{
		return new Terminal(TOKEN_comma, pos);
		}
		break;
	case 16:
		{
		return new Terminal(TOKEN_dot, pos);
		}
		break;
	case 17:
		{
		return new Terminal(TOKEN_assignment, pos);
		}
		break;
	case 18:
		{
		return new Terminal(TOKEN_equality, pos);
		}
		break;
	case 19:
		{
		return new Terminal(TOKEN_inequality, pos);
		}
		break;
	case 20:
		{
		return new Terminal(TOKEN_less_than, pos);
		}
		break;
	case 21:
		{
		return new Terminal(TOKEN_less_than_or_equal, pos);
		}
		break;
	case 22:
		{
		return new Terminal(TOKEN_greater_than, pos);
		}
		break;
	case 23:
		{
		return new Terminal(TOKEN_greater_than_or_equal, pos);
		}
		break;
	case 24:
		{
		return new Terminal(TOKEN_shift_left, pos);
		}
		break;
	case 25:
		{
		return new Terminal(TOKEN_shift_right, pos);
		}
		break;
	case 26:
		{
		return new Terminal(TOKEN_plus, pos);
		}
		break;
	case 27:
		{
		return new Terminal(TOKEN_minus, pos);
		}
		break;
	case 28:
		{
		return new Terminal(TOKEN_arrow, pos);
		}
		break;
	case 29:
		{
		return new Terminal(TOKEN_mul, pos);
		}
		break;
	case 30:
		{
		return new Terminal(TOKEN_div, pos);
		}
		break;
	case 31:
		{
		return new Terminal(TOKEN_modulo, pos);
		}
		break;
	case 32:
		{
		return new Terminal(TOKEN_left_p, pos);
		}
		break;
	case 33:
		{
		return new Terminal(TOKEN_right_p, pos);
		}
		break;
	case 34:
		{
		return new BooleanLiteral(true, pos);
		}
		break;
	case 35:
		{
		return new BooleanLiteral(false, pos);
		}
		break;
	case 36:
		{
		return new StringLiteral(token, toklen, pos);
		}
		break;
	case 37:
		{
		return new Identifier(token, toklen, pos);
		}
		break;
	case 38:
		{
		return IntegerFromDecimalString(token, toklen, pos);
		}
		break;
	case 39:
		{
		return new RealLiteral(token, toklen, pos);
		}
		break;
	case 40:
		{
		return new Terminal(TOKEN_EOF, pos);
		}
		break;
	case 41:
		{
		goto BEGIN;
		}
		break;
	case 42:
		{
		goto BEGIN;
		}
		break;
	case 43:
		{
		
													goto got_indents;
												
		}
		break;
	default:
		{
		return new Terminal(TOKEN_error, pos);
		}
		break;
	}
	bufstart = marker;
	goto START;
State1:
	cursor++;
	if(limit == cursor) fill();
	accept = 40;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State4:
	cursor++;
	if(limit == cursor) fill();
	accept = 42;
	marker = cursor;
	switch(*cursor){
		case 9: goto State2;
		case 32: goto State2;	//' '
		case 10: goto State3;
		case 13: goto State2;
		default: goto final;
	};

State35:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State44;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State25:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State44:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State45;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State73:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State74;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State59:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State62;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State45:
	cursor++;
	if(limit == cursor) fill();
	accept = 0;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State61:
	cursor++;
	if(limit == cursor) fill();
	accept = 5;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State52:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State53;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State33:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State49;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State99:
	cursor++;
	if(limit == cursor) fill();
	accept = 19;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State53:
	cursor++;
	if(limit == cursor) fill();
	accept = 13;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State72:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State9:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 38: goto State96;	//'&'
		default: goto final;
	};

State30:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State57;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State58;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State70:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State71;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State75:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State76;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State48:
	cursor++;
	if(limit == cursor) fill();
	accept = 34;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State64:
	cursor++;
	if(limit == cursor) fill();
	accept = 35;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State8:
	cursor++;
	if(limit == cursor) fill();
	accept = 31;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State17:
	cursor++;
	if(limit == cursor) fill();
	accept = 16;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State50:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State51;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State85:
	cursor++;
	if(limit == cursor) fill();
	accept = 23;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State76:
	cursor++;
	if(limit == cursor) fill();
	accept = 2;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State77;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State89:
	cursor++;
	if(limit == cursor) fill();
	accept = 21;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State38:
	cursor++;
	if(limit == cursor) fill();
	accept = 9;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State2:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 9: goto State2;
		case 32: goto State2;	//' '
		case 10: goto State3;
		case 13: goto State2;
		default: goto final;
	};

State18:
	cursor++;
	if(limit == cursor) fill();
	accept = 30;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State82:
	cursor++;
	if(limit == cursor) fill();
	accept = 11;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State55:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State56;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State16:
	cursor++;
	if(limit == cursor) fill();
	accept = 27;
	marker = cursor;
	switch(*cursor){
		case 62: goto State92;	//'>'
		default: goto final;
	};

State63:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State64;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State65:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State75;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State51:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State52;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State26:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State83;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State93:
	cursor++;
	if(limit == cursor) fill();
	accept = 36;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State88:
	cursor++;
	if(limit == cursor) fill();
	accept = 24;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State92:
	cursor++;
	if(limit == cursor) fill();
	accept = 28;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State56:
	cursor++;
	if(limit == cursor) fill();
	accept = 7;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State22:
	cursor++;
	if(limit == cursor) fill();
	accept = 17;
	marker = cursor;
	switch(*cursor){
		case 61: goto State87;	//'='
		default: goto final;
	};

State0:
	cursor++;
	if(limit == cursor) fill();
START: 
	switch(*cursor){
		case 4: goto State1;
		case 32: goto State5;	//' '
		case 40: goto State11;	//'('
		case 44: goto State15;	//','
		case 48: goto State19;	//'0'
		case 52: goto State19;	//'4'
		case 56: goto State19;	//'8'
		case 60: goto State21;	//'<'
		case 68: goto State24;	//'D'
		case 72: goto State24;	//'H'
		case 76: goto State24;	//'L'
		case 80: goto State24;	//'P'
		case 84: goto State24;	//'T'
		case 88: goto State24;	//'X'
		case 100: goto State24;	//'d'
		case 104: goto State24;	//'h'
		case 108: goto State24;	//'l'
		case 112: goto State24;	//'p'
		case 116: goto State34;	//'t'
		case 120: goto State24;	//'x'
		case 124: goto State37;	//'|'
		case 39: goto State10;	//'''
		case 43: goto State14;	//'+'
		case 47: goto State18;	//'/'
		case 51: goto State19;	//'3'
		case 55: goto State19;	//'7'
		case 67: goto State24;	//'C'
		case 71: goto State24;	//'G'
		case 75: goto State24;	//'K'
		case 79: goto State24;	//'O'
		case 83: goto State24;	//'S'
		case 87: goto State24;	//'W'
		case 95: goto State25;	//'_'
		case 99: goto State27;	//'c'
		case 103: goto State24;	//'g'
		case 107: goto State24;	//'k'
		case 111: goto State32;	//'o'
		case 115: goto State24;	//'s'
		case 119: goto State36;	//'w'
		case 10: goto State3;
		case 34: goto State7;	//'"'
		case 38: goto State9;	//'&'
		case 42: goto State13;	//'*'
		case 46: goto State17;	//'.'
		case 50: goto State19;	//'2'
		case 54: goto State19;	//'6'
		case 58: goto State20;	//':'
		case 62: goto State23;	//'>'
		case 66: goto State24;	//'B'
		case 70: goto State24;	//'F'
		case 74: goto State24;	//'J'
		case 78: goto State24;	//'N'
		case 82: goto State24;	//'R'
		case 86: goto State24;	//'V'
		case 90: goto State24;	//'Z'
		case 98: goto State24;	//'b'
		case 102: goto State29;	//'f'
		case 106: goto State24;	//'j'
		case 110: goto State31;	//'n'
		case 114: goto State33;	//'r'
		case 118: goto State35;	//'v'
		case 122: goto State24;	//'z'
		case 9: goto State2;
		case 13: goto State4;
		case 33: goto State6;	//'!'
		case 37: goto State8;	//'%'
		case 41: goto State12;	//')'
		case 45: goto State16;	//'-'
		case 49: goto State19;	//'1'
		case 53: goto State19;	//'5'
		case 57: goto State19;	//'9'
		case 61: goto State22;	//'='
		case 65: goto State24;	//'A'
		case 69: goto State24;	//'E'
		case 73: goto State24;	//'I'
		case 77: goto State24;	//'M'
		case 81: goto State24;	//'Q'
		case 85: goto State24;	//'U'
		case 89: goto State24;	//'Y'
		case 97: goto State26;	//'a'
		case 101: goto State28;	//'e'
		case 105: goto State30;	//'i'
		case 109: goto State24;	//'m'
		case 113: goto State24;	//'q'
		case 117: goto State24;	//'u'
		case 121: goto State24;	//'y'
		default: goto final;
	};

State34:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State46;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State36:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State40;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State46:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State47;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State49:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State50;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State98:
	cursor++;
	if(limit == cursor) fill();
	accept = 36;
	marker = cursor;
	switch(*cursor){
		case 32: goto State7;	//' '
		case 36: goto State7;	//'$'
		case 40: goto State7;	//'('
		case 44: goto State7;	//','
		case 48: goto State7;	//'0'
		case 52: goto State7;	//'4'
		case 56: goto State7;	//'8'
		case 60: goto State7;	//'<'
		case 64: goto State7;	//'@'
		case 68: goto State7;	//'D'
		case 72: goto State7;	//'H'
		case 76: goto State7;	//'L'
		case 80: goto State7;	//'P'
		case 84: goto State7;	//'T'
		case 88: goto State7;	//'X'
		case 92: goto State97;	//'\'
		case 96: goto State7;	//'`'
		case 100: goto State7;	//'d'
		case 104: goto State7;	//'h'
		case 108: goto State7;	//'l'
		case 112: goto State7;	//'p'
		case 116: goto State7;	//'t'
		case 120: goto State7;	//'x'
		case 124: goto State7;	//'|'
		case 35: goto State7;	//'#'
		case 43: goto State7;	//'+'
		case 47: goto State7;	//'/'
		case 51: goto State7;	//'3'
		case 55: goto State7;	//'7'
		case 59: goto State7;	//';'
		case 63: goto State7;	//'?'
		case 67: goto State7;	//'C'
		case 71: goto State7;	//'G'
		case 75: goto State7;	//'K'
		case 79: goto State7;	//'O'
		case 83: goto State7;	//'S'
		case 87: goto State7;	//'W'
		case 91: goto State7;	//'['
		case 95: goto State7;	//'_'
		case 99: goto State7;	//'c'
		case 103: goto State7;	//'g'
		case 107: goto State7;	//'k'
		case 111: goto State7;	//'o'
		case 115: goto State7;	//'s'
		case 119: goto State7;	//'w'
		case 123: goto State7;	//'{'
		case 10: goto State7;
		case 34: goto State93;	//'"'
		case 38: goto State7;	//'&'
		case 42: goto State7;	//'*'
		case 46: goto State7;	//'.'
		case 50: goto State7;	//'2'
		case 54: goto State7;	//'6'
		case 58: goto State7;	//':'
		case 62: goto State7;	//'>'
		case 66: goto State7;	//'B'
		case 70: goto State7;	//'F'
		case 74: goto State7;	//'J'
		case 78: goto State7;	//'N'
		case 82: goto State7;	//'R'
		case 86: goto State7;	//'V'
		case 90: goto State7;	//'Z'
		case 94: goto State7;	//'^'
		case 98: goto State7;	//'b'
		case 102: goto State7;	//'f'
		case 106: goto State7;	//'j'
		case 110: goto State7;	//'n'
		case 114: goto State7;	//'r'
		case 118: goto State7;	//'v'
		case 122: goto State7;	//'z'
		case 126: goto State7;	//'~'
		case 33: goto State7;	//'!'
		case 37: goto State7;	//'%'
		case 41: goto State7;	//')'
		case 45: goto State7;	//'-'
		case 49: goto State7;	//'1'
		case 53: goto State7;	//'5'
		case 57: goto State7;	//'9'
		case 61: goto State7;	//'='
		case 65: goto State7;	//'A'
		case 69: goto State7;	//'E'
		case 73: goto State7;	//'I'
		case 77: goto State7;	//'M'
		case 81: goto State7;	//'Q'
		case 85: goto State7;	//'U'
		case 89: goto State7;	//'Y'
		case 93: goto State7;	//']'
		case 97: goto State7;	//'a'
		case 101: goto State7;	//'e'
		case 105: goto State7;	//'i'
		case 109: goto State7;	//'m'
		case 113: goto State7;	//'q'
		case 117: goto State7;	//'u'
		case 121: goto State7;	//'y'
		case 125: goto State7;	//'}'
		default: goto final;
	};

State67:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State68;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State40:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State41;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State66:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State73;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State27:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State79;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State91:
	cursor++;
	if(limit == cursor) fill();
	accept = 39;
	marker = cursor;
	switch(*cursor){
		case 49: goto State91;	//'1'
		case 48: goto State91;	//'0'
		case 51: goto State91;	//'3'
		case 50: goto State91;	//'2'
		case 53: goto State91;	//'5'
		case 52: goto State91;	//'4'
		case 55: goto State91;	//'7'
		case 54: goto State91;	//'6'
		case 57: goto State91;	//'9'
		case 56: goto State91;	//'8'
		default: goto final;
	};

State90:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 49: goto State91;	//'1'
		case 48: goto State91;	//'0'
		case 51: goto State91;	//'3'
		case 50: goto State91;	//'2'
		case 53: goto State91;	//'5'
		case 52: goto State91;	//'4'
		case 55: goto State91;	//'7'
		case 54: goto State91;	//'6'
		case 57: goto State91;	//'9'
		case 56: goto State91;	//'8'
		default: goto final;
	};

State10:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 32: goto State10;	//' '
		case 36: goto State10;	//'$'
		case 40: goto State10;	//'('
		case 44: goto State10;	//','
		case 48: goto State10;	//'0'
		case 52: goto State10;	//'4'
		case 56: goto State10;	//'8'
		case 60: goto State10;	//'<'
		case 64: goto State10;	//'@'
		case 68: goto State10;	//'D'
		case 72: goto State10;	//'H'
		case 76: goto State10;	//'L'
		case 80: goto State10;	//'P'
		case 84: goto State10;	//'T'
		case 88: goto State10;	//'X'
		case 92: goto State94;	//'\'
		case 96: goto State10;	//'`'
		case 100: goto State10;	//'d'
		case 104: goto State10;	//'h'
		case 108: goto State10;	//'l'
		case 112: goto State10;	//'p'
		case 116: goto State10;	//'t'
		case 120: goto State10;	//'x'
		case 124: goto State10;	//'|'
		case 35: goto State10;	//'#'
		case 39: goto State93;	//'''
		case 43: goto State10;	//'+'
		case 47: goto State10;	//'/'
		case 51: goto State10;	//'3'
		case 55: goto State10;	//'7'
		case 59: goto State10;	//';'
		case 63: goto State10;	//'?'
		case 67: goto State10;	//'C'
		case 71: goto State10;	//'G'
		case 75: goto State10;	//'K'
		case 79: goto State10;	//'O'
		case 83: goto State10;	//'S'
		case 87: goto State10;	//'W'
		case 91: goto State10;	//'['
		case 95: goto State10;	//'_'
		case 99: goto State10;	//'c'
		case 103: goto State10;	//'g'
		case 107: goto State10;	//'k'
		case 111: goto State10;	//'o'
		case 115: goto State10;	//'s'
		case 119: goto State10;	//'w'
		case 123: goto State10;	//'{'
		case 10: goto State10;
		case 38: goto State10;	//'&'
		case 42: goto State10;	//'*'
		case 46: goto State10;	//'.'
		case 50: goto State10;	//'2'
		case 54: goto State10;	//'6'
		case 58: goto State10;	//':'
		case 62: goto State10;	//'>'
		case 66: goto State10;	//'B'
		case 70: goto State10;	//'F'
		case 74: goto State10;	//'J'
		case 78: goto State10;	//'N'
		case 82: goto State10;	//'R'
		case 86: goto State10;	//'V'
		case 90: goto State10;	//'Z'
		case 94: goto State10;	//'^'
		case 98: goto State10;	//'b'
		case 102: goto State10;	//'f'
		case 106: goto State10;	//'j'
		case 110: goto State10;	//'n'
		case 114: goto State10;	//'r'
		case 118: goto State10;	//'v'
		case 122: goto State10;	//'z'
		case 126: goto State10;	//'~'
		case 33: goto State10;	//'!'
		case 37: goto State10;	//'%'
		case 41: goto State10;	//')'
		case 45: goto State10;	//'-'
		case 49: goto State10;	//'1'
		case 53: goto State10;	//'5'
		case 57: goto State10;	//'9'
		case 61: goto State10;	//'='
		case 65: goto State10;	//'A'
		case 69: goto State10;	//'E'
		case 73: goto State10;	//'I'
		case 77: goto State10;	//'M'
		case 81: goto State10;	//'Q'
		case 85: goto State10;	//'U'
		case 89: goto State10;	//'Y'
		case 93: goto State10;	//']'
		case 97: goto State10;	//'a'
		case 101: goto State10;	//'e'
		case 105: goto State10;	//'i'
		case 109: goto State10;	//'m'
		case 113: goto State10;	//'q'
		case 117: goto State10;	//'u'
		case 121: goto State10;	//'y'
		case 125: goto State10;	//'}'
		default: goto final;
	};

State28:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State65;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State66;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State67;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State15:
	cursor++;
	if(limit == cursor) fill();
	accept = 15;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State83:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State84;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State68:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State69;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State6:
	cursor++;
	if(limit == cursor) fill();
	accept = 7;
	marker = cursor;
	switch(*cursor){
		case 61: goto State99;	//'='
		default: goto final;
	};

State43:
	cursor++;
	if(limit == cursor) fill();
	accept = 4;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State78:
	cursor++;
	if(limit == cursor) fill();
	accept = 3;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State77:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State78;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State3:
	cursor++;
	if(limit == cursor) fill();
	accept = 43;
	marker = cursor;
	switch(*cursor){
		case 9: goto State3;
		case 32: goto State2;	//' '
		case 10: goto State3;
		case 13: goto State2;
		default: goto final;
	};

State74:
	cursor++;
	if(limit == cursor) fill();
	accept = 10;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State97:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 32: goto State7;	//' '
		case 36: goto State7;	//'$'
		case 40: goto State7;	//'('
		case 44: goto State7;	//','
		case 48: goto State7;	//'0'
		case 52: goto State7;	//'4'
		case 56: goto State7;	//'8'
		case 60: goto State7;	//'<'
		case 64: goto State7;	//'@'
		case 68: goto State7;	//'D'
		case 72: goto State7;	//'H'
		case 76: goto State7;	//'L'
		case 80: goto State7;	//'P'
		case 84: goto State7;	//'T'
		case 88: goto State7;	//'X'
		case 92: goto State97;	//'\'
		case 96: goto State7;	//'`'
		case 100: goto State7;	//'d'
		case 104: goto State7;	//'h'
		case 108: goto State7;	//'l'
		case 112: goto State7;	//'p'
		case 116: goto State7;	//'t'
		case 120: goto State7;	//'x'
		case 124: goto State7;	//'|'
		case 35: goto State7;	//'#'
		case 39: goto State7;	//'''
		case 43: goto State7;	//'+'
		case 47: goto State7;	//'/'
		case 51: goto State7;	//'3'
		case 55: goto State7;	//'7'
		case 59: goto State7;	//';'
		case 63: goto State7;	//'?'
		case 67: goto State7;	//'C'
		case 71: goto State7;	//'G'
		case 75: goto State7;	//'K'
		case 79: goto State7;	//'O'
		case 83: goto State7;	//'S'
		case 87: goto State7;	//'W'
		case 91: goto State7;	//'['
		case 95: goto State7;	//'_'
		case 99: goto State7;	//'c'
		case 103: goto State7;	//'g'
		case 107: goto State7;	//'k'
		case 111: goto State7;	//'o'
		case 115: goto State7;	//'s'
		case 119: goto State7;	//'w'
		case 123: goto State7;	//'{'
		case 10: goto State7;
		case 34: goto State98;	//'"'
		case 38: goto State7;	//'&'
		case 42: goto State7;	//'*'
		case 46: goto State7;	//'.'
		case 50: goto State7;	//'2'
		case 54: goto State7;	//'6'
		case 58: goto State7;	//':'
		case 62: goto State7;	//'>'
		case 66: goto State7;	//'B'
		case 70: goto State7;	//'F'
		case 74: goto State7;	//'J'
		case 78: goto State7;	//'N'
		case 82: goto State7;	//'R'
		case 86: goto State7;	//'V'
		case 90: goto State7;	//'Z'
		case 94: goto State7;	//'^'
		case 98: goto State7;	//'b'
		case 102: goto State7;	//'f'
		case 106: goto State7;	//'j'
		case 110: goto State7;	//'n'
		case 114: goto State7;	//'r'
		case 118: goto State7;	//'v'
		case 122: goto State7;	//'z'
		case 126: goto State7;	//'~'
		case 33: goto State7;	//'!'
		case 37: goto State7;	//'%'
		case 41: goto State7;	//')'
		case 45: goto State7;	//'-'
		case 49: goto State7;	//'1'
		case 53: goto State7;	//'5'
		case 57: goto State7;	//'9'
		case 61: goto State7;	//'='
		case 65: goto State7;	//'A'
		case 69: goto State7;	//'E'
		case 73: goto State7;	//'I'
		case 77: goto State7;	//'M'
		case 81: goto State7;	//'Q'
		case 85: goto State7;	//'U'
		case 89: goto State7;	//'Y'
		case 93: goto State7;	//']'
		case 97: goto State7;	//'a'
		case 101: goto State7;	//'e'
		case 105: goto State7;	//'i'
		case 109: goto State7;	//'m'
		case 113: goto State7;	//'q'
		case 117: goto State7;	//'u'
		case 121: goto State7;	//'y'
		case 125: goto State7;	//'}'
		default: goto final;
	};

State14:
	cursor++;
	if(limit == cursor) fill();
	accept = 26;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State5:
	cursor++;
	if(limit == cursor) fill();
	accept = 41;
	marker = cursor;
	switch(*cursor){
		case 9: goto State2;
		case 32: goto State2;	//' '
		case 10: goto State3;
		case 13: goto State2;
		default: goto final;
	};

State29:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State59;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State60;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State31:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State55;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State69:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State70;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State20:
	cursor++;
	if(limit == cursor) fill();
	accept = 14;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State32:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State54;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State81:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State82;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State57:
	cursor++;
	if(limit == cursor) fill();
	accept = 1;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State58:
	cursor++;
	if(limit == cursor) fill();
	accept = 6;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State86:
	cursor++;
	if(limit == cursor) fill();
	accept = 25;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State60:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State61;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State41:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State42;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State71:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State72;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State37:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 124: goto State38;	//'|'
		default: goto final;
	};

State42:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State43;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State21:
	cursor++;
	if(limit == cursor) fill();
	accept = 20;
	marker = cursor;
	switch(*cursor){
		case 61: goto State89;	//'='
		case 60: goto State88;	//'<'
		default: goto final;
	};

State87:
	cursor++;
	if(limit == cursor) fill();
	accept = 18;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State47:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State48;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State62:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State63;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State13:
	cursor++;
	if(limit == cursor) fill();
	accept = 29;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State11:
	cursor++;
	if(limit == cursor) fill();
	accept = 32;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State12:
	cursor++;
	if(limit == cursor) fill();
	accept = 33;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State79:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State80;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State54:
	cursor++;
	if(limit == cursor) fill();
	accept = 9;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State96:
	cursor++;
	if(limit == cursor) fill();
	accept = 8;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State7:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 32: goto State7;	//' '
		case 36: goto State7;	//'$'
		case 40: goto State7;	//'('
		case 44: goto State7;	//','
		case 48: goto State7;	//'0'
		case 52: goto State7;	//'4'
		case 56: goto State7;	//'8'
		case 60: goto State7;	//'<'
		case 64: goto State7;	//'@'
		case 68: goto State7;	//'D'
		case 72: goto State7;	//'H'
		case 76: goto State7;	//'L'
		case 80: goto State7;	//'P'
		case 84: goto State7;	//'T'
		case 88: goto State7;	//'X'
		case 92: goto State97;	//'\'
		case 96: goto State7;	//'`'
		case 100: goto State7;	//'d'
		case 104: goto State7;	//'h'
		case 108: goto State7;	//'l'
		case 112: goto State7;	//'p'
		case 116: goto State7;	//'t'
		case 120: goto State7;	//'x'
		case 124: goto State7;	//'|'
		case 35: goto State7;	//'#'
		case 43: goto State7;	//'+'
		case 47: goto State7;	//'/'
		case 51: goto State7;	//'3'
		case 55: goto State7;	//'7'
		case 59: goto State7;	//';'
		case 63: goto State7;	//'?'
		case 67: goto State7;	//'C'
		case 71: goto State7;	//'G'
		case 75: goto State7;	//'K'
		case 79: goto State7;	//'O'
		case 83: goto State7;	//'S'
		case 87: goto State7;	//'W'
		case 91: goto State7;	//'['
		case 95: goto State7;	//'_'
		case 99: goto State7;	//'c'
		case 103: goto State7;	//'g'
		case 107: goto State7;	//'k'
		case 111: goto State7;	//'o'
		case 115: goto State7;	//'s'
		case 119: goto State7;	//'w'
		case 123: goto State7;	//'{'
		case 10: goto State7;
		case 34: goto State93;	//'"'
		case 38: goto State7;	//'&'
		case 42: goto State7;	//'*'
		case 46: goto State7;	//'.'
		case 50: goto State7;	//'2'
		case 54: goto State7;	//'6'
		case 58: goto State7;	//':'
		case 62: goto State7;	//'>'
		case 66: goto State7;	//'B'
		case 70: goto State7;	//'F'
		case 74: goto State7;	//'J'
		case 78: goto State7;	//'N'
		case 82: goto State7;	//'R'
		case 86: goto State7;	//'V'
		case 90: goto State7;	//'Z'
		case 94: goto State7;	//'^'
		case 98: goto State7;	//'b'
		case 102: goto State7;	//'f'
		case 106: goto State7;	//'j'
		case 110: goto State7;	//'n'
		case 114: goto State7;	//'r'
		case 118: goto State7;	//'v'
		case 122: goto State7;	//'z'
		case 126: goto State7;	//'~'
		case 33: goto State7;	//'!'
		case 37: goto State7;	//'%'
		case 41: goto State7;	//')'
		case 45: goto State7;	//'-'
		case 49: goto State7;	//'1'
		case 53: goto State7;	//'5'
		case 57: goto State7;	//'9'
		case 61: goto State7;	//'='
		case 65: goto State7;	//'A'
		case 69: goto State7;	//'E'
		case 73: goto State7;	//'I'
		case 77: goto State7;	//'M'
		case 81: goto State7;	//'Q'
		case 85: goto State7;	//'U'
		case 89: goto State7;	//'Y'
		case 93: goto State7;	//']'
		case 97: goto State7;	//'a'
		case 101: goto State7;	//'e'
		case 105: goto State7;	//'i'
		case 109: goto State7;	//'m'
		case 113: goto State7;	//'q'
		case 117: goto State7;	//'u'
		case 121: goto State7;	//'y'
		case 125: goto State7;	//'}'
		default: goto final;
	};

State23:
	cursor++;
	if(limit == cursor) fill();
	accept = 22;
	marker = cursor;
	switch(*cursor){
		case 61: goto State85;	//'='
		case 62: goto State86;	//'>'
		default: goto final;
	};

State80:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State81;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State84:
	cursor++;
	if(limit == cursor) fill();
	accept = 8;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State39:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State95:
	cursor++;
	if(limit == cursor) fill();
	accept = 36;
	marker = cursor;
	switch(*cursor){
		case 32: goto State10;	//' '
		case 36: goto State10;	//'$'
		case 40: goto State10;	//'('
		case 44: goto State10;	//','
		case 48: goto State10;	//'0'
		case 52: goto State10;	//'4'
		case 56: goto State10;	//'8'
		case 60: goto State10;	//'<'
		case 64: goto State10;	//'@'
		case 68: goto State10;	//'D'
		case 72: goto State10;	//'H'
		case 76: goto State10;	//'L'
		case 80: goto State10;	//'P'
		case 84: goto State10;	//'T'
		case 88: goto State10;	//'X'
		case 92: goto State94;	//'\'
		case 96: goto State10;	//'`'
		case 100: goto State10;	//'d'
		case 104: goto State10;	//'h'
		case 108: goto State10;	//'l'
		case 112: goto State10;	//'p'
		case 116: goto State10;	//'t'
		case 120: goto State10;	//'x'
		case 124: goto State10;	//'|'
		case 35: goto State10;	//'#'
		case 39: goto State93;	//'''
		case 43: goto State10;	//'+'
		case 47: goto State10;	//'/'
		case 51: goto State10;	//'3'
		case 55: goto State10;	//'7'
		case 59: goto State10;	//';'
		case 63: goto State10;	//'?'
		case 67: goto State10;	//'C'
		case 71: goto State10;	//'G'
		case 75: goto State10;	//'K'
		case 79: goto State10;	//'O'
		case 83: goto State10;	//'S'
		case 87: goto State10;	//'W'
		case 91: goto State10;	//'['
		case 95: goto State10;	//'_'
		case 99: goto State10;	//'c'
		case 103: goto State10;	//'g'
		case 107: goto State10;	//'k'
		case 111: goto State10;	//'o'
		case 115: goto State10;	//'s'
		case 119: goto State10;	//'w'
		case 123: goto State10;	//'{'
		case 10: goto State10;
		case 38: goto State10;	//'&'
		case 42: goto State10;	//'*'
		case 46: goto State10;	//'.'
		case 50: goto State10;	//'2'
		case 54: goto State10;	//'6'
		case 58: goto State10;	//':'
		case 62: goto State10;	//'>'
		case 66: goto State10;	//'B'
		case 70: goto State10;	//'F'
		case 74: goto State10;	//'J'
		case 78: goto State10;	//'N'
		case 82: goto State10;	//'R'
		case 86: goto State10;	//'V'
		case 90: goto State10;	//'Z'
		case 94: goto State10;	//'^'
		case 98: goto State10;	//'b'
		case 102: goto State10;	//'f'
		case 106: goto State10;	//'j'
		case 110: goto State10;	//'n'
		case 114: goto State10;	//'r'
		case 118: goto State10;	//'v'
		case 122: goto State10;	//'z'
		case 126: goto State10;	//'~'
		case 33: goto State10;	//'!'
		case 37: goto State10;	//'%'
		case 41: goto State10;	//')'
		case 45: goto State10;	//'-'
		case 49: goto State10;	//'1'
		case 53: goto State10;	//'5'
		case 57: goto State10;	//'9'
		case 61: goto State10;	//'='
		case 65: goto State10;	//'A'
		case 69: goto State10;	//'E'
		case 73: goto State10;	//'I'
		case 77: goto State10;	//'M'
		case 81: goto State10;	//'Q'
		case 85: goto State10;	//'U'
		case 89: goto State10;	//'Y'
		case 93: goto State10;	//']'
		case 97: goto State10;	//'a'
		case 101: goto State10;	//'e'
		case 105: goto State10;	//'i'
		case 109: goto State10;	//'m'
		case 113: goto State10;	//'q'
		case 117: goto State10;	//'u'
		case 121: goto State10;	//'y'
		case 125: goto State10;	//'}'
		default: goto final;
	};

State19:
	cursor++;
	if(limit == cursor) fill();
	accept = 38;
	marker = cursor;
	switch(*cursor){
		case 46: goto State90;	//'.'
		case 49: goto State19;	//'1'
		case 48: goto State19;	//'0'
		case 51: goto State19;	//'3'
		case 50: goto State19;	//'2'
		case 53: goto State19;	//'5'
		case 52: goto State19;	//'4'
		case 55: goto State19;	//'7'
		case 54: goto State19;	//'6'
		case 57: goto State19;	//'9'
		case 56: goto State19;	//'8'
		default: goto final;
	};

State24:
	cursor++;
	if(limit == cursor) fill();
	accept = 37;
	marker = cursor;
	switch(*cursor){
		case 49: goto State24;	//'1'
		case 48: goto State24;	//'0'
		case 51: goto State24;	//'3'
		case 50: goto State24;	//'2'
		case 53: goto State24;	//'5'
		case 52: goto State24;	//'4'
		case 55: goto State24;	//'7'
		case 54: goto State24;	//'6'
		case 57: goto State24;	//'9'
		case 56: goto State24;	//'8'
		case 65: goto State24;	//'A'
		case 67: goto State24;	//'C'
		case 66: goto State24;	//'B'
		case 69: goto State24;	//'E'
		case 68: goto State24;	//'D'
		case 71: goto State24;	//'G'
		case 70: goto State24;	//'F'
		case 73: goto State24;	//'I'
		case 72: goto State24;	//'H'
		case 75: goto State24;	//'K'
		case 74: goto State24;	//'J'
		case 77: goto State24;	//'M'
		case 76: goto State24;	//'L'
		case 79: goto State24;	//'O'
		case 78: goto State24;	//'N'
		case 81: goto State24;	//'Q'
		case 80: goto State24;	//'P'
		case 83: goto State24;	//'S'
		case 82: goto State24;	//'R'
		case 85: goto State24;	//'U'
		case 84: goto State24;	//'T'
		case 87: goto State24;	//'W'
		case 86: goto State24;	//'V'
		case 89: goto State24;	//'Y'
		case 88: goto State24;	//'X'
		case 90: goto State24;	//'Z'
		case 95: goto State39;	//'_'
		case 97: goto State24;	//'a'
		case 99: goto State24;	//'c'
		case 98: goto State24;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State24;	//'d'
		case 103: goto State24;	//'g'
		case 102: goto State24;	//'f'
		case 105: goto State24;	//'i'
		case 104: goto State24;	//'h'
		case 107: goto State24;	//'k'
		case 106: goto State24;	//'j'
		case 109: goto State24;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State24;	//'o'
		case 110: goto State24;	//'n'
		case 113: goto State24;	//'q'
		case 112: goto State24;	//'p'
		case 115: goto State24;	//'s'
		case 114: goto State24;	//'r'
		case 117: goto State24;	//'u'
		case 116: goto State24;	//'t'
		case 119: goto State24;	//'w'
		case 118: goto State24;	//'v'
		case 121: goto State24;	//'y'
		case 120: goto State24;	//'x'
		case 122: goto State24;	//'z'
		default: goto final;
	};

State94:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 32: goto State10;	//' '
		case 36: goto State10;	//'$'
		case 40: goto State10;	//'('
		case 44: goto State10;	//','
		case 48: goto State10;	//'0'
		case 52: goto State10;	//'4'
		case 56: goto State10;	//'8'
		case 60: goto State10;	//'<'
		case 64: goto State10;	//'@'
		case 68: goto State10;	//'D'
		case 72: goto State10;	//'H'
		case 76: goto State10;	//'L'
		case 80: goto State10;	//'P'
		case 84: goto State10;	//'T'
		case 88: goto State10;	//'X'
		case 92: goto State94;	//'\'
		case 96: goto State10;	//'`'
		case 100: goto State10;	//'d'
		case 104: goto State10;	//'h'
		case 108: goto State10;	//'l'
		case 112: goto State10;	//'p'
		case 116: goto State10;	//'t'
		case 120: goto State10;	//'x'
		case 124: goto State10;	//'|'
		case 35: goto State10;	//'#'
		case 39: goto State95;	//'''
		case 43: goto State10;	//'+'
		case 47: goto State10;	//'/'
		case 51: goto State10;	//'3'
		case 55: goto State10;	//'7'
		case 59: goto State10;	//';'
		case 63: goto State10;	//'?'
		case 67: goto State10;	//'C'
		case 71: goto State10;	//'G'
		case 75: goto State10;	//'K'
		case 79: goto State10;	//'O'
		case 83: goto State10;	//'S'
		case 87: goto State10;	//'W'
		case 91: goto State10;	//'['
		case 95: goto State10;	//'_'
		case 99: goto State10;	//'c'
		case 103: goto State10;	//'g'
		case 107: goto State10;	//'k'
		case 111: goto State10;	//'o'
		case 115: goto State10;	//'s'
		case 119: goto State10;	//'w'
		case 123: goto State10;	//'{'
		case 10: goto State10;
		case 34: goto State10;	//'"'
		case 38: goto State10;	//'&'
		case 42: goto State10;	//'*'
		case 46: goto State10;	//'.'
		case 50: goto State10;	//'2'
		case 54: goto State10;	//'6'
		case 58: goto State10;	//':'
		case 62: goto State10;	//'>'
		case 66: goto State10;	//'B'
		case 70: goto State10;	//'F'
		case 74: goto State10;	//'J'
		case 78: goto State10;	//'N'
		case 82: goto State10;	//'R'
		case 86: goto State10;	//'V'
		case 90: goto State10;	//'Z'
		case 94: goto State10;	//'^'
		case 98: goto State10;	//'b'
		case 102: goto State10;	//'f'
		case 106: goto State10;	//'j'
		case 110: goto State10;	//'n'
		case 114: goto State10;	//'r'
		case 118: goto State10;	//'v'
		case 122: goto State10;	//'z'
		case 126: goto State10;	//'~'
		case 33: goto State10;	//'!'
		case 37: goto State10;	//'%'
		case 41: goto State10;	//')'
		case 45: goto State10;	//'-'
		case 49: goto State10;	//'1'
		case 53: goto State10;	//'5'
		case 57: goto State10;	//'9'
		case 61: goto State10;	//'='
		case 65: goto State10;	//'A'
		case 69: goto State10;	//'E'
		case 73: goto State10;	//'I'
		case 77: goto State10;	//'M'
		case 81: goto State10;	//'Q'
		case 85: goto State10;	//'U'
		case 89: goto State10;	//'Y'
		case 93: goto State10;	//']'
		case 97: goto State10;	//'a'
		case 101: goto State10;	//'e'
		case 105: goto State10;	//'i'
		case 109: goto State10;	//'m'
		case 113: goto State10;	//'q'
		case 117: goto State10;	//'u'
		case 121: goto State10;	//'y'
		case 125: goto State10;	//'}'
		default: goto final;
	};

	}
got_indents:
{
	//Count newlines and tabs
	char* tk_pos = token;
	char* last_n = tk_pos; //Last new line
	while(tk_pos < token + toklen){
		if(*tk_pos == '\n'){
			last_n = tk_pos;
			this->pos._line++;
		}
		tk_pos++;
	}
	//Tabs found
	int tabs = tk_pos - last_n - 1;
	//Set col to 0, since we got a new line
	this->pos._col = 0;
	toklen = tabs; //toklen will be added to col at next call
	//Compute change in indent
	d_indent = tabs - indent;
	indent = tabs;
	if(d_indent == 0) //If didn't change
		return new Terminal(TOKEN_newline, pos);
	throwNewline = false;
}
	//Handle change in indentation
handle_indents:
	assert(d_indent != 0);
	if(d_indent > 0){
		d_indent--;
		return new Terminal(TOKEN_indent, pos);
	}else{
		//throwNewline = true;
		d_indent++;
		//throwNewline = true;
		return new Terminal(TOKEN_dedent, pos);
	}
}

