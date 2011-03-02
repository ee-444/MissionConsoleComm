 /*! @mainpage MainPage for the Mission Console class!
 *
 * @section intro_sec Introduction
 *
 *	This class is part of the Peripheral Library collection 
 *	for the Arduino Mars Rover project.  The source code is 
 *	downloadable from https://github.com/ee-444/MissionConsoleComm
 *
 * @section install_sec Bugs
 *
 * @subsection step1 Known Bugs: Release 1.01
 *
 * No known bugs.
 */


/** @example main.cpp
 * This is an example of how to use the ArduinoLibrary::Cmissioncontrol class.
 */

#include "ArduinoLib.h"

// declare the mission console object
ArduinoLibrary::Cmissioncontrol mission_console;

int main (void)
{
	// varialbes for temporary testing 
	// of the data packets
	uint8_t inc_tx = 1;
	uint8_t tx_cnt = 0;

	// Allow commumication throught the defined channel
	mission_console.enable();
	
	while(1){

		// delay for some time
		for (uint32_t i=0; i<110000; i++){
			i += 2;
		}

		// send data to the console
		mission_console.longRangeIR(inc_tx++);
		mission_console.mediumRangeIR(0xff-inc_tx);
		mission_console.adValue(inc_tx);

		// increment the value to make a change in the display
		tx_cnt++;

	}

	// deconstruct the object
	mission_console.~Cmissioncontrol();
}
