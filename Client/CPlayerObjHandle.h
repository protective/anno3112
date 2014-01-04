/* 
 * File:   CPlayerObjHandle.h
 * Author: karsten
 *
 * Created on 22. maj 2011, 15:32
 */

#ifndef CPLAYEROBJHANDLE_H
#define	CPLAYEROBJHANDLE_H
#include "CFunctions.h"
#include "spaceobjects/cargo/CCargoBay.h"
#include "spaceobjects/COrdres.h"

class CPos;
class CObj;
class CMovable;
class CSubAble;
class CSubSystem;
class CCargoBay;
class CSlotNode;
class CSubSystemFac;
class COrdres;
class CPlayerObjHandle {
public:
	CPlayerObjHandle();

	void ReciveShipFullUpdate(uint32_t id, uint32_t playerOwner, CPos& pos, uint32_t stype);
	void ReciveShipDetailUpdate(uint32_t id, uint32_t ordreId, uint32_t energy);
	void ReciveObjPrioUpdate(uint32_t id, uint8_t prio);
	void ReciveAstoroidFullUpdate(uint32_t id, CPos& pos, uint32_t atype);
	void ReciveShipDestroy(uint32_t id, DestroyMode::Enum mode);
	void ReciveAstoroidDestroy(uint32_t id, DestroyMode::Enum mode);
	void ReciveObjPosUpdate(uint32_t id);
	void ReciveShipTargetPosUpdate(uint32_t id,CPos& pos, CPos& targetPos, int32_t speed, uint32_t moveST);
	void ReciveAstoroidPosUpdate(uint32_t id,CPos& pos);
	void ReciveShotFullUpdate(uint32_t id,CPos& pos, CPos& targetPos, uint32_t targetId, uint32_t texId, uint32_t speed, uint32_t flightTime, uint32_t maxFlightTime, uint32_t tracking, uint32_t trackingTime);
	void ReciveHpUpdate(uint32_t id, int32_t shield[6], int32_t deflector, int32_t armor, int32_t hull);
	void ReciveShotHit(uint32_t id, uint32_t TargetId, uint32_t textype, CPos& hitPos);
	void ReciveCargoUpdate(uint32_t id, uint32_t item, uint32_t quan);
	void ServerNotisTargetPosChange(CObj& obj);
	void ServerNotisSubscribe(CObj& obj);
	void ServerNotisUnSubscribe(CObj& obj);
	void ServerRequestBuild(CSubSystemFac* fac, CItemType* item, uint32_t quan);
	void ServerRequsetTransfere(CSubAble* from, CSubAble* to, CItemType* item, uint32_t quan);
	void ServerRequestCreateLoadout(CSubAble* fromThis, string name);
	void ServerRequsetFitLoadout(CSubAble* to, CCargoBay* from, CLoadout* loadout);
	void ServerRequsetFit(CSlotNode* slot, CCargoBay* from, CItemType* item, uint32_t quan);
	void ServerRequsetUnFit(CSlotNode* slot, CCargoBay* to, uint32_t quan);
	void ServerRequestChangeSubTG(CSubAble* obj, uint32_t subid, TargetGroup::Enum tg);
	void ServerRequestChangeOrdre(CObj* obj,COrdres* ord);
	void ServerRequestSetOrdreUnit(CObj* obj, CObj* toObj, uint32_t oindex);
	void ServerRequestSetOrdrePos(CObj* obj, CPos* toPos, uint32_t oindex);
	void ServerRequestChangePrio(CObj* obj,uint8_t prio);
	void ServerRequestChangeSubStatus(CSlotNode* slot,bool online, bool recharge);

	map<uint32_t, CSlotNode*>* GetShipSubsysytems(uint32_t id);
	map<uint32_t,CObj*>& getObjs();
private:
	map<uint32_t,CObj*> objs;
};

#endif	/* CPLAYEROBJHANDLE_H */

