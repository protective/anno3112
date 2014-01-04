/* 
 * File:   CUIRCMenuLoadout.h
 * Author: karsten
 *
 * Created on 1. marts 2012, 21:39
 */

#ifndef CUIRCMENULOADOUT_H
#define	CUIRCMENULOADOUT_H
#include "../CUIRightClickMenu.h"

class CUIRCMenuLoadout : public CUIRightClickMenu {
public:
	CUIRCMenuLoadout(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t hight, CCargoBay* cargo);
	virtual ~CUIRCMenuLoadout();
private:

};

#endif	/* CUIRCMENULOADOUT_H */

