/* 
 * File:   CUIButtonChangeView.h
 * Author: karsten
 *
 * Created on 1. oktober 2011, 21:02
 */

#ifndef CUIBUTTONCHANGEVIEW_H
#define	CUIBUTTONCHANGEVIEW_H

#include "../CUIButton.h"

class CUIButtonChangeView : public CUIButton {
public:
	CUIButtonChangeView(CUIBaseFrame* parrent, UIviews::Enum changeto);
	virtual ~CUIButtonChangeView();
private:

};

#endif	/* CUIBUTTONCHANGEVIEW_H */

