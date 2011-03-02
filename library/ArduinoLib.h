// $Id$  

/**  

  * @file ArduinoLib.h  
  * The header file for namespace and global includes when using ArduinoLibrary and its
  *	collective sources.  
  *  
  * @brief This file contains the namespace inplementation and header file collection
  * that is needed for easy project incorporation and management
  *  
  * @author sgrove   
  *
  * @version 1.01   
  *
  */ 

// $Log$ 


#ifndef ARDUINOLIB_H
#define ARDUINOLIB_H

//! Useful C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//! MCU IO library and defines
#include <avr/io.h>
#include "ArduinoPins.h"

//! Members of the Library
//#include "Cio.h"
#include "MissionControl.h"

//! Declaration of the namespace
//using namespace ArduinoLibrary;

#endif
