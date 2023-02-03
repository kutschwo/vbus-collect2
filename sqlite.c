//****************************************************************************
// sqlite.c
//
// Tobias Tangemann 2020
// 
// function to publish data to sqlite database
// implementation
//
//****************************************************************************
#include <sqlite3.h>
#include <stdio.h>

#include "sqlite.h"

static sqlite3 *db = NULL;

void sqlite_print_error(char* error_msg)
{
  printf("SQL error: %s\n", error_msg);
  sqlite3_free(error_msg);
}

bool sqlite_open(const char *path)
{
  if (sqlite3_open(path, &db) != 0)
  {
    printf("Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite_close();
    return false;
  }

  return true;
}


void sqlite_close()
{
  if (db != NULL)
  {
    sqlite3_close(db);
  }
}


bool sqlite_exec(char* sql)
{
  char *error_msg;

  if (sqlite3_exec(db, sql, NULL, 0, &error_msg) != SQLITE_OK) {
    sqlite_print_error(error_msg);
    return false;
  }

  return true;
}


bool sqlite_insert_data(Data_Packet* packet)
{
  char *error_msg;
  char sql_buffer[256];
  //    short dow, h, m;


#ifdef DS_E_CONTROLLER
   // m = data->DSECtrlPkt.SystemTime % 60;
   // dow = data->DSECtrlPkt.SystemTime / 1440;
   // h = (data->DSECtrlPkt.SystemTime - 1440*dow) / 60
    sprintf(sql_buffer, "INSERT INTO dsectrl "
    "(system_time, temp1, temp2, temp3, temp4, pump1, pump2,pump4) VALUES "
    "(datetime('now','localtime'), %.1f, %.1f, %.1f, %.1f, %d, %d, %d);",
    packet->DSECtrlPkt.TempSensor01 * 0.1,
    packet->DSECtrlPkt.TempSensor02 * 0.1,
    packet->DSECtrlPkt.TempSensor03 * 0.1,
    packet->DSECtrlPkt.TempSensor04 * 0.1,
    packet->DSECtrlPkt.PumpSpeed1,
    packet->DSECtrlPkt.PumpSpeed2,
    packet->DSECtrlPkt.PumpSpeed4);
#endif
  
#ifdef DS_BS_PLUS
  sprintf(sql_buffer, "INSERT INTO data "
    "(system_time, temp1, temp2, temp3, temp4, pump1, pump2, hours1, hours2) VALUES "
    "(\"%02d:%02d\", %.1f, %.1f, %.1f, %.1f, %d, %d, %d, %d);",
    packet->bsPlusPkt.SystemTime / 60,
    packet->bsPlusPkt.SystemTime % 60,
    packet->bsPlusPkt.TempSensor1 * 0.1,
    packet->bsPlusPkt.TempSensor2 * 0.1,
    packet->bsPlusPkt.TempSensor3 * 0.1,
    packet->bsPlusPkt.TempSensor4 * 0.1,
    packet->bsPlusPkt.PumpSpeed1,
    packet->bsPlusPkt.PumpSpeed2,
    packet->bsPlusPkt.OperatingHoursRelay1,
    packet->bsPlusPkt.OperatingHoursRelay2);
#endif
  if (sqlite3_exec(db, sql_buffer, NULL, 0, &error_msg) != 0)
  {
    sqlite_print_error(error_msg);
    return false;
  }

  return true;
}

#ifdef DS_E_CONTROLLER
bool sqlite_create_table()
{
  char *error_msg;
  char sql_create_table[] = "CREATE TABLE IF NOT EXISTS dsectrl ("
    "\"id\"          INTEGER PRIMARY KEY AUTOINCREMENT,"
    "\"time\"        DEFAULT CURRENT_TIMESTAMP NOT NULL,"
    "\"system_time\" TEXT NOT NULL,"
    "\"temp1\"       DOUBLE NOT NULL,"
    "\"temp2\"       DOUBLE NOT NULL,"
    "\"temp3\"       DOUBLE NOT NULL,"
    "\"temp4\"       DOUBLE NOT NULL,"
    "\"pump1\"       INTEGER NOT NULL,"
    "\"pump2\"       INTEGER NOT NULL,"
    "\"pump4\"       INTEGER NOT NULL);";

  if (sqlite3_exec(db, sql_create_table, NULL, 0, &error_msg) != 0)
  {
    sqlite_print_error(error_msg);
    return false;
  }

  return true;
}
#endif

#ifdef DS_BS_PLUS
bool sqlite_create_table()
{
  char *error_msg;
  char sql_create_table[] = "CREATE TABLE IF NOT EXISTS data ("
    "\"id\"          INTEGER PRIMARY KEY AUTOINCREMENT,"
    "\"time\"        DEFAULT CURRENT_TIMESTAMP NOT NULL,"
    "\"system_time\" TEXT NOT NULL,"
    "\"temp1\"       DOUBLE NOT NULL,"
    "\"temp2\"       DOUBLE NOT NULL,"
    "\"temp3\"       DOUBLE NOT NULL,"
    "\"temp4\"       DOUBLE NOT NULL,"
    "\"pump1\"       INTEGER NOT NULL,"
    "\"pump2\"       INTEGER NOT NULL,"
    "\"hours1\"      INTEGER NOT NULL,"
    "\"hours2\"      INTEGER NOT NULL);";

  if (sqlite3_exec(db, sql_create_table, NULL, 0, &error_msg) != 0)
  {
    sqlite_print_error(error_msg);
    return false;
  }

  return true;
}
#endif


