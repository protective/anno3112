/* 
 * File:   SSubTypeWep.h
 * Author: karsten
 *
 * Created on 30. juni 2011, 16:14
 */

#ifndef SSUBTYPEWEP_H
#define	SSUBTYPEWEP_H

#include "SSubType.h"
#include "../../SItems/SItemType.h"

class SSubTypeWep : public SSubType {
public:
	SSubTypeWep();

	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Wep;}
	virtual SSubTypeWep* isWeapon(){return this;}
	virtual ~SSubTypeWep();

	int32_t getDmgMin(){return this->_dmgMin;}
	int32_t getDmgMax(){return this->_dmgMax;}
	int32_t getDmgMin(map<BonusTypes::Enum, int32_t>& bonus){
		double rating = 0;
		if(bonus.find(BonusTypes::BeamDmgBonus) != bonus.end() && _subKeys.find(SubKeyWord::Beam) != _subKeys.end()){
			 rating = bonus.find(BonusTypes::BeamDmgBonus)->second/1000;
		}else if(bonus.find(BonusTypes::ProjectileDmgBonus) != bonus.end() && _subKeys.find(SubKeyWord::Projectile) != _subKeys.end()){
			rating = bonus.find(BonusTypes::ProjectileDmgBonus)->second/1000;
		}else if(bonus.find(BonusTypes::MissileDmgBonus) != bonus.end() && _subKeys.find(SubKeyWord::Guided) != _subKeys.end()){
			rating = bonus.find(BonusTypes::MissileDmgBonus)->second/1000;
		}
				
		if(rating > 0){
			double mod = 0;
			if(rating<= 10)
				mod = rating/100;
			else if(rating<= 50)	
				mod = 0.1+(rating-10)/400;
			else if(rating<= 2500)	
				mod = 0.2+(rating-50)/2500;	
			mod += 1;
			return (double)this->_dmgMin * mod;
		}else			
			return this->_dmgMin;
	}
	int32_t getDmgMax(map<BonusTypes::Enum, int32_t>& bonus){
		double rating = 0;
		if(bonus.find(BonusTypes::BeamDmgBonus) != bonus.end() && _subKeys.find(SubKeyWord::Beam) != _subKeys.end()){
			 rating = bonus.find(BonusTypes::BeamDmgBonus)->second/1000;
		}else if(bonus.find(BonusTypes::ProjectileDmgBonus) != bonus.end() && _subKeys.find(SubKeyWord::Projectile) != _subKeys.end()){
			rating = bonus.find(BonusTypes::ProjectileDmgBonus)->second/1000;
		}else if(bonus.find(BonusTypes::MissileDmgBonus) != bonus.end() && _subKeys.find(SubKeyWord::Guided) != _subKeys.end()){
			rating = bonus.find(BonusTypes::MissileDmgBonus)->second/1000;
		}
				
		if(rating > 0){
			double mod = 0;
			if(rating<= 10)
				mod = rating/100;
			else if(rating<= 50)	
				mod = 0.1+(rating-10)/400;
			else if(rating<= 2500)	
				mod = 0.2+(rating-50)/2500;	
			mod += 1;
			return (double)this->_dmgMax * mod;
		}else			
			return this->_dmgMax;
	}
	
	DmgTypes::Enum getDmgTypes(){return this->_dmgType;}

	int32_t getMaxCd(){return this->_maxCd;}
	uint32_t getTexId(){return this->_texId;}
	uint32_t getamoCost(){return this->_amoCost;}
	uint32_t getMaxAmo(){return this->_maxAmo;}
	SItemType* getAmoCostType(){return this->_amoCostType;}
	uint32_t getAmoRechargeRate(){return this->_amoRechargeRate;}

	uint32_t getenegyCost(){return this->_enegyCost;}
	int32_t getSpeed(){return this->_speed;}
	uint32_t getmaxseq(){return this->_maxseq;}
	
	void setDmgMin(int32_t value){this->_dmgMin = value;}
	void setDmgMax(int32_t value){this->_dmgMax = value;}
	void setMaxCd(int32_t value){this->_maxCd = value;}
	void setTexId(uint32_t value){this->_texId = value;}
	void setDmgTypes(DmgTypes::Enum dmgtype){this->_dmgType = dmgtype;}

	void setamoCost(uint32_t value){this->_amoCost = value;}
	void setAmoCostType(SItemType* type){this->_amoCostType = type;}
	void setAmoRechargeRate(uint32_t value){this->_amoRechargeRate = value;}
	void setMaxAmo(uint32_t amo){this->_maxAmo = amo;}

	void setenegyCost(uint32_t value){this->_enegyCost = value;}
	void setSpeed(int32_t value){this->_speed = value;}
	void setmaxseq(uint32_t value){this->_maxseq = value;}

	uint32_t getRecoil(){return this->_recoil;}
	uint32_t getRange(){return this->_range;}
	uint32_t getFlightTime(){return this->_flightTime;}
	uint32_t getTracking(){return this->_tracking;}
	uint32_t getTrackingTime(){return this->_trackingTime;}
	uint32_t getSpread(){return this->_spread;}
	uint32_t getResolution(map<BonusTypes::Enum, int32_t>& bonus){
		if(bonus.find(BonusTypes::TurretRes) != bonus.end() && _subKeys.find(SubKeyWord::Turret) != _subKeys.end()){
			double rating = bonus.find(BonusTypes::TurretRes)->second/1000;
			double mod = 0;
			if(rating<= 10)
				mod = rating/100;
			else if(rating<= 50)	
				mod = 0.1+(rating-10)/400;
			else if(rating<= 2500)	
				mod = 0.2+(rating-50)/2500;			
			//cerr<<"mod>"<<mod<<" rating>"<<rating<<endl;
			//cerr<<"res>"<<((double)this->_resolution * ((double)1-mod))<<endl;
			return ((double)this->_resolution * ((double)1-mod));
		}else
			return this->_resolution;}

	void setRecoil(uint32_t value){this->_recoil = value;}
	
	void setRange(uint32_t value){this->_range = value;}
	void setFlightTime(uint32_t value){this->_flightTime = value;}
	void setTracking(uint32_t value){this->_tracking = value;}
	void setTrackingTime(uint32_t value){this->_trackingTime = value;}
	void setResolution(uint32_t value){this->_resolution = value;}
	void setSpread(uint32_t value){this->_spread = value;}
	list<uint32_t>& fireseq(){return _fireseq;}
private:
	list<uint32_t> _fireseq;
	uint32_t _maxseq;
	uint32_t _texId;
	int32_t _dmgMin;
	int32_t _dmgMax;
	DmgTypes::Enum _dmgType;
	int32_t _maxCd;
	int32_t _speed;
	uint32_t _range;
	uint32_t _flightTime;
	uint32_t _tracking;
	uint32_t _trackingTime;
	uint32_t _resolution;
	uint32_t _spread;
	uint32_t _recoil;
	uint32_t _maxAmo;

	SItemType* _amoCostType;
	uint32_t _amoRechargeRate;
	uint32_t _amoCost;
	uint32_t _enegyCost;

};

#endif	/* SSUBTYPEWEP_H */

