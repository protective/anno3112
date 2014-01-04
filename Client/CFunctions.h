/* 
 * File:   CFunctions.h
 * Author: karsten
 *
 * Created on 24. april 2011, 13:54
 */

#ifndef CFUNCTIONS_H
#define	CFUNCTIONS_H
#include "../GShare/GFunctions.h"
#include "CGlobals.h"
#include "../Network/Serialize.h"
#include "CPlayerObjHandle.h"
#include "Grafic/Grafic.h"
void* Connect(string ip, uint32_t playerid, uint32_t pass);
void* Disconnect();
void* thread_Recive();
uint32_t getTime();
uint32_t parseBuffer(char* buffer, uint32_t len);
uint32_t Rangeobj(CPos& pos1, CPos& pos2);
uint32_t Rangeobj(CPos& pos1, int32_t x2, int32_t y2);
uint32_t Rangeobj(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

#endif	/* CFUNCTIONS_H */

