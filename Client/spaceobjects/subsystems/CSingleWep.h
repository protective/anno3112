/* 
 * File:   CSingleWep.h
 * Author: karsten
 *
 * Created on 31. juli 2011, 23:36
 */

#ifndef CSINGLEWEP_H
#define	CSINGLEWEP_H
#include "../../CFunctions.h"
class CSubSystemW;
class CSingleWep {
public:
	CSingleWep(CSubSystemW* subsys);
	void proces(uint32_t DTime);
	void setDuration(int32_t value){this->_cur = value;}
	int32_t getDuration(){return this->_cur;}
	virtual ~CSingleWep();
private:
	CSubSystemW* subsys;
	int32_t _cur;
	int32_t _charge;
};
typedef map<uint32_t,CSingleWep*>::iterator CSingleWI;
#endif	/* CSINGLEWEP_H */

