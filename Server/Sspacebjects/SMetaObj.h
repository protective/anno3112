/* 
 * File:   SMetaObj.h
 * Author: karsten
 *
 * Created on 22. februar 2014, 11:48
 */

#ifndef SMETAOBJ_H
#define	SMETAOBJ_H
#include "../SFunctions.h"

class Processor;
class SMetaObj {
public:
	SMetaObj(uint32_t id, uint8_t team, uint32_t size, TargetType::Enum targetType);
	SMetaObj(uint32_t id, uint8_t team, uint32_t size, TargetType::Enum targetType, uint32_t owner);

	//SPos* getPos(){return &pos;}
	//SPos getRPos();
	TargetType::Enum getTargetType(){return targetType;}
	uint8_t getTeam(){return team;}
	map<uint8_t,Visibility::Enum> getVisibleTo(){}//TODO fix
	bool isTargetable(){return targetType==TargetType::Invalid ? false: true;}
	bool isAstoroid(){return targetType== TargetType::Astoroid? true:false;}
	bool isMoveable();
	uint32_t getSpeed();
	virtual void checkCollisions(Processor* processor){}
	uint32_t getTargetSize(){return _size;}
	virtual ~SMetaObj();

	//updateTimers
	uint32_t _timerLowFeq;
	uint32_t _id;
	uint8_t varfreq;
	//static
	uint32_t _size;
	TargetType::Enum targetType;	
	uint32_t owner;
	uint8_t team;
	//variable
	//bool posValid;
	//SPos pos;
	int32_t vecX;
	int32_t vecY;
	int32_t vecZ;

	uint32_t scan, scanP;
	uint8_t procesNodeId;

};

#endif	/* SMETAOBJ_H */

