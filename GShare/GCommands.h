/* 
 * File:   GCommands.h
 * Author: karsten
 *
 * Created on 7. juni 2011, 19:09
 */

#ifndef GCOMMANDS_H
#define	GCOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <SDL/SDL.h>
#include <list>
#include <map>

#include "Enums.h"
struct GCommands {
	PlayerCommands::Enum _type;
	uint32_t _timeStamp;
};

struct GCommandsMove: public GCommands{
	int32_t _x;
	int32_t _y;
	int32_t _d;
};

#endif	/* GCOMMANDS_H */

