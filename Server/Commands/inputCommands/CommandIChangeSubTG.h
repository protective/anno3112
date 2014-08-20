/* 
 * File:   CommandIChangeSubTG.h
 * Author: karsten
 *
 * Created on 15. august 2014, 23:55
 */

#ifndef COMMANDICHANGESUBTG_H
#define	COMMANDICHANGESUBTG_H
#include "../Command.h"
class CommandIChangeSubTG : public Command  {
public:

	CommandIChangeSubTG(uint32_t shipId, uint32_t subId, TargetGroup::Enum targetGroup, uint32_t clientId);
	virtual uint32_t execute();
	virtual ~CommandIChangeSubTG();
private:
	uint32_t _shipId;
	uint32_t _subId;
	TargetGroup::Enum _targetGroup;
	uint32_t _clientId;
};

#endif	/* COMMANDICHANGESUBTG_H */

