/* 
 * File:   AChoice.h
 * Author: karsten
 *
 * Created on 29. juni 2012, 20:05
 */

#ifndef ACHOICE_H
#define	ACHOICE_H
#include "../AFunctions.h"
#include "AObjGroup.h"
#include "Ordre/AOrdre.h"



class AChoice {
public:
	AChoice(int32_t power, int32_t tactical, int32_t economic, AOrdre* ordre, ABeacon* affectedBeacon);
	virtual ~AChoice();
	void SetOrdre( AOrdre* ordre){_ordre = ordre;}
	int32_t _power;
	int32_t _tactical;
	int32_t _economic;
	AOrdre* _ordre;
	ABeacon* _affectedBeacon;
	



};



#endif	/* ACHOICE_H */

