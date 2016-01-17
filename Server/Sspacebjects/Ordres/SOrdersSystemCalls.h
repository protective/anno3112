/* 
 * File:   SOrdersSystemCalls.h
 * Author: karsten
 *
 * Created on 14. september 2014, 18:26
 */

#ifndef SORDERSSYSTEMCALLS_H
#define	SORDERSSYSTEMCALLS_H

#include "../../SFunctions.h"

class CommandOrderThread;
class SProgrammable;
typedef void (*systemCallFunc)(Processor*,Command*, SProgrammable* obj, void*);

typedef struct systemCallBack_table{
	uint32_t _id;
	string _name;
}systemCallBack_t;	

typedef struct systemCallFunc_table{
	systemCallFunc _systemCallFunc;
	string _name;
}systemCallFunc_t;

void systemSetSubsystemFlags(Processor*, Command*, SProgrammable* obj, void* arg);
void systemSleep(Processor*, Command*, SProgrammable* obj, void* arg);
void qureyItems(Processor*, Command*, SProgrammable* obj, void* arg);
void transfereItems(Processor*, Command*, SProgrammable* obj, void* arg);


static const systemCallFunc_t GlobalSystemCallLib[] =
{
{systemSetSubsystemFlags,"systemSetFlags"},
{systemSleep,"wait"}, //int ms
{qureyItems,"queryItems"}, //int itemid, conditionAttribute, op, value
{transfereItems,"transfereItems"}, //int from, int itemid, int quan
{(systemCallFunc)NULL, "null"}
};

static const systemCallBack_t GlobalSystemCallBackLib[] =
{
{1,"queryComplete"},
{2,"queryItemsComplete"},
{0, "null"}
};
#endif	/* SORDERSSYSTEMCALLS_H */

