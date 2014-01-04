/* 
 * File:   AOrdreSet.h
 * Author: karsten
 *
 * Created on 20. juni 2012, 18:41
 */

#ifndef AORDRESET_H
#define	AORDRESET_H
#include "../../AFunctions.h"
#include "AOrdre.h"


class AOrdreSet {
public:
	AOrdreSet();
	void addordre(AOrdre* ordre){_ordres.push_back(ordre);}
	void addordreDelete(AOrdre* ordre){_ordres.push_back(ordre);_ordresDelete.push_back(ordre);}
	void execute();
	void addtoDelete(AObjGroup* group){_todelete.push_back(group);}
	int32_t gettotalUtil(){return _utility - _moveCost;}
	int32_t addMoveCost(int32_t cost){_moveCost+= cost;}
	int32_t getMoveCost(){return _moveCost;}
	int32_t setUtility(int32_t util){_utility = util;}
	virtual ~AOrdreSet();
private:
	int32_t _utility;
	int32_t _moveCost;
	list<AOrdre*> _ordres;
	list<AOrdre*> _ordresDelete;
	list<AObjGroup*> _todelete;
};

#endif	/* AORDRESET_H */

