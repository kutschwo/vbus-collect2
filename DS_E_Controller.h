//*******************************************************************************************************************
// DS_E_Controller.h
//
// (c) Wolfgang Kutscherauer 2023
//
// packet struct for:
// Resol Deltasol E (Controller)
// Identical types from other companies:
// Citrin Solar CS 3.2
//*******************************************************************************************************************

#ifndef DS_E_CONTROLLER_H
#define DS_E_CONTROLLER_H

#pragma pack(1)
typedef union {
  struct {
    short TempSensor01;
    short TempSensor02;
    short TempSensor03;
    short TempSensor04;
    short TempSensor05;
    short TempSensor06;
    short TempSensor07;
    short TempSensor08;
    short TempSensor09;
    short TempSensor10;
    short Irradiation;
    short Impulse_I_V40;
    short Digital_Input;
    unsigned char PumpSpeed1;
    unsigned char PumpSpeed2;
    unsigned char PumpSpeed3;
    unsigned char PumpSpeed4;
    unsigned char PumpSpeed5;
    unsigned char PumpSpeed6;
    unsigned char PumpSpeed7;
    unsigned char Unused1;
    unsigned char Unused2;
    unsigned char Unused3;
    short ErrorMask;
    short Messages;
    unsigned char System;
    unsigned char Unused4;
    short Scheme;
    short SetPointHC1ModuleSensor18;
    short StatusHC1Module;
    short SetPointHCModuleSensor25;
    short StatusHC2Module;
    short SetPointHC3ModuleSensor25;
    short StatusHC3Module;
    short Sensor_11;
    short State_HC;
    unsigned char Unused5;
    unsigned char Unused6;
    unsigned short SystemTime;
    unsigned short Year;
    unsigned char Month;
    unsigned char Day;
  } DSECtrlPkt;
  unsigned char asBytes[68];
} Data_Packet;

#endif
