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


#include "CFunctions.h"
#include "Grafic/Grafic.h"

#include "spaceobjects/CPos.h"
#include "spaceobjects/CShip.h"
#include "spaceobjects/CShot.h"
#include "spaceobjects/CAstoroid.h"
#include "spaceobjects/subsystems/CSubTypeWep.h"
#include "spaceobjects/subsystems/CSubSystemW.h"
#include "Grafic/CPartical.h"
#include "UI/CUIMainFrame.h"

//#define width 640
//#define height 480
#define BPP 4
#define DEPTH 32
using namespace std;

void DrawScreen(SDL_Surface* screen)
{
	glClear(GL_COLOR_BUFFER_BIT);



	mainFrame->Draw();

	//for (CobjI it = playerObj->getObjs().begin(); it != playerObj->getObjs().end();it++){
	//	it->second->Draw();
	//}



 

	SDL_GL_SwapBuffers();

}


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

    SDL_Event event;

    int keypress = 0;
    int h=0;
	SDL_EnableUNICODE(1);
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
	printf("Unable to initialize SDL: %s\n", SDL_GetError());
	return 1;
	}
	
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_Surface* screen = SDL_SetVideoMode(Basewidth, Basehight, 24, SDL_OPENGL); // *changed*
	if(!screen){
		cerr<<"ERROR init SDL >"<<SDL_GetError()<<endl;
		exit(1);
	}
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.5);
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glViewport( 0, 0, Basewidth, Basehight );
	glClear( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0.0f, Basewidth, Basehight, 0.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	
	textures[Textures::EffectSheet] = loadTexture(Textures::EffectSheet);
	textures[Textures::EffectSheet2] = loadTexture(Textures::EffectSheet2);
	textures[Textures::SlotSheet] = loadTexture(Textures::SlotSheet);
	textures[Textures::ShotSheet] = loadTexture(Textures::ShotSheet);
	textures[Textures::ItemSheet] = loadTexture(Textures::ItemSheet);
	textures[Textures::SubItemSheet] = loadTexture(Textures::SubItemSheet);
	textures[Textures::ObjSheet] = loadTexture(Textures::ObjSheet);
	textures[Textures::OwObjSheet] = loadTexture(Textures::OwObjSheet);
	textures[Textures::IconSheet] = loadTexture(Textures::IconSheet);

	Connect(argip,argteam, 42);
	uint32_t deltaTime = 0;
	uint32_t lastTime = 0;
	cerr<<"begin loop"<<endl;
    while(!keypress){
		//main loop

		deltaTime = SDL_GetTicks() - lastTime;
		while(deltaTime < 30){
			deltaTime = SDL_GetTicks() - lastTime;
			usleep(100);
		}


		//cerr<<deltaTime<<endl;
		lastTime = SDL_GetTicks();
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
		
		DrawScreen(screen);
		
		pthread_mutex_unlock(&lockInput);
		
		//end main loop
		// begin input

		while(SDL_PollEvent(&event)){
			pthread_mutex_lock(&lockInput);
			
			switch (event.type){
				case SDL_QUIT:
					keypress = 1;
					break;
				case SDL_KEYDOWN:
					//if (event.key.keysym.sym == SDLK_s)
					
					if(focusFrame){
						cerr<<"key"<<endl;
						focusFrame->KeyDown(event);
					}
					if(mainFrame){
						if (event.key.keysym.sym == SDLK_DOWN)
							viewPos->y += 20000*viewRZoom;
						if(event.key.keysym.sym == SDLK_UP)
							viewPos->y -= 20000*viewRZoom;
						if (event.key.keysym.sym == SDLK_LEFT)
							viewPos->x -= 20000*viewRZoom;
						if(event.key.keysym.sym == SDLK_RIGHT)
							viewPos->x += 20000*viewRZoom;						
					}
					break;
				case SDL_MOUSEMOTION:
					//if (selectedFrame && event.button.button == SDL_BUTTON_LEFT){
						//selectedFrame->moveX(event.motion.xrel);
						//selectedFrame->moveY(event.motion.yrel);
						hoverFrame = NULL;
						mainFrame->Move(event,event.button.x,event.button.y);
						break;
					//}
				case SDL_MOUSEBUTTONUP:
					mainFrame->MouseUp(event,event.button.x,event.button.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_WHEELDOWN){
						double oldZ = viewRZoom;
						viewZoom -= viewZoom*0.1;

						if (viewZoom< 0.25)
							viewZoom = 0.25;
						
						viewRZoom = pow(viewZoom,-1);
						if (viewRZoom> 4)
							viewRZoom = 4;
						
						int32_t mx = (Basewidth * viewRZoom)-(Basewidth * oldZ);
						int32_t my = (Basehight * viewRZoom)-(Basehight * oldZ);
						cerr<<mx<<" "<<my<<endl;
						//viewPos->x = (mx* viewRZoom)+viewPos->x;
						//viewPos->y = (my* viewRZoom)+viewPos->y;
						viewPos->x-= mx*50;
						viewPos->y-= my*50;
						
						break;
					}else if(event.button.button == SDL_BUTTON_WHEELUP){
						viewZoom += viewZoom*0.1;

						
						if (viewZoom> 2)
							viewZoom = 2;
						
						viewRZoom = pow(viewZoom,-1);
						if (viewRZoom< 0.5)
							viewRZoom = 0.5;
						
						int32_t mx = (event.button.x - (Basewidth/2)) *100;
						int32_t my = (event.button.y- (Basehight/2))*100;
						viewPos->x = (mx* viewRZoom)+viewPos->x;
						viewPos->y = (my* viewRZoom)+viewPos->y;						
						
						break;
					}
					
					mainFrame->Click(event, event.button.x,event.button.y);
					
			
					break;

			}
			pthread_mutex_unlock(&lockInput);
		}
	}
	Disconnect();
	SDL_Quit();
}