// $Id$  

/**  

  * @file ArduinoPins.h  
  * This header file is for enumeration types that are used and associated with Arduino 
  *	peripheral classes that reside in the ArduinoLibrary namespace.
  *  
  * @brief This file contains enumeration types for use with in the ArduinoLibrary namespace.
  *  
  * @author sgrove   
  *
  * @version 1.01   
  *
  */ 

// $Log$ 

#ifndef ARDUINOPINS_H
#define ARDUINOPINS_H

namespace ArduinoLibrary{

//! Enumerated type for object association with a specific IO pin.
enum PinName{
	PIN_PA0 = 0x000, PIN_PA1, PIN_PA2, PIN_PA3, PIN_PA4, PIN_PA5, PIN_PA6, PIN_PA7,
	PIN_PB0 = 0x100, PIN_PB1, PIN_PB2, PIN_PB3, PIN_PB4, PIN_PB5, PIN_PB6, PIN_PB7,
	PIN_PC0 = 0x200, PIN_PC1, PIN_PC2, PIN_PC3, PIN_PC4, PIN_PC5, PIN_PC6, PIN_PC7,
	PIN_PD0 = 0x400, PIN_PD1, PIN_PD2, PIN_PD3, PIN_PD4, PIN_PD5, PIN_PD6, PIN_PD7,
	PA_BASE = 0x000,
	PB_BASE = 0x100,
	PC_BASE = 0x200,
	PD_BASE = 0x400,
	Px_BASE = 0x800
};

//! Enumerated type for setting up a pin as input or output
enum PinType{
	PINTYPE_INPUT = 0x00, PINTYPE_OUTPUT
};

//! Enumerated type for using the internal pull up circuit
enum BuiltInPullUp{
	PULLUP_DISABLE = 0x00, PULLUP_ENABLE
};

};

#endif
