/* 
 * File:   SItem.h
 * Author: karsten
 *
 * Created on 30. juni 2011, 17:19
 */

#ifndef SITEM_H
#define	SITEM_H

#include "../SFunctions.h"
#include "SItemType.h"


class SItem {
public:
	SItem();
	virtual ~SItem();
private:
	uint32_t _quan;
	SItemType* _type;
};

#endif	/* SITEM_H */

