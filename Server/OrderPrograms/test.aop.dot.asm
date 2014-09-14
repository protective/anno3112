no instruction =22
line	opcode			arg	
000000	0X06 (pushN_1)	0X01
0X0001		  	(value)        0X00000002
0X0002	0X06 (pushN_1)	0X01
0X0003		  	(value)        0X00000007
0X0004	0X06 (pushN_1)	0X01
0X0005		  	(value)        0X00000002
0X0006	0X06 (pushN_1)	0X01
0X0007		  	(value)        0X00000004
0X0008	0X05 (pushN)	0X01
0X0009	0X0F (cpN_FT2)	0X01
0X000A		  	(Rel dest)     0000000000
0X000B		  	(Rel src)      0X00000003
0X000C	0X06 (pushN_1)	0X01
0X000D		  	(value)        0X00000001
0X000E	0X22 (addS01dS1)
0X000F	0X05 (pushN)	0X01
0X0010	0X0F (cpN_FT2)	0X01
0X0011		  	(Rel dest)     0000000000
0X0012		  	(Rel src)      0X00000005
0X0013	0XF0 (sysCall)
0X0014	0X07 (popN)	0X03
0X0015	0X07 (popN)	0X01

