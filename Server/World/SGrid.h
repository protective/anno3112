/* 
 * File:   SGrid.h
 * Author: karsten
 *
 * Created on 22. maj 2011, 16:42
 */

#ifndef SGRID_H
#define	SGRID_H
#include "../SFunctions.h"
#include "../Sspacebjects/SObj.h"
#include "../Sspacebjects/SShot.h"
#include "../Sspacebjects/subsystems/SSubSystem.h"
class Client;
class SGrid {
public:
	SGrid(uint32_t id);
	SGrid(uint32_t id, uint32_t spaceWight, uint32_t spaceHight);
	void addObj(SObj* obj);
	void removeObj(SObj* obj);
	void addShot(SShot* shot);
	void addShip(SShip* ship);
	void addAstoroid(SAstoroid* asto);
	uint32_t _id;
	map<uint32_t,SObj*>& getObjInGrid(){return objInGrid;}
	void Proces(uint32_t thead_id);
	void SendShipFull(Client* cli,SShip* ship);
	void SendShipShipDestroyd(Client* cli,SShip* ship, DestroyMode::Enum mode);
	void SendAstoroidDestroyd(Client* cli,SAstoroid* asto, DestroyMode::Enum mode);
	void SendObjTargetPrio(Client* cli, SObj* obj);
	void SendShipDetails(Client* cli,SShip* ship);
	void SendShipPosUpdate(SShip* ship);
	void SendShipSubsystem(Client* cli, SSubSystem* subs);
	void SendAstoroidFull(Client* cli,SAstoroid* astoroid);
	void ReportHit(STargetable* target, SShot* shot, ParticalTex::Enum tex, int32_t x, int32_t y);
	void ReportObjHpUdate(Client* cli, SObj* obj);
	void BroadCastReportObjHpUdate(SObj* obj);
	void ReportAstoroidDepleted(SAstoroid* asto );
	void ReportShipDestroyd(SShip* ship);
	void ReportCharge(SSubSystem* subs,bool ToAll);
	void SendObjInfoToClients();
	void SendCargoUpdate(SSubAble* obj, SItemType* item, uint32_t quan);
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
	map<uint32_t,SObj*> objInGrid;
	map<uint32_t,SObj*> objToAdd;
	pthread_mutex_t lockgrid;
	pthread_mutex_t locksubscriber;

	uint32_t _spaceWight;
	uint32_t _spaceHight;
};

typedef map<uint32_t,SGrid*>::iterator SGridI;
typedef list<Client*>::iterator ClientI;
#endif	/* SGRID_H */

