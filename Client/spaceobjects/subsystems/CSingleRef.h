/* 
 * File:   CSingleRef.h
 * Author: karsten
 *
 * Created on 24. marts 2012, 18:54
 */

#ifndef CSINGLEREF_H
#define	CSINGLEREF_H

#include "../../CFunctions.h"


class CSubSystemRef;
class CSingleRef {
public:
	CSingleRef(CSubSystemRef* subsys);
	void setDuration(int32_t value){this->_cur = value;}
	void proces(uint32_t DTime);
	int32_t getDuration(){return _cur;}
	virtual ~CSingleRef();
private:
	int32_t _cur;
	int32_t _charge;
	CSubSystemRef* subsys;
};

typedef map<uint32_t,CSingleRef*>::iterator CSingleRefI;

#endif	/* CSINGLEREF_H */

