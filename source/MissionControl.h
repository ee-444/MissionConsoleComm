// $Id$  

/**  

  * @file MissionControl.h  
  * The header file for class Cmissioncontrol.  This is a class to handle communication
  * with the host PC running the MissionControl software
  *  
  * @brief This file contains the class resources for Cmissioncontrol - communication software 
  *  
  * @author sgrove   
  *
  * @version 1.01   
  *
  */  

// $Log$ 

#ifndef MISSIONCONTROL_H
#define MISSIONCONTROL_H

#include "ArduinoLib.h"

#ifndef FOSC
#define FOSC 16000000 // Clock Speed
#endif
#define UART_BAUD		57600
#define REG_BAUD_VAL 	FOSC/16/UART_BAUD-1

//! scope for peripheral library driver software
namespace ArduinoLibrary{

//! Mission Console communication class definition
class Cmissioncontrol{

private:
	// functions that are used for transmitting
	void write(char*);
	void write(uint8_t);
	
public:
 	
	/**  
    	This is the default constructor for the Cmissioncontrol class.
  	*/ 
	Cmissioncontrol();

	/**  
    	This is the default deconstructor for the Cmissioncontrol class.
  	*/ 
	~Cmissioncontrol();	

	/**  
    	Used to enable communication.  This must be called before any transmitting
		members are called
  	*/ 
	void enable();

	/**  
    	Used to disable communication.  If a partial transmission in taking place it
		will be dropped or partially sent
  	*/ 
	void disable();
	
	/**  
    	Send an analog to digital result value to the debugging console.  This is
		stored in the a_d_log.csv file if it is capturing

		@param[in]	in - A 10-bit analog to digital result for any conversion
  	*/ 
	void adValue(uint16_t in);

	/**  
    	Send the Long Range IR result to to the debugging console
		
		@param[in]	in - A 10-bit analog to digital result for the long range IR sensor
  	*/ 
	void longRangeIR(uint16_t in);

	/**  
    	Send the Medium Range IR result to to the debugging console
		
		@param[in]	in - A 10-bit analog to digital result for the meduim range IR sensor
  	*/ 
	void mediumRangeIR(uint16_t in);
		
	
};

};	// end of namespace

#endif
