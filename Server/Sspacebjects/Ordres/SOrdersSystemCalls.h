/* 
 * File:   SOrdersSystemCalls.h
 * Author: karsten
 *
 * Created on 14. september 2014, 18:26
 */

#ifndef SORDERSSYSTEMCALLS_H
#define	SORDERSSYSTEMCALLS_H

#include "../../SFunctions.h"


typedef void (*systemCallFunc)(Processor*, OBJID obj, void*);

typedef struct systemCallFunc_table{
	systemCallFunc _systemCallFunc;
	string _name;
	

}systemCallFunc_t;
void systemSetSubsystemFlags(Processor*, OBJID obj, void* arg);


static const systemCallFunc_t GlobalSystemCallLib[] =
{{ systemSetSubsystemFlags,"systemSetFlags"}, {(systemCallFunc)NULL, "null"}};
#endif	/* SORDERSSYSTEMCALLS_H */

