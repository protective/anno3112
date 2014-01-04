/* 
 * File:   CGrid.h
 * Author: karsten
 *
 * Created on 8. februar 2012, 19:27
 */

#ifndef CGRID_H
#define	CGRID_H
#include "../CFunctions.h"
class CGrid {
public:
	CGrid(uint32_t id, uint32_t spaceWight, uint32_t spaceHight);
	uint32_t _id;
	uint32_t getWight(){return this->_spaceWight;}
	uint32_t getHight(){return this->_spaceHight;}
	virtual ~CGrid();
private:
	uint32_t _spaceWight;
	uint32_t _spaceHight;
};

#endif	/* CGRID_H */

