//******************************************************************
//
// printvbus.c
//
// (c) Wolfgang Kutscherauer
// 
// output functions for VBus Data from paket.
// the propper funktion will be selected depending on #define statements
//
//******************************************************************

#include <stdio.h>

#include "datatypes.h"
#include "printvbus.h"

#ifdef DS_E_CONTROLLER
void print_vbus_data(Data_Packet *data)
{
    short dow, h, m;
    m = data->DSECtrlPkt.SystemTime % 60;
    dow = data->DSECtrlPkt.SystemTime / 1440;
    h = (data->DSECtrlPkt.SystemTime - 1440*dow) / 60;
    
//    /*
    printf("Tag der Woche    %d\n", dow);
    printf("SystemTime:      %d\n", data->DSECtrlPkt.SystemTime);
    printf("Zeit:         %02d:%02d\n", h, m);
    printf("Jahr:                %4d\n", data->DSECtrlPkt.Year);
    printf("Monat:               %2d\n", data->DSECtrlPkt.Month);
    printf("Tag:                 %2d\n", data->DSECtrlPkt.Day);
    printf("Kollektor:           %.1f °C\n", data->DSECtrlPkt.TempSensor01 * 0.1);
    printf("Speicher mitte:      %.1f °C\n", data->DSECtrlPkt.TempSensor02 * 0.1);
    printf("Speicher unten:      %.1f °C\n", data->DSECtrlPkt.TempSensor04 * 0.1);
    printf("Wäremtauscher:       %.1f °C\n", data->DSECtrlPkt.TempSensor03 * 0.1);
    printf("Kollektor Pumpe:     %d %%\n", data->DSECtrlPkt.PumpSpeed1);
    printf("Wäremtauscher Pumpe: %d %%\n", data->DSECtrlPkt.PumpSpeed2);
    printf("Aktor 3: %d %%\n", data->DSECtrlPkt.PumpSpeed3);
    printf("Umschaltventil:      %d \n", data->DSECtrlPkt.PumpSpeed4);
    printf("Aktor 5: %d %%\n", data->DSECtrlPkt.PumpSpeed5);
    printf("Aktor 6: %d %%\n", data->DSECtrlPkt.PumpSpeed6);
    printf("Aktor 7: %d %%\n\n\n", data->DSECtrlPkt.PumpSpeed7);
//*/ 
// CSV Output
    /*
    printf("%d-%d-%d;", data->DSECtrlPkt.Year, data->DSECtrlPkt.Month, data->DSECtrlPkt.Day);
    printf("%02d;", data->DSECtrlPkt.SystemTime);
    printf("%d;%d;%d;%d;", data->DSECtrlPkt.TempSensor01, data->DSECtrlPkt.TempSensor02, data->DSECtrlPkt.TempSensor03, data->DSECtrlPkt.TempSensor04);
    //printf("%d;%d;%d;%d;%d;", data->DSECtrlPkt.TempSensor06, data->DSECtrlPkt.TempSensor07, data->DSECtrlPkt.TempSensor08, data->DSECtrlPkt.TempSensor09, data->DSECtrlPkt.TempSensor10);
    printf("%d;%d;%d;%d;%d;%d;%d;%d;", data->DSECtrlPkt.Irradiation, data->DSECtrlPkt.PumpSpeed1, data->DSECtrlPkt.PumpSpeed2,  data->DSECtrlPkt.PumpSpeed3, data->DSECtrlPkt.PumpSpeed4, data->DSECtrlPkt.PumpSpeed5, data->DSECtrlPkt.PumpSpeed6, data->DSECtrlPkt.PumpSpeed7);
    printf("%d;%d;%d;%d;%d;%d;%d;", data->DSECtrlPkt.Unused1 ,  data->DSECtrlPkt.Unused2 ,  data->DSECtrlPkt.Unused3 ,  data->DSECtrlPkt.ErrorMask  ,  data->DSECtrlPkt.Messages  , data->DSECtrlPkt.Messages, data->DSECtrlPkt.Scheme);
    printf("%d;%d;%d;%d;%d;", data->DSECtrlPkt.SetPointHC1ModuleSensor18  , data->DSECtrlPkt.StatusHC1Module  , data->DSECtrlPkt.SetPointHCModuleSensor25  , data->DSECtrlPkt.StatusHC2Module  , data->DSECtrlPkt.SetPointHC3ModuleSensor25);
    printf("%d;%d;%d\n", data->DSECtrlPkt.StatusHC3Module , data->DSECtrlPkt.Unused4 , data->DSECtrlPkt.Unused5 );
    */
}
#endif

#ifdef DS_BS_PLUS
void print_vbus_data(Data_Packet *data)
{
   printf("\nSystem time:%02d:%02d"
                        ", Sensor1 temp:%.1fC"
                        ", Sensor2 temp:%.1fC"
                        ", Sensor3 temp:%.1fC"
                        ", Sensor4 temp:%.1fC"
                        ", Pump speed1:%d%%"
                        ", Pump speed2:%d%%"
                        //", RelayMask:%d"
                        //", ErrorMask:%d"
                        //", Scheme:%d, %d, %d, %d, %d, %d, %d"
                        ", Hours1:%d, Hours2:%d"
                        //", %dWH, %dkWH, %dMWH"
                        //", Version:%.2f"
                        "\n",
                        data->bsPlusPkt.SystemTime / 60,
                        data->bsPlusPkt.SystemTime % 60,
                        data->bsPlusPkt.TempSensor1 * 0.1,
                        data->bsPlusPkt.TempSensor2 * 0.1,
                        data->bsPlusPkt.TempSensor3 * 0.1,
                        data->bsPlusPkt.TempSensor4 * 0.1,
                        data->bsPlusPkt.PumpSpeed1,
                        data->bsPlusPkt.PumpSpeed2,
                        //data->bsPlusPkt.RelayMask,
                        //data->bsPlusPkt.ErrorMask,
                        //data->bsPlusPkt.Scheme,
                        //data->bsPlusPkt.OptionCollectorMax,
                        //data->bsPlusPkt.OptionCollectorMin,
                        //data->bsPlusPkt.OptionCollectorFrost,
                        //data->bsPlusPkt.OptionTubeCollector,
                        //data->bsPlusPkt.OptionRecooling,
                        //data->bsPlusPkt.OptionHQM,
                        data->bsPlusPkt.OperatingHoursRelay1,
                        data->bsPlusPkt.OperatingHoursRelay2
                        //data->bsPlusPkt.HeatQuantityWH,
                        //data->bsPlusPkt.HeatQuantityKWH,
                        //data->bsPlusPkt.HeatQuantityMWH
                        //data->bsPlusPkt.Version * 0.01
                    );
    
    
}
#endif
