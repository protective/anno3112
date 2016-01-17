/* 
 * File:   Destiny.h
 * Author: karsten
 *
 * Created on 16. august 2015, 20:56
 */

#ifndef DESTINY_H
#define	DESTINY_H
#include "../../SFunctions.h"
#include "QTreeIndex.h"
#include "../../Sspacebjects/SPos.h"

class Destiny {
public:
	Destiny();
	void update(SObj* obj);
	void remove(SObj* obj);
	list<OBJID> collide(SObj* obj);
	list<OBJID> inRange(SObj* obj, uint32_t range);
	bool getPos(SPos& set, OBJID id);
	virtual ~Destiny();
private:
	pthread_mutex_t _lock;
	QTreeNode* root;
	map<OBJID, SPos> _pos;
};

#endif	/* DESTINY_H */

