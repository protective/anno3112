/* 
 * File:   CShipType.h
 * Author: karsten
 *
 * Created on 21. august 2011, 11:19
 */

#ifndef CSHIPTYPE_H
#define	CSHIPTYPE_H

#include "../CFunctions.h"
#include "subsystems/CShipTypeSlotData.h"

class CShipType {
public:
	CShipType(uint32_t id);
	uint32_t getId(){return this->_id;}
	map<uint32_t, CShipTypeSlotData*>& getSlots(){return _slots;}
	uint32_t getTexture(){return this->_texture;}
	uint32_t getSize(){return this->_size;}
	uint32_t getMass(){return this->_mass;}
	int32_t getTopSpeed(){return this->_topSpeed;}
	uint32_t getAgility(){return this->_agility;}

	uint32_t getCargo(){return _cargo;}

	int32_t getEnergy(){return _energy;}
	int32_t getShield(uint16_t index){return _shield[index];}
	int32_t getShieldStr(){return _shieldStr;}
	int32_t getDeflector(){return _deflector;}
	int32_t getArmor(){return _armor;}
	int32_t getHull(){return _hull;}
	uint32_t getScanRange(){return this->_scanRange;}
	uint32_t getScanPRange(){return this->_scanPRange;}

	void setTexture(uint32_t tex){this->_texture = tex;}
	void setMass(uint32_t mass){this->_mass = mass;}
	void setSize(uint32_t size){this->_size = size;}
	void setTopSpeed(uint32_t topSpeed){this->_topSpeed = topSpeed;}
	void setAgility(uint32_t agility){this->_agility = agility;}

	void setCargo(uint32_t cargo){this->_cargo = cargo;}

	void setEnergy(int32_t energy){this->_energy = energy;}
	void setHull(int32_t hull){this->_hull = hull;}
	void setarmor(int32_t armor){this->_armor = armor;}
	void setShield(int32_t shield, uint32_t index){this->_shield[index] = shield;}
	void setShieldStr(int32_t shield){this->_shieldStr = shield;}

	void setdeflector(int32_t deflector){this->_deflector = deflector;}
	void setScanRange(uint32_t range){this->_scanRange = range;}
	void setScanPRange(uint32_t range){this->_scanPRange = range;}


	//void setItemTexId(uint32_t tex){this->_itemTexId = tex;}
	//uint32_t getItemTexId(){return this->_itemTexId;}

	virtual ~CShipType();
private:
	uint32_t _id;
	map<uint32_t, CShipTypeSlotData*> _slots;
	uint32_t _texture;
	uint32_t _size;
	uint32_t _mass;
	int32_t _topSpeed;
	uint32_t _agility;
	int32_t _hull;
	uint32_t _cargo;
	int32_t _energy;
	int32_t _armor;
	int32_t _shield[6];
	int32_t _shieldStr;
	int32_t _deflector;
	uint32_t _scanRange;
	uint32_t _scanPRange;
};

#endif	/* CSHIPTYPE_H */

