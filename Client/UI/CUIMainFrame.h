/* 
 * File:   CUIMainFrame.h
 * Author: karsten
 *
 * Created on 20. juli 2011, 21:36
 */

#ifndef CUIMAINFRAME_H
#define	CUIMAINFRAME_H

#include "CUIBaseFrame.h"
#include "CUIShipDetailFrame.h"
#include "../Grafic/CPartical.h"
#include "CUICargoViewer.h"
#include "Build/CUIBuildFrame.h"

class CUIMainFrame : public CUIBaseFrame {
public:
	CUIMainFrame(CUIBaseFrame* parrent);
	virtual void Draw();
	virtual void add(CUIBaseFrame& frame){_toBeAdded.push_back(&frame);}
	virtual void preAdd();
	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual void Move(SDL_Event event,int32_t x, int32_t y);
	virtual void MouseUp(SDL_Event event, int32_t x, int32_t y);
	int32_t getVx(){return this->Vx;}
	int32_t getVy(){return this->Vy;}
	CSlotNode* GetSelSlot(){return this->_selslot;}
	list<CSlotNode*>& GetSelSlotList(){return this->_selslotList;}
	void SetSelSlot(CSlotNode* subsys,bool add);
	CUIShipDetailFrame* shipDetail(){return this->_shipDetail;}
	
	list<CCargoBay*>& getOpenCargoList(){return this->_openCargo;}

	void setsetOrdreUnit(int32_t unit){this->_setOrdreUnit = unit;}
	void setsetOrdrePos(int32_t pos){this->_setOrdrePos = pos;}

	int32_t getsetOrdreUnit(){return this->_setOrdreUnit;}
	int32_t getsetOrdrePos(){return this->_setOrdrePos;}
	virtual ~CUIMainFrame();
private:

	int32_t Vx;
	int32_t Vy;
	CSlotNode* _selslot;
	list<CSlotNode*> _selslotList;
	CUIShipDetailFrame* _shipDetail;
	
	list<CCargoBay*> _openCargo;
	int32_t _setOrdreUnit;
	int32_t _setOrdrePos;
	list<CUIBaseFrame*> _toBeAdded;
};

#endif	/* CUIMAINFRAME_H */

