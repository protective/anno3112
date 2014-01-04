/* 
 * File:   main.cpp
 * Author: karsten
 *
 * Created on 23. april 2011, 09:33
 */

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
#include <SDL/SDL_ttf.h>
#include "SDL/SDL_opengl.h"
#include "GL/gl.h"
#include <pthread.h>
#include <cstdlib>


#include "../Client/CFunctions.h"
#include "../Client/Grafic/Grafic.h"

#include "../Client/spaceobjects/CPos.h"
#include "../Client/spaceobjects/CShip.h"
#include "../Client/spaceobjects/CShot.h"
#include "../Client/spaceobjects/CAstoroid.h"
#include "../Client/spaceobjects/subsystems/CSubTypeWep.h"
#include "../Client/spaceobjects/subsystems/CSubSystemW.h"
#include "../Client/Grafic/CPartical.h"
#include "../Client/UI/CUIMainFrame.h"
#include "AI/AIMain.h"
#include "spaceobjects/subsystems/CLoadout.h"
//#define width 640
//#define height 480
#define BPP 4
#define DEPTH 32
using namespace std;
/*
void DrawScreen(SDL_Surface* screen)
{
	glClear(GL_COLOR_BUFFER_BIT);



	mainFrame->Draw();

	//for (CobjI it = playerObj->getObjs().begin(); it != playerObj->getObjs().end();it++){
	//	it->second->Draw();
	//}



 

	SDL_GL_SwapBuffers();

}
*/

 int main(int argc, char* argv[]){

	ifstream ifile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");
	if (!ifile) {
		cerr<<"ERROR mscorefonts arial.ttf not found"<<endl;
		exit(1);
	}

	int argteam = 1;
	cerr<<"argc"<<argc<<endl;
	string argip = "127.0.0.1";
	if(argc >= 3){
		argteam = atoi(argv[1]);
			if(argteam == 0)
				argteam = 1;
		argip = string(argv[2]);
	}else if(argc >= 2){
		argteam = atoi(argv[1]);
			if(argteam == 0)
				argteam = 1;
	}
			
	cerr<<"argip"<<argip<<endl;


	for(int i = 0 ; i< 360; i++){
		double vector = (i*PI)/180;
		MySin[i] = sin(vector);
		MyCos[i] = cos(vector);
	}

	printbufferbool = true;
	//teamlist[1] = 1; //TODO ANOTHER BIG TODO TO FIX
	//teamlist[2] = 2;

	playercolour[1] = CPlayercolour(0,0,1);
	playercolour[2] = CPlayercolour(1,0,0);
	playercolour[3] = CPlayercolour(1,1,0);
	playercolour[4] = CPlayercolour(1,0,1);
	//loadGData();
		TTF_Init();
	  atexit(TTF_Quit);
	  /*fronts
	  for (int i = 16; i < 31; i++ ){
	  	front1.insert(pair<uint32_t, TTF_Font* >(i, TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf",i)));

	  }
	   */

	  
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	  
    SDL_Event event;

    int keypress = 0;
    int h=0;
	SDL_EnableUNICODE(1);

	AIMain* ai = new AIMain();
	
	Connect(argip,argteam, 42);
	uint32_t deltaTime = 0;
	uint32_t lastTime = 0;
	uint32_t aiprocesTimer = 10000;
	
	//playerObj->ServerRequestCreateLoadout();
	globalLoadout[6] = new CLoadout(6,"AI_AC",*itemlist[6]->getShipType());

	globalLoadout[6]->getItems()[1]._xitem = 1;
	globalLoadout[6]->getItems()[1]._type = itemlist[3];
	globalLoadout[6]->getItems()[1]._targetGroup = TargetGroup::Heavy;

	globalLoadout[6]->getItems()[2]._xitem = 2;
	globalLoadout[6]->getItems()[2]._type = itemlist[2];
	globalLoadout[6]->getItems()[2]._targetGroup = TargetGroup::Heavy;

	globalLoadout[6]->getItems()[3]._xitem = 2;
	globalLoadout[6]->getItems()[3]._type = itemlist[2];
	globalLoadout[6]->getItems()[3]._targetGroup = TargetGroup::Heavy;
	
	globalLoadout[6]->getItems()[4]._xitem = 1;
	globalLoadout[6]->getItems()[4]._type = itemlist[13];
	globalLoadout[6]->getItems()[4]._targetGroup = TargetGroup::Light;
	
	globalLoadout[6]->getItems()[5]._xitem = 1;
	globalLoadout[6]->getItems()[5]._type = itemlist[45];

	globalLoadout[6]->getItems()[6]._xitem = 1;
	globalLoadout[6]->getItems()[6]._type = itemlist[15];

	globalLoadout[6]->getItems()[7]._xitem = 1;
	globalLoadout[6]->getItems()[7]._type = itemlist[22];

	globalLoadout[6]->getItems()[8]._xitem = 1;
	globalLoadout[6]->getItems()[8]._type = itemlist[25];

	globalLoadout[6]->getItems()[9]._xitem = 1;
	globalLoadout[6]->getItems()[9]._type = itemlist[25];

	
	globalLoadout[16] = new CLoadout(16,"AI_HAC",*itemlist[16]->getShipType());

	globalLoadout[16]->getItems()[1]._xitem = 2;
	globalLoadout[16]->getItems()[1]._type = itemlist[21];
	globalLoadout[16]->getItems()[1]._targetGroup = TargetGroup::Heavy;

	globalLoadout[16]->getItems()[2]._xitem = 1;
	globalLoadout[16]->getItems()[2]._type = itemlist[11];
	globalLoadout[16]->getItems()[2]._targetGroup = TargetGroup::Heavy;

	globalLoadout[16]->getItems()[3]._xitem = 1;
	globalLoadout[16]->getItems()[3]._type = itemlist[20];
	globalLoadout[16]->getItems()[3]._targetGroup = TargetGroup::Medium;
	
	globalLoadout[16]->getItems()[4]._xitem = 1;
	globalLoadout[16]->getItems()[4]._type = itemlist[20];
	globalLoadout[16]->getItems()[4]._targetGroup = TargetGroup::Medium;

	globalLoadout[16]->getItems()[5]._xitem = 1;
	globalLoadout[16]->getItems()[5]._type = itemlist[20];
	globalLoadout[16]->getItems()[5]._targetGroup = TargetGroup::Medium;
	
	globalLoadout[16]->getItems()[6]._xitem = 1;
	globalLoadout[16]->getItems()[6]._type = itemlist[20];
	globalLoadout[16]->getItems()[6]._targetGroup = TargetGroup::Medium;

	globalLoadout[16]->getItems()[7]._xitem = 2;
	globalLoadout[16]->getItems()[7]._type = itemlist[15];
	
	globalLoadout[16]->getItems()[8]._xitem = 2;
	globalLoadout[16]->getItems()[8]._type = itemlist[15];
	
	globalLoadout[16]->getItems()[9]._xitem = 1;
	globalLoadout[16]->getItems()[9]._type = itemlist[45];
	
	globalLoadout[16]->getItems()[10]._xitem = 1;
	globalLoadout[16]->getItems()[10]._type = itemlist[17];
	
	globalLoadout[16]->getItems()[11]._xitem = 1;
	globalLoadout[16]->getItems()[11]._type = itemlist[44];
				
	globalLoadout[16]->getItems()[12]._xitem = 3;
	globalLoadout[16]->getItems()[12]._type = itemlist[25];
	
	globalLoadout[16]->getItems()[13]._xitem = 3;
	globalLoadout[16]->getItems()[13]._type = itemlist[25];

	globalLoadout[1] = new CLoadout(1,"AI_BC",*itemlist[16]->getShipType());

	globalLoadout[1]->getItems()[1]._xitem = 2;
	globalLoadout[1]->getItems()[1]._type = itemlist[3];
	globalLoadout[1]->getItems()[1]._targetGroup = TargetGroup::Heavy;

	globalLoadout[1]->getItems()[2]._xitem = 2;
	globalLoadout[1]->getItems()[2]._type = itemlist[3];
	globalLoadout[1]->getItems()[2]._targetGroup = TargetGroup::Heavy;

	globalLoadout[1]->getItems()[3]._xitem = 2;
	globalLoadout[1]->getItems()[3]._type = itemlist[11];
	globalLoadout[1]->getItems()[3]._targetGroup = TargetGroup::Heavy;
	
	globalLoadout[1]->getItems()[4]._xitem = 2;
	globalLoadout[1]->getItems()[4]._type = itemlist[11];
	globalLoadout[1]->getItems()[4]._targetGroup = TargetGroup::Heavy;

	globalLoadout[1]->getItems()[5]._xitem = 2;
	globalLoadout[1]->getItems()[5]._type = itemlist[2];
	globalLoadout[1]->getItems()[5]._targetGroup = TargetGroup::Medium;
	
	globalLoadout[1]->getItems()[6]._xitem = 2;
	globalLoadout[1]->getItems()[6]._type = itemlist[2];
	globalLoadout[1]->getItems()[6]._targetGroup = TargetGroup::Medium;

	globalLoadout[1]->getItems()[7]._xitem = 2;
	globalLoadout[1]->getItems()[7]._type = itemlist[12];
	globalLoadout[1]->getItems()[7]._targetGroup = TargetGroup::Medium;

	globalLoadout[1]->getItems()[8]._xitem = 1;
	globalLoadout[1]->getItems()[8]._type = itemlist[41];

	globalLoadout[1]->getItems()[9]._xitem = 1;
	globalLoadout[1]->getItems()[9]._type = itemlist[41];

	globalLoadout[1]->getItems()[10]._xitem = 1;
	globalLoadout[1]->getItems()[10]._type = itemlist[17];
	
	globalLoadout[1]->getItems()[11]._xitem = 1;
	globalLoadout[1]->getItems()[11]._type = itemlist[45];

	globalLoadout[1]->getItems()[12]._xitem = 2;
	globalLoadout[1]->getItems()[12]._type = itemlist[15];

	globalLoadout[1]->getItems()[13]._xitem = 3;
	globalLoadout[1]->getItems()[13]._type = itemlist[41];

	globalLoadout[1]->getItems()[14]._xitem = 3;
	globalLoadout[1]->getItems()[14]._type = itemlist[22];
		
	globalLoadout[1]->getItems()[15]._xitem = 4;
	globalLoadout[1]->getItems()[15]._type = itemlist[25];
			
	globalLoadout[1]->getItems()[16]._xitem = 4;
	globalLoadout[1]->getItems()[16]._type = itemlist[25];
	
	
	globalLoadout[46] = new CLoadout(46,"AI_DD",*itemlist[46]->getShipType());

	globalLoadout[46]->getItems()[1]._xitem = 1;
	globalLoadout[46]->getItems()[1]._type = itemlist[12];
	globalLoadout[46]->getItems()[1]._targetGroup = TargetGroup::Medium;

	globalLoadout[46]->getItems()[2]._xitem = 4;
	globalLoadout[46]->getItems()[2]._type = itemlist[9];
	globalLoadout[46]->getItems()[2]._targetGroup = TargetGroup::Light;

	globalLoadout[46]->getItems()[3]._xitem = 1;
	globalLoadout[46]->getItems()[3]._type = itemlist[22];
	
	globalLoadout[46]->getItems()[4]._xitem = 2;
	globalLoadout[46]->getItems()[4]._type = itemlist[25];

	cerr<<"begin loop"<<endl;
    while(!keypress){
		//main loop
		deltaTime = SDL_GetTicks() - lastTime;
		while(deltaTime < 10){
			deltaTime = SDL_GetTicks() - lastTime;
			usleep(100);
		}
		lastTime = SDL_GetTicks();
		aiprocesTimer += deltaTime;
		if (aiprocesTimer > 10000){
			aiprocesTimer = 0;
			cerr<<"proces<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
			ai->recreateGroups();
			cerr<<"done proces<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
			
		}	
		pthread_mutex_lock(&lockInput);
		map<uint32_t,CObj*> toberemoved;
		mainFrame->preAdd();
		for(map<uint32_t,CObj*>::iterator it = playerObj->getObjs().begin(); it!= playerObj->getObjs().end(); it++ ){
			it->second->Proces(deltaTime);
			if (it->second->canBeRemoved()){
				
				CObj* oldid = it->second;
				if(it->second->isShot()){

					mainFrame->remove(*it->second->isShot());
					toberemoved[it->first] =it->second;
				}if(it->second->isShip()){
					mainFrame->remove(*it->second->isShip());
					toberemoved[it->first] =it->second;
				}if(it->second->isAstoroid()){
					mainFrame->remove(*it->second->isAstoroid());
					toberemoved[it->first] =it->second;
				}
				for (CobjI it2 = playerObj->getObjs().begin() ; it2 != playerObj->getObjs().end();it2++){
					it2->second->announceRemovalOf(oldid);
				}

			}
		}
		for(map<uint32_t,CObj*>::iterator it = toberemoved.begin(); it!= toberemoved.end(); it++ ){
			delete playerObj->getObjs()[it->first];
			playerObj->getObjs().erase(it->first);
		}
		toberemoved.clear();
		for(list<CPartical*>::iterator it = particals.begin(); it != particals.end();){
			(*it)->Proces(deltaTime);
			if((*it)->canBeRemoved()){
				delete *it;
				particals.erase(it++);
			}else
				 it++;
		}
		mainFrame->finalRemove();
		pthread_mutex_unlock(&lockInput);
		
		//DrawScreen(screen);
		while(SDL_PollEvent(&event)){
			pthread_mutex_lock(&lockInput);
			
				switch (event.type){
					case SDL_QUIT:
						keypress = 1;
						break;
				}
			pthread_mutex_unlock(&lockInput);
		}
		pthread_mutex_unlock(&lockInput);
	}
	Disconnect();
	SDL_Quit();
	return 0;
}