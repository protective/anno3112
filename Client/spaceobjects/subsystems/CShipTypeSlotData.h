/* 
 * File:   CShipTypeSlotData.h
 * Author: karsten
 *
 * Created on 16. august 2011, 23:40
 */

#ifndef CSHIPTYPESLOTDATA_H
#define	CSHIPTYPESLOTDATA_H
#include "../../CFunctions.h"

class CShipTypeSlotData {
public:
	CShipTypeSlotData(uint32_t slotType, int32_t gX, int32_t gY, uint32_t uiX, uint32_t uiY);
	int32_t gX(){return _gX;}
	int32_t gY(){return _gY;}
	uint32_t uiX(){return _uiX;}
	uint32_t uiY(){return _uiY;}
	uint32_t slotType(){return _slotType;}
	virtual ~CShipTypeSlotData();
private:
	int32_t _gX;
	int32_t _gY;
	uint32_t _uiX;
	uint32_t _uiY;
	uint32_t _slotType;
};

#endif	/* CSHIPTYPESLOTDATA_H */

