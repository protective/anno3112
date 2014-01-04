/* 
 * File:   AOrdreBuild.h
 * Author: karsten
 *
 * Created on 29. juni 2012, 21:12
 */

#ifndef AORDREBUILD_H
#define	AORDREBUILD_H
#include "AOrdre.h"
#include "../Client/Items/CItemType.h"
#include "../Client/spaceobjects/subsystems/CSubSystemFac.h"
struct AordreBuildSingle{
CItemType* item;
uint32_t quan;
};

class AOrdreBuild : public AOrdre {
public:
	AOrdreBuild(CSubSystemFac* builder, CItemType* item, uint32_t quan);
	virtual void Execute();
	void build( CItemType* item, uint32_t quan);
	virtual ~AOrdreBuild();
private:
	CSubSystemFac* _builder;
	map<uint32_t,AordreBuildSingle> _ToBuild;
};

#endif	/* AORDREBUILD_H */

