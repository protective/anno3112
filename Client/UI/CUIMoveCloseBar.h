/* 
 * File:   CUIMoveCloseBar.h
 * Author: karsten
 *
 * Created on 22. september 2011, 11:29
 */

#ifndef CUIMOVECLOSEBAR_H
#define	CUIMOVECLOSEBAR_H

#include "CUIBaseFrame.h"


class CUIMoveCloseBar : public CUIBaseFrame {
public:
	CUIMoveCloseBar(CUIBaseFrame* parrent);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual ~CUIMoveCloseBar();
private:

};

#endif	/* CUIMOVECLOSEBAR_H */

