/* 
 * File:   QTreeIndex.cpp
 * Author: karsten
 * 
 * Created on 16. august 2015, 21:09
 */

#include "QTreeIndex.h"
#include "../../Sspacebjects/SObj.h"

QTreeAABB::QTreeAABB(int32_t centerX, int32_t centerY, uint32_t size){
	_centerX = centerX;
	_centerY = centerY;
	_size = size;
}

QTreeNode::QTreeNode(int32_t centerX, int32_t centerY, uint32_t size){
	_boundery = new QTreeAABB(centerX, centerY, size);
	_parrent = NULL;
	_ll = NULL;
	_lr = NULL;
	_ul = NULL;
	_ur = NULL;
}

bool QTreeAABB::contains(int32_t x, int32_t y){
	if (x >= this->_centerX - (int32_t)this->_size &&
		x <= this->_centerX + (int32_t)this->_size &&
		y >= this->_centerY - (int32_t)this->_size && 
		y <= this->_centerY + (int32_t)this->_size)
		return true;
	return false;
}

bool QTreeAABB::contains(int32_t x, int32_t y, uint32_t size){
	if (x + size >= this->_centerX - (int32_t)this->_size &&
		x - size <= this->_centerX + (int32_t)this->_size &&
		y + size >= this->_centerY - (int32_t)this->_size && 
		y - size <= this->_centerY + (int32_t)this->_size)
		return true;
	return false;
}

bool QTreeAABB::intersect(QTreeAABB& aabb){
	bool ret = (aabb._centerX + (int32_t)aabb._size > this->_centerX - (int32_t)this->_size &&
		aabb._centerX - (int32_t)aabb._size < this->_centerX + (int32_t)this->_size &&
		aabb._centerY + (int32_t)aabb._size > this->_centerY - (int32_t)this->_size &&
		aabb._centerY - (int32_t)aabb._size < this->_centerY + (int32_t)this->_size);
	return ret;

}
bool QTreeNode::updateUp(QTreePoints& point, int32_t x, int32_t y){
	//if(this->_boundery->contains(x, y))
	//	return true;
}

bool QTreeNode::remove(QTreePoints& point){
	if(!this->_boundery->contains(point.x, point.y))
		return false;

	for (list<QTreePoints*>::iterator it = _points.begin(); it != _points.end(); it++) {
		if(*it == &point){
			_points.erase(it);
			(*it)->_node = NULL;
			this->merge();
			return true;
		}
	}
	
	if ((_ll && _ll->remove(point)) ||
		(_lr && _lr->remove(point)) ||
		(_ul && _ul->remove(point)) ||
		(_ur && _ur->remove(point))) {
		return true;

	} else {
		//cerr<<"ERROR point not found<<x="<<point.x<<" y="<<point.y<<endl;
		return false;
	}

}

QTreeNode::~QTreeNode() {
	delete _boundery;
	if (_ll)
		delete _ll;
	if (_lr)
		delete _lr;
	if (_ul)
		delete _ul;
	if (_ur)
		delete _ur;
}

bool QTreeNode::insert(QTreePoints& point){
	if(!this->_boundery->contains(point.x, point.y))
		return false;
	if(_points.size() < maxPoints ||
		point.size >= this->_boundery->_size * 2 ||
		this->_boundery->_size < 5000){
		
		_points.push_back(&point);
		point._node = this;
		_size = _points.size();
		return true;
	}
	
	if (this->_ur == NULL)
		this->subdevide();
	_size = _points.size();
	if (this->_ll->insert(point)) return true;
	if (this->_lr->insert(point)) return true;
	if (this->_ul->insert(point)) return true;
	if (this->_ur->insert(point)) return true;
	
	cerr<<"QTreeNode::insert error insert"<<endl;
	return false;
}

void QTreeNode::queryRange(list<QTreePoints*>& ret, QTreeAABB& range, uint32_t* counter){
	(*counter)++;
	if(!this->_boundery->intersect(range)){
		//cerr<<"intersect"<<endl;
		return;
	}
	
	for(list<QTreePoints*>::iterator it = _points.begin(); it != _points.end(); it++){
		if( range.contains((*it)->x, (*it)->y, (*it)->size))
			ret.push_back(*it);
	}
	
	if (this->_ur == NULL)
		return;
	
	this->_ll->queryRange(ret, range, counter);
	this->_lr->queryRange(ret, range, counter);
	this->_ul->queryRange(ret, range, counter);
	this->_ur->queryRange(ret, range, counter);
	
	return;
}

void QTreeNode::subdevide(){
	//cerr<<"subdevide"<<endl;
	uint32_t hsize = this->_boundery->_size / 2;
	this->_ll = new QTreeNode(this->_boundery->_centerX - hsize, this->_boundery->_centerY - hsize, hsize);
	this->_lr = new QTreeNode(this->_boundery->_centerX + hsize, this->_boundery->_centerY - hsize, hsize);
	this->_ul = new QTreeNode(this->_boundery->_centerX - hsize, this->_boundery->_centerY + hsize, hsize);
	this->_ur = new QTreeNode(this->_boundery->_centerX + hsize, this->_boundery->_centerY + hsize, hsize);
}

uint32_t QTreeNode::count(){
	
if (_ur)
	return _points.size() +
		_ll->count() +
		_lr->count() + 
		_ul->count() + 
		_ur->count();
else
	return _points.size();
}

uint32_t QTreeNode::boxCount(){
	
if (_ur)
	return 1 +
		_ll->boxCount() +
		_lr->boxCount() + 
		_ul->boxCount() + 
		_ur->boxCount();
else
	return 1;
}

void QTreeNode::merge(){
	
	if (_ur && _points.size() <= maxPoints / 4){
		//cerr<<"merge"<<endl;
		_ll->merge();
		_lr->merge();
		_ul->merge();
		_ur->merge();	
	}

	if (_ur 
		&& !_ll->_ur
		&& !_lr->_ur
		&& !_ul->_ur 
		&& !_ur->_ur 
		&& _points.size() +
		_ll->_points.size() +
		_lr->_points.size() + 
		_ul->_points.size() + 
		_ur->_points.size() < maxPoints / 2) {


		
		_points.merge(_ll->_points);
		_points.merge(_lr->_points);
		_points.merge(_ul->_points);
		_points.merge(_ur->_points);
		for(list<QTreePoints*>::iterator it = _points.begin(); it != _points.end(); it++){
			(*it)->_node = this;
		}
		delete _ll;
		delete _lr;
		delete _ul;
		delete _ur;
		_ll = NULL;
		_lr = NULL;
		_ul = NULL;
		_ur = NULL;

	}

}