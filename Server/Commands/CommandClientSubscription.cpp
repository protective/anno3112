/* 
 * File:   CommandClientSubscription.cpp
 * Author: karsten
 * 
 * Created on 17. april 2014, 09:36
 */

#include "CommandClientSubscription.h"
#include "Processable.h"

CommandClientSubscription::CommandClientSubscription(uint32_t time, uint32_t client, Processable* target, SubscriptionLevel::Enum level):
Command(time){
	_client = client; 
	_target = target;
	_level = level;
}

uint32_t CommandClientSubscription::execute(){
	cerr<<"execute client subsction id="<<_client<<endl;
	_target->subscribeClient(_client, _level);
}

CommandClientSubscription::~CommandClientSubscription() {
}

