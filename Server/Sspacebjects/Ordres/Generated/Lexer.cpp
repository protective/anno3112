#include "Lexer.h"
#include "../Terminals/SOrderTerminals.h"
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

SOrderTerminal* Lexer::nextToken(){

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
		cerr<<"terminal var"<<endl; return new SOrderTerminal(TOKEN_var, pos);
		}
		break;
	case 1:
		{
		cerr<<"terminal if"<<endl; return new SOrderTerminal(TOKEN_if, pos);
		}
		break;
	case 2:
		{
		cerr<<"terminal while"<<endl; return new SOrderTerminal(TOKEN_while, pos);
		}
		break;
	case 3:
		{
		cerr<<"terminal assignment"<<endl; return new SOrderTerminal(TOKEN_assignment, pos);
		}
		break;
	case 4:
		{
		cerr<<"terminal comma"<<endl;return new SOrderTerminal(TOKEN_comma, pos);
		}
		break;
	case 5:
		{
		cerr<<"terminal plus"<<endl;return new SOrderTerminal(TOKEN_plus, pos);
		}
		break;
	case 6:
		{
		cerr<<"terminal minus"<<endl;return new SOrderTerminal(TOKEN_minus, pos);
		}
		break;
	case 7:
		{
		cerr<<"terminal semicolon"<<endl;return new SOrderTerminal(TOKEN_semicolon, pos);
		}
		break;
	case 8:
		{
		cerr<<"terminal leftp"<<endl;return new SOrderTerminal(TOKEN_left_p, pos);
		}
		break;
	case 9:
		{
		cerr<<"terminal rightp"<<endl;return new SOrderTerminal(TOKEN_right_p, pos);
		}
		break;
	case 10:
		{
		cerr<<"terminal leftcur"<<endl;return new SOrderTerminal(TOKEN_left_c, pos);
		}
		break;
	case 11:
		{
		cerr<<"terminal rightcur"<<endl;return new SOrderTerminal(TOKEN_right_c, pos);
		}
		break;
	case 12:
		{
		cerr<<"terminal id"<<endl;return new SOrderIdentifier(token, toklen, pos);
		}
		break;
	case 13:
		{
		cerr<<"terminal int"<<endl;return IntegerFromDecimalString(token, toklen, pos);
		}
		break;
	case 14:
		{
		cerr<<"terminal eof"<<endl;return new SOrderTerminal(TOKEN_EOF, pos);
		}
		break;
	case 15:
		{
		cerr<<"space"<<endl;goto BEGIN;
		}
		break;
	case 16:
		{
		cerr<<"tab"<<endl;goto BEGIN;
		}
		break;
	case 17:
		{
		cerr<<"newline lf"<<endl;goto BEGIN;
		}
		break;
	case 18:
		{
		cerr<<"newline cr"<<endl;goto BEGIN;
		}
		break;
	default:
		{
		cerr<<"terminal ERROR"<<endl;return new SOrderTerminal(TOKEN_error, pos);
		}
		break;
	}
	bufstart = marker;
	goto START;
State1:
	cursor++;
	if(limit == cursor) fill();
	accept = 14;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State4:
	cursor++;
	if(limit == cursor) fill();
	accept = 17;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State17:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State26;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State26:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State27;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State8:
	cursor++;
	if(limit == cursor) fill();
	accept = 5;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State27:
	cursor++;
	if(limit == cursor) fill();
	accept = 0;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State2:
	cursor++;
	if(limit == cursor) fill();
	accept = 16;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State20:
	cursor++;
	if(limit == cursor) fill();
	accept = 11;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State18:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State22;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State0:
	cursor++;
	if(limit == cursor) fill();
START: 
	switch(*cursor){
		case 4: goto State1;
		case 9: goto State2;
		case 10: goto State3;
		case 13: goto State4;
		case 32: goto State5;	//' '
		case 41: goto State7;	//')'
		case 40: goto State6;	//'('
		case 43: goto State8;	//'+'
		case 45: goto State10;	//'-'
		case 44: goto State9;	//','
		case 49: goto State11;	//'1'
		case 48: goto State11;	//'0'
		case 51: goto State11;	//'3'
		case 50: goto State11;	//'2'
		case 53: goto State11;	//'5'
		case 52: goto State11;	//'4'
		case 55: goto State11;	//'7'
		case 54: goto State11;	//'6'
		case 57: goto State11;	//'9'
		case 56: goto State11;	//'8'
		case 59: goto State12;	//';'
		case 61: goto State13;	//'='
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State15;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State16;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State18;	//'w'
		case 118: goto State17;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 123: goto State19;	//'{'
		case 122: goto State14;	//'z'
		case 125: goto State20;	//'}'
		default: goto final;
	};

State22:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State23;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State7:
	cursor++;
	if(limit == cursor) fill();
	accept = 9;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State6:
	cursor++;
	if(limit == cursor) fill();
	accept = 8;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State5:
	cursor++;
	if(limit == cursor) fill();
	accept = 15;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State16:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State28;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State25:
	cursor++;
	if(limit == cursor) fill();
	accept = 2;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State23:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State24;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State13:
	cursor++;
	if(limit == cursor) fill();
	accept = 3;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State10:
	cursor++;
	if(limit == cursor) fill();
	accept = 6;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State28:
	cursor++;
	if(limit == cursor) fill();
	accept = 1;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State3:
	cursor++;
	if(limit == cursor) fill();
	accept = 18;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State24:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State25;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State19:
	cursor++;
	if(limit == cursor) fill();
	accept = 10;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State12:
	cursor++;
	if(limit == cursor) fill();
	accept = 7;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State9:
	cursor++;
	if(limit == cursor) fill();
	accept = 4;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State15:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State11:
	cursor++;
	if(limit == cursor) fill();
	accept = 13;
	marker = cursor;
	switch(*cursor){
		case 49: goto State11;	//'1'
		case 48: goto State11;	//'0'
		case 51: goto State11;	//'3'
		case 50: goto State11;	//'2'
		case 53: goto State11;	//'5'
		case 52: goto State11;	//'4'
		case 55: goto State11;	//'7'
		case 54: goto State11;	//'6'
		case 57: goto State11;	//'9'
		case 56: goto State11;	//'8'
		default: goto final;
	};

State14:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 95: goto State21;	//'_'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

State21:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 49: goto State14;	//'1'
		case 48: goto State14;	//'0'
		case 51: goto State14;	//'3'
		case 50: goto State14;	//'2'
		case 53: goto State14;	//'5'
		case 52: goto State14;	//'4'
		case 55: goto State14;	//'7'
		case 54: goto State14;	//'6'
		case 57: goto State14;	//'9'
		case 56: goto State14;	//'8'
		case 65: goto State14;	//'A'
		case 67: goto State14;	//'C'
		case 66: goto State14;	//'B'
		case 69: goto State14;	//'E'
		case 68: goto State14;	//'D'
		case 71: goto State14;	//'G'
		case 70: goto State14;	//'F'
		case 73: goto State14;	//'I'
		case 72: goto State14;	//'H'
		case 75: goto State14;	//'K'
		case 74: goto State14;	//'J'
		case 77: goto State14;	//'M'
		case 76: goto State14;	//'L'
		case 79: goto State14;	//'O'
		case 78: goto State14;	//'N'
		case 81: goto State14;	//'Q'
		case 80: goto State14;	//'P'
		case 83: goto State14;	//'S'
		case 82: goto State14;	//'R'
		case 85: goto State14;	//'U'
		case 84: goto State14;	//'T'
		case 87: goto State14;	//'W'
		case 86: goto State14;	//'V'
		case 89: goto State14;	//'Y'
		case 88: goto State14;	//'X'
		case 90: goto State14;	//'Z'
		case 97: goto State14;	//'a'
		case 99: goto State14;	//'c'
		case 98: goto State14;	//'b'
		case 101: goto State14;	//'e'
		case 100: goto State14;	//'d'
		case 103: goto State14;	//'g'
		case 102: goto State14;	//'f'
		case 105: goto State14;	//'i'
		case 104: goto State14;	//'h'
		case 107: goto State14;	//'k'
		case 106: goto State14;	//'j'
		case 109: goto State14;	//'m'
		case 108: goto State14;	//'l'
		case 111: goto State14;	//'o'
		case 110: goto State14;	//'n'
		case 113: goto State14;	//'q'
		case 112: goto State14;	//'p'
		case 115: goto State14;	//'s'
		case 114: goto State14;	//'r'
		case 117: goto State14;	//'u'
		case 116: goto State14;	//'t'
		case 119: goto State14;	//'w'
		case 118: goto State14;	//'v'
		case 121: goto State14;	//'y'
		case 120: goto State14;	//'x'
		case 122: goto State14;	//'z'
		default: goto final;
	};

	}

}

