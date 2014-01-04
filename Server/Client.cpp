/* 
 * File:   Client.cpp
 * Author: karsten
 * 
 * Created on 23. april 2011, 10:00
 */

#include <vector>

#include "Client.h"
#include "World/SWorld.h"
#include "Sspacebjects/SShipType.h"
#include "Sspacebjects/subsystems/SSubType.h"
#include "Sspacebjects/subsystems/SSubTypeWep.h"
#include "Sspacebjects/subsystems/SSubTypeFac.h"
#include "Sspacebjects/subsystems/SSubTypeBoost.h"
#include "Sspacebjects/subsystems/SSubSystemBonus.h"
#include "Sspacebjects/SAstoroidType.h"
#include "Sspacebjects/SOrdres.h"
#include "Sspacebjects/subsystems/SLoadout.h"
#include "Sspacebjects/subsystems/SSubTypeRef.h"
//#include "Sspacebjects/subsystems/SShipTypeSlotData.h"

Client::Client(int socket) {

	this->socket = socket;
	playerID = 0;
	_teamId = 2;
	this->parsingoutput = false;
	this->active_buffer = 1;
	this->networkBuf1.recived = 0;
	this->networkBuf2.recived = 0;
	pthread_mutex_init(&this->networkBufLock, NULL);
	pthread_mutex_init(&this->networkSendLock, NULL);
	pthread_mutex_init(&this->locksubscriber, NULL);
	
	pthread_mutex_lock(&this->networkSendLock);
	networkSendLockBool = true;
	pthread_mutex_unlock(&this->networkSendLock);
	//this->switchBuffer();
	inputnetworkBuf = &networkBuf1;
	outputnetworkBuf = &networkBuf2;




	cerr << "create client" << endl;
}


void Client::initTransfere(){
	this->sendTeams();
	this->sendGrids();
	this->sendItemTypes();
	this->sendShipTypes();
	this->sendAstoroidTypes();
	this->sendOrdres();
	this->sendLoadOuts();

	if (world) {
		if (world->getGrids()[1]) {
			world->getGrids()[1]->Subscribe(this); //TODO FIX This
		}
	}
	cerr<<"data sendt"<<endl;
}

void Client::sendItemTypes() {

	//TODO send shiptype
	for (map<uint32_t, SItemType*>::iterator it = itemlist.begin(); it != itemlist.end(); it++) {
		if (!it->second) {
			cerr << "WARNING Client:senditemtype undefined item in itemlist itemid >"<<it->first<< endl;
			continue;
		}
		
		//**********************
		//send subsystemdata
		if (it->second->getSubType()) {
			if (it->second->getSubType()->isWeapon()) {
				SSubTypeWep * temp = it->second->getSubType()->isWeapon();
				uint32_t xmats = it->second->getCost().size();
				
				char message[sizeof (SerialTypeWeapon)+ (xmats * sizeof (SerialPartMat))];
				memset(message, 0, sizeof (SerialTypeWeapon)+ (xmats * sizeof (SerialPartMat)));

				SerialTypeWeapon* data = (SerialTypeWeapon*) (message);
				data->_type = SerialType::SerialTypeWeapon;
				data->_size = sizeof(SerialTypeWeapon)+ (xmats * sizeof (SerialPartMat));
				data->_item._itemId = it->first;
				data->_item._itemtex = it->second->getTexId();
				data->_item._mass = it->second->getMass();
				data->_item._buildtime = it->second->getBuildTime();
				if (it->second->getName().size() <= 20){
					memcpy(data->_item._name, it->second->getName().c_str(), it->second->getName().size());
				}else
					cerr << "WARNING Client:senditemtype serial wep  Name to long" << endl;
				data->_item._matcount = it->second->getCost().size(); //TODO
				data->_maxamo = temp->getMaxAmo();
				data->_amocost = temp->getamoCost();
				data->_amotype = 0; //TODO
				data->_cooldown = temp->getMaxCd();
				data->_fitClass = 0; //TODO;
				data->_maxdmg = temp->getDmgMax();
				data->_mindmg = temp->getDmgMin();
				data->_maxseq = 0; //TODO;
				data->_mount = 0; //TODO;
				data->_prospeed = temp->getSpeed();
				data->_protex = temp->getamoCost();
				for (int i = 0; i < 10; i++) {
					data->_seq[i] = 0;
				}
				int i = 0;
				
				for (map<uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin(); it2 != it->second->getCost().end(); it2++) {
					SerialPartMat* data2 = (SerialPartMat*)(message + sizeof(SerialTypeWeapon) + (sizeof(SerialPartMat) * i));
					data2->_matid = it2->second._item->getTypeID();
					data2->_quantity = it2->second._quan;

					i++;
				}
				send(this->getSocket(), message, sizeof (SerialTypeWeapon)+ (xmats * sizeof (SerialPartMat)), 0);


			}else if (it->second->getSubType()->isBoost()) {
				SSubTypeBoost * temp = it->second->getSubType()->isBoost();
				uint32_t xmats = it->second->getCost().size();
				char message[sizeof (SerialTypeBoost)+ (xmats * sizeof (SerialPartMat))];
				memset(message, 0, sizeof (SerialTypeBoost)+ (xmats * sizeof (SerialPartMat)));
				SerialTypeBoost* data = (SerialTypeBoost*) (message);
				data->_type = SerialType::SerialTypeBoost;
				data->_size = sizeof(SerialTypeBoost)+ (xmats * sizeof (SerialPartMat));
				data->_item._itemId = it->first;
				data->_item._itemtex = it->second->getTexId();
				data->_item._mass = it->second->getMass();
				data->_item._buildtime = it->second->getBuildTime();
				if (it->second->getName().size() <= 20){
					memcpy(data->_item._name, it->second->getName().c_str(), it->second->getName().size());
				}else
					cerr << "WARNING Client:senditemtype serial boost  Name to long" << endl;
				data->_item._matcount = it->second->getCost().size(); //TODO
				data->_boostType = (uint32_t)temp->getBoostType();
				data->_boostValue = temp->getBoostAmount();


				for (map<BonusTypes::Enum, int32_t>::iterator it2 = temp->getBonuslist().begin(); it2 != temp->getBonuslist().end(); it2++){
					switch(it2->first){
						case BonusTypes::Armor:{data->_bonus._armor = it2->second;break;}
						case BonusTypes::Hull:{data->_bonus._hull = it2->second;break;}
						case BonusTypes::Deflector:{data->_bonus._deflector = it2->second;break;}
						case BonusTypes::ShieldStr:{data->_bonus._shStr = it2->second;break;}
						case BonusTypes::ScanRange:{data->_bonus._scanrange = it2->second;break;}
						case BonusTypes::ScanPRange:{data->_bonus._scanprange = it2->second;break;}
						case BonusTypes::SpeedThruster:{data->_bonus._speedthruster = it2->second;break;}
						case BonusTypes::ManuvereThruster:{data->_bonus._manuverethruster = it2->second;break;}
					}
				}
				data->_maxamo = temp->getMaxAmo();
				data->_amocost = temp->getamoCost();
				data->_amotype = 0; //TODO
				data->_cooldown = temp->getMaxCd();
				data->_fitClass = 0; //TODO;
				data->_mount = 0; //TODO;
	
				int i = 0;

				for (map<uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin(); it2 != it->second->getCost().end(); it2++) {
					SerialPartMat* data2 = (SerialPartMat*)(message + sizeof(SerialTypeBoost) + (sizeof(SerialPartMat) * i));
					data2->_matid = it2->second._item->getTypeID();
					data2->_quantity = it2->second._quan;

					i++;
				}
				send(this->getSocket(), message, sizeof (SerialTypeBoost)+ (xmats * sizeof (SerialPartMat)), 0);


			}else if (it->second->getSubType()->isBonus()) {
				SSubTypeBonus * temp = it->second->getSubType()->isBonus();
				uint32_t xmats = it->second->getCost().size();

				char message[sizeof (SerialTypeBonus)+ (xmats * sizeof (SerialPartMat))];
				memset(message, 0, sizeof (SerialTypeBonus)+ (xmats * sizeof (SerialPartMat)));

				SerialTypeBonus* data = (SerialTypeBonus*) (message);
				data->_type = SerialType::SerialTypeBonus;
				data->_size = sizeof(SerialTypeBonus)+ (xmats * sizeof (SerialPartMat));
				data->_item._itemId = it->first;
				data->_item._itemtex = it->second->getTexId();
				data->_item._mass = it->second->getMass();
				data->_item._buildtime = it->second->getBuildTime();
				if (it->second->getName().size() <= 20){
					memcpy(data->_item._name, it->second->getName().c_str(), it->second->getName().size());
				}else
					cerr << "WARNING Client:senditemtype serial boost  Name to long" << endl;
				data->_item._matcount = it->second->getCost().size(); //TODO

				for (map<BonusTypes::Enum, int32_t>::iterator it2 = temp->getBonuslist().begin(); it2 != temp->getBonuslist().end(); it2++){
					switch(it2->first){
						case BonusTypes::Armor:{data->_bonus._armor = it2->second;break;}
						case BonusTypes::Hull:{data->_bonus._hull = it2->second;break;}
						case BonusTypes::Deflector:{data->_bonus._deflector = it2->second;break;}
						case BonusTypes::ShieldStr:{data->_bonus._shStr = it2->second;break;}
						case BonusTypes::Energy:{data->_bonus._energy = it2->second;break;}
						case BonusTypes::ScanRange:{data->_bonus._scanrange = it2->second;break;}
						case BonusTypes::ScanPRange:{data->_bonus._scanprange = it2->second;break;}
						case BonusTypes::SpeedThruster:{data->_bonus._speedthruster = it2->second;break;}
						case BonusTypes::ManuvereThruster:{data->_bonus._manuverethruster = it2->second;break;}

					}
				}
				data->_fitClass = 0; //TODO;
				data->_mount = 0; //TODO;

				int i = 0;

				for (map<uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin(); it2 != it->second->getCost().end(); it2++) {
					SerialPartMat* data2 = (SerialPartMat*)(message + sizeof(SerialTypeBonus) + (sizeof(SerialPartMat) * i));
					data2->_matid = it2->second._item->getTypeID();
					data2->_quantity = it2->second._quan;

					i++;
				}
				send(this->getSocket(), message, sizeof (SerialTypeBonus)+ (xmats * sizeof (SerialPartMat)), 0);


			} else if (it->second->getSubType()->isFac()) {

				SSubTypeFac * temp = it->second->getSubType()->isFac();
				uint32_t xmats = it->second->getCost().size();
				uint32_t xbuild = it->second->getSubType()->isFac()->getCanBuildList().size();
				char message[sizeof (SerialTypeFac)+ (xmats * sizeof (SerialPartMat))+ (xbuild * sizeof (SerialPartConstruct))];
				memset(message, 0, sizeof (SerialTypeFac)+ (xmats * sizeof (SerialPartMat))+ (xbuild * sizeof (SerialPartConstruct)));
				SerialTypeFac* data = (SerialTypeFac*) (message);
				data->_type = SerialType::SerialTypeFac;
				data->_size = sizeof (SerialTypeFac)+ (xmats * sizeof (SerialPartMat))+ (xbuild * sizeof (SerialPartConstruct));
				data->_item._itemId = it->first;
				data->_item._itemtex = it->second->getTexId();
				data->_item._mass = it->second->getMass();
				data->_item._buildtime = it->second->getBuildTime();
				if (it->second->getName().size() <= 20)
					memcpy(data->_item._name, it->second->getName().c_str(), it->second->getName().size());
				else
					cerr << "WARNING Client:senditemtype serial fac Name to long " << endl;
				data->_item._matcount = it->second->getCost().size(); //TODO
				data->_fitClass = 0; //TODO;
				data->_mount = 0; //TODO;;
				data->_xcanbuild = xbuild;
				int i = 0;
				for (map<uint32_t, SItemType*>::iterator it2 = temp->getCanBuildList().begin(); it2 != temp->getCanBuildList().end(); it2++) {
					SerialPartConstruct* data3 = (SerialPartConstruct*) (message + sizeof (SerialTypeFac)+(sizeof (SerialPartConstruct) * i));
					if(it2->second){
						data3->_buildTypeId = it2->second->getTypeID();
						i++;
					}else{
						cerr << "WARNING Client:senditemtype buildlist contain invalid item " << endl;
					}
				}
				i = 0;
				for (map<uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin(); it2 != it->second->getCost().end(); it2++) {
					SerialPartMat* data2 = (SerialPartMat*) (message + sizeof (SerialTypeFac)+(sizeof (SerialPartConstruct) * xbuild)+(sizeof (SerialPartMat) * i));
					data2->_matid = it2->second._item->getTypeID();
					data2->_quantity = it2->second._quan;

					i++;
				}
				send(this->getSocket(), message, sizeof (SerialTypeFac)+ (xmats * sizeof (SerialPartMat))+ (xbuild * sizeof (SerialPartConstruct)), 0);
			} else if (it->second->getSubType()->isRef()) {
				SSubTypeRef * temp = it->second->getSubType()->isRef();
				uint32_t xmats = it->second->getCost().size();
				uint32_t xrefine = it->second->getSubType()->isRef()->getCanRefineList().size();
				char message[sizeof (SerialTypeRef)+ (xmats * sizeof (SerialPartMat))+ (xrefine * sizeof (SerialPartRefine))];
				memset(message, 0, sizeof (SerialTypeRef)+ (xmats * sizeof (SerialPartMat))+ (xrefine * sizeof (SerialPartRefine)));
				SerialTypeRef* data = (SerialTypeRef*) (message);
				data->_type = SerialType::SerialTypeRef;
				data->_size = sizeof (SerialTypeRef)+ (xmats * sizeof (SerialPartMat))+ (xrefine * sizeof (SerialPartRefine));
				data->_item._itemId = it->first;
				data->_item._itemtex = it->second->getTexId();
				data->_item._mass = it->second->getMass();
				data->_item._buildtime = it->second->getBuildTime();
				if (it->second->getName().size() <= 20)
					memcpy(data->_item._name, it->second->getName().c_str(), it->second->getName().size());
				else
					cerr << "WARNING Client:senditemtype serial fac Name to long " << endl;
				data->_item._matcount = it->second->getCost().size(); //TODO
				data->_fitClass = 0; //TODO;
				data->_mount = 0; //TODO;;
				data->_xcanRefine = xrefine;
				int i = 0;
				for (map<uint32_t, SItemType*>::iterator it2 = temp->getCanRefineList().begin(); it2 != temp->getCanRefineList().end(); it2++) {
					SerialPartRefine* data3 = (SerialPartRefine*) (message + sizeof (SerialTypeRef)+(sizeof (SerialPartRefine) * i));
					if(it2->second){
						data3->_refineTypeId = it2->second->getTypeID();
						i++;
					}else{
						cerr << "WARNING Client:senditemtype buildlist contain invalid item " << endl;
					}
				}
				i = 0;
				for (map<uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin(); it2 != it->second->getCost().end(); it2++) {
					SerialPartMat* data2 = (SerialPartMat*) (message + sizeof (SerialTypeRef)+(sizeof (SerialPartRefine) * xrefine)+(sizeof (SerialPartMat) * i));
					data2->_matid = it2->second._item->getTypeID();
					data2->_quantity = it2->second._quan;

					i++;
				}
				send(this->getSocket(), message, sizeof (SerialTypeRef)+ (xmats * sizeof (SerialPartMat))+ (xrefine * sizeof (SerialPartRefine)), 0);
			}
		}else if(it->second->getShipType() == NULL) {
			//send material
			uint32_t xmats = it->second->getCost().size();

			char message[sizeof (SerialTypeMaterial)+ (xmats * sizeof (SerialPartMat))];
			memset(message, 0, sizeof (SerialTypeMaterial)+ (xmats * sizeof (SerialPartMat)));

			SerialTypeMaterial* data = (SerialTypeMaterial*) (message);
			data->_type = SerialType::SerialTypeMaterial;
			data->_size = sizeof(SerialTypeMaterial)+ (xmats * sizeof (SerialPartMat));
			data->_item._itemId = it->first;
			data->_item._itemtex = it->second->getTexId();
			data->_item._mass = it->second->getMass();
			data->_item._buildtime = it->second->getBuildTime();
			if (it->second->getName().size() <= 20)
				memcpy(data->_item._name, it->second->getName().c_str(), it->second->getName().size());
			else
				cerr << "WARNING Client:senditemtype serial material  Name to long" << endl;
			data->_item._matcount = xmats;

			int i = 0;

			for (map<uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin(); it2 != it->second->getCost().end(); it2++) {
				SerialPartMat* data2 = (SerialPartMat*)(message + sizeof(SerialTypeMaterial) + (sizeof(SerialPartMat) * i));
				data2->_matid = it2->second._item->getTypeID();
				data2->_quantity = it2->second._quan;

				i++;
			}
			send(this->getSocket(), message, sizeof (SerialTypeMaterial)+ (xmats * sizeof (SerialPartMat)), 0);
		}
	}
	cerr<<"done send"<<endl;
}


void Client::sendOrdres() {

	cerr<<"player id "<<this->playerID<<endl;
	for (map<uint32_t,SOrdres*>::iterator it = globalOrders[this->playerID].begin(); it != globalOrders[this->playerID].end(); it++) {

		char message[sizeof (SerialOrders)];
		memset(message, 0, sizeof (SerialOrders));

		SerialOrders* data = (SerialOrders*) (message);
		data->_type = SerialType::SerialOrders;
		data->_size = sizeof (SerialOrders);
		
		data->_PlayerId = this->playerID;
		data->_OrdreId = it->first;
		data->_posesset = 0;
		data->_unitsset = 0;
		if(it->second->getunitSet().find(0) != it->second->getunitSet().end())
			data->_unitsset  = data->_unitsset | BitF_MiningUnit;
		if(it->second->getPosSet().find(0) != it->second->getPosSet().end())
			data->_posesset  = data->_posesset | BitF_MiningPos;
		if(it->second->getunitSet().find(1) != it->second->getunitSet().end())
			data->_unitsset  = data->_unitsset | BitF_DropOfUnit;

		if (it->second->getName().size() <= 20)
			memcpy(data->_name, it->second->getName().c_str(), it->second->getName().size());
		else
			cerr << "WARNING Client:sendOrdres serial  Name to long" << endl;

		send(this->getSocket(), message, sizeof (SerialOrders), 0);

	}
}

void Client::sendTeams() {

	for (map<uint32_t,uint8_t>::iterator it = teamlist.begin(); it != teamlist.end(); it++) {

		char message[sizeof (SerialPlayerTeam)];
		memset(message, 0, sizeof (SerialPlayerTeam));

		SerialPlayerTeam* data = (SerialPlayerTeam*) (message);
		data->_type = SerialType::SerialPlayerTeam;
		data->_size = sizeof (SerialPlayerTeam);

		data->_playerId = it->first;
		data->_team = it->second;

		send(this->getSocket(), message, sizeof (SerialPlayerTeam), 0);

	}
}
void Client::sendLoadOuts() {
	for(map<uint32_t,SLoadout*>::iterator it = globalLoadout[this->getPlayerId()].begin() ; it != globalLoadout[this->getPlayerId()].end(); it++){
		sendLoadout(it->first);
	}
}

void Client::sendLoadout(uint32_t id) {

	char message[sizeof (SerialLoadout)];
	memset(message, 0, sizeof (SerialLoadout));

	SerialLoadout* data = (SerialLoadout*) (message);
	data->_type = SerialType::SerialLoadout;
	data->_size = sizeof (SerialLoadout);

	data->_id = id;
	data->_shiptype = globalLoadout[getPlayerId()][id]->getShipType()->getId();
	string sus = globalLoadout[getPlayerId()][id]->getName();
	if (sus.size() <= 20)
		memcpy(data->_name, sus.c_str(), sus.size());
	else
		cerr << "WARNING Client:sendLoadout serial Name to long" << endl;

	send(this->getSocket(), message, sizeof (SerialLoadout), 0);

}


void Client::sendShipTypes() {


	//TODO send shiptype

	for (map<uint32_t, SShipType*>::iterator it = shipTypes.begin(); it != shipTypes.end(); it++) {

		uint32_t xmats = 0;
		SItemType* tempitem = NULL;
		for (map<uint32_t, SItemType*>::iterator ititem = itemlist.begin(); ititem != itemlist.end(); ititem++) {
			if (ititem->second->getShipType() != NULL && ititem->second->getShipType() ==it->second){
				xmats = ititem->second->getCost().size();
				tempitem = ititem->second;
			}
		}


		char message2[sizeof (SerialShipType)+(xmats * sizeof (SerialPartMat))];
		memset(message2, 0, sizeof (SerialShipType)+(xmats * sizeof (SerialPartMat)));

		SerialShipType* data2 = (SerialShipType*) (message2);
		data2->_type = SerialType::SerialShipType;
		data2->_size = sizeof (SerialShipType)+(xmats * sizeof (SerialPartMat));
		data2->_item._itemtex = 0;
		data2->_item._itemId = 0;
		data2->_item._matcount = 0;

		data2->_item._itemtex = tempitem->getTexId();
		data2->_item._itemId = tempitem->getTypeID();
		data2->_item._matcount = tempitem->getCost().size();

		
		data2->_ShipTypeId = it->second->getId();
		data2->_texture = it->second->gettexture();
		data2->_ShipSize = it->second->getSize();
		data2->_mass = it->second->getMass();
		data2->_topspeed = it->second->getTopSpeed();
		data2->_cargo = it->second->getCargo();
		data2->_agility = it->second->getAgility();
		data2->_energy = it->second->getEnergy();
		data2->_scanrange = it->second->getScanRange();
		data2->_scanprange = it->second->getScanPRange();
		data2->_hull = it->second->getHull();
		data2->_armor = it->second->getArmor();
		data2->_deflector = it->second->getDeflector();
		for(int i = 0; i < 6; i++)
			data2->_shield[i] = it->second->getShield(i);
		data2->_shieldStr = it->second->getShieldStr();
		if(tempitem){
			uint32_t i = 0;
			for (map<uint32_t,bmaterial>::iterator it2 = tempitem->getCost().begin(); it2 != tempitem->getCost().end(); it2++) {
				SerialPartMat* data3 = (SerialPartMat*) (message2 + sizeof (SerialShipType)+(sizeof(SerialPartMat) * i));
				data3->_matid = it2->second._item->getTypeID();
				data3->_quantity = it2->second._quan;
				i++;
			}
		}

		send(this->getSocket(), message2, sizeof (SerialShipType)+(xmats * sizeof (SerialPartMat)), 0);

		for (map<uint32_t, SShipTypeSlotData*>::iterator itslot = it->second->getSlots().begin(); itslot != it->second->getSlots().end(); itslot++) {
			//**********************
			//send subsystemdata
			char message[sizeof (SerialShipTypeSlotNode)];
			memset(message, 0, sizeof (SerialShipTypeSlotNode));

			SerialShipTypeSlotNode* data = (SerialShipTypeSlotNode*) (message);
			data->_type = SerialType::SerialShipTypeSlotNode;
			data->_size = sizeof (SerialShipTypeSlotNode);
			data->_ShipTypeId = it->first;
			data->_SlotId = itslot->first;
			data->_gX = itslot->second->gX();
			data->_gY = itslot->second->gY();
			data->_uiX = itslot->second->uiX();
			data->_uiY = itslot->second->uiY();
			data->_slotType = itslot->second->slotType();
			send(this->getSocket(), message, sizeof (SerialShipTypeSlotNode), 0);
		}
	}

}


void Client::sendAstoroidTypes() {


	//TODO send shiptype

	for (map<uint32_t, SAstoroidType*>::iterator it = astoroidTypes.begin(); it != astoroidTypes.end(); it++) {

		char message2[sizeof (SerialTypeAstoroid)];
		memset(message2, 0, sizeof (SerialTypeAstoroid));

		SerialTypeAstoroid* data2 = (SerialTypeAstoroid*) (message2);
		data2->_type = SerialType::SerialTypeAstoroid;
		data2->_size = sizeof (SerialTypeAstoroid);
		data2->_astoroidsize = it->second->getSize();
		data2->_astoroidTypeid = it->first;
		data2->_texture = it->second->gettexture();
		data2->_itemTypeId = it->second->getItemType()->getTypeID();

		
		send(this->getSocket(), message2, sizeof (SerialTypeAstoroid), 0);

	}

}

void Client::sendGrids() {
	for (map<uint32_t, SGrid*>::iterator it = world->getGrids().begin(); it != world->getGrids().end(); it++) {

		char message[sizeof (SerialGrid)];
		memset(message, 0, sizeof (SerialGrid));

		SerialGrid* data = (SerialGrid*) (message);
		data->_type = SerialType::SerialGrid;
		data->_size = sizeof (SerialGrid);
		data->_Id = it->second->_id;
		data->_wight = it->second->getWight();
		data->_hight = it->second->getHight();

		send(this->getSocket(), message, sizeof (SerialGrid), 0);

	}

}
Client::~Client() {
}

