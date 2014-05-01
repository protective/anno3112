/* 
 * File:   SMetaObj.h
 * Author: karsten
 *
 * Created on 22. februar 2014, 11:48
 */

#ifndef SMETAOBJ_H
#define	SMETAOBJ_H

#include "SPos.h"


class SMetaObj {
public:
	SMetaObj();
	SMetaObj(const SMetaObj& orig);
	SPos* getPos(){return &pos;}
	TargetType::Enum getTargetType(){return targetType;}
	uint8_t getTeam(){return team;}
	map<uint8_t,Visibility::Enum> getVisibleTo(){}//TODO fix
	bool isTargetable(){return targetType==TargetType::Invalid ? false: true;}
	bool isAstoroid(){return targetType== TargetType::Astoroid? true:false;}
	virtual ~SMetaObj();

	uint8_t varfreq;
	//static
	uint32_t size;
	TargetType::Enum targetType;	
	uint32_t owner;
	uint8_t team;
	//variable
	SPos pos;

	uint32_t scan, scanP;
	uint8_t procesNodeId;

	
	
};

#endif	/* SMETAOBJ_H */

