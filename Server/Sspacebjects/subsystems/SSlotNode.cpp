/* 
 * File:   SSlotNode.cpp
 * Author: karsten
 * 
 * Created on 25. juni 2011, 00:20
 */

#include "SSlotNode.h"

SSlotNode::SSlotNode(SSubAble* owner, uint32_t id, SShipTypeSlotData* slotdata) {
	this->_subsys = NULL;
	this->_subtype = slotdata;
	this->_id = id;
	this->_owner = owner;
}

bool SSlotNode::CanFit(FitTypes::Enum type, FitTypes::Enum on){
	switch(type){
		case FitTypes::Armo: {if(on == FitTypes::Armo || on == FitTypes::ShAr)return true; else return false;}
		case FitTypes::Shie: {if(on == FitTypes::Shie || on == FitTypes::ShAr || on == FitTypes::MwSh || on == FitTypes::ShEl)return true; else return false;}
		case FitTypes::Elec: {if(on == FitTypes::Elec || on == FitTypes::ElMe || on == FitTypes::MwEl || on == FitTypes::ShEl)return true; else return false;}
		case FitTypes::Mech: {if(on == FitTypes::Mech || on == FitTypes::ElMe)return true; else return false;}
		case FitTypes::Engi: {if(on == FitTypes::Engi)return true; else return false;}
		case FitTypes::Figh: {if(on == FitTypes::Figh)return true; else return false;}
		case FitTypes::Lwep: {if(on == FitTypes::Lwep || on == FitTypes::Mwep || on == FitTypes::MwSh || on == FitTypes::MwEl || on == FitTypes::Hwep)return true; else return false;}
		case FitTypes::Mwep: {if(on == FitTypes::Mwep || on == FitTypes::MwSh || on == FitTypes::MwEl || on == FitTypes::Hwep)return true; else return false;}
		case FitTypes::Hwep: {if(on == FitTypes::Hwep)return true; else return false;}

		case FitTypes::Lfac: {if(on == FitTypes::Lfac || on == FitTypes::Mfac || on == FitTypes::Hfac)return true; else return false;}
		case FitTypes::Mfac: {if(on == FitTypes::Mfac || on == FitTypes::Hfac)return true; else return false;}
		case FitTypes::Hfac: {if(on == FitTypes::Hfac)return true; else return false;}

		case FitTypes::Mini: {if(on == FitTypes::Mini)return true; else return false;}
				
		default: {return false;}
	}
}

SSlotNode::~SSlotNode() {
	delete this->_subsys;
}

