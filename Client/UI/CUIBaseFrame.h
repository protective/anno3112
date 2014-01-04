/* 
 * File:   CUIBaseFrame.h
 * Author: karsten
 *
 * Created on 20. juli 2011, 20:10
 */

#ifndef CUIBASEFRAME_H
#define	CUIBASEFRAME_H
#include "../CFunctions.h"
#include "CUIDragDrop.h"


class CUIButtonItem;

class CUIBaseFrame {
public:
	CUIBaseFrame(CUIBaseFrame* parrent);
	virtual void Click(SDL_Event event,int32_t x, int32_t y);
	virtual void KeyDown(SDL_Event event);
	virtual void Move(SDL_Event event,int32_t x, int32_t y);
	virtual void MouseUp(SDL_Event event,int32_t x, int32_t y);
	virtual CUIDragDrop* DragDropable(){return NULL;}
	virtual void Draw();
	virtual void Draw(int32_t x, int32_t y){}
	virtual void predraw(uint32_t level){}
	virtual void add(CUIBaseFrame& frame);
	virtual void clear();
	virtual void remove(CUIBaseFrame& frame);
	virtual void finalRemove();
	virtual int32_t getX(){return this->_x;}
	virtual int32_t getY(){return this->_y;}
	virtual int32_t getWight(){return this->_wight;}
	virtual int32_t getHight(){return this->_hight;}
	//virtual CUIMoveCloseBar* getMCbar(){return NULL;}
	virtual string getHoverMsg(){return NULL;}
	virtual void setUILevel(int level){this->_UIlevel = level;}
	virtual int getUILevel();
	virtual CItemType* getFrameItemTypeRep(){return NULL;}
	virtual void setX(int32_t x){this->_x = x;}
	virtual void setY(int32_t y ){this->_y = y;}
	virtual void moveX(int32_t x){this->_x+= x;}
	virtual void moveY(int32_t y){this->_y+= y;}
	
	virtual void setDrawFront(bool df){this->_toBeDrawnFront = df;}
	virtual void OnDrop(CUIBaseFrame* frame){}
	virtual void OnDrop(CUIButtonItem* frame){}
	virtual void setWight(int32_t w ){this->_wight = w;}
	virtual void setHight(int32_t h){this->_hight = h;}
	virtual bool getCanberemoved(){ return this->_canBeRemoved;}
	virtual bool ToBeDrawFront(){return _toBeDrawnFront;}
	virtual void setCanberemoved(bool b){this->_canBeRemoved = b;}
	virtual ~CUIBaseFrame();
	virtual list<CUIBaseFrame*>& frames(){return this->_frames;}
protected:

	int _UIlevel;
	list<CUIBaseFrame*> _frames;

	bool _canBeRemoved;
	bool _toBeDrawnFront;
	CUIBaseFrame* _parrent;
	int32_t _x;
	int32_t _y;
	int32_t _wight;
	int32_t _hight;

	
};

#endif	/* CUIBASEFRAME_H */

