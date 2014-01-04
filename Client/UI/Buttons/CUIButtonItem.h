/* 
 * File:   CUIButtonItem.h
 * Author: karsten
 *
 * Created on 20. september 2011, 20:57
 */

#ifndef CUIBUTTONITEM_H
#define	CUIBUTTONITEM_H

#include "../CUIButton.h"
#include "../CUIDragDrop.h"
#include "../../Items/CItemType.h"
#include "../../spaceobjects/cargo/CCargoBay.h"
class CUIButtonItem : public CUIButton , public CUIDragDrop {
public:
	CUIButtonItem(CUIBaseFrame* parrent,uint32_t x, uint32_t y, uint32_t wight, uint32_t hight,CCargoBay* cargobay, CItemType* item, uint32_t quan);
	CUIButtonItem(CUIBaseFrame* parrent,uint32_t x, uint32_t y, uint32_t wight, uint32_t hight, CSlotNode* slot, uint32_t quan);
	virtual void Draw();
	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual CUIDragDrop* DragDropable(){return (CUIDragDrop*)this;}
	virtual void drop(CUIBaseFrame* dropedFrame);
	virtual void drag();
	virtual string getHoverMsg(){if(_item)return _item->getName();else return "";}
	virtual void Move(SDL_Event event, int32_t x, int32_t y);
	CItemType* getItem(){return this->_item;}
	CSlotNode* getSlot(){return this->_slot;}
	uint32_t getQuan(){return this->_quan;}
	CCargoBay* getCargoBay(){return this->_cargobay;}
	void updateQuan(uint32_t quan){this->_quan = quan;}
	virtual ~CUIButtonItem();
private:
	CItemType* _item;
	uint32_t _quan;
	CCargoBay* _cargobay;
	CSlotNode* _slot;
};

#endif	/* CUIBUTTONITEM_H */

