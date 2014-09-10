/* 
 * File:   SOrdreInstructionSet.h
 * Author: karsten
 *
 * Created on 5. september 2014, 17:51
 */

#ifndef SORDREINSTRUCTIONSET_H
#define	SORDREINSTRUCTIONSET_H

namespace inst{
	enum Enum{
		jmpR     = 0x00010000,
		jmpA     = 0x00020000,
		jmpRC    = 0x00030000,
		jmpAC    = 0x00040000,
		push     = 0x00050000,
		popn     = 0x00050000,
		call     = 0x00060000,
		ret      = 0x00070000,
		cmpS0S1  = 0x00080000,
		cmpS0R   = 0x00090000,
		cmpS0A   = 0x000A0000,		
		pushS0R  = 0x000B0000,
		pushS0A  = 0x000C0000,
	};
}

#endif	/* SORDREINSTRUCTIONSET_H */

