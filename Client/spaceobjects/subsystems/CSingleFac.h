/* 
 * File:   CSingleFac.h
 * Author: karsten
 *
 * Created on 16. september 2011, 21:38
 */

#ifndef CSINGLEFAC_H
#define	CSINGLEFAC_H

#include "../../CFunctions.h"

class CSubSystemFac;
class CSingleFac {
public:
	CSingleFac(CSubSystemFac* subsys);
	void setDuration(int32_t value){this->_cur = value;}
	void proces(uint32_t DTime);
	int32_t getDuration(){return _cur;}
	virtual ~CSingleFac();
private:
	int32_t _cur;
	int32_t _charge;
	CSubSystemFac* subsys;
	
};
typedef map<uint32_t,CSingleFac*>::iterator CSingleFacI;

#endif	/* CSINGLEFAC_H */

