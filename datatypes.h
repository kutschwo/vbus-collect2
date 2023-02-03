//******************************************************************************************************************
// datatypes.h
//
// (c) Hewell Technology Ltd. 2014
//
// Tobias Tangemann 2020
// Wolfgang Kutscherauer 2023
// Modifikation to deal with different types of VBus devices
// Define a structure / union for the VBus data depending on the VBus device
// 
//*******************************************************************************************************************

#ifndef DATATYPES_H
#define DATATYPES_H

//#define DS_E_CONTROLLER

#ifdef DS_BS_PLUS
#include "vbus/DS_BS_Plus.h"
#endif

#ifdef DS_E_CONTROLLER
#include "vbus/DS_E_Controller.h"
#endif


#endif
