/* 
 * File:   Processor.cpp
 * Author: karsten
 * 
 * Created on 16. februar 2014, 22:24
 */

#include "Processor.h"
#include "CommandProcessor.h"
#include "CommandAdd.h"
#include "../World/SWorld.h"
#include "../Sspacebjects/SFighter.h"
#include "../Sspacebjects/SShip.h"
#include "../Sspacebjects/SAstoroidBelt.h"
#include "../Sspacebjects/SShot.h"
#include "CommandProcesMetas.h"
#include "../Sspacebjects/Ordres/Compiler/CommandCompiler.h"
#include "../Sspacebjects/Ordres/CommandOrderThread.h"
#include "CommandQueryCmp.h"
#include <sys/time.h>
Processor::Processor() {
	
	cerr<<"init processor"<<endl;
	pthread_cond_init(&_workCond,NULL);
	pthread_mutex_init(&_workMutex,NULL);
	pthread_mutex_init(&_lockFreeID, NULL);
	pthread_mutex_init(&_lockCommands, NULL);
	addCommand(new CommandTimedSubscribeUpdate(SubscriptionLevel::lowFreq));
	addCommand(new CommandProcesMetas());
	addCommand(new CommandCompiler("/home/karsten/anno3112/Server/OrderPrograms/test.aop"));

	_workReady = false;
	_freeIdCount = 1;
	_id = 0;
}

uint32_t Processor::getFreeID(){
	uint32_t ret;
	pthread_mutex_lock(&_lockFreeID);
		_freeIdCount++;
		ret = _freeIdCount | (_id << 24); //add the 8 bit processor id
	pthread_mutex_unlock(&_lockFreeID);
	return ret;
}

list<Command*> Processor::removeByProcessable(Processable* proc){
	list<Command*> temp;
	pthread_mutex_lock(&this->_lockCommands);
		for(list<Command*>::iterator it = _commands.begin(); it != _commands.end();){
			if((*it)->getProcessable() == proc)
			{
				temp.push_back(*it);
				(*it)->setProcessor(NULL);
				_commands.erase(it++);
			}else
				 it++;
		}
	pthread_mutex_unlock(&this->_lockCommands);
	return temp;
}

void* Processor::workThreadFunction(void* context){
	((Processor*)context)->work(); //cast the thread att to the class function
}

void Processor::work(){
	struct timespec timeToWait;
	struct timeval now;
	Command* tempCommand = NULL;

	
	while(true){
		//get next command that are ready
		tempCommand = procesFirstReadyCommand(); 
		if(tempCommand){
			uint32_t result  = tempCommand->execute();
			if (result == COMMAND_FINAL)
				delete tempCommand;  //comand return 0 (DONE) delete it
			else if(result == COMMAND_REPEAT)
				this->addCommand(tempCommand);
		}else{
			clock_gettime(CLOCK_REALTIME, &timeToWait);
			timeToWait.tv_nsec+=25000000;  //25ms
			if(timeToWait.tv_nsec >= 1000000000) {
				timeToWait.tv_nsec -= 1000000000;
				timeToWait.tv_sec++;
			}
			pthread_mutex_lock(&_workMutex);
			pthread_cond_timedwait(&_workCond,&_workMutex,&timeToWait);
			pthread_mutex_unlock(&_workMutex);
		}
	}
}

Command* Processor::procesFirstReadyCommand(){
		Command* temp = NULL;
		//lock commandList
		pthread_mutex_lock(&this->_lockCommands);
		if(_commands.size()){
			if(_commands.front()->getTime() <= world->getTime()){
				temp = _commands.front();
				_commands.pop_front();
			}
		}
		//we are done Unlock list
		pthread_mutex_unlock(&this->_lockCommands);
		//return the command found if any
		return temp;
}

uint32_t Processor::addCommand(Command* cmd){
	//lock commandlist
	pthread_mutex_lock(&this->_lockCommands);
	list<Command*>::iterator it = _commands.begin();
	//cerr<<"insert ="<<cmd<<endl;
	
	while (true){
		if(it != _commands.end()){
			if (cmd->getTime() <= (*it)->getTime()){
				cmd->setProcessor(this);
				_commands.insert(it,cmd);
				break;
			}else{
				it++;
			}
		}else{
			cmd->setProcessor(this);
			_commands.push_back(cmd);
			break;
		}
	}
	//cerr<<"content=";
	//for(list<Command*>::iterator it = _commands.begin(); it!=_commands.end(); it++){
	//	cerr<<*it<<" "<<(*it)->getTime()<<" ";
	//}
	//cerr<<endl;
	//we are done adding
	pthread_mutex_unlock(&this->_lockCommands);
	//we have work to do signal! 
	pthread_mutex_lock(&_workMutex);
	this->_workReady = true;
	pthread_mutex_unlock(&_workMutex);
	pthread_cond_signal(&this->_workCond);
	return 0;
}

uint32_t Processor::removeCommand(Command* cmd){
	cerr<<"remove command"<<endl;
	pthread_mutex_lock(&this->_lockCommands);
	list<Command*>::iterator it = _commands.begin();
	while(it != _commands.end()){
		if(*it == cmd){
			cmd->setProcessor(NULL);
			_commands.remove(cmd);
			pthread_mutex_unlock(&this->_lockCommands);
			return 1;
		}
		it++;
	}
	pthread_mutex_unlock(&this->_lockCommands);
	return 0;
}


SShot* Processor::createShot(SPos& pos, SSubAble* owner, uint32_t target, SSubTypeWep* type){
	SShot* shot = new SShot(getFreeID(), pos, owner, target, type, this);
	CommandProcessor* proces = new CommandProcessor(shot,200/FRAMERATE,0);
	list<Command*> cmdlist;
	cmdlist.push_back(proces);
	CommandAdd* add = new CommandAdd(world->getTime(), shot, cmdlist);
	this->addCommand(add);
	return shot;
}

SShip* Processor::createShip(SPos& pos, SShipType& stype, uint32_t playerId){
	cerr<<"create ship"<<endl;
	SShip* ship = new SShip(getFreeID(), pos, stype, playerId);
	CommandProcessor* proces = new CommandProcessor(ship,1000/FRAMERATE,0);
	
	CommandOrderThread* t = new CommandOrderThread(ship->getId());

	list<Command*> cmdlist;
	cmdlist.push_back(proces);
	cmdlist.push_back(t);

	CommandAdd* add = new CommandAdd(world->getTime(), ship, cmdlist);
	this->addCommand(add);
	return ship;
}

SFighter* Processor::createFighter(SPos& pos, SFighterType& ftype, uint32_t playerId , uint32_t mothership, uint32_t motherShipSub){
	SFighter* fighter = new SFighter(getFreeID(), pos, ftype, playerId, mothership, motherShipSub);
	CommandProcessor* proces = new CommandProcessor(fighter,1000/FRAMERATE,0);
	list<Command*> cmdlist;
	cmdlist.push_back(proces);
	CommandAdd* add = new CommandAdd(world->getTime(), fighter, cmdlist);
	this->addCommand(add);
	return fighter;
}

SAstoroid* Processor::createAsteroid(SPos& pos, SAstoroidType& atype, SAstoroidBelt* belt){
	SAstoroid* asteroid = new SAstoroid(getFreeID(), pos, atype, belt);
	CommandProcessor* proces = new CommandProcessor(asteroid,1000/FRAMERATE, 0);
	list<Command*> cmdlist;
	cmdlist.push_back(proces);
	CommandAdd* add = new CommandAdd(world->getTime(), asteroid, cmdlist);
	this->addCommand(add);
	return asteroid;
}


SAstoroidBelt* Processor::createAsteroidBelt(SPos& pos){
	SAstoroidBelt* asteroid = new SAstoroidBelt(getFreeID(), pos);
	CommandProcessor* proces = new CommandProcessor(asteroid,1000/FRAMERATE, 0);
	list<Command*> cmdlist;
	cmdlist.push_back(proces);
	CommandAdd* add = new CommandAdd(world->getTime(), asteroid, cmdlist);
	this->addCommand(add);
	return asteroid;
}

SGrid* Processor::createGrid(){
	cerr<<"create grid"<<endl;
	SGrid* grid = new SGrid(0); //TODO FIX SOON ON CLIENT
	CommandProcessor* proces = new CommandProcessor(grid,1000/FRAMERATE, 0);
	list<Command*> cmdlist;
	cmdlist.push_back(proces);
	CommandAdd* add = new CommandAdd(world->getTime(), grid, cmdlist);
	this->addCommand(add);
	return grid;
}

Processor::~Processor() {
}

