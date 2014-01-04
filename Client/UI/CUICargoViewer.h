/* 
 * File:   CUICargoViewer.h
 * Author: karsten
 *
 * Created on 20. september 2011, 20:44
 */

#ifndef CUICARGOVIEWER_H
#define	CUICARGOVIEWER_H

#include "CUIButtonFrame.h"
#include "../spaceobjects/cargo/CCargoBay.h"
#include "CUIMainFrame.h"

class CUICargoViewer : public CUIButtonFrame {
public:
	CUICargoViewer(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight, CCargoBay* cargobay);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);

	virtual void OnDrop(CUIButtonItem* frame);
	virtual void setCanberemoved(bool b);
	
	virtual ~CUICargoViewer();
private:
	void updateScrolls();
	void updateButtons();
	CCargoBay* _cargobay;
};

#endif	/* CUICARGOVIEWER_H */

