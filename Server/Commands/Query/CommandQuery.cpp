/* 
 * File:   CommandQuery.cpp
 * Author: karsten
 * 
 * Created on 26. september 2014, 17:56
 */

#include "CommandQuery.h"
#include "../Processor.h"
#include "CommandQueryRsp.h"
#include "../../Sspacebjects/SObj.h"
#include "../../Sspacebjects/SSubAble.h"
CommandQuery::CommandQuery(OBJID sender, qureyOrderBy orderby, list<qureyCondition> conditions, uint32_t limit):
Command(0){
	_sender = sender;
	_orderby = orderby;
	_attriRsp.push_back(_orderby._attri);
	_conditions = conditions;
	_limit = limit;
}
namespace qureyOperator{
	template<typename T>
	bool op(qureyOperator::Enum op, T val1, T val2){
		switch(op){
			case GT: {return val1 > val2;}
			case GTE: {return val1 >= val2;}
			case E: {return val1 == val2;}
			case LT: {return val1 < val2;}
			case LTE: {return val1 <= val2;}
			case NE: {return val1 != val2;}
		};
	}
}
bool CommandQuery::checkCondition(qureyCondition condition, SObj* obj){
	
	switch(condition._attri){
		case qureyAttributes::id:{return qureyOperator::op<OBJID>(condition._operator,(OBJID)obj->getId(), (OBJID)condition._value);}		
	};
	
	return false;
}

uint32_t CommandQuery::getValue(uint32_t attri, SObj* obj){
	cerr<<"getvalue "<<attri<<endl;
	if(attri & (1<<31)){
		//We are dealing with an item
		if(obj->getsubable()){
			uint32_t iType = attri & 0x7FFFFFFF;
			return obj->getsubable()->getCargoBay()->GetById(iType);
		}
	}
	return 0;
}

uint32_t CommandQuery::execute(){
	cerr<<"execure CommandQuery"<<endl;
	list<pair<SObj*, uint32_t> > _results;
	bool sat;
	for(map<uint32_t, Processable*>::iterator it = _processor->getLocalProcssables().begin() ; it!= _processor->getLocalProcssables().end(); it++){
		sat = true;
		if(!it->second->isObj())
			continue;
		for(list<qureyCondition>::iterator it2 = _conditions.begin(); it2 != _conditions.end();it2++){
			if(!checkCondition(*it2,it->second->isObj()) ){
				sat = false;
				break;
			}
		}
		if(!sat)
			continue;
		uint32_t oValue = getValue(_orderby._attri, it->second->isObj());
		cerr<<"oattri "<<_orderby._attri<<endl;
		list<pair<SObj*, uint32_t> >::iterator  it2;
		for(it2 = _results.begin(); it2 != _results.end(); it2++){
			if (oValue > it2->second){
				break;
			}
		}
		_results.insert(it2, pair<SObj*, uint32_t>(it->second->isObj(),oValue));

		if(_results.size() > _limit)
			_results.pop_back();
			
	}

	list<qureyRow> rspList;
	for(list<pair<SObj*, uint32_t> >::iterator it = _results.begin(); it!= _results.end();it++){
		qureyRow t;
		t.attri = _attriRsp.front();
		t.objId = it->first->getId();
		t.value = getValue(t.attri, it->first);
		rspList.push_back(t);
	}
	CommandQueryRsp* rsp = new CommandQueryRsp(_sender,rspList);
	if(networkControl->addCommandToProcesable(rsp,_sender))
		delete rsp;
	
	return COMMAND_FINAL;
}

CommandQuery::~CommandQuery() {
}

