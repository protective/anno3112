/* 
 * File:   CSubTypeBonus.cpp
 * Author: karsten
 * 
 * Created on 25. december 2011, 18:46
 */

#include "CSubTypeBonus.h"

CSubTypeBonus::CSubTypeBonus() {
}

void CSubTypeBonus::addBonus(BonusTypes::Enum bonus, int32_t value){
	_bonuslist[bonus] = value;
}

void CSubTypeBonus::addBonusFromNet(BonusAttri* st){

	if(st->_armor)
		addBonus(BonusTypes::Armor, st->_armor);
	if(st->_hull)
		addBonus(BonusTypes::Hull, st->_hull);
	if(st->_deflector)
		addBonus(BonusTypes::Deflector, st->_deflector);
	if(st->_shStr)
		addBonus(BonusTypes::ShieldStr, st->_shStr);
	if(st->_energy)
		addBonus(BonusTypes::Energy, st->_energy);
	if(st->_scanrange)
		addBonus(BonusTypes::ScanRange, st->_scanrange);
	if(st->_scanprange)
		addBonus(BonusTypes::ScanPRange, st->_scanprange);
	if(st->_speedthruster)
		addBonus(BonusTypes::SpeedThruster, st->_speedthruster);
	if(st->_manuverethruster)
		addBonus(BonusTypes::ManuvereThruster, st->_manuverethruster);

}

CSubTypeBonus::~CSubTypeBonus() {
}

