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
		cerr<<"newline lf"<<endl;goto BEGIN;
		}
		break;
	case 17:
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
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State25;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State25:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State26;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State7:
	cursor++;
	if(limit == cursor) fill();
	accept = 5;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State26:
	cursor++;
	if(limit == cursor) fill();
	accept = 0;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State18:
	cursor++;
	if(limit == cursor) fill();
	accept = 10;
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
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State21;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State0:
	cursor++;
	if(limit == cursor) fill();
START: 
	switch(*cursor){
		case 4: goto State1;
		case 10: goto State2;
		case 13: goto State3;
		case 32: goto State4;	//' '
		case 41: goto State6;	//')'
		case 40: goto State5;	//'('
		case 43: goto State7;	//'+'
		case 45: goto State9;	//'-'
		case 44: goto State8;	//','
		case 49: goto State10;	//'1'
		case 48: goto State10;	//'0'
		case 51: goto State10;	//'3'
		case 50: goto State10;	//'2'
		case 53: goto State10;	//'5'
		case 52: goto State10;	//'4'
		case 55: goto State10;	//'7'
		case 54: goto State10;	//'6'
		case 57: goto State10;	//'9'
		case 56: goto State10;	//'8'
		case 59: goto State11;	//';'
		case 61: goto State12;	//'='
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State14;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State15;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State17;	//'w'
		case 118: goto State16;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 123: goto State18;	//'{'
		case 122: goto State13;	//'z'
		case 125: goto State19;	//'}'
		default: goto final;
	};

State21:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State22;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State6:
	cursor++;
	if(limit == cursor) fill();
	accept = 9;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State5:
	cursor++;
	if(limit == cursor) fill();
	accept = 8;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State15:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State27;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State24:
	cursor++;
	if(limit == cursor) fill();
	accept = 2;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State22:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State23;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State12:
	cursor++;
	if(limit == cursor) fill();
	accept = 3;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State9:
	cursor++;
	if(limit == cursor) fill();
	accept = 6;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State27:
	cursor++;
	if(limit == cursor) fill();
	accept = 1;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State3:
	cursor++;
	if(limit == cursor) fill();
	accept = 16;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State23:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State24;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State2:
	cursor++;
	if(limit == cursor) fill();
	accept = 17;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State11:
	cursor++;
	if(limit == cursor) fill();
	accept = 7;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State8:
	cursor++;
	if(limit == cursor) fill();
	accept = 4;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State19:
	cursor++;
	if(limit == cursor) fill();
	accept = 11;
	marker = cursor;
	switch(*cursor){
		default: goto final;
	};

State14:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State10:
	cursor++;
	if(limit == cursor) fill();
	accept = 13;
	marker = cursor;
	switch(*cursor){
		case 49: goto State10;	//'1'
		case 48: goto State10;	//'0'
		case 51: goto State10;	//'3'
		case 50: goto State10;	//'2'
		case 53: goto State10;	//'5'
		case 52: goto State10;	//'4'
		case 55: goto State10;	//'7'
		case 54: goto State10;	//'6'
		case 57: goto State10;	//'9'
		case 56: goto State10;	//'8'
		default: goto final;
	};

State13:
	cursor++;
	if(limit == cursor) fill();
	accept = 12;
	marker = cursor;
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 95: goto State20;	//'_'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

State20:
	cursor++;
	if(limit == cursor) fill();
	switch(*cursor){
		case 49: goto State13;	//'1'
		case 48: goto State13;	//'0'
		case 51: goto State13;	//'3'
		case 50: goto State13;	//'2'
		case 53: goto State13;	//'5'
		case 52: goto State13;	//'4'
		case 55: goto State13;	//'7'
		case 54: goto State13;	//'6'
		case 57: goto State13;	//'9'
		case 56: goto State13;	//'8'
		case 65: goto State13;	//'A'
		case 67: goto State13;	//'C'
		case 66: goto State13;	//'B'
		case 69: goto State13;	//'E'
		case 68: goto State13;	//'D'
		case 71: goto State13;	//'G'
		case 70: goto State13;	//'F'
		case 73: goto State13;	//'I'
		case 72: goto State13;	//'H'
		case 75: goto State13;	//'K'
		case 74: goto State13;	//'J'
		case 77: goto State13;	//'M'
		case 76: goto State13;	//'L'
		case 79: goto State13;	//'O'
		case 78: goto State13;	//'N'
		case 81: goto State13;	//'Q'
		case 80: goto State13;	//'P'
		case 83: goto State13;	//'S'
		case 82: goto State13;	//'R'
		case 85: goto State13;	//'U'
		case 84: goto State13;	//'T'
		case 87: goto State13;	//'W'
		case 86: goto State13;	//'V'
		case 89: goto State13;	//'Y'
		case 88: goto State13;	//'X'
		case 90: goto State13;	//'Z'
		case 97: goto State13;	//'a'
		case 99: goto State13;	//'c'
		case 98: goto State13;	//'b'
		case 101: goto State13;	//'e'
		case 100: goto State13;	//'d'
		case 103: goto State13;	//'g'
		case 102: goto State13;	//'f'
		case 105: goto State13;	//'i'
		case 104: goto State13;	//'h'
		case 107: goto State13;	//'k'
		case 106: goto State13;	//'j'
		case 109: goto State13;	//'m'
		case 108: goto State13;	//'l'
		case 111: goto State13;	//'o'
		case 110: goto State13;	//'n'
		case 113: goto State13;	//'q'
		case 112: goto State13;	//'p'
		case 115: goto State13;	//'s'
		case 114: goto State13;	//'r'
		case 117: goto State13;	//'u'
		case 116: goto State13;	//'t'
		case 119: goto State13;	//'w'
		case 118: goto State13;	//'v'
		case 121: goto State13;	//'y'
		case 120: goto State13;	//'x'
		case 122: goto State13;	//'z'
		default: goto final;
	};

	}

}

