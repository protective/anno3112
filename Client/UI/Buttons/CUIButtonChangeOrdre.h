/* 
 * File:   CUIButtonChangeOrdre.h
 * Author: karsten
 *
 * Created on 14. januar 2012, 01:43
 */

#ifndef CUIBUTTONCHANGEORDRE_H
#define	CUIBUTTONCHANGEORDRE_H
#include "../CUIButton.h"
#include "../../spaceobjects/COrdres.h"
using namespace std;
class CUIButtonChangeOrdre : public CUIButton{
public:
	CUIButtonChangeOrdre(CUIBaseFrame* parrent, COrdres* changeTo);
	virtual void Draw();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);

	virtual ~CUIButtonChangeOrdre();
private:
	COrdres* _changeTo;
};

#endif	/* CUIBUTTONCHANGEORDRE_H */

