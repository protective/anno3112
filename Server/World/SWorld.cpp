/* 
 * File:   SWorld.cpp
 * Author: karsten
 * 
 * Created on 22. maj 2011, 16:24
 */

#include "SWorld.h"
#include "../Commands/Processor.h"
#include "../Commands/CommandProcessor.h"
#include "../Commands/CommandAdd.h"
SWorld::SWorld(Processor* processors) {
	_processors = processors;
}

void SWorld::addGrid(SGrid* grid){
	this->grids[grid->_id] = grid;
}

map<uint32_t, SGrid*>& SWorld::getGrids(){
	return this->grids;
}
map<uint32_t, SObj*>& SWorld::getObjs(){
	return this->objInWorld;
}

void SWorld::add(SUnit* unit){
	list<Command*> tempL;
	CommandProcessor* unitProces = new CommandProcessor(unit,1000/FRAMERATE,0);
	tempL.push_back(unitProces);
	CommandAdd* temp = new CommandAdd(getTime(),unit,tempL);
	_processors[0].addCommand(temp);
}


void SWorld::proces(uint32_t deltaT){
	_time = SDL_GetTicks();
	
}
/*
void SWorld::proces(uint32_t thead_id){
	pthread_barrier_wait(&procesBar);
	
	//proces object internal //create shots!!!
	SObjI it = this->objInWorld.begin();
	for (int i = 0; i < thead_id;i++){
		if(it == this->objInWorld.end())
			break;
		it++;
	}
	while(true){

		if (it != this->objInWorld.end()){
			it->second->proces();
		}else{
			break;
		}
		for (int i = 0; i < NRTHREADS ;i++){
			it++;
			if (it == this->objInWorld.end())
				break;
		}
	}
	pthread_barrier_wait(&procesBar);
	//Move objects
	it = this->objInWorld.begin();
	for (int i = 0; i < thead_id;i++){
		if(it == this->objInWorld.end())
			break;
		it++;
	}
	while(true){
		if (it != this->objInWorld.end()){
			if (it->second->isMovable())
				it->second->isMovable()->Move(0);
		}else
			break;

		for (int i = 0; i < NRTHREADS ;i++){
			it++;
			if (it == this->objInWorld.end())
				break;
		}
	}
	pthread_barrier_wait(&procesBar);

	//proces object external
	it = this->objInWorld.begin();
	for (int i = 0; i < thead_id;i++){
		if(it == this->objInWorld.end())
			break;
		it++;
	}
	while(true){

		if (it != this->objInWorld.end()){
			it->second->postProces();
		}else{
			break;
		}
		for (int i = 0; i < NRTHREADS ;i++){
			it++;
			if (it == this->objInWorld.end())
				break;
		}
	}
	//Test shot hits
	pthread_barrier_wait(&procesBar);

	it = this->objInWorld.begin();
	for (int i = 0; i < thead_id;i++){
		if(it == this->objInWorld.end())
			break;
		it++;
	}
	while(true){
		if (it != this->objInWorld.end()){
			if (it->second->isShot())
				it->second->isShot()->TestHit();
		}else
			break;

		for (int i = 0; i < NRTHREADS ;i++){
			it++;
			if (it == this->objInWorld.end())
				break;
		}
	}
	pthread_barrier_wait(&procesBar);

	if(thead_id == 0){
		for (SGridI it = this->grids.begin(); it != this->grids.end();it++){
			it->second->Proces(thead_id);
			it->second->SendObjInfoToClients();
		}
	}
	pthread_barrier_wait(&procesBar);
}
*/


SWorld::~SWorld() {
}

