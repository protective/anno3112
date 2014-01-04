/* 
 * File:   SSubTypeBonus.h
 * Author: karsten
 *
 * Created on 24. december 2011, 12:06
 */

#ifndef SSUBTYPEBONUS_H
#define	SSUBTYPEBONUS_H
#include "SSubType.h"
class SSubTypeBonus : public SSubType {
public:
	SSubTypeBonus();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::bonus;}
	map<BonusTypes::Enum, int32_t>& getBonuslist(){return this->_bonuslist;};
	void setTexId(uint32_t value){this->_texId = value;}
	uint32_t getTexId(){return this->_texId;}

	void addBonus(BonusTypes::Enum bonus, int32_t value);
	

	virtual SSubTypeBonus* isBonus(){return this;}

	virtual ~SSubTypeBonus();
	
protected:
	uint32_t _texId;
	map<BonusTypes::Enum, int32_t> _bonuslist;
};

#endif	/* SSUBTYPEBONUS_H */

