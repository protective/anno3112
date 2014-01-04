/* 
 * File:   CUISubSystem.h
 * Author: karsten
 *
 * Created on 3. august 2011, 16:33
 */

#ifndef CUISUBSYSTEM_H
#define	CUISUBSYSTEM_H

#include "CUIButton.h"
#include "../spaceobjects/subsystems/CSlotNode.h"
class CUISubSystem : public CUIButton, public CUIDragDrop{
public:
	CUISubSystem(CUIBaseFrame* parrent, CSlotNode& slotNode);
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual void OnDrop(CUIButtonItem* frame);
	virtual CUIDragDrop* DragDropable(){return (CUIDragDrop*)this;}
	virtual string getHoverMsg();
	virtual void Move(SDL_Event event,int32_t x, int32_t y);

	virtual void Draw();
	virtual ~CUISubSystem();
private:
	void DrawBack();
	void DrawCDs();
	uint16_t _lockingdisplay;
	CSlotNode* _slot;
};

#endif	/* CUISUBSYSTEM_H */

