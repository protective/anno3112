/* 
 * File:   CAstoroidType.h
 * Author: karsten
 *
 * Created on 21. oktober 2011, 20:59
 */

#ifndef CASTOROIDTYPE_H
#define	CASTOROIDTYPE_H
#include "../CFunctions.h"

class CAstoroidType {
public:
	CAstoroidType(uint32_t id);
	uint32_t getSize(){return this->_size;}
	uint32_t getId(){return _id;}
	void setSize(uint32_t size){this->_size = size;}

	uint32_t getTexture(){return this->_texture;}
	void setTexture(uint32_t tex){this->_texture = tex;}

	virtual ~CAstoroidType();
private:
	uint32_t _texture;
	uint32_t _size;
	uint32_t _id;
};

#endif	/* CASTOROIDTYPE_H */

