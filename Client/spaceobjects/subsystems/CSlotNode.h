/* 
 * File:   CSlotNode.h
 * Author: karsten
 *
 * Created on 31. juli 2011, 23:30
 */

#ifndef CSLOTNODE_H
#define	CSLOTNODE_H
#include "CSubSystem.h"
#include "CShipTypeSlotData.h"
class CSlotNode {
public:
	CSlotNode(CSubAble* owner, uint32_t id, CShipTypeSlotData* slotdata);
	CSubSystem* getSS(){return this->_subsys;}
	CShipTypeSlotData* getST(){return this->_subtype;}
	CSubAble* getOwner(){return this->_owner;}
	uint32_t getId(){return this->_id;}
	void setSS(CSubSystem* subsystem){this->_subsys = subsystem;};
	void setST(CShipTypeSlotData* subtype){this->_subtype = subtype;};
private:
	CSubSystem* _subsys;
	CShipTypeSlotData* _subtype;
	CSubAble* _owner;
	uint32_t _id;
	virtual ~CSlotNode();
};

typedef map<uint32_t, CSlotNode*>::iterator CSlotNodeI;

#endif	/* CSLOTNODE_H */

