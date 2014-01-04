/* 
 * File:   CUIListBox.h
 * Author: karsten
 *
 * Created on 3. november 2011, 21:16
 */

#ifndef CUILISTBOX_H
#define	CUILISTBOX_H
#include "../CUIFrame.h"
class CUIListBox : public CUIFrame  {
public:
	CUIListBox(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight);
	map<uint32_t, map<uint32_t, string> >& getStrings(){return this->_strings;}
	map<uint32_t, map<uint32_t, uint32_t> >& getFlag(){return this->_flag;}
	void Draw();
	void clearall();
	virtual ~CUIListBox();
private:
	map<uint32_t, map<uint32_t, string> > _strings;
	map<uint32_t, map<uint32_t, uint32_t> > _flag;
	uint32_t _spreadX;
	uint32_t _spreadY;

};

#endif	/* CUILISTBOX_H */

