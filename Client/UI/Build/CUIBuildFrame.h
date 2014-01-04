/* 
 * File:   CUIBuildFrame.h
 * Author: karsten
 *
 * Created on 26. oktober 2011, 09:19
 */

#ifndef CUIBUILDFRAME_H
#define	CUIBUILDFRAME_H
#include "../CUIFrame.h"
#include "../ListBox/CUIListBox.h"
class CUIButtonFrame;
class CSubSystemFac;
class CCargoBay;
class CItemType;

class CUIBuildFrame : public CUIFrame {
public:
	CUIBuildFrame(CUIBaseFrame* parrent, CCargoBay* cargo);
	void addCanBuild(CSubSystemFac* fac, CItemType* item);
	void Draw();
	void Click(SDL_Event event, int32_t x, int32_t y);
	virtual void Move(SDL_Event event,int32_t x, int32_t y);
	virtual ~CUIBuildFrame();
private:
	CCargoBay* _cargo;
	CUIButtonFrame* _buildList;
	CUIListBox* _matList;
};

#endif	/* CUIBUILDFRAME_H */

