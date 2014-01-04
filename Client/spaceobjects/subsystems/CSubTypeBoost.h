/* 
 * File:   CSubTypeBoost.h
 * Author: karsten
 *
 * Created on 25. december 2011, 18:46
 */

#ifndef CSUBTYPEBOOST_H
#define	CSUBTYPEBOOST_H


#include "CSubTypeBonus.h"


class CSubTypeBoost :public CSubTypeBonus {
public:
	CSubTypeBoost();
	
	CSubTypeBoost(BonusTypes::Enum boostType, int32_t boostAmount,int32_t maxCd, CItemType* amoCostType, uint32_t amoRechargeRate, uint32_t maxAmo, uint32_t amoCost, uint32_t enegyCost);
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::boost;}

	int32_t getMaxCd(){return this->_maxCd;}
	uint32_t getamoCost(){return this->_amoCost;}
	uint32_t getMaxAmo(){return this->_maxAmo;}
	CItemType* getAmoCostType(){return this->_amoCostType;}
	uint32_t getAmoRechargeRate(){return this->_amoRechargeRate;}
	uint32_t getenegyCost(){return this->_enegyCost;}
	BonusTypes::Enum getBoostType(){return _boostType;}
	int32_t getBoostAmount(){return _boostAmount;}

	void setMaxCd(int32_t value){this->_maxCd = value;}
	void setAmoCost(uint32_t value){this->_amoCost = value;}
	void setAmoCostType(CItemType* type){this->_amoCostType = type;}
	void setAmoRechargeRate(uint32_t value){this->_amoRechargeRate = value;}
	void setMaxAmo(uint32_t amo){this->_maxAmo = amo;}
	void setenegyCost(uint32_t value){this->_enegyCost = value;}

	void setBoostType(BonusTypes::Enum type){_boostType = type;}
	void setBoostAmount(int32_t value){_boostAmount = value;}
	virtual CSubTypeBoost* isBoost(){return this;}

	virtual ~CSubTypeBoost();
private:
		BonusTypes::Enum _boostType;
		int32_t _boostAmount;
		int32_t _maxCd;

		CItemType* _amoCostType;
		uint32_t _amoRechargeRate;
		uint32_t _maxAmo;
		uint32_t _amoCost;
		uint32_t _enegyCost;
};

#endif	/* CSUBTYPEBOOST_H */

