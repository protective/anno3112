/* 
 * File:   CUICreateFitForm.h
 * Author: karsten
 *
 * Created on 15. marts 2012, 19:42
 */

#ifndef CUICREATEFITFORM_H
#define	CUICREATEFITFORM_H
#include "../CUIBaseFrame.h"
class CUITextInputField;
class CUIButtonOK;
class CUIButtonCancel;
class CUICreateFitForm : public CUIBaseFrame {
public:
	CUICreateFitForm(CUIBaseFrame* parrent, uint32_t x, uint32_t y);
	virtual void Click(SDL_Event event,int32_t x, int32_t y);

	virtual void Draw();
	virtual ~CUICreateFitForm();
private:
	CUITextInputField* _name;
	CUIButtonOK* _ok;
	CUIButtonCancel* _cancel;
};

#endif	/* CUICREATEFITFORM_H */

