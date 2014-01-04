/* 
 * File:   SSlotNode.h
 * Author: karsten
 *
 * Created on 25. juni 2011, 00:20
 */

#ifndef SSLOTNODE_H
#define	SSLOTNODE_H

#include "SSubSystem.h"
#include "SShipTypeSlotData.h"


class SSlotNode {
public:
	SSlotNode(SSubAble* owner, uint32_t id, SShipTypeSlotData* slotdata);
	SSubSystem* getSS(){return this->_subsys;};
	SShipTypeSlotData* getST(){return this->_subtype;};
	SSubAble* getOwner(){return this->_owner;}
	uint32_t getId(){return this->_id;}
	void setSS(SSubSystem* subsystem){this->_subsys = subsystem;};
	void setST(SShipTypeSlotData* subtype){this->_subtype = subtype;};

	bool CanFit(FitTypes::Enum type, FitTypes::Enum on);
	virtual ~SSlotNode();
private:
	SSubSystem* _subsys;
	SShipTypeSlotData* _subtype;
	SSubAble* _owner;
	uint32_t _id;
};

typedef map<uint32_t, SSlotNode*>::iterator SSlotNodeI;
#endif	/* SSLOTNODE_H */

