/* 
 * File:   SFunctions.h
 * Author: karsten
 *
 * Created on 23. april 2011, 09:57
 */

#ifndef SFUNCTIONS_H
#define	SFUNCTIONS_H
#include "../GShare/GFunctions.h"
#include "SGlobals.h"
#include "../Network/Serialize.h"
#define FRAMERATE 25

using namespace std;



class Client;
class SPos;
void* thread_Listen();
void* thread_Recive(Client* client);
uint32_t parseBuffer(Client* client,uint32_t len);
void* ReadBuffer(Client* client);
void sendtoC(Client* cli, char* buffer, uint32_t len);
uint32_t getFreeID();

uint32_t Rangeobj(SPos& pos1, SPos& pos2);

bool LinePointIntersect(int32_t p1x,  int32_t p1y, int32_t p2x,int32_t p2y, int32_t pointx, int32_t pointy, int32_t range);
int32_t Direction(SPos& pos1, SPos& pos2);
bool InAngle(int32_t angle, FireDir::Enum fd);
#endif	/* SFUNCTIONS_H */

