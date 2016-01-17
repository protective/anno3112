/* 
 * File:   Destiny.cpp
 * Author: karsten
 * 
 * Created on 16. august 2015, 20:56
 */

#include "Destiny.h"
#include "../../Sspacebjects/SObj.h"

Destiny::Destiny() {
	pthread_mutex_init(&this->_lock, NULL);
	root = new QTreeNode(0,0, 16777216);
}

void Destiny::remove(SObj* obj){
pthread_mutex_lock(&this->_lock);

	if(obj->getPos().grid){
		for(int i = 0; i < 4; i++){
			root->remove(obj->getPos()._boundPoints[i]);
		}
		delete [] obj->getPos()._boundPoints;
		_pos.erase(obj->getId());
		//root->merge();
		cerr<<"size = "<<root->count()<<"box size=" <<root->boxCount()<<endl;
	}

pthread_mutex_unlock(&this->_lock);
}
void Destiny::update(SObj* obj){

pthread_mutex_lock(&this->_lock);

	if(obj->getPos().grid){
		if(!obj->getPos()._boundPoints){
			obj->getPos()._boundPoints = new QTreePoints[4];
			for(int i = 0; i < 4; i++){
				obj->getPos()._boundPoints[i]._node = NULL;
				obj->getPos()._boundPoints[i].obj = obj->getId();
				obj->getPos()._boundPoints[i].size = obj->getSize();
			}
		}
		QTreePoints* bp = obj->getPos()._boundPoints;
		uint32_t size2 = obj->getSize() / 2;

		int32_t tX, tY;

		for(int i = 0; i < 4; i++){

			switch (i) {
				case 0: {
					tX = obj->getPos().x - size2;
					tY = obj->getPos().y - size2;
					break;
				}
				case 1: {
					tX = obj->getPos().x + size2;
					tY = obj->getPos().y - size2;
					break;
				}
				case 2: {
					tX = obj->getPos().x + size2;
					tY = obj->getPos().y + size2;
					break;
				}
				case 3: {
					tX = obj->getPos().x - size2;
					tY = obj->getPos().y + size2;		
					break;
				}
			}
			if (!bp[i]._node) {
				bp[i].x = tX;
				bp[i].y = tY;
				root->insert(bp[i]);
			} else if (bp[i]._node->_boundery->contains(tX, tY)) {
				bp[i].x = tX;
				bp[i].y = tY;
			} else {

				root->remove(bp[i]);
				bp[i].x = tX;
				bp[i].y = tY;
				root->insert(bp[i]);
			}
		}
		SPos* tmpPos = &_pos[obj->getId()];
		tmpPos->x = obj->getPos().x;
		tmpPos->y = obj->getPos().y;
		tmpPos->z = obj->getPos().z;
		tmpPos->d = obj->getPos().d;
		tmpPos->grid = obj->getPos().grid;
	}

pthread_mutex_unlock(&this->_lock);
}

list<OBJID> Destiny::collide(SObj* obj){
	list<OBJID> ret;
pthread_mutex_lock(&this->_lock);
	list<QTreePoints*> queryret;
	QTreeAABB range(obj->getPos().x, obj->getPos().y, obj->getSize());
	uint32_t test = 0;
	root->queryRange(queryret, range, &test);
	//cerr<<"counter ="<<test<<endl;
	for (list<QTreePoints*>::iterator it = queryret.begin(); it != queryret.end(); it++){
		if((*it)->obj != obj->getId()){
			ret.push_back((*it)->obj);
		}
	}
	if(ret.size() > 0){
		cerr<<"hit "<<ret.size()<<endl;
	}
	
pthread_mutex_unlock(&this->_lock);
	return ret;
}

bool Destiny::getPos(SPos& set, OBJID id){
	bool ret = false;
	pthread_mutex_lock(&this->_lock);
	if (_pos.find(id) != _pos.end()) {
		set.x = _pos[id].x;
		set.y = _pos[id].y;
		set.z = _pos[id].z;
		set.d = _pos[id].d;
		set.grid = _pos[id].grid;
		set._boundPoints = NULL;
		ret = true;
	}
	pthread_mutex_unlock(&this->_lock);
	return ret;
}

list<OBJID> Destiny::inRange(SObj* obj, uint32_t range ){
	//cerr<<"range <<"<<range<<endl;
	list<OBJID> ret;
pthread_mutex_lock(&this->_lock);
	list<QTreePoints*> queryret;
	QTreeAABB boxrange(obj->getPos().x, obj->getPos().y, range);
	uint32_t test = 0;

	root->queryRange(queryret, boxrange, &test);
		//cerr<<"counter ="<<test<<endl;
	for (list<QTreePoints*>::iterator it = queryret.begin(); it != queryret.end(); it++){
		if((*it)->obj != obj->getId()){
			//cerr<<(*it)->obj<<endl;
			ret.push_back((*it)->obj);
		}
	}
	ret.sort();
	ret.unique();

pthread_mutex_unlock(&this->_lock);
	return ret;
}



Destiny::~Destiny() {
}

