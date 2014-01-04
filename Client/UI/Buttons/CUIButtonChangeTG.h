/* 
 * File:   CUIButtonChangeTG.h
 * Author: karsten
 *
 * Created on 9. oktober 2011, 11:01
 */

#ifndef CUIBUTTONCHANGETG_H
#define	CUIBUTTONCHANGETG_H
#include "../CUIButton.h"

using namespace std;
class CUIButtonChangeTG  : public CUIButton{
public:
	CUIButtonChangeTG(CUIBaseFrame* parrent, TargetGroup::Enum changeTo);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual ~CUIButtonChangeTG();
private:
	TargetGroup::Enum _changeTo;
};

#endif	/* CUIBUTTONCHANGETG_H */

