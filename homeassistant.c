//****************************************************************************
// homeassistant.c
//
// Tobias Tangemann 2020
// 
// Funktionen zur übertragung der Werte an den Homeassistant Server
// Implementation
//
//****************************************************************************

#include "homeassistant.h"

#include "cJSON/cJSON.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <curl/curl.h>

#define AUTHORIZATION_HEADER "Authorization: Bearer %s"
#define DEFAULT_HOMEASSISTANT_URL "http://supervisor/core"
#define API_ENDPOINT "/api/states/%s%s"

char* base_url = NULL;
CURL* curl = NULL;
struct curl_slist *headers = NULL;

void publish_json(const char* sensor, CONFIG* cfg, cJSON* json);
size_t curl_ignore_data(void *buffer, size_t size, size_t nmemb, void *userp);

bool homeassistant_init(CONFIG* cfg)
{
    if (curl != NULL)
    {
        return true;
    }

    curl = curl_easy_init();

    const char* token = getenv("SUPERVISOR_TOKEN");
    if (token == NULL) {
        printf("Homeassistant SUPERVISOR_TOKEN not found in environment\n");
        return 0;
    }

    const char* env_base_url = getenv("HOMEASSISTANT_API_URL");
    if (env_base_url != NULL) {
        base_url = calloc(strlen(env_base_url) + strlen(API_ENDPOINT) + 1, sizeof(char));
        strcpy(base_url, env_base_url);
    }
    else
    {
	base_url = calloc(strlen(DEFAULT_HOMEASSISTANT_URL) + strlen(API_ENDPOINT) + 1, sizeof(char));
	strcpy(base_url, DEFAULT_HOMEASSISTANT_URL);
    }

    strcat(base_url, API_ENDPOINT);

    int bearer_length = strlen(AUTHORIZATION_HEADER) + strlen(token) + 1;
    char *bearer = calloc(bearer_length, sizeof(char));
    snprintf(bearer, bearer_length, AUTHORIZATION_HEADER, token);

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, bearer);
    free(bearer);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    if (cfg->verbose)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }
    else
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_ignore_data);
    }

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);

    return true;
}

void homeassistant_cleanup()
{
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}

void publish_homeassistant(CONFIG* cfg, Data_Packet* data)
{
    if (curl == NULL)
    {
        return;
    }

    cJSON* root = cJSON_CreateObject();
#ifdef DS_E_CONTROLLER
    cJSON_AddNumberToObject(root, "state", round(data->DSECtrlPkt.TempSensor01 * 0.1));
#endif
#ifdef DS_BS_PLUS
    cJSON_AddNumberToObject(root, "state", round(data->bsPlusPkt.TempSensor1 * 0.1));
#endif
    cJSON* attributes = cJSON_AddObjectToObject(root, "attributes");
    cJSON_AddStringToObject(attributes, "unit_of_measurement", "°C");
    cJSON_AddStringToObject(attributes, "device_class", "temperature");
    publish_json("_furnace", cfg, root);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
#ifdef DS_E_CONTROLLER
    cJSON_AddNumberToObject(root, "state", round(data->DSECtrlPkt.PumpSpeed1 / 2.55));
#endif
#ifdef DS_BS_PLUS
    cJSON_AddNumberToObject(root, "state", round(data->bsPlusPkt.PumpSpeed1 / 2.55));
#endif
    attributes = cJSON_AddObjectToObject(root, "attributes");
    cJSON_AddStringToObject(attributes, "unit_of_measurement", "%");
    publish_json("_furnace_pump", cfg, root);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
#ifdef DS_E_CONTROLLER
    cJSON_AddNumberToObject(root, "state", round(data->DSECtrlPkt.TempSensor04 * 0.1));
#endif
#ifdef DS_BS_PLUS
    cJSON_AddNumberToObject(root, "state", round(data->bsPlusPkt.TempSensor4 * 0.1));
#endif
    attributes = cJSON_AddObjectToObject(root, "attributes");
    cJSON_AddStringToObject(attributes, "unit_of_measurement", "°C");
    cJSON_AddStringToObject(attributes, "device_class", "temperature");
#ifdef DS_E_CONTROLLER
    cJSON_AddNumberToObject(attributes, "valve", data->DSECtrlPkt.PumpSpeed2 / 100);
#endif
#ifdef DS_BS_PLUS
    cJSON_AddNumberToObject(attributes, "valve", data->bsPlusPkt.PumpSpeed2 / 100);
#endif
    publish_json("_returnflow", cfg, root);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
#ifdef DS_E_CONTROLLER
    cJSON_AddNumberToObject(root, "state", data->DSECtrlPkt.PumpSpeed2 / 100);
#endif
#ifdef DS_BS_PLUS
    cJSON_AddNumberToObject(root, "state", data->bsPlusPkt.PumpSpeed2 / 100);
#endif
    publish_json("_returnflow_valve", cfg, root);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
#ifdef DS_E_CONTROLLER
    cJSON_AddNumberToObject(root, "state", round(data->DSECtrlPkt.TempSensor03 * 0.1));
#endif
#ifdef DS_BS_PLUS
    cJSON_AddNumberToObject(root, "state", round(data->bsPlusPkt.TempSensor3 * 0.1));
#endif
    attributes = cJSON_AddObjectToObject(root, "attributes");
    cJSON_AddStringToObject(attributes, "unit_of_measurement", "°C");
    cJSON_AddStringToObject(attributes, "device_class", "temperature");
    publish_json("_tank_top", cfg, root);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
#ifdef DS_E_CONTROLLER
    cJSON_AddNumberToObject(root, "state", round(data->DSECtrlPkt.TempSensor02 * 0.1));
#endif
#ifdef DS_BS_PLUS
    cJSON_AddNumberToObject(root, "state", round(data->bsPlusPkt.TempSensor2 * 0.1));
#endif
    attributes = cJSON_AddObjectToObject(root, "attributes");
    cJSON_AddStringToObject(attributes, "unit_of_measurement", "°C");
    cJSON_AddStringToObject(attributes, "device_class", "temperature");
    publish_json("_tank_bottom", cfg, root);
    cJSON_Delete(root);
}

void publish_json(const char* sensor, CONFIG* cfg, cJSON* json)
{
    int url_length = strlen(base_url) + strlen(cfg->homeassistant_entity_id_base) + strlen(sensor) + 1;
    char *url = calloc(url_length, sizeof(char));

    // Set url
    snprintf(url, url_length, base_url, cfg->homeassistant_entity_id_base, sensor);
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set json payload
    char* jsonString = cJSON_PrintUnformatted(json);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString);

    // Send HTTP POST request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        char errbuf[CURL_ERROR_SIZE] = { 0, };
        size_t len = strlen(errbuf);

        fprintf(stderr, "\nlibcurl: (%d) ", res);
        if (len)
        {
            fprintf(stderr, "%s%s", errbuf, ((errbuf[len - 1] != '\n') ? "\n" : ""));
        }

        fprintf(stderr, "%s\n\n", curl_easy_strerror(res));
    }

    free(url);
    free(jsonString);
}

size_t curl_ignore_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}

