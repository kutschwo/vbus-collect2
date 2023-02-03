//****************************************************************************
// sqlite.h
//
// Tobias Tangemann 2020
// 
// function to publish data to sqlite database
// header file
//
//****************************************************************************
#pragma once

#include <stdbool.h>
#include "datatypes.h"

bool sqlite_open(const char *path);
void sqlite_close();
bool sqlite_exec(char* sql);
bool sqlite_create_table();
bool sqlite_insert_data(Data_Packet* data);
