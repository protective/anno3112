no instruction =71
line	opcode			arg	
000000	0X06 (pushN_1)	0X01
0X0001		  	(value)        0000000000
0X0002	0X06 (pushN_1)	0X01
0X0003		  	(value)        0000000000
0X0004	0X06 (pushN_1)	0X01
0X0005		  	(value)        0000000000
0X0006	0X06 (pushN_1)	0X01
0X0007		  	(value)        0X0000AAAA
0X0008	0X43 (pushPC)
0X0009	0X32 (jmpA_1)	0000
0X000A		  	(Line)         0X0020
0X000B	0X01 (...EOP...)
0X000C	0000 (...NOP...)
0X000D	0X06 (pushN_1)	0X01
0X000E		  	(value)        0X0000EEEE
0X000F	0X05 (pushN)	0X01
0X0010	0X50 (cpN_DS2)	0X01
0X0011		  	(Rel dest)     0000000000
0X0012		  	(Rel src)      0X00000004
0X0013	0X05 (pushN)	0X01
0X0014	0X50 (cpN_DS2)	0X01
0X0015		  	(Rel dest)     0000000000
0X0016		  	(Rel src)      0X00000004
0X0017	0X06 (pushN_1)	0X01
0X0018		  	(value)        0X00000032
0X0019	0XF0 (sysCall)	0X03
0X001A		  	(Stack)        0X00000004
0X001B	0X07 (popN)	0X03
0X001C	0X07 (popN)	0X01
0X001D	0X07 (popN)	0X03
0X001E	0X42 (popPC)
0X001F	0000 (...NOP...)
0X0020	0X06 (pushN_1)	0X01
0X0021		  	(value)        0X0000EEEE
0X0022	0X06 (pushN_1)	0X01
0X0023		  	(value)        0X000003E8
0X0024	0XF0 (sysCall)	0X01
0X0025		  	(Stack)        0X00000002
0X0026	0X07 (popN)	0X01
0X0027	0X07 (popN)	0X01
0X0028	0X32 (jmpA_1)	0000
0X0029		  	(Line)         0X0041
0X002A	0X07 (popN)	0X01
0X002B	0X06 (pushN_1)	0X01
0X002C		  	(value)        0X0000EEEE
0X002D	0X06 (pushN_1)	0X01
0X002E		  	(value)        0X00000018
0X002F	0X06 (pushN_1)	0X01
0X0030		  	(value)        0X00000001
0X0031	0X06 (pushN_1)	0X01
0X0032		  	(value)        0X00000005
0X0033	0X06 (pushN_1)	0X01
0X0034		  	(value)        0X00000002
0X0035	0XF0 (sysCall)	0X02
0X0036		  	(Stack)        0X00000005
0X0037	0X07 (popN)	0X04
0X0038	0X07 (popN)	0X01
0X0039	0X06 (pushN_1)	0X01
0X003A		  	(value)        0X0000EEEE
0X003B	0X06 (pushN_1)	0X01
0X003C		  	(value)        0X00001F40
0X003D	0XF0 (sysCall)	0X01
0X003E		  	(Stack)        0X00000002
0X003F	0X07 (popN)	0X01
0X0040	0X07 (popN)	0X01
0X0041	0X06 (pushN_1)	0X01
0X0042		  	(value)        0X00000001
0X0043	0X33 (cjmpA_1)	0000
0X0044		  	(Line)         0X002A
0X0045	0X07 (popN)	0X01
0X0046	0X42 (popPC)

