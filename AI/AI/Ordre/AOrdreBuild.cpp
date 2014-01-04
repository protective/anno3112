/* 
 * File:   AOrdreBuild.cpp
 * Author: karsten
 * 
 * Created on 29. juni 2012, 21:12
 */

#include "AOrdreBuild.h"

AOrdreBuild::AOrdreBuild(CSubSystemFac* builder, CItemType* item, uint32_t quan) {
	_builder = builder;
	_ToBuild[0].item = item;
	_ToBuild[0].quan = quan;
}
void AOrdreBuild::build(CItemType* item, uint32_t quan){
	uint32_t i = _ToBuild.size();
	_ToBuild[i].item = item;
	_ToBuild[i].quan = quan;
}

void AOrdreBuild::Execute(){
	for(map<uint32_t,AordreBuildSingle>::iterator it = _ToBuild.begin(); it != _ToBuild.end();it++){
		cerr<<"build "<<it->second.item->getTypeID()<<" quan "<<it->second.quan<<endl;
		playerObj->ServerRequestBuild(_builder,it->second.item,it->second.quan);
	}
	
}

AOrdreBuild::~AOrdreBuild() {
}

