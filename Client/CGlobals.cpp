/* 
 * File:   CGlobals.cpp
 * Author: karsten
 * 
 * Created on 24. april 2011, 13:54
 */

#include "CGlobals.h"
#include "CPlayerObjHandle.h"
#include "spaceobjects/CShip.h"
#include "Grafic/CPartical.h"
#include "UI/CUIBaseFrame.h"
#include "spaceobjects/CPos.h"
#include "UI/CUIMainFrame.h"
#include "spaceobjects/COrdres.h"
#include "spaceobjects/subsystems/CLoadout.h"
#include "world/CWorld.h"
ConnectionStruct connection;
uint32_t tTime = 0;
pthread_mutex_t lockInput= PTHREAD_MUTEX_INITIALIZER;
CPlayerObjHandle* playerObj = new CPlayerObjHandle();
map<uint32_t,GLuint> textures;
map<uint32_t,CItemType*> itemlist;
map<uint32_t, CShipType*> shipTypes;
map<uint32_t, CAstoroidType*> astoroidTypes;
list<CPartical*> particals;
CObj* playerSels;
CWorld* world = new CWorld();
uint32_t playerId;
map<uint32_t,uint8_t> teamlist;

list<CObj*> playerMultiSels;
map<uint32_t,COrdres*> globalOrders;
map<uint32_t,CLoadout*> globalLoadout;
CUIMainFrame* mainFrame = new CUIMainFrame(NULL);
CUIBaseFrame* selectedFrame = NULL;
CUIBaseFrame* focusFrame = NULL;
CUIBaseFrame* hoverFrame =NULL;
CPos* viewPos = new CPos();
double viewZoom = 1;
double viewRZoom = 1;
map<uint32_t, CPlayercolour> playercolour;
FTGLPixmapFont font("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");


