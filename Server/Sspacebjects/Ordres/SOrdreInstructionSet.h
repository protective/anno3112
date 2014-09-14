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
		jmpR        = 0x00010000,
		jmpA_1      = 0x00020000,
                cjmpA_1     = 0x00120000,
		jmpRC       = 0x00030000,
		jmpAC       = 0x00040000,
		pushN       = 0x00050000,
		pushS0N     = 0x00150000,
                pushN_1     = 0x00060000,
		popN        = 0x00070000,
		call        = 0x00080000,
		ret         = 0x00090000,
		cmpS0S1     = 0x000A0000,
		cmpS0R      = 0x000B0000,
		cmpS0A      = 0x000C0000,		
		pushRS_1    = 0x000D0000,
		pushS0A     = 0x000E0000,
                cpN_FT2     = 0x000F0000,
		addS01      = 0x00200000,
		minusS01    = 0x00210000,	 
		addS01dS1   = 0x00220000,
		minusS01dS1 = 0x00230000,
		sysCall     = 0x00F00000,
	};
}

#endif	/* SORDREINSTRUCTIONSET_H */

