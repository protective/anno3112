/* 
 * File:   CItemType.h
 * Author: karsten
 *
 * Created on 1. august 2011, 00:51
 */

#ifndef CITEMTYPE_H
#define	CITEMTYPE_H
#include "../CFunctions.h"
class CSubType;
struct bmaterial{
	CItemType* _item;
	uint32_t _quan;
};
class CItemType {
public:
	CItemType(uint32_t typeID,uint32_t picID);
	CSubType* getSubType();
	uint32_t getTypeID(){return this->_typeID;}
	uint32_t getPicID(){return this->_picID;}
	uint32_t getMass(){return this->_mass;}
	void setMass(uint32_t mass){this->_mass = mass;}
	uint32_t getBatch(){return this->_batchSize;}
	void setBatch(uint32_t batch){this->_batchSize = batch;}
	void setBuildTime(uint32_t value){this->_buildTime = value;}
	uint32_t getBuildTime(){return this->_buildTime;}

	CShipType* getShipType(){return this->_shiptype;}
	void  setShipType(CShipType* shipType){this->_shiptype = shipType;}

	void setSubType(CSubType* subtype);
	map<uint32_t,bmaterial>& getCost(){return this->_cost;}
	void setName(string value){this->_name = value;}

	string getName(){return this->_name;}

	virtual ~CItemType();
private:
	string _name;
	map<uint32_t,bmaterial> _cost;
	CSubType* _subtype;
	CShipType* _shiptype;
	uint32_t _typeID;
	uint32_t _picID;
	uint32_t _mass;
	uint32_t _batchSize;
	uint32_t _buildTime;
};

#endif	/* CITEMTYPE_H */

