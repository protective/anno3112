/* 
 * File:   Processor.cpp
 * Author: karsten
 * 
 * Created on 16. februar 2014, 22:24
 */

#include "Processor.h"

Processor::Processor() {
	
	pthread_cond_init(&_workCond,NULL);
	pthread_mutex_init(&_workMutex,NULL);
	pthread_mutex_init(&_lockFreeID, NULL);
}

uint32_t Processor::getFreeID(){
	uint32_t ret;
	pthread_mutex_lock(&_lockFreeID);
		_freeIdCount++;
		ret = _freeIdCount | (_id << 24); //add the 8 bit processor id
	pthread_mutex_unlock(&_lockFreeID);
	return ret;
}

void* Processor::workThreadFunction(void* context){
	((Processor*)context)->work(); //cast the thread att to the class function
}

void Processor::work(){
	Command* tempCommand = NULL;
	while(true){	
		pthread_mutex_lock(&_workMutex);
		while(!_workReady) //IF no work go to sleep
			pthread_cond_wait(&_workCond,&_workMutex);
		_workReady = false; //we are going to do all the work
		pthread_mutex_unlock(&_workMutex);
		
		while(true){
			//get next command that are ready
			tempCommand = procesFirstReadyCommand(); 
			if(tempCommand){
				if (tempCommand->execute() == COMMAND_FINAL); 
					delete tempCommand;  //comand return 0 (DONE) delete it
			}else{
				break;
			}
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
	while (true){
		if(it != _commands.end()){
			if (cmd->getTime() <= (*it)->getTime()){
				_commands.insert(it,cmd);
				break;
			}else{
				it++;
			}
		}else{
			_commands.push_back(cmd);
			break;
		}
	}
	//we are done adding
	pthread_mutex_unlock(&this->_lockCommands);
	
	
	//we have work to do signal! 
	pthread_mutex_lock(&_workMutex);
	this->_workReady = true;
	pthread_mutex_unlock(&_workMutex);
	pthread_cond_signal(&this->_workCond);
}

uint32_t Processor::removeCommand(Command* cmd){
	pthread_mutex_lock(&this->_lockCommands);
	list<Command*>::iterator it = _commands.begin();
	while(it != _commands.end()){
		if(*it == cmd){
			_commands.remove(cmd);
			pthread_mutex_unlock(&this->_lockCommands);
			return 1;
		}
		it++;
	}
	pthread_mutex_unlock(&this->_lockCommands);
	return 0;
}


Processor::~Processor() {
}

