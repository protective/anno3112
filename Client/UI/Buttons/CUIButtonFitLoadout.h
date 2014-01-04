/* 
 * File:   CUIButtonFitLoadout.h
 * Author: karsten
 *
 * Created on 1. marts 2012, 21:45
 */

#ifndef CUIBUTTONFITLOADOUT_H
#define	CUIBUTTONFITLOADOUT_H
#include "../CUIButton.h"
class CUIButtonFitLoadout : public CUIButton{
public:
	CUIButtonFitLoadout(CUIBaseFrame* parrent, CCargoBay* cargo, uint32_t idLoadout);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);

	virtual ~CUIButtonFitLoadout();
private:
	uint32_t _IdLoadout;
	CCargoBay* _cargo;
};

#endif	/* CUIBUTTONFITLOADOUT_H */

