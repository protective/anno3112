/* 
 * File:   SGrid.h
 * Author: karsten
 *
 * Created on 22. maj 2011, 16:42
 */

#ifndef SGRID_H
#define	SGRID_H
#include "../SFunctions.h"
#include "../Commands/Processor.h"
//#include "../Sspacebjects/SObj.h"
//#include "../Sspacebjects/SShot.h"
//#include "../Sspacebjects/SShip.h"
//#include "../Sspacebjects/SAstoroidBelt.h"
//#include "../Sspacebjects/subsystems/SSubSystem.h"

class Client;
class SGrid : public Processable{
public:
	SGrid(uint32_t id);
	SGrid(uint32_t id, uint32_t spaceWight, uint32_t spaceHight);
	virtual uint32_t getId(){return _id;}
	virtual SGrid* getGrid(){return this;}
	void addObj(uint32_t obj);
	void removeObj(uint32_t obj);
	
	/*
	virtual void add(SObj* obj);
	virtual void addShot(SShot* shot);
	virtual void addUnit(SUnit* unit);
	virtual void addAsto(SAstoroid* asto);
	*/
	uint32_t _id;
	map<uint32_t,uint32_t>& getObjInGrid(){return objInGrid;}
	
	virtual void proces(uint32_t delta, Processor* processor );
	virtual void subscribeClient(uint32_t clientId, SubscriptionLevel::Enum);
	
	//void SendShipFull(Client* cli,SShip* ship);
	//void SendShipShipDestroyd(Client* cli,SShip* ship, DestroyMode::Enum mode);
	//void SendAstoroidDestroyd(Client* cli,SAstoroid* asto, DestroyMode::Enum mode);
	//void SendObjTargetPrio(Client* cli, SObj* obj);
	//void SendShipDetails(Client* cli,SShip* ship);
	//void SendAstoroidFull(Client* cli,SAstoroid* astoroid);
	virtual void sendFull(SubscriptionLevel::Enum level);
	virtual void sendFull(Client* cli);
	//void ReportHit(STargetable* target, SShot* shot, ParticalTex::Enum tex, int32_t x, int32_t y);
	//void ReportObjHpUdate(Client* cli, SObj* obj);
	//void BroadCastReportObjHpUdate(SObj* obj);
	//void ReportAstoroidDepleted(SAstoroid* asto );
	//void ReportShipDestroyd(SShip* ship);
	//void ReportCharge(SSubSystem* subs,bool ToAll);
	void SendObjInfoToClients();
	//void SendCargoUpdate(SSubAble* obj, SItemType* item, uint32_t quan);
	void Subscribe(Client* cli);
	void UnSubscribe(Client* cli);

	uint32_t getWight(){return this->_spaceWight;}
	uint32_t getHight(){return this->_spaceHight;}
	void setWight(uint32_t value){this->_spaceWight = value;}
	void setHight(uint32_t value){ this->_spaceHight = value;}
	virtual ~SGrid();
private:
	list<Client*> subscriber;
	int listlock;
	map<uint32_t,uint32_t> objInGrid;
	pthread_mutex_t lockgrid;
	pthread_mutex_t locksubscriber;

	map<uint32_t , SubscriptionLevel::Enum> _clientSubscriptions;
	uint32_t _spaceWight;
	uint32_t _spaceHight;
};

typedef map<uint32_t,SGrid*>::iterator SGridI;
typedef list<Client*>::iterator ClientI;
#endif	/* SGRID_H */

