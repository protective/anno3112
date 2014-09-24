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
typedef void (*systemCallFunc)(Processor*,Command*, OBJID obj, void*);

typedef struct systemCallBack_table{
	uint32_t _id;
	string _name;
}systemCallBack_t;	

typedef struct systemCallFunc_table{
	systemCallFunc _systemCallFunc;
	string _name;
}systemCallFunc_t;

void systemSetSubsystemFlags(Processor*, Command*, OBJID obj, void* arg);
void systemSleep(Processor*, Command*, OBJID obj, void* arg);


static const systemCallFunc_t GlobalSystemCallLib[] =
{
{systemSetSubsystemFlags,"systemSetFlags"},
{systemSleep,"wait"},
{(systemCallFunc)NULL, "null"}
};

static const systemCallBack_t GlobalSystemCallBackLib[] =
{
{1,"queryComplete"},
{0, "null"}
};
#endif	/* SORDERSSYSTEMCALLS_H */

