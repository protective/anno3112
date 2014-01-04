/* 
 * File:   Serialize.h
 * Author: karsten
 *
 * Created on 23. april 2011, 11:17
 */

#ifndef SERIALIZE_H
#define	SERIALIZE_H


namespace SerialType{
	/** Identifiers for each serializable type
	  */
	enum Enum{
		/** Dummy entry for serialization of incomplete types
		  */
		Invalid = 0,
                SerialTime= 1,
                SerialReqJoin = 5,
				SerialObjFullUpdate = 6,
				SerialShipTargetPosUpdate = 7,
				SerialPCShipTargetPosUpdate = 8,
				SerialShotFullUpdate = 9,
				SerialObjHpUpdate = 10,
				SerialShotHitTarget = 11,
				SerialShipSub = 12,
				SerialShipType = 13,
				SerialShipTypeSlotNode = 14,
				SerialShipFullUpdate = 15,
				SerialShipDestroy = 16,
				SerialTypeWeapon = 17,
				SerialSubscribeObj = 18,
				SerialUnSubscribeObj = 19,
				SerialTypeFac = 20,
				SerialReqInitBuild = 21,
				SerialCargoItem = 22,
				SerialReqTransfereCargo = 23,
				SerialReqFit = 24,
				SerialReqUnfit = 25,
				SerialReqChangeSubTG = 26,
				SerialTypeMaterial = 27,
				SerialTypeAstoroid = 28,
				SerialAstoroidPosUpdate = 29,
				SerialAstoroidFullUpdate = 30,
				SerialReqChangeSubStatus = 31,
				SerialTypeBonus = 32,
				SerialTypeBoost = 33,
				SerialOrders = 34,
				SerialReqChangeOrdres = 35,
				SerialShipDetailUpdate = 36,
				SerialReqChangePrio = 37,
				SerialObjPrio = 38,
				SerialGrid = 39,
				SerialPlayerTeam = 40,
				SerialReqSetOrdreUnit = 41,
				SerialReqSetOrdrePos = 42,
				SerialLoadout = 43,
				SerialReqFitLoadout = 44,
				SerialReqCreateLoadOut = 45,
				SerialTypeRef = 46,
				SerialAstoroidDestroy = 47

	};
}

struct SerialData{
	/** Type identifier of the serialized object
	  */
	SerialType::Enum _type;

	/** Size of the buffer used for serialization of this object
	  */
	uint32_t _size;
}__attribute__((__packed__));


struct SerialTime : public SerialData{ //id = 1
    uint32_t time;
    uint32_t local;
};

struct SerialReqJoin : public SerialData{ //id = 5
    uint32_t _unitId;
    uint32_t _pass;
};

struct SerialReqCreateLoadItems{
	uint32_t _itemid;
	uint32_t _slotid;
	uint32_t _xitem;
	uint32_t _targetgroup;
};

struct SerialReqCreateLoadOut : public SerialData{ //id = 45
	uint32_t _shiptype;
	uint32_t _xloaditems;
	char _name[20];
};

struct SerialLoadout : public SerialData{ //id = 43
    uint32_t _id;
	uint32_t _shiptype;
	char _name[20];
};


struct SerialPlayerTeam : public SerialData{ //id = 40
    uint32_t _playerId;
    uint8_t _team;
};

struct SerialObjFullUpdate : public SerialData{ //id = 6
	uint32_t _Id;
	uint32_t _objType;
	int32_t _Pos_x;
	int32_t _Pos_y;
	int32_t _Pos_d;
};
struct SerialGrid : public SerialData{ //id = 39
	uint32_t _Id;
	uint32_t _wight;
	uint32_t _hight;

};

struct SerialReqChangePrio : public SerialData{ //id = 37
	uint32_t _Id;
	uint8_t _prio;
};

struct SerialObjPrio : public SerialData{ //id = 38
	uint32_t _Id;
	uint8_t _prio;
};

struct SerialSubscribeObj : public SerialData{ //id = 18
	uint32_t _Id;
};

struct SerialUnSubscribeObj : public SerialData{ //id = 19
	uint32_t _Id;
};



struct SerialReqSetOrdreUnit : public SerialData{ //id = 41
	uint32_t _Id;
	uint32_t _oindex;
	uint32_t _ToId;
};


struct SerialReqSetOrdrePos : public SerialData{ //id = 42
	uint32_t _Id;
	uint32_t _oindex;
	int32_t _Pos_x;
	int32_t _Pos_y;
	int32_t _Pos_d;
};

struct SerialShipFullUpdate : public SerialData{ //id = 15
	uint32_t _Id;
	uint32_t _playerOwner;
	uint32_t _ShipType;
	int32_t _Pos_x;
	int32_t _Pos_y;
	int32_t _Pos_d;
};




struct SerialShipDetailUpdate : public SerialData{ //id = 36
	uint32_t _Id;
	uint32_t _OrdreId;
	uint32_t _energy;
};

struct SerialAstoroidFullUpdate : public SerialData{ //id = 15
	uint32_t _Id;
	uint32_t _astoroidType;
	int32_t _Pos_x;
	int32_t _Pos_y;
	int32_t _Pos_d;
};


struct SerialReqChangeSubTG : public SerialData{ //id = 26
	uint32_t _ShipId;
	uint32_t _SubId;
	uint32_t _TargetGroup;
};

struct SerialReqChangeOrdres : public SerialData{ //id = 35
	uint32_t _ShipId;
	uint32_t _OrdreId;
};

struct SerialReqChangeSubStatus : public SerialData{ //id = 31
	uint32_t _ShipId;
	uint32_t _SubId;
	uint32_t _StatusField;
};

struct SerialReqInitBuild : public SerialData{ //id = 21
	uint32_t _ShipId;
	uint32_t _SubId;
	uint32_t _BuildItem;
	uint32_t _Quantity;
	
};

struct SerialShipDestroy : public SerialData{ //id = 16
	uint32_t _Id;
	uint32_t _mode;
};

struct SerialAstoroidDestroy : public SerialData{
	uint32_t _Id;
	uint32_t _mode;
};


struct SerialReqFitLoadout : public SerialData{ //id = 44
	uint32_t _FromId;
	uint32_t _ToId;
	uint32_t _loadoutId;
};

struct SerialReqFit : public SerialData{ //id = 24
	uint32_t _FromId;
	uint32_t _ToId;
	uint32_t _subid;
	uint32_t _itemid;
	uint32_t _quantity;
};

struct SerialReqUnfit : public SerialData{ //id = 25
	uint32_t _FromId;
	uint32_t _subid;
	uint32_t _ToId;
	uint32_t _quantity;
};

struct SerialReqTransfereCargo : public SerialData{ //id = 23
	uint32_t _FromId;
	uint32_t _ToId;
	uint32_t _itemid;
	uint32_t _quantity;
};

struct SerialCargoItem : public SerialData{ //id = 22
	uint32_t _Id;
	uint32_t _itemid;
	uint32_t _quantity;
};

struct SerialPartItem{
	char _name[20];
	uint32_t _itemId;
	uint32_t _itemtex;
	uint32_t _mass;
	uint32_t _buildtime;
	uint32_t _matcount;
};
struct SerialPartMat{
	uint32_t _matid;
	uint32_t _quantity;
};


struct SerialTypeWeapon : public SerialData{ //id = 17
	SerialPartItem _item;
	uint32_t _fitClass;
	uint32_t _mount;
	uint32_t _mindmg;
	uint32_t _maxdmg;
	uint32_t _cooldown;
	uint32_t _prospeed;
	uint32_t _protex;
	uint32_t _maxamo;
	uint32_t _amocost;
	uint32_t _amotype;
	uint32_t _seq[10];
	uint32_t _maxseq;
};

struct BonusAttri {
	int32_t _armor;
	int32_t _hull;
	int32_t _deflector;
	int32_t _shStr;
	int32_t _energy;
	int32_t _scanrange;
	int32_t _scanprange;
	int32_t _speedthruster;
	int32_t _manuverethruster;
};

struct SerialTypeBonus : public SerialData{ //id = 32
	SerialPartItem _item;
	uint32_t _fitClass;
	uint32_t _mount;
	BonusAttri _bonus;
};

struct SerialTypeBoost : public SerialData{ //id = 33
	SerialPartItem _item;
	uint32_t _fitClass;
	uint32_t _mount;
	BonusAttri _bonus;
	uint32_t _boostType;
	uint32_t _boostValue;
	uint32_t _cooldown;
	uint32_t _maxamo;
	uint32_t _amocost;
	uint32_t _amotype;
};


struct SerialPartConstruct{
	uint32_t _buildTypeId;
};

struct SerialTypeFac : public SerialData{ //id = 20
	SerialPartItem _item;
	uint32_t _fitClass;
	uint32_t _mount;
	uint32_t _speedMod;
	uint32_t _xcanbuild;
};

struct SerialPartRefine{
	uint32_t _refineTypeId;
};

struct SerialTypeRef : public SerialData{ //id = 46
	SerialPartItem _item;
	uint32_t _fitClass;
	uint32_t _mount;
	uint32_t _speedMod;
	uint32_t _xcanRefine;
};


struct SerialTypeMaterial : public SerialData{ //id = 27
	SerialPartItem _item;
};

struct SerialTypeAstoroid : public SerialData{ //id = 28
	uint32_t _astoroidTypeid;
	uint32_t _astoroidsize;
	uint32_t _itemTypeId;
	uint32_t _texture;
};

struct SerialShipType : public SerialData{ //id = 13
	SerialPartItem _item;
	uint32_t _ShipTypeId;
	uint32_t _ShipSize;
	uint32_t _mass;
	uint32_t _texture;
	int32_t _topspeed;
	uint32_t _agility;
	uint32_t _cargo;
	uint32_t _shield[6];
	uint32_t _shieldStr;
	uint32_t _deflector;
	uint32_t _armor;
	uint32_t _hull;
	uint32_t _energy;
	uint32_t _scanrange;
	uint32_t _scanprange;
};


struct SerialShipTypeSlotNode : public SerialData{ //id = 14
	uint32_t _ShipTypeId;
	uint32_t _SlotId;
	int32_t _gX;
	int32_t _gY;
	uint32_t _uiX;
	uint32_t _uiY;
	uint32_t _slotType;
};

struct SerialShipSub : public SerialData{ //id = 12
	uint32_t _Id;
	uint32_t _subId;
	uint32_t _itemType;
	uint32_t _xitem;
	uint32_t _amo;
	uint32_t _shipEnergy;
	uint32_t _statusField;
	uint32_t _targetGroup;
};

struct SerialShipSubIndu{
	uint32_t _maxdurration;
	uint32_t _durration;
	uint32_t _hp;
};

struct SerialShipTargetPosUpdate : public SerialData{ //id = 7
	uint32_t _Id;
	int32_t _Pos_x;
	int32_t _Pos_y;
	int32_t _Pos_d;
	int32_t _TargetPos_x;
	int32_t _TargetPos_y;
	int32_t _TargetPos_d;
	uint32_t _MovementStatus;
	int32_t _Speed;
};



struct SerialAstoroidPosUpdate : public SerialData{ //id = 29
	uint32_t _Id;
	int32_t _Pos_x;
	int32_t _Pos_y;
	int32_t _Pos_d;
};

struct SerialPCShipTargetPosUpdate : public SerialData{ //id = 8
	uint32_t _Id;
	int32_t _TargetPos_x;
	int32_t _TargetPos_y;
	int32_t _TargetPos_d;
};

struct SerialShotFullUpdate : public SerialData{ //id = 9
	uint32_t _Id;
	uint32_t _targetId;
	uint32_t _texId;
	int32_t _speed;
	uint32_t _maxFlightTime;
	uint32_t _FlightTime;
	uint32_t _tracking;
	uint32_t _trackingTime;
	int32_t _Pos_x;
	int32_t _Pos_y;
	int32_t _Pos_d;
	int32_t _TargetPos_x;
	int32_t _TargetPos_y;
	int32_t _TargetPos_d;
};

struct SerialShotHitTarget : public SerialData{ //id = 9
	uint32_t _Id;
	uint32_t _targetId;
	uint32_t _textype;
	int32_t _hitPos_x;
	int32_t _hitPos_y;
	int32_t _hitPos_d;
};

struct SerialObjHpUpdate : public SerialData{ //id = 10
	uint32_t _Id;
	int32_t _shield[6];
	int32_t _deflector;
	int32_t _armor;
	int32_t _hull;

};

struct SerialOrders : public SerialData{ //id = 34
	uint32_t _PlayerId;
	uint32_t _OrdreId;
	char _name[20];
	uint32_t _unitsset;
	uint32_t _posesset;
};

#endif	/* SERIALIZE_H */

