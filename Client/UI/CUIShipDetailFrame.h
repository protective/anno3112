/* 
 * File:   CUIShipDetailFrame.h
 * Author: karsten
 *
 * Created on 31. juli 2011, 23:18
 */

#ifndef CUISHIPDETAILFRAME_H
#define	CUISHIPDETAILFRAME_H
#include "CUIBaseFrame.h"



#include "Buttons/CUIButtonOpenCargo.h"
#include "Buttons/CUIButtonSetUnitPos.h"
#include "ComboBox/CUIComboTgChange.h"
#include "ComboBox/CUIComboOrdreChange.h"
#include "Build/CUIBuildFrame.h"
#include "../spaceobjects/subsystems/CSlotNode.h"
#include "../spaceobjects/subsystems/CSubTypeFac.h"
#include "../spaceobjects/subsystems/CSubSystemFac.h"
#include "CUITextInputField.h"
#include "Buttons/CUIButtonCreateFit.h"
#include "Forms/CUICreateFitForm.h"
class CUIShipDetailFrame : public CUIBaseFrame{
public:
	CUIShipDetailFrame();
	void updateShip();
	void updateLateShip();
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	virtual void MouseUp(SDL_Event event,int32_t x, int32_t y);
	virtual void Move(SDL_Event event,int32_t x, int32_t y);

	virtual void Draw();
	CUIComboTgChange* getChangeSubTargetGroup(){return this->_changeSubTargetGroup;}
	void setChangeSubTargetGroup(CUIComboTgChange* combobox){this->_changeSubTargetGroup = combobox;}

	CUIComboOrdreChange* getChangeOrdre(){return this->_changeOrdre;}
	void setChangeOrdre(CUIComboOrdreChange* combobox){this->_changeOrdre = combobox;}

	CUICreateFitForm* getCreateFitForm(){return this->_createFitForm;}
	void setCreateFitForm(CUICreateFitForm* form){this->_createFitForm = form;}

	void UpdateSelvSubsystemChange();
	virtual ~CUIShipDetailFrame();
private:
	CUIButtonOpenCargo* _opencargobut;
	CUIComboTgChange* _changeSubTargetGroup;
	CUIComboOrdreChange* _changeOrdre;

	CUICreateFitForm* _createFitForm;

	CUIBuildFrame* _buildFrame;
	CUIButtonCreateFit* _buttonFit;
	map<uint32_t,CUIButtonSetUnitPos*> _setUnits;
	map<uint32_t,CUIButtonSetUnitPos*> _setPoses;
};

#endif	/* CUISHIPDETAILFRAME_H */

