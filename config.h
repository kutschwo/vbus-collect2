//****************************************************************************
// config.h
//
// Tobias Tangemann 2020
// 
// Funktionen zum Auslesen von Konfigurations-Werten aus .json Datei
// Header-File
//
//****************************************************************************
#pragma once

#include <stdbool.h>

typedef struct {
    char *softlic_url;

    char* post_string;

    int delay;

    const char* database;
    bool withSql;

    bool print_result;
    bool verbose;

    bool mqtt_enabled;
    const char* mqtt_user;
    const char* mqtt_password;
    const char* mqtt_server;
    const char* mqtt_base_topic;
    const char* mqtt_client_id;

    bool homeassistant_enabled;
    const char* homeassistant_entity_id_base;
} CONFIG;

int parseConfig(const char* file, CONFIG* cfg);
