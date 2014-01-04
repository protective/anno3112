/* 
 * File:   SSingleFac.h
 * Author: karsten
 *
 * Created on 15. september 2011, 09:46
 */

#ifndef SSINGLEFAC_H
#define	SSINGLEFAC_H
#include "../../SFunctions.h"
class SSubSystemFac;
class SSingleFac {
public:
	SSingleFac(SSubSystemFac* subsys);
	void proces();
	int32_t getDuration(){return _cur;}
	virtual ~SSingleFac();
private:
	int32_t _cur;
	int32_t _charge;
	SSubSystemFac* subsys;
	
};

typedef map<uint32_t,SSingleFac*>::iterator SSingleFacI;


#endif	/* SSINGLEFAC_H */

