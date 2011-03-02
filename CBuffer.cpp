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

#include "CBuffer.h"

//! scope for peripheral driver software
namespace ArduinoLibrary{

CBuffer8_t::CBuffer8_t(uint16_t in)
{
	// make sure we are starting off 
	// with an empty and initialized buffer
	buf_t.rptr = 0x0;
	buf_t.wptr = 0x0;
	// build the object on the heap
	buf_t.data = (uint8_t*)calloc(in, sizeof(uint8_t));
	heap_base = buf_t.data;
	BUFFER_SIZE = in;
}

CBuffer8_t::~CBuffer8_t()
{
	free(heap_base);
}

uint8_t CBuffer8_t::IsReadable(void)
{
  	// do we have unread data??
	if(buf_t.rptr != buf_t.wptr){
		// roll over has occured in the queue
		if (buf_t.wptr < buf_t.rptr)
			return ((BUFFER_SIZE - buf_t.rptr) + buf_t.wptr);
		// roll over has not occured in the queue
		else
			return (buf_t.wptr - buf_t.rptr);
	}
	// nothing to read
	return 0x0;
}

uint8_t CBuffer8_t::IsWriteable()
{
	// Assuming that Readable works - we can 
	// subtract it from the max buffersize
	return (BUFFER_SIZE - IsReadable());
}

uint8_t CBuffer8_t::RawRead(void)
{
	uint8_t tmp_rtn = buf_t.data[buf_t.rptr++];
	// if the queue hits the limit roll over
	if (buf_t.rptr == BUFFER_SIZE)
		buf_t.rptr = 0x0;
	// pass the data back
	return tmp_rtn;
}

void CBuffer8_t::RawWrite(uint8_t data)
{
	buf_t.data[buf_t.wptr++] = data;
	// prepare for the next access
	if (buf_t.wptr == BUFFER_SIZE)
		buf_t.wptr = 0;
}

uint8_t CBuffer8_t::ReadSingle(void)
{
	// dont read if there is nothing available
	if (!IsReadable())
		return 0x0;
	uint8_t tmp_rtn = buf_t.data[buf_t.rptr++];
	// if the queue hits the limit roll over
	if (buf_t.rptr == BUFFER_SIZE)
		buf_t.rptr = 0x0;
	// pass the data back
	return tmp_rtn;
}

uint8_t CBuffer8_t::ReadBlock(uint8_t* data, uint32_t amount)
{ 
	uint32_t data_amt = IsReadable();
	if (data_amt == 0)
		return 0x0;
	// something exists, and the caller wants
	// less than is available for read
	if (amount < data_amt){
		for (uint32_t  i=0; i<amount; i++)
			data[i] = RawRead();
		// return the amount that was read
		return amount;
	}
	// There is less in the buffer than the 
	// caller is asking for - give them what
	// is available
	for (uint32_t i=0; i<data_amt; i++)
		data[i] = RawRead();
	// return the amount that was in the buffer
	return data_amt;
}

uint8_t CBuffer8_t::ReadTo(uint8_t* data, uint8_t limit)
{
	// dont bother if the buffer is empty
	if (!IsReadable())
		return 0x0;
	// make a copy of the readpointer for seeking
	uint8_t ent_rptr, tmp_rptr;
	ent_rptr = tmp_rptr = buf_t.rptr;
	// this is the more difficult transaction
	// this will need 2 seperate memory checks
	// unless the limit is found on the first 
	// transaction
	if (buf_t.wptr < buf_t.rptr){
		// first check occurs up to the buffer 
		// size limit
		uint32_t lft_justify = 0;
		while(tmp_rptr < BUFFER_SIZE){
			// found a match before the buffer roll over
			if (limit == buf_t.data[tmp_rptr]){
				for (uint32_t i=ent_rptr; i<=tmp_rptr; i++)
					data[lft_justify++] = RawRead();
				// all loaded up, return the amount read
				return (tmp_rptr + 0x1);
			}
			// increment for the next pass
			tmp_rptr++;
		}
		// store the previous amount read
		uint8_t first_try = (tmp_rptr - ent_rptr);
		ent_rptr = tmp_rptr = 0;
		// the second check starts at buffer location 0
		// and should not surpass the write location
		while (tmp_rptr != buf_t.wptr){
		 	// found the match
			if (limit == buf_t.data[tmp_rptr]){
				for (uint32_t i=ent_rptr; i<=(tmp_rptr+first_try); i++)
					data[i] = RawRead();
				// all loaded up, return the amount read
				return ((tmp_rptr + first_try) + 0x1);	
			}
			// increment for the next pass
			tmp_rptr++;
		}
	}
	// straight forward transaction, the queue
	// has not rolled over
	while (tmp_rptr != buf_t.wptr){
		// found the match, now load up the 
		// data into the caller supplied pointer
		uint8_t lft_justify = 0;
		if (limit == buf_t.data[tmp_rptr]){
			for (uint32_t i=ent_rptr; i<=tmp_rptr; i++)
				data[lft_justify++] = RawRead();
			// all loaded up, return the amount read
			return ((tmp_rptr - ent_rptr) + 0x1);
		}
		// increment for the next pass
		tmp_rptr++;
	}
	// default error return
	return 0x0;
}

uint8_t CBuffer8_t::WriteBuff(uint8_t data)
{
	// make sure the buffer is not full
	if (!IsWriteable())
		return 0x0;
	buf_t.data[buf_t.wptr++] = data;
	// prepare for the next access
	if (buf_t.wptr == BUFFER_SIZE)
		buf_t.wptr = 0;
	return 0x1;
}

uint8_t CBuffer8_t::WriteBuff(uint8_t* data, uint32_t amount)
{
	// make sure there is enough room for 
	// the requested transaction
	uint8_t tmp_amt = IsWriteable();
	// there is enough room
	if (tmp_amt > amount){
		for (uint32_t i=0; i<amount; i++)
			RawWrite(data[i]);
		// return the amount that was written
		return amount;
	}
	// indicate to caller that the was no write
	return 0x0;
}

uint8_t CBuffer8_t::WriteBuff(char* data)
{
	// Find out how much room is available
	// in the buffer
	uint8_t tmp_amt = IsWriteable();
	uint8_t tmp_len = strlen(data);
	// If there is room proceed with the write
	if (tmp_amt > tmp_len){
		for (uint32_t i=0; i<tmp_len; i++)
			RawWrite(data[i]);
		return tmp_len;
	}
	// indicate to caller that the read did 
	// not take place
	return 0x0;
}

}; 	// end the namespace



