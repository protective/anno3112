/* 
 * File:   SSingleRef.h
 * Author: karsten
 *
 * Created on 23. marts 2012, 23:51
 */

#ifndef SSINGLEREF_H
#define	SSINGLEREF_H
#include "../../SFunctions.h"
#include "../../SItems/SItemType.h"
class SSubSystemRef;

class SSingleRef {
public:
	SSingleRef(SSubSystemRef* subsys);
	void proces();
	int32_t getDuration(){return _cur;}
	void Refine(SItemType* item);
	virtual ~SSingleRef();
private:
	int32_t _cur;
	SItemType* _curitem;
	int32_t _charge;
	SSubSystemRef* subsys;
};

typedef map<uint32_t,SSingleRef*>::iterator SSingleRefI;


#endif	/* SSINGLEREF_H */

