/* 
 * File:   SShipTypeSlotData.h
 * Author: karsten
 *
 * Created on 25. juni 2011, 00:21
 */

#ifndef SSHIPTYPESLOTDATA_H
#define	SSHIPTYPESLOTDATA_H
#include "../../SFunctions.h"
class SShipTypeSlotData {
public:
	SShipTypeSlotData(FitTypes::Enum slotType, int32_t gX, int32_t gY, uint32_t uiX, uint32_t uiY);
	SShipTypeSlotData();

	int32_t gX(){return _gX;}
	int32_t gY(){return _gY;}
	uint32_t uiX(){return _uiX;}
	uint32_t uiY(){return _uiY;}
	FitTypes::Enum slotType(){return _slotType;}
	uint32_t slotMount(){return _mount;}
	FireDir::Enum getFireDir(){return this->_firedir;}
	
	SItemType* getBaseItem(){return _baseItem;}
	uint32_t getBaseItemCount(){return _baseItemCount;}
	
	void setgX(int32_t value){_gX = value;}
	void setgY(int32_t value){_gY = value;}
	void setuiX(uint32_t value){_uiX = value;}
	void setuiY(uint32_t value){_uiY = value;}
	void setslotType(FitTypes::Enum value){_slotType = value;}
	void setslotMount(uint32_t value){_mount = value;}

	void setFireDir(FireDir::Enum firedir){this->_firedir = firedir;}
	
	void setBaseItem(SItemType* baseItem){_baseItem = baseItem;}
	void setBaseItemCount(uint32_t value){_baseItemCount = value;}
	virtual ~SShipTypeSlotData();
private:
	int32_t _gX;
	int32_t _gY;
	uint32_t _uiX;
	uint32_t _uiY;
	FitTypes::Enum _slotType;
	uint32_t _mount;
	FireDir::Enum _firedir;
	SItemType* _baseItem;
	uint32_t _baseItemCount;
};

#endif	/* SSHIPTYPESLOTDATA_H */

