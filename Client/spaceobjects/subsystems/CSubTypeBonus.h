/* 
 * File:   CSubTypeBonus.h
 * Author: karsten
 *
 * Created on 25. december 2011, 18:46
 */

#ifndef CSUBTYPEBONUS_H
#define	CSUBTYPEBONUS_H

#include "CSubType.h"

class CSubTypeBonus  : public CSubType {
public:
	CSubTypeBonus();

	virtual SubSystemClass::Enum getClass(){return SubSystemClass::bonus;}
	
	map<BonusTypes::Enum, int32_t>& getBonuslist(){return this->_bonuslist;};

	virtual CSubTypeBonus* isBonus(){return this;}
	void addBonus(BonusTypes::Enum bonus, int32_t value);
	void addBonusFromNet(BonusAttri* _bonus);

	virtual ~CSubTypeBonus();
private:
	map<BonusTypes::Enum, int32_t> _bonuslist;
};

#endif	/* CSUBTYPEBONUS_H */

