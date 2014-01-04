/* 
 * File:   COrdres.h
 * Author: karsten
 *
 * Created on 13. januar 2012, 23:50
 */

#ifndef CORDRES_H
#define	CORDRES_H

#include "../CFunctions.h"

class COrdres {
public:
	COrdres(string name,uint32_t id);
	string getName(){return this->_name;}
	uint32_t getId(){return _id;}
	map<uint32_t,bool>& getunitSet(){return this->_unitSet;}
	map<uint32_t,bool>& getPosSet(){return this->_PosSet;}
	virtual ~COrdres();
private:
	string _name;
	uint32_t _id;
	map<uint32_t,bool> _unitSet;
	map<uint32_t,bool> _PosSet;
};

#endif	/* CORDRES_H */

