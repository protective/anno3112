/* 
 * File:   SOrderBinaryOperatorExpr.h
 * Author: karsten
 *
 * Created on 12. september 2014, 19:42
 */

#ifndef SORDERBINARYOPERATOREXPR_H
#define	SORDERBINARYOPERATOREXPR_H
#include "SOrderNodeExpr.h"
#include "../Terminals/SOrderTerminal.h"
class SOrderBinaryOperatorExpr : public SOrderNodeExpr{
public:
	SOrderBinaryOperatorExpr(SOrderNodeExpr* firstOperand, SOrderTerminal* appliedOperator, SOrderNodeExpr* secondOperand) : SOrderNodeExpr(appliedOperator->pos()){
		this->_firstOperand = firstOperand;
		this->_secondOperand = secondOperand;
		this->_appliedOperator = appliedOperator;
	}
	
	virtual TypeDenoter* getType(){return _firstOperand->getType();}

	/** Get the first operand */
	SOrderNodeExpr* firstOperand(){
		return _firstOperand;
	}
	/** Get the second operand */
	SOrderNodeExpr* secondOperand(){
		return _secondOperand;
	}
	/** Get the operator applied */
	SOrderTerminal* appliedOperator(){
		return _appliedOperator;
	}
	void accept(SOrderVisitor* v);
private:
	SOrderNodeExpr* _firstOperand;
	SOrderNodeExpr* _secondOperand;
	SOrderTerminal* _appliedOperator;
};

#endif	/* SORDERBINARYOPERATOREXPR_H */

