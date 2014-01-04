/* 
 * File:   CUIDragDrop.h
 * Author: karsten
 *
 * Created on 25. september 2011, 19:18
 */

#ifndef CUIDRAGDROP_H
#define	CUIDRAGDROP_H
#include "../CFunctions.h"
class CUIBaseFrame;
class CUIDragDrop {
public:
	CUIDragDrop();

	virtual void drag(){}
	virtual void drop(CUIBaseFrame* dropedFrame){}

	virtual ~CUIDragDrop();
protected:
	int32_t _oldX;
	int32_t _oldY;

};

#endif	/* CUIDRAGDROP_H */

