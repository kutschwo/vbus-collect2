//******************************************************************
//
// tstprintvbus.c
//
// (c) Wolfgang Kutscherauer
// 
// prog to test function PrintVBusData(paket)
//
// compile for Delta Sol E / Citrin Solar CS 3.2
// gcc -DDS_E_CONTROLLER  tstprintvbus.c printvbus.c -o ~/tstprintvbus
// 
// compile for Delta Sol BS Plus
// gcc -DDS_BS_PLUS  tstprintvbus.c printvbus.c -o ~/tstprintvbus
//
//
//*******************************************************************
//#define DS_E_CONTROLLER

#include <stdio.h>
#include "datatypes.h"
#include "printvbus.h"

int main(int argc, char *argv[])
{
    printf("test prog for PrintVBusData()\n");

    Data_Packet packet; 
    packet.DSECtrlPkt.TempSensor01 = 810;
    packet.DSECtrlPkt.TempSensor02 = 1223;
    packet.DSECtrlPkt.PumpSpeed1 = 50;
    packet.DSECtrlPkt.PumpSpeed2 = 70;

    print_vbus_data(&packet);
    printf("\n\n\n");
    print_vbus_data(&packet);
}
