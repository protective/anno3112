/* 
 * File:   CPlayerObjHandle.cpp
 * Author: karsten
 * 
 * Created on 22. maj 2011, 15:32
 */


#include "CPlayerObjHandle.h"
#include "spaceobjects/CObj.h"
#include "spaceobjects/COrdres.h"
#include "spaceobjects/CPos.h"
#include "spaceobjects/CShip.h"
#include "spaceobjects/CShot.h"
#include "Grafic/CPartical.h"
#include "spaceobjects/subsystems/CSubSystem.h"
#include "spaceobjects/subsystems/CSubSystemFac.h"
#include "spaceobjects/subsystems/CSlotNode.h"
#include "UI/CUIMainFrame.h"
#include "spaceobjects/CAstoroid.h"
#include "spaceobjects/subsystems/CLoadout.h"
CPlayerObjHandle::CPlayerObjHandle() {
}

map<uint32_t,CObj*>& CPlayerObjHandle::getObjs(){
	return this->objs;
}

map<uint32_t, CSlotNode*>* CPlayerObjHandle::GetShipSubsysytems(uint32_t id){
	CShip* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = (CShip*)temp->second;
	}else{
		cerr<<"WARNING GetShipSub ship not found"<<endl;
		return NULL;
	}
	if (handle){
		return &handle->getSlots();

	}

}

void CPlayerObjHandle::ServerNotisSubscribe(CObj& obj){
		char message[sizeof(SerialSubscribeObj)];
		memset(message,0,sizeof(SerialSubscribeObj));

		SerialSubscribeObj* data = (SerialSubscribeObj*)(message);
		data->_type = SerialType::SerialSubscribeObj;
		data->_size = sizeof(SerialSubscribeObj);
		data->_Id = obj.getId();
		send(connection.SocketFD,message,sizeof(SerialSubscribeObj),0);
	
}

void CPlayerObjHandle::ServerNotisUnSubscribe(CObj& obj){
	
		char message[sizeof(SerialUnSubscribeObj)];
		memset(message,0,sizeof(SerialUnSubscribeObj));

		SerialUnSubscribeObj* data = (SerialUnSubscribeObj*)(message);
		data->_type = SerialType::SerialUnSubscribeObj;
		data->_size = sizeof(SerialUnSubscribeObj);
		data->_Id = obj.getId();
		send(connection.SocketFD,message,sizeof(SerialUnSubscribeObj),0);
	

}
void CPlayerObjHandle::ReciveObjPrioUpdate(uint32_t id, uint8_t prio){
	CObj* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = temp->second;
		if(handle->isTargetable()){
			handle->isTargetable()->setPrio(prio);
		}
	}

}

void CPlayerObjHandle::ReciveShipDetailUpdate(uint32_t id, uint32_t ordreId, uint32_t energy){
	CObj* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = temp->second;
		if(handle->isShip() && globalOrders.find(ordreId) != globalOrders.end()){
			handle->isShip()->setOrdres(globalOrders[ordreId]);
			handle->isShip()->setEnergy(energy);
		}
	}
	mainFrame->shipDetail()->updateLateShip();
}

void CPlayerObjHandle::ReciveShipFullUpdate(uint32_t id, uint32_t playerOwner, CPos& pos,uint32_t stype){
	CObj* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = temp->second;
	}else{
		map<uint32_t, CShipType*>::iterator st = shipTypes.find(stype);
		if (st == shipTypes.end()){
			cerr<<"WARNING PlayerObjHandle::ReciveObjFullUpdate shiptype not found"<<endl;
			return;
		}

		handle = new CShip(id,playerOwner,pos,*st->second);
		handle->fadein(25);
		this->objs[id] = handle;
		mainFrame->add(*handle->isShip());
	}
	handle->ResivePosUpdate(pos);

	//playerSels = handle; //TODO fix
}


void CPlayerObjHandle::ReciveAstoroidFullUpdate(uint32_t id, CPos& pos, uint32_t atype){
	CObj* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = temp->second;
	}else{
		map<uint32_t, CAstoroidType*>::iterator st = astoroidTypes.find(atype);
		if (st == astoroidTypes.end()){
			cerr<<"WARNING PlayerObjHandle::ReciveAstoroidFullUpdate astoroidtype not found"<<endl;
			return;
		}

		handle = new CAstoroid(id,0,pos,*st->second);
		this->objs[id] = handle;
		mainFrame->add(*(CAstoroid*)handle);
	}
	handle->ResivePosUpdate(pos);

	//playerSels = handle; //TODO fix
}


void CPlayerObjHandle::ReciveShipDestroy(uint32_t id, DestroyMode::Enum mode){
	CObj* handle = NULL;
	
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = temp->second;
		if (playerSels == handle){
			playerSels = NULL;
			mainFrame->SetSelSlot(NULL,false);
			mainFrame->shipDetail()->updateShip();
		}
		playerMultiSels.remove(handle);
	
		if(mode == DestroyMode::Destroy){
			ParticalTex::Enum tex = ParticalTex::eksship1;
			particals.push_back(new CPartical(tex, handle->getPos()));
		}else if(mode == DestroyMode::Vanish){
			handle->isShip()->fadeout(25);
		}
		handle->isShip()->setToBeRemoved(true);
	}
}

void CPlayerObjHandle::ReciveAstoroidDestroy(uint32_t id, DestroyMode::Enum mode){
	CObj* handle = NULL;

	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = temp->second;
		if (playerSels == handle){
			playerSels = NULL;
			mainFrame->SetSelSlot(NULL,false);
			mainFrame->shipDetail()->updateShip();
		}
		playerMultiSels.remove(handle);
		if(handle->isAstoroid())
			handle->isAstoroid()->setToBeRemoved(true);
	}
}

void CPlayerObjHandle::ReciveObjPosUpdate(uint32_t id){

}

void CPlayerObjHandle::ReciveCargoUpdate(uint32_t id, uint32_t item, uint32_t quan){
	CSubAble* shandle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		shandle = temp->second->issubable();
	}else{
		cerr<<"WARNING CPlayerObjHandle::ReciveCargoUpdate not found"<<endl;
		return;
	}
	if(shandle && itemlist.find(item) != itemlist.end()){
		shandle->getCargoBay()->getContent()[itemlist[item]] = quan;
		shandle->getCargoBay()->updateCurCargo();
	}
}

void CPlayerObjHandle::ReciveShotHit(uint32_t id, uint32_t TargetId, uint32_t textype, CPos& hitPos){
	CShot* shandle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		shandle = temp->second->isShot();
	}else{
		cerr<<"WARNING: ReciveShotHit: shot not found"<<endl;
		return;
	}

	CTargetable* thandle = NULL;
	CobjI temp2 = this->objs.find(id);
	if (temp != this->objs.end()){
		thandle = (CTargetable*)temp2->second;
	}else{
		cerr<<"WARNING: ReciveShotHit: target not found"<<endl;
		
	}
	CPos temppos =shandle->getPos();
	//cerr<<"bx "<<temppos.x<<endl;
	//cerr<<"by "<<temppos.y<<endl;
	temppos.x += (hitPos.x);
	temppos.y += (hitPos.y);

	//cerr<<"ax "<<temppos.x<<endl;
	//cerr<<"ay "<<temppos.y<<endl;


	ParticalTex::Enum tex = (ParticalTex::Enum)textype;

	particals.push_back(new CPartical(tex, temppos));
	
	shandle->finishMe();

}

void CPlayerObjHandle::ReciveShipTargetPosUpdate(uint32_t id,CPos& pos, CPos& targetPos, int32_t speed, uint32_t moveST){
	CShip* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		if (temp->second->isShip())
			handle = temp->second->isShip();
	}else{
		cerr<<"WARNING TargetPosUpdate ship not found"<<endl;
	}
	if (handle){
		handle->ResivePosUpdate(pos);
		handle->getTargetPos().x = targetPos.x;
		handle->getTargetPos().y = targetPos.y;
		handle->getTargetPos().d = targetPos.d;
		handle->setMovementStatus(moveST);
		handle->setSpeed(speed);
	}
}



void CPlayerObjHandle::ReciveAstoroidPosUpdate(uint32_t id, CPos& pos){
	CAstoroid* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		if (temp->second->isAstoroid())
			handle = temp->second->isAstoroid();
	}else{
		cerr<<"WARNING Astoroid not found"<<endl;
	}
	if (handle){
		handle->ResivePosUpdate(pos);
	}
}

void CPlayerObjHandle::ReciveHpUpdate(uint32_t id, int32_t shield[6], int32_t deflector, int32_t armor, int32_t hull){
	CShip* handle = NULL;
	CobjI temp = this->objs.find(id);
	if (temp != this->objs.end()){
		handle = temp->second->isShip();
	}else{
		cerr<<"WARNING ReciveHp ship not found"<<endl;
	}
	if (handle){
		for(int i = 0; i < 6; i++)
			handle->setShield(shield[i],i);
		handle->setDeflector(deflector);
		handle->setArmor(armor);
		handle->setHull(hull);
	}
}
void CPlayerObjHandle::ReciveShotFullUpdate(uint32_t id,CPos& pos, CPos& targetPos, uint32_t targetId, uint32_t texId, uint32_t speed, uint32_t flightTime, uint32_t maxFlightTime, uint32_t tracking, uint32_t trackingTime){
	CObj* handle = NULL;
	CobjI temp = this->objs.find(id);

	CTargetable* targethandle = NULL;
	CobjI temptarget = this->objs.find(targetId);
	if (temptarget != this->objs.end()){
		targethandle = temptarget->second->isTargetable();
	}

	if (temp != this->objs.end()){
		handle = temp->second;
	}else{
		handle = new CShot(id,0,pos,targetPos,texId,speed);
		
		this->objs[id] = handle;
		mainFrame->add(*handle->isShot());
	}
	CShot* handle2 = handle->isShot();
	if (handle2){
		handle2->setTarget(targethandle);
		handle2->ResivePosUpdate(pos);
		handle2->setFlightTime(flightTime);
		handle2->setMaxFlightTime(maxFlightTime);
		handle2->setTracking(tracking);
		handle2->setTrackingTime(trackingTime);
	}
}

void CPlayerObjHandle::ServerNotisTargetPosChange(CObj& obj){

	char message[sizeof(SerialPCShipTargetPosUpdate)];
	memset(message,0,sizeof(SerialPCShipTargetPosUpdate));

	SerialPCShipTargetPosUpdate* data = (SerialPCShipTargetPosUpdate*)(message);
	data->_type = SerialType::SerialPCShipTargetPosUpdate;
	data->_size = sizeof(SerialPCShipTargetPosUpdate);
	data->_Id = obj.getId();
	data->_TargetPos_x = ((CShip&)obj).getTargetPos().x;
	data->_TargetPos_y = ((CShip&)obj).getTargetPos().y;
	data->_TargetPos_d = ((CShip&)obj).getTargetPos().d;
	
	send(connection.SocketFD,message,sizeof(SerialPCShipTargetPosUpdate),0);


}


void CPlayerObjHandle::ServerRequestChangeSubStatus(CSlotNode* slot,bool online, bool recharge){

	char message[sizeof(SerialReqChangeSubStatus)];
	memset(message,0,sizeof(SerialReqChangeSubStatus));

	SerialReqChangeSubStatus* data = (SerialReqChangeSubStatus*)(message);
	data->_type = SerialType::SerialReqChangeSubStatus;
	data->_size = sizeof(SerialReqChangeSubStatus);
	data->_ShipId = slot->getOwner()->obj()->getId();
	data->_SubId = slot->getId();
	data->_StatusField = 0;
	if(online)
		data->_StatusField |= BitF_online;
	if(recharge)
		data->_StatusField |= BitF_rechargin;
	cerr<<"send req"<<endl;
	send(connection.SocketFD,message,sizeof(SerialReqChangeSubStatus),0);


}

void CPlayerObjHandle::ServerRequestChangeOrdre(CObj* obj,COrdres* ord){
	if(obj && ord){
		if(obj->isShip()){
			char message[sizeof(SerialReqChangeOrdres)];
			memset(message,0,sizeof(SerialReqChangeOrdres));

			SerialReqChangeOrdres* data = (SerialReqChangeOrdres*)(message);
			data->_type = SerialType::SerialReqChangeOrdres;
			data->_size = sizeof(SerialReqChangeOrdres);
			data->_ShipId = obj->getId();
			data->_OrdreId = ord->getId();

			send(connection.SocketFD,message,sizeof(SerialReqChangeOrdres),0);
		}
	}
}

void CPlayerObjHandle::ServerRequestChangePrio(CObj* obj, uint8_t prio){
	if(obj){
		if(obj->isTargetable()){
			char message[sizeof(SerialReqChangePrio)];
			memset(message,0,sizeof(SerialReqChangePrio));

			SerialReqChangePrio* data = (SerialReqChangePrio*)(message);
			data->_type = SerialType::SerialReqChangePrio;
			data->_size = sizeof(SerialReqChangePrio);
			data->_Id = obj->getId();
			data->_prio = prio;

			send(connection.SocketFD,message,sizeof(SerialReqChangePrio),0);
		}
	}
}

void CPlayerObjHandle::ServerRequestChangeSubTG(CSubAble* obj, uint32_t subid,TargetGroup::Enum tg){
	char message[sizeof(SerialReqChangeSubTG)];
	memset(message,0,sizeof(SerialReqChangeSubTG));

	SerialReqChangeSubTG* data = (SerialReqChangeSubTG*)(message);
	data->_type = SerialType::SerialReqChangeSubTG;
	data->_size = sizeof(SerialReqChangeSubTG);
	data->_ShipId =	obj->obj()->getId();
	data->_SubId = subid;
	data->_TargetGroup = tg;

	send(connection.SocketFD,message,sizeof(SerialReqChangeSubTG),0);

}


void CPlayerObjHandle::ServerRequestBuild(CSubSystemFac* fac, CItemType* item, uint32_t quan){
	char message[sizeof(SerialReqInitBuild)];
	memset(message,0,sizeof(SerialReqInitBuild));

	SerialReqInitBuild* data = (SerialReqInitBuild*)(message);
	data->_type = SerialType::SerialReqInitBuild;
	data->_size = sizeof(SerialReqInitBuild);
	data->_ShipId = fac->getOwner().getId();
	data->_SubId = fac->getId();
	data->_BuildItem = item->getTypeID();
	data->_Quantity = quan;

	send(connection.SocketFD,message,sizeof(SerialReqInitBuild),0);


}

void CPlayerObjHandle::ServerRequsetTransfere(CSubAble* from, CSubAble* to, CItemType* item, uint32_t quan){
	char message[sizeof(SerialReqTransfereCargo)];
	memset(message,0,sizeof(SerialReqTransfereCargo));

	SerialReqTransfereCargo* data = (SerialReqTransfereCargo*)(message);
	data->_type = SerialType::SerialReqTransfereCargo;
	data->_size = sizeof(SerialReqTransfereCargo);
	data->_FromId = from->obj()->getId();
	data->_ToId = to->obj()->getId();
	data->_itemid = item->getTypeID();
	data->_quantity = quan;

	send(connection.SocketFD,message,sizeof(SerialReqTransfereCargo),0);

}


void CPlayerObjHandle::ServerRequestCreateLoadout(CSubAble* fromThis, string name){

	if(!fromThis->obj()->isShip())
		return;
	uint32_t xitem = fromThis->getSlots().size();
	string fname = name;


	char message[sizeof(SerialReqCreateLoadOut) + (sizeof(SerialReqCreateLoadItems) * xitem)];
	memset(message,0,sizeof(SerialReqCreateLoadOut) + (sizeof(SerialReqCreateLoadItems) * xitem));

	SerialReqCreateLoadOut* data = (SerialReqCreateLoadOut*)(message);
	data->_type = SerialType::SerialReqCreateLoadOut;
	data->_size = sizeof(SerialReqCreateLoadOut) + (sizeof(SerialReqCreateLoadItems) * xitem);
	if (fname.size() <= 20){
		memcpy(data->_name, fname.c_str(), fname.size());
	}else
		cerr << "WARNING CPlayerObjHandle:ServerRequestCreateLoadout serial  Name to long" << endl;
	data->_xloaditems = xitem;
	data->_shiptype = fromThis->obj()->isShip()->getShipType()->getId();

	int i = 0;
	for(map<uint32_t, CSlotNode*>::iterator it = fromThis->getSlots().begin(); it != fromThis->getSlots().end();it++){
		SerialReqCreateLoadItems* data2 = (SerialReqCreateLoadItems*)(message + sizeof(SerialReqCreateLoadOut) + (sizeof(SerialReqCreateLoadItems) * i));
		
		if(it->second->getSS()){
			data2->_slotid = it->first;
			data2->_itemid = it->second->getSS()->getItemType()->getTypeID();
			data2->_xitem = it->second->getSS()->Xitem();
			data2->_targetgroup = (uint32_t)it->second->getSS()->getTargetGroup();

			i++;
		}
	}

	send(connection.SocketFD,message,sizeof(SerialReqCreateLoadOut) + (sizeof(SerialReqCreateLoadItems) * xitem),0);

}


void CPlayerObjHandle::ServerRequsetFitLoadout(CSubAble* to, CCargoBay* from, CLoadout* loadout){
	char message[sizeof(SerialReqFitLoadout)];
	memset(message,0,sizeof(SerialReqFitLoadout));

	SerialReqFitLoadout* data = (SerialReqFitLoadout*)(message);
	data->_type = SerialType::SerialReqFitLoadout;
	data->_size = sizeof(SerialReqFitLoadout);
	data->_FromId = from->getOwner()->obj()->getId();
	data->_ToId = to->obj()->getId();
	data->_loadoutId = loadout->getId();

	send(connection.SocketFD,message,sizeof(SerialReqFitLoadout),0);

}



void CPlayerObjHandle::ServerRequsetFit(CSlotNode* slot, CCargoBay* from, CItemType* item, uint32_t quan){
char message[sizeof(SerialReqFit)];
	memset(message,0,sizeof(SerialReqFit));

	SerialReqFit* data = (SerialReqFit*)(message);
	data->_type = SerialType::SerialReqFit;
	data->_size = sizeof(SerialReqFit);
	data->_FromId = from->getOwner()->obj()->getId();
	data->_ToId = slot->getOwner()->obj()->getId();
	data->_subid = slot->getId();
	data->_itemid = item->getTypeID();
	data->_quantity = quan;

	send(connection.SocketFD,message,sizeof(SerialReqFit),0);

}

void CPlayerObjHandle::ServerRequsetUnFit(CSlotNode* slot, CCargoBay* to, uint32_t quan){
char message[sizeof(SerialReqUnfit)];
	memset(message,0,sizeof(SerialReqUnfit));

	SerialReqUnfit* data = (SerialReqUnfit*)(message);
	data->_type = SerialType::SerialReqUnfit;
	data->_size = sizeof(SerialReqUnfit);
	data->_FromId = slot->getOwner()->obj()->getId();
	data->_ToId = to->getOwner()->obj()->getId();
	data->_subid = slot->getId();
	data->_quantity = quan;

	send(connection.SocketFD,message,sizeof(SerialReqUnfit),0);
}

void CPlayerObjHandle::ServerRequestSetOrdreUnit(CObj* obj, CObj* toObj, uint32_t oindex){
char message[sizeof(SerialReqSetOrdreUnit)];
	memset(message,0,sizeof(SerialReqSetOrdreUnit));

	SerialReqSetOrdreUnit* data = (SerialReqSetOrdreUnit*)(message);
	data->_type = SerialType::SerialReqSetOrdreUnit;
	data->_size = sizeof(SerialReqSetOrdreUnit);
	data->_Id = obj->getId();
	data->_ToId = toObj->getId();
	data->_oindex = oindex;

	send(connection.SocketFD,message,sizeof(SerialReqSetOrdreUnit),0);

}



void CPlayerObjHandle::ServerRequestSetOrdrePos(CObj* obj, CPos* toPos, uint32_t oindex){
char message[sizeof(SerialReqSetOrdrePos)];
	memset(message,0,sizeof(SerialReqSetOrdrePos));

	SerialReqSetOrdrePos* data = (SerialReqSetOrdrePos*)(message);
	data->_type = SerialType::SerialReqSetOrdrePos;
	data->_size = sizeof(SerialReqSetOrdrePos);
	data->_Id = obj->getId();
	data->_Pos_x = toPos->x;
	data->_Pos_y = toPos->y;
	data->_Pos_d = toPos->d;
	data->_oindex = oindex;

	send(connection.SocketFD,message,sizeof(SerialReqSetOrdrePos),0);

}