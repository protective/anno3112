/* 
 * File:   CGlobals.h
 * Author: karsten
 *
 * Created on 24. april 2011, 13:54
 */

#ifndef CGLOBALS_H
#define	CGLOBALS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#include "SDL/SDL_opengl.h"
#include "GL/gl.h"
#include <pthread.h>
#include <cstdlib>
#include "../GShare/GFunctions.h"

#include <FTGL/ftgl.h>
class CPlayerObjHandle;
class CObj;

class CPartical;
class CUIMainFrame;
class CUIBaseFrame;
class CPos;
class COrdres;
class CItemType;
class CShipType;
class CAstoroidType;
class CWorld;
class CLoadout;
using namespace std;

struct ConnectionStruct{
	int SocketFD;
	char* messagebuffer;
	char* messagepointer;
	bool connected;
	pthread_t listenThread;
};

struct CPlayercolour{
	CPlayercolour(double r,double g,double b){_r = r; _g = g; _b = b;}
	CPlayercolour(){}
	double _r;
	double _g;
	double _b;
};



extern pthread_mutex_t lockInput;
extern ConnectionStruct connection;
extern uint32_t tTime;
extern CPlayerObjHandle* playerObj;
extern list<CPartical*> particals;
extern map<uint32_t,GLuint> textures;
extern map<uint32_t,CItemType*> itemlist;
extern map<uint32_t, CShipType*> shipTypes;
extern map<uint32_t, CAstoroidType*> astoroidTypes;
extern CWorld* world;
extern CObj* playerSels;
extern list<CObj*> playerMultiSels;
extern map<uint32_t,COrdres*> globalOrders;
extern map<uint32_t,CLoadout*> globalLoadout;

extern uint32_t playerId;
extern map<uint32_t,uint8_t> teamlist;
extern CUIMainFrame* mainFrame;
extern CUIBaseFrame* selectedFrame;
extern CUIBaseFrame* focusFrame;
extern CUIBaseFrame* hoverFrame;
extern CPos* viewPos;
extern double viewZoom;
extern double viewRZoom;
extern FTGLPixmapFont font;
extern map<uint32_t, CPlayercolour> playercolour;
#endif	/* CGLOBALS_H */

