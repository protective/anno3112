/* 
 * File:   CUIFrame.h
 * Author: karsten
 *
 * Created on 20. juli 2011, 18:35
 */

#ifndef CUIFRAME_H
#define	CUIFRAME_H
#include "../CFunctions.h"
#include "CUIBaseFrame.h"
#include "CUIMoveCloseBar.h"
class CUIFrame : public CUIBaseFrame {
public:
	CUIFrame(CUIBaseFrame* parrent);
	virtual void Draw();

	void setMCbar(CUIMoveCloseBar* mcbar){this ->_MCbar = mcbar;}
	virtual CUIMoveCloseBar* getMCbar(){return this ->_MCbar;}
	virtual int32_t getY(){if (this->_MCbar) return this->_y- _MCbar->getHight();return this->_y;}
	virtual ~CUIFrame();
protected:
	CUIMoveCloseBar* _MCbar;
};

#endif	/* CUIFRAME_H */

