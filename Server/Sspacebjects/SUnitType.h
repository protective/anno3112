/* 
 * File:   SUnitType.h
 * Author: karsten
 *
 * Created on 11. februar 2014, 19:26
 */

#ifndef SUNITTYPE_H
#define	SUNITTYPE_H
#include "../SFunctions.h"
#include "subsystems/SShipTypeSlotData.h"
#include "subsystems/SLoadout.h"

class SFighterType;
class SShipType;
class SUnitType {
public:
	SUnitType(uint32_t id);
	
	map<uint32_t, SShipTypeSlotData*>& getSlots(){return _slots;}
	uint32_t getId(){return _id;}

	uint32_t getSize(){return this->_size;}
	uint32_t getMass(){return this->_mass;}
	int32_t getShield(uint16_t index){return _shield[index];}
	int32_t getShieldStr(){return _shieldStr;}
	int32_t getDeflector(){return _deflector;}
	int32_t getEnergy(){return _energy;}
	int32_t getRecharge(){return _recharge;}
	int32_t getRecoil(){return _recoil;}
	int32_t getRecoilRecharge(){return _recoilRecharge;}
	int32_t getArmor(){return _armor;}
	int32_t getHull(){return _hull;}
	uint32_t getScanRange(){return this->_scanRange;}
	uint32_t getScanPRange(){return this->_scanPRange;}
	int32_t getTopSpeed(){return this->_topSpeed;}
	uint32_t getAgility(){return this->_agility;}
	uint32_t getCargo(){return this->_cargo;}

	uint32_t gettexture(){return this->_texture;}
	TargetType::Enum getTargetType(){return this->_targetType;}

	void setSize(uint32_t size){this->_size = size;}
	void setMass(uint32_t mass){this->_mass = mass;}
	void setName(string name){this->_name = name;}
	void setHull(int32_t hull){this->_hull = hull;}
	void setarmor(int32_t armor){this->_armor = armor;}
	void setEnergy(int32_t energy){this->_energy = energy;}
	void setRecharge(int32_t recharge){this->_recharge = recharge;}
	void setRecoil(int32_t recoil){this->_recoil = recoil;}
	void setRecoilRecharge(int32_t recoil){this->_recoilRecharge = recoil;}
	void setShield(int32_t shield, uint32_t index){this->_shield[index] = shield;}
	void setShieldStr(int32_t shield){this->_shieldStr = shield;}
	void setdeflector(int32_t deflector){this->_deflector = deflector;}
	void settexture(uint32_t texture){this->_texture = texture;}
	void setTargetType(TargetType::Enum tt){this->_targetType = tt;}
	void setScanRange(uint32_t range){this->_scanRange = range;}
	void setScanPRange(uint32_t range){this->_scanPRange = range;}
	void setTopSpeed(uint32_t topSpeed){this->_topSpeed = topSpeed;}
	void setAgility(uint32_t agility){this->_agility = agility;}
	void setCargo(uint32_t cargo){this->_cargo = cargo;}
	
	virtual SShipType* isShipType(){return NULL;}
	virtual SFighterType* isFighterType(){return NULL;}
	virtual ~SUnitType();
protected:
	
	uint32_t _id;
	string _name;
	uint32_t _size;
	uint32_t _mass;
	int32_t _topSpeed;
	uint32_t _agility;
	uint32_t _cargo;
	int32_t _hull;
	int32_t _armor;
	int32_t _shield[6];
	int32_t _shieldStr;
	int32_t _deflector;
	int32_t _energy;
	int32_t _recharge;
	uint32_t _recoil;
	uint32_t _recoilRecharge;
	uint32_t _scanRange;
	uint32_t _scanPRange;
	uint32_t _texture;
	//uint32_t _itemTexId;
	TargetType::Enum _targetType;
	map<uint32_t, SShipTypeSlotData*> _slots;
};

#endif	/* SUNITTYPE_H */

