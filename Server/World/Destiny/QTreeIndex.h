/* 
 * File:   QTreeIndex.h
 * Author: karsten
 *
 * Created on 16. august 2015, 21:09
 */

#ifndef QTREEINDEX_H
#define	QTREEINDEX_H
#include "../../SFunctions.h"

class SObj;
class QTreeNode;
class QTreePoints {
public:	
	int32_t x;
	int32_t y;
	OBJID obj;
	uint32_t size;
	QTreeNode* _node;
};

class QTreeAABB {
public:
	QTreeAABB(int32_t centerX, int32_t centerY, uint32_t size);
	int32_t _centerX;
	int32_t _centerY;
	uint32_t _size;
	bool intersect(QTreeAABB& aabb);
	bool contains(int32_t x, int32_t y);
	bool contains(int32_t x, int32_t y, uint32_t size);
	
};

class QTreeNode {
public:
	QTreeNode(int32_t centerX, int32_t centerY, uint32_t size);
	bool insert(QTreePoints& point);
	bool remove(QTreePoints& point);
	bool updateUp(QTreePoints& point, int32_t x, int32_t y); 
	void queryRange(list<QTreePoints*>& ret, QTreeAABB& range, uint32_t* counter);

	static const int maxPoints = 16;
	void merge();
	uint32_t count();
	uint32_t boxCount();
	virtual ~QTreeNode();
	QTreeAABB* _boundery;
private:

	
	void subdevide();
	
	QTreeNode* _parrent;
	QTreeNode* _ul;
	QTreeNode* _ll;
	QTreeNode* _ur;
	QTreeNode* _lr;
	list<QTreePoints*> _points;
	uint32_t _size;
};



#endif	/* QTREEINDEX_H */

