/* 
 * File:   SSubSystemFighter.cpp
 * Author: karsten
 * 
 * Created on 4. februar 2014, 19:57
 */

#include "SSubSystemFighter.h"
#include "SSubTypeFighter.h"
#include "../SFighter.h"
#include "../../World/SWorld.h"
SSubSystemFighter::SSubSystemFighter(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem):
SSubSystem(owner,slotnode,id)
{
	for(int i = 0; i < getTypeFighter()->getBayCount(); i++){
		
				//TODO FIX id 
			SFighter* fighter = new SFighter(0, owner.getPos(), *getTypeFighter()->getFighterType(),owner.getPlayerId());
			world->getGrids()[1]->addUnit(fighter);
	}
}

void SSubSystemFighter::proces(Processor* processor){

}

uint32_t SSubSystemFighter::AddItem(uint32_t Xitem){

}

uint32_t SSubSystemFighter::RemoveItem(uint32_t Xitem){

}

SSubSystemFighter::~SSubSystemFighter() {
}
