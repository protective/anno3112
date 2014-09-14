/* 
 * File:   SOrderNode.h
 * Author: karsten
 *
 * Created on 3. september 2014, 22:20
 */

#ifndef SORDERNODE_H
#define	SORDERNODE_H



class SOrderNodeStmt;
class SOrderVisitor;

class SOrderNode {
public:
	SOrderNode(){}
	virtual void accept(SOrderVisitor* v);
	//virtual SOrderNodeStmt* getSOrderNodeStmt(){return NULL;}
	virtual ~SOrderNode(){}
private:

};

#endif	/* SORDERNODE_H */

