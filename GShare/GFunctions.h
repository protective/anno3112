/* 
 * File:   GFunctions.h
 * Author: karsten
 *
 * Created on 23. april 2011, 10:43
 */

#ifndef GFUNCTIONS_H
#define	GFUNCTIONS_H
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <SDL/SDL.h>
#include <list>
#include <map>
#include <algorithm>
#include "Enums.h"
#include <math.h>
#include "GCommands.h"
#include "GGlobals.h"
using namespace std;
void printBuffer(char* buffer, uint32_t len);
uint32_t myrandom(uint32_t min,uint32_t max);

int32_t Deg(double x, double y);
double VektorUnitX(uint32_t deg);
double VektorUnitY(uint32_t deg);
int32_t dirDiff(uint32_t d1, uint32_t d2);
uint32_t Rangecord(int32_t p1x,  int32_t p1y, int32_t p2x,int32_t p2y);
bool LinePointIntersect(int32_t p1x,  int32_t p1y, int32_t p2x,int32_t p2y, int32_t pointx, int32_t pointy, int32_t range);
string getTargetGroupstring(TargetGroup::Enum en);
//double range(int32_t x1, int32_t y1, int32_t x2, int32_t y2){
//	return sqrt((x1 - x2) ^ 2 + (y1 - y2) ^ 2);
//}
#endif	/* GFUNCTIONS_H */

