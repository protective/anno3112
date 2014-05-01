/* 
 * File:   main.cpp
 * Author: karsten
 *
 * Created on 23. april 2011, 09:32
 */

//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <cstdlib>

#include "Sspacebjects/subsystems/SSubSystemFac.h"
#include <math.h>
#include <unistd.h>
#include "SFunctions.h"
#include "World/SWorld.h"
#include "Sspacebjects/SShip.h"
#include "Sspacebjects/subsystems/SSubTypeWep.h"
#include "Sspacebjects/subsystems/SSubSystemW.h"
#include "Client.h"
#include "Sspacebjects/SShipType.h"
#include "SDatabase.h"
#include "Sspacebjects/subsystems/SSingleFac.h"
#include "Sspacebjects/SAstoroid.h"
#include "Sspacebjects/SOrdres.h"
#include "Sspacebjects/Ordres/SOrdreActionMoveTo.h"
#include "Sspacebjects/Ordres/SOrdreCondition.h"
#include "Sspacebjects/Ordres/SOrdreConditionUnitEqTo.h"
#include "Sspacebjects/Ordres/SOrdreConditionStatOp.h"
#include "Sspacebjects/subsystems/SLoadout.h"
#include "Sspacebjects/SAstoroidBelt.h"
#include "Sspacebjects/Ordres/SOrdreActionTrasfereCargo.h"
#include "Commands/Processor.h"

using namespace std;


	pthread_cond_t  procesConBegin = PTHREAD_COND_INITIALIZER;
	pthread_cond_t  procesConallReady = PTHREAD_COND_INITIALIZER;
	pthread_t procesThreads[NRTHREADS];
	list<Processor*> processors;
	int threadsReady;
//void* procesworldThread(uint32_t id);

int main(int argc, char** argv) {
	for(int i = 0 ; i< 360; i++){
		double vector = (i*PI)/180;
		MySin[i] = sin(vector);
		MyCos[i] = cos(vector);
	}

	teamlist[1] = 1;
	teamlist[2] = 2;
	teamlist[3] = 3;
	teamlist[4] = 1;
	allteams.push_back(1);
	allteams.push_back(2);
	allteams.push_back(3);
	printbufferbool = true;
	
	for(int i = 0; i < NRTHREADS;i++)
	{
		cerr<<"create processor"<<endl;
		Processor* temp = new Processor();
		cerr<<"p "<<temp<<endl;
		processors.push_back(temp);
	}	
	world = new SWorld(processors.front());
	
	SDL_Init(SDL_INIT_TIMER);

	pthread_t listenThread;
	pthread_create(&listenThread, NULL, (void*(*)(void*))thread_Listen, NULL);
	srand((unsigned)time(0));
        cerr<<"hello world"<<endl;
	//LOAD GAME DATA

	SDatabase data;
	itemlistFileNames["BC1"] = 1;
	itemlistFileNames["RailGun1"] = 2;
	itemlistFileNames["PlasmaGun1"] = 3;
	itemlistFileNames["FacShip1"] = 4;
	itemlistFileNames["Minglaz1"] = 5;
	itemlistFileNames["AC"] = 6;
	itemlistFileNames["VeldSpar"] = 7;
	itemlistFileNames["VeldSparRoid"] = 8;
	itemlistFileNames["Laser1"] = 9;
	itemlistFileNames["GatlingLaser1"] = 10;
	itemlistFileNames["IonGun1"] = 11;
	itemlistFileNames["FusionGun1"] = 12;
	itemlistFileNames["Missile1"] = 13;
	itemlistFileNames["Armor1"] = 14;
	itemlistFileNames["ArmorRep1"] = 15;
	itemlistFileNames["HAC"] = 16;
	itemlistFileNames["Reactor1"] = 17;
	itemlistFileNames["Scanner1"] = 18;
	itemlistFileNames["Station1"] = 19;
	itemlistFileNames["Laser2"] = 20;
	itemlistFileNames["Laser3"] = 21;
	itemlistFileNames["DeflectorBoost1"] = 22;
	itemlistFileNames["Refinery1"] = 23;
	itemlistFileNames["Tritanium"] = 24;
	itemlistFileNames["Engine1"] = 25;
	itemlistFileNames["Freighter1"] = 26;
	itemlistFileNames["Andorite"] = 27;
	itemlistFileNames["Cerussite"] = 28;
	itemlistFileNames["Denite"] = 29;
	itemlistFileNames["Hedenbergite"] = 30;
	itemlistFileNames["Morganite"] = 31;
	itemlistFileNames["Nephrite"] = 32;
	itemlistFileNames["Neptunite"] = 33;
	itemlistFileNames["Pyrite"] = 34;
	itemlistFileNames["NeptuniteRoid"] = 35;
	itemlistFileNames["CerussiteRoid"] = 36;
	itemlistFileNames["NephriteRoid"] = 37;
	itemlistFileNames["HedenbergiteRoid"] = 38;
	itemlistFileNames["Minglaz2"] = 39;
	itemlistFileNames["Torpedo1"] = 40;
	itemlistFileNames["ShieldBoost1"] = 41;
	itemlistFileNames["LightCarrier"] = 42;
	itemlistFileNames["BS1"] = 43;
	itemlistFileNames["HeatSink1"] = 44;
	itemlistFileNames["Trackingcomputer1"] = 45;
	itemlistFileNames["DD"] = 46;
	itemlistFileNames["FacModule1"] = 47;
	itemlistFileNames["FacWep1"] = 48;
	itemlistFileNames["Fighter1"] = 49;
	data.LoadAllItems();
	cerr<<"done load data"<<endl;

	//WORLD
	//world->addGrid(new SGrid(1,300000,300000));

	SOrdres* tempo = new SOrdres("normal",0);

	tempo->getPrimary().push_back(TargetType::All);

	tempo->getLight().push_back(TargetType::Frigat);
	tempo->getLight().push_back(TargetType::LightSupport);
	tempo->getLight().push_back(TargetType::HeavySupport);
	tempo->getLight().push_back(TargetType::Freighter);
	tempo->getLight().push_back(TargetType::MiningShip);
	tempo->getLight().push_back(TargetType::All);

	tempo->getMedium().push_back(TargetType::HeavySupport);
	tempo->getMedium().push_back(TargetType::Capital);
	tempo->getMedium().push_back(TargetType::SuperCapital);
	tempo->getMedium().push_back(TargetType::All);

	tempo->getHeavy().push_back(TargetType::SuperCapital);
	tempo->getHeavy().push_back(TargetType::Capital);
	tempo->getHeavy().push_back(TargetType::HeavySupport);
	tempo->getHeavy().push_back(TargetType::All);
	tempo->setPrimeOrdre(OrdresTactice::Front);
	tempo->setAutoMoveRange(30000);

	globalOrders[1][tempo->getId()] = tempo;
	globalOrders[2][tempo->getId()] = tempo;
	globalOrders[3][tempo->getId()] = tempo;
	globalOrders[4][tempo->getId()] = tempo;

	tempo = new SOrdres("Evasive",1);

	tempo->getPrimary().push_back(TargetType::All);
	tempo->getLight().push_back(TargetType::Frigat);
	tempo->getLight().push_back(TargetType::LightSupport);
	tempo->getLight().push_back(TargetType::HeavySupport);
	tempo->getLight().push_back(TargetType::Freighter);
	tempo->getLight().push_back(TargetType::MiningShip);
	tempo->getLight().push_back(TargetType::All);

	tempo->getMedium().push_back(TargetType::HeavySupport);
	tempo->getMedium().push_back(TargetType::Capital);
	tempo->getMedium().push_back(TargetType::SuperCapital);
	tempo->getMedium().push_back(TargetType::All);

	tempo->getHeavy().push_back(TargetType::SuperCapital);
	tempo->getHeavy().push_back(TargetType::Capital);
	tempo->getHeavy().push_back(TargetType::HeavySupport);
	tempo->getHeavy().push_back(TargetType::All);
	tempo->setPrimeOrdre(OrdresTactice::Evasive);
	tempo->setAutoMoveRange(30000);


	globalOrders[1][tempo->getId()] = tempo;
	globalOrders[2][tempo->getId()] = tempo;
	globalOrders[3][tempo->getId()] = tempo;
	globalOrders[4][tempo->getId()] = tempo;

	tempo = new SOrdres("Mining",2);

	tempo->getPrimary().push_back(TargetType::Astoroid);
	tempo->getPrimary().push_back(TargetType::All);

	tempo->getSpecial().push_back(TargetType::Astoroid);

	tempo->getLight().push_back(TargetType::Frigat);
	tempo->getLight().push_back(TargetType::LightSupport);
	tempo->getLight().push_back(TargetType::HeavySupport);
	tempo->getLight().push_back(TargetType::Capital);
	tempo->getLight().push_back(TargetType::All);

	tempo->getMedium().push_back(TargetType::HeavySupport);
	tempo->getMedium().push_back(TargetType::Capital);
	tempo->getMedium().push_back(TargetType::All);

	tempo->getHeavy().push_back(TargetType::Capital);
	tempo->getHeavy().push_back(TargetType::All);

	tempo->setPrimeOrdre(OrdresTactice::Front);

	tempo->getunitSet()[0] = true;
	tempo->getPosSet()[0] = true;
	SOrdreRule* sor = new SOrdreRule();
	sor->addEvent(OrdreEvent::UnitEnterRangeUnit,20000);

	sor->addCondition(new SOrdreConditionUnitEqTo(OrdresConditionUnits::OindexUnit, 0) );

	sor->addAction(new SOrdreActionTrasfereCargo(0));
	sor->addAction(new SOrdreActionMoveTo(false,0));
	tempo->addRule(sor);

	sor = new SOrdreRule();
	sor->addEvent(OrdreEvent::CargoChange);

	sor->addCondition(new SOrdreConditionStatOp(OrdreConditionsStat::CargoPGreaterThen, 90));

	sor->addAction(new SOrdreActionMoveTo(true,0));
	tempo->addRule(sor);

	globalOrders[1][tempo->getId()] = tempo;
	globalOrders[2][tempo->getId()] = tempo;
	globalOrders[3][tempo->getId()] = tempo;
	globalOrders[4][tempo->getId()] = tempo;

	tempo = new SOrdres("Frontmin",3);

	tempo->getPrimary().push_back(TargetType::All);
	tempo->getLight().push_back(TargetType::Frigat);
	tempo->getLight().push_back(TargetType::LightSupport);
	tempo->getLight().push_back(TargetType::HeavySupport);
	tempo->getLight().push_back(TargetType::Freighter);
	tempo->getLight().push_back(TargetType::MiningShip);
	tempo->getLight().push_back(TargetType::All);

	tempo->getMedium().push_back(TargetType::HeavySupport);
	tempo->getMedium().push_back(TargetType::Capital);
	tempo->getMedium().push_back(TargetType::SuperCapital);
	tempo->getMedium().push_back(TargetType::All);

	tempo->getHeavy().push_back(TargetType::SuperCapital);
	tempo->getHeavy().push_back(TargetType::Capital);
	tempo->getHeavy().push_back(TargetType::HeavySupport);
	tempo->getHeavy().push_back(TargetType::All);
	tempo->setPrimeOrdre(OrdresTactice::FrontMinRange);
	tempo->setAutoMoveRange(20000);


	globalOrders[1][tempo->getId()] = tempo;
	globalOrders[2][tempo->getId()] = tempo;
	globalOrders[3][tempo->getId()] = tempo;
	globalOrders[4][tempo->getId()] = tempo;

	
	tempo = new SOrdres("Frontmax",4);

	tempo->getPrimary().push_back(TargetType::All);
	tempo->getLight().push_back(TargetType::Frigat);
	tempo->getLight().push_back(TargetType::LightSupport);
	tempo->getLight().push_back(TargetType::HeavySupport);
	tempo->getLight().push_back(TargetType::Freighter);
	tempo->getLight().push_back(TargetType::MiningShip);
	tempo->getLight().push_back(TargetType::All);

	tempo->getMedium().push_back(TargetType::HeavySupport);
	tempo->getMedium().push_back(TargetType::Capital);
	tempo->getMedium().push_back(TargetType::SuperCapital);
	tempo->getMedium().push_back(TargetType::All);

	tempo->getHeavy().push_back(TargetType::SuperCapital);
	tempo->getHeavy().push_back(TargetType::Capital);
	tempo->getHeavy().push_back(TargetType::HeavySupport);
	tempo->getHeavy().push_back(TargetType::All);
	tempo->setPrimeOrdre(OrdresTactice::FrontMaxRange);
	tempo->setAutoMoveRange(160000);


	globalOrders[1][tempo->getId()] = tempo;
	globalOrders[2][tempo->getId()] = tempo;
	globalOrders[3][tempo->getId()] = tempo;
	globalOrders[4][tempo->getId()] = tempo;	
	
	data.LoadGame();
	cerr<<"done load game"<<endl;

	SPos* temppos =  NULL;

	cerr<<"done init"<<endl;
	//INIT GAME

	//tempU->ActivateAI();
	list<Processor*>::iterator it = processors.begin();
	for (int i = 0 ; i< NRTHREADS; i++){
		Processor* temp = *it++;
		pthread_create(&procesThreads[i], NULL, &Processor::workThreadFunction, temp);
	}
	networkControl = new NetworkControler();

	//GAME LOOP************************
	uint32_t timer;
	uint32_t fpstimer = 0;
	uint32_t fpscounter= 0;
	uint32_t fpswait = 1000/FRAMERATE; // 25 fps men korigere lidt for skeduleren
	while(true){

		timer = SDL_GetTicks();
		networkControl->readBuffers();
		//************
		if ( SDL_GetTicks() > fpstimer +10000){
			fpstimer = SDL_GetTicks();
			cerr<<"fps "<<fpscounter/10<<endl;
			fpscounter = 0;
		}
		world->proces(0);
		while (SDL_GetTicks() < timer+fpswait)
			usleep(100);
		//*************


			threadsReady = 0;
			//cerr<<"done"<<endl;


		fpscounter +=1;


	}

	cerr<<"end do join join"<<endl;
	//END GAME LOOP********************
	pthread_join(listenThread, NULL);
	cerr<<"SERVER EXIT"<<endl;
	return 0;
}
