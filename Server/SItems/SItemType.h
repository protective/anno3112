/* 
 * File:   SItemType.h
 * Author: karsten
 *
 * Created on 30. juni 2011, 17:18
 */

#ifndef SITEMTYPE_H
#define	SITEMTYPE_H
#include "../SFunctions.h"
struct bmaterial{
	SItemType* _item;
	uint32_t _quan;
};
class SSubType;
class SItemType {
public:
	SItemType(uint32_t typeID);
	SSubType* getSubType();
	uint32_t getTypeID(){return this->_typeID;}
	void setSubType(SSubType* subtype);
	SShipType* getShipType(){return this->_shiptype;}
	void  setShipType(SShipType* shipType){this->_shiptype = shipType;}

	void setName(string value){this->_name = value;}
	void setTexId(uint32_t tex){this->_texid = tex;}
	void setBuildTime(uint32_t value){this->_buildTime = value;}
	uint32_t getBuildTime(){return this->_buildTime;}
	uint32_t getMass(){return this->_mass;}
	void setMass(uint32_t mass){this->_mass = mass;}
	uint32_t getBatch(){return this->_batchSize;}
	void setBatch(uint32_t batch){this->_batchSize = batch;}
	uint32_t getRefineBatch(){return this->_refineBatch;}
	void setRefineBatch(uint32_t batch){this->_refineBatch = batch;}
	uint32_t getTexId(){return this->_texid;}


	string getName(){return this->_name;}
	map<uint32_t, bmaterial>& getCost(){return this->_cost;}
	map<uint32_t, bmaterial>& getRefineTo(){return this->_refineto;}
	virtual ~SItemType();
private:
	string _name;
	SSubType* _subtype;
	SShipType* _shiptype;
	map<uint32_t, bmaterial> _cost;
	map<uint32_t, bmaterial> _refineto;
	uint32_t _refineBatch;
	uint32_t _texid;
	
	uint32_t _typeID;
	uint32_t _mass;
	uint32_t _batchSize;
	uint32_t _buildTime;
};

#endif	/* SITEMTYPE_H */

