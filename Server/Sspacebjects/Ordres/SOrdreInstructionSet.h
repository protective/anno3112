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
		NOP			= 0x00000000,
		EOP         = 0x00010000, //i
		jmpR        = 0x00310000,
		jmpA_1      = 0x00320000,
        cjmpA_1     = 0x00330000,
		jmpRC       = 0x00340000,
		jmpAC       = 0x00350000,
		pushN       = 0x00050000,
		pushS0N     = 0x00150000,
        pushN_1     = 0x00060000, //i
		popN        = 0x00070000, //i
		call        = 0x00400000, 
		ret         = 0x00410000,
		popPC       = 0x00420000,
		pushPC      = 0x00430000, 
		pushRPC     = 0x00440000, 
		
		cmpS0S1     = 0x000A0000,
		cmpS0R      = 0x000B0000,
		cmpS0A      = 0x000C0000,		
		pushRS_1    = 0x000D0000,
		pushS0A     = 0x000E0000,
        cpN_DS2     = 0x00500000, //i
		cpN_DRS2    = 0x00510000,
		cpN_RDS2    = 0x00520000,
		addS01      = 0x00200000,
		minusS01    = 0x00210000,	 
		addS01dS1   = 0x00220000, //i
		minusS01dS1 = 0x00230000,
		sysCall     = 0x00F00000, //i
	};
}

#endif	/* SORDREINSTRUCTIONSET_H */

