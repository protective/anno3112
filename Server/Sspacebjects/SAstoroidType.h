/* 
 * File:   SAstoroidType.h
 * Author: karsten
 *
 * Created on 21. oktober 2011, 19:26
 */

#ifndef SASTOROIDTYPE_H
#define	SASTOROIDTYPE_H
#include "../SFunctions.h"
#include "../SItems/SItemType.h"

class SAstoroidType {
public:
	SAstoroidType(uint32_t id);

	uint32_t getId(){return this->_id;}
	void setName(string name){this->_name = name;}

	void setItemType(SItemType* itemType){this->_itemType = itemType;}
	SItemType* getItemType(){return this->_itemType;}
	
	uint32_t getMminQuan(){return this->_minQuan;}
	uint32_t getMaxQuan(){return this->_maxQuan;}

	uint32_t getSize(){return this->_size;}

	void setSize(uint32_t size){this->_size = size;}
	void settexture(uint32_t texture){this->_texture = texture;}
	uint32_t gettexture(){return this->_texture;}

	void setMinQuan(uint32_t quan){this->_minQuan = quan;}
	void setMaxQuan(uint32_t quan){this->_maxQuan = quan;}

	uint32_t getItemTypeId(){return this->_itemType->getTypeID();}
	//void setItemTypeId(uint32_t id){this->_itemTypeId = id;}

	virtual ~SAstoroidType();
private:
	uint32_t _id;
	SItemType* _itemType;
	uint32_t _size;
	string _name;
	uint32_t _texture;
	uint32_t _maxQuan;
	uint32_t _minQuan;
};

#endif	/* SASTOROIDTYPE_H */

