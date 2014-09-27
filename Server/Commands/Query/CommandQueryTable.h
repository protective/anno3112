/* 
 * File:   CommandQueryTable.h
 * Author: karsten
 *
 * Created on 26. september 2014, 18:04
 */

#ifndef COMMANDQUERYTABLE_H
#define	COMMANDQUERYTABLE_H

namespace qureyAttributes{
	enum Enum{
		id = 1,
		freeCargo,
		usedCargo,
		freeCargoP,
		usedCargoP,
	};
}

typedef struct {
	OBJID objId;
	uint32_t attri;
	uint32_t value;
} qureyRow;

namespace qureyOperator{
	enum Enum{
		GT = 0,
		GTE = 1,
		E = 2,
		LT= 3,
		LTE = 4,
		NE = 5,		
	};
}

typedef struct qureyCondition{
	qureyCondition(qureyOperator::Enum p_operator, uint32_t p_attri, uint32_t p_value){
		_operator = p_operator;
		_attri = p_attri;
		_value = p_value;
    }
	qureyCondition(const qureyCondition& v){
		_operator = v._operator;
		_attri = v._attri;
		_value = v._value;
    }	
	qureyOperator::Enum _operator;
	uint32_t _attri;
	uint32_t _value;
} qureyCondition;

typedef struct qureyOrderBy{
	qureyOrderBy(){
		_operator = 0;
		_attri = 0;
	}
	qureyOrderBy(uint32_t p_operator, uint32_t p_attri){
		_operator = p_operator;
		_attri = p_attri;
    }
	qureyOrderBy(const qureyOrderBy& v){
		_operator = v._operator;
		_attri = v._attri;
    }
	uint32_t _operator;
	uint32_t _attri;
} qureyOrderBy;

#endif	/* COMMANDQUERYTABLE_H */

