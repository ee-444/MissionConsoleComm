// $Id$  

/**  

  * @file Cbuffer.h  
  * The header file for class CBuffer8_t.  This is a class to handle digital communication
  * with the host PC running the MissionControl software.  It buffers the request until the 
  * hardware is able to access.
  *  
  * @brief This file contains the class definition for CBuffer8_t - communication tool  
  *  
  * @author sgrove   
  *
  * @version 1.01   
  *
  */  

// $Log$ 

#ifndef CBUFFER_H
#define CBUFFER_H

#include "ArduinoLib.h"

//! scope for peripheral driver software
namespace ArduinoLibrary{

typedef struct{
	uint8_t wptr;
	uint8_t rptr;
	uint8_t* data;
}BUF_T;

class CBuffer8_t
{
private:
	// unprotected read and write methods
	uint8_t RawRead(void);
	void RawWrite(uint8_t);
	volatile BUF_T buf_t;
	uint8_t BUFFER_SIZE;
	uint8_t* heap_base;

public:
	CBuffer8_t(uint16_t);
	~CBuffer8_t();
	// How much data is available??
	uint8_t IsReadable();
	// How much Write space is available??
	uint8_t IsWriteable();
	// ways to read - single byte return
	uint8_t ReadSingle(void);
	// read a specific amount from the buffer
	uint8_t ReadBlock(uint8_t*, uint32_t);
	// read up to a specific byte in the buffer
	uint8_t ReadTo(uint8_t*, uint8_t);
	// various ways to write data
	uint8_t WriteBuff(uint8_t);
	uint8_t WriteBuff(uint8_t*, uint32_t);
	uint8_t WriteBuff(char*);
};

}; 	// end the namespace

#endif
