/* 
 * File:   CUIListBox.cpp
 * Author: karsten
 * 
 * Created on 3. november 2011, 21:16
 */

#include <sys/types.h>

#include "CUIListBox.h"

CUIListBox::CUIListBox(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight):
CUIFrame(parrent){
	_UIlevel = 3;
	this->_x = x;
	this->_y = y;
	this->_wight = wight;
	this->_hight = hight;
	this->_spreadX = 100;
	this->_spreadY = 12;
	
}

/**
*  Erases all strings in listBox
*/
void CUIListBox::clearall(){
	for(map<uint32_t, map<uint32_t, string> >::iterator it = this->_strings.begin() ; it != this->_strings.end();it++){
		it->second.clear();
		
	}
	for(map<uint32_t, map<uint32_t, uint32_t> >::iterator it = this->_flag.begin() ; it != this->_flag.end();it++){
		it->second.clear();
		
	}
	this->_strings.clear();
	this->_flag.clear();
	
}


void CUIListBox::Draw(){
	if(this->_strings.size() > 0)
		Drawbox(_x+_parrent->getX(),-12+_y+_parrent->getY(),_wight,_hight,0,0,0,0.6);
	uint32_t i = 0, j = 0;
	for (map<uint32_t, map<uint32_t, string> >::iterator it = this->_strings.begin(); it != this->_strings.end();it++){
		for (map<uint32_t, string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
			glLoadIdentity();
			font.FaceSize(16);
			if(_flag[it->first][it2->first] == 0)
				glColor3f(1, 0.3, 0.3);
			if(_flag[it->first][it2->first] == 1)
				glColor3f(0.3, 1, 0.3);			
			glRasterPos2f((j*_spreadX)+_parrent->getX()+_x, (i*_spreadY)+_parrent->getY()+_y);

			stringstream s;
			s<<it2->second;
			font.Render(s.str().c_str());
			j++;
			}
		i++;
		j = 0;
	}
}

CUIListBox::~CUIListBox() {
}

