#pragma once
#include "cJSON.h"
#include "stdio.h"
cJSON* createJSON();
cJSON* createParametersJSON();
char* findCityAtIndex(cJSON* cjson, int index);
int findValueForString(cJSON* json, char* string);