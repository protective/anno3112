/* 
 * File:   SSubTypeBoost.h
 * Author: karsten
 *
 * Created on 24. december 2011, 12:07
 */

#ifndef SSUBTYPEBOOST_H
#define	SSUBTYPEBOOST_H

#include "SSubTypeBonus.h"


class SSubTypeBoost : public SSubTypeBonus{
public:
	SSubTypeBoost();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::boost;}

	int32_t getMaxCd(){return this->_maxCd;}
	uint32_t getamoCost(){return this->_amoCost;}
	uint32_t getMaxAmo(){return this->_maxAmo;}
	SItemType* getAmoCostType(){return this->_amoCostType;}
	uint32_t getAmoRechargeRate(){return this->_amoRechargeRate;}
	uint32_t getenegyCost(){return this->_enegyCost;}
	BonusTypes::Enum getBoostType(){return _boostType;}
	int32_t getBoostAmount(){return _boostAmount;}

	void setMaxCd(int32_t value){this->_maxCd = value;}
	void setamoCost(uint32_t value){this->_amoCost = value;}
	void setAmoCostType(SItemType* type){this->_amoCostType = type;}
	void setAmoRechargeRate(uint32_t value){this->_amoRechargeRate = value;}
	void setMaxAmo(uint32_t amo){this->_maxAmo = amo;}
	void setenegyCost(uint32_t value){this->_enegyCost = value;}

	void setBoostType(BonusTypes::Enum type){_boostType = type;}
	void setBoostAmount(int32_t value){_boostAmount = value;}
	virtual SSubTypeBoost* isBoost(){return this;}
	//virtual SSubTypeBonus* isBonus(){return this;}
	virtual ~SSubTypeBoost();
private:
		BonusTypes::Enum _boostType;
		int32_t _boostAmount;
		int32_t _maxCd;

		SItemType* _amoCostType;
		uint32_t _amoRechargeRate;
		uint32_t _maxAmo;
		uint32_t _amoCost;
		uint32_t _enegyCost;

};

#endif	/* SSUBTYPEBOOST_H */

