/* 
 * File:   SProgrammable.h
 * Author: karsten
 *
 * Created on 24. september 2014, 19:34
 */

#ifndef SPROGRAMMABLE_H
#define	SPROGRAMMABLE_H

class SProgrammable  {
public:
	virtual void interrupt(uint32_t programId, uint32_t handlerId, uint32_t* payload, uint32_t payloadLen) = 0;
protected:
	uint32_t _interruptProgramID;
	uint32_t _interruptcallbackHandler;
	uint32_t* _interruptpayload;

};

#endif	/* SPROGRAMMABLE_H */

