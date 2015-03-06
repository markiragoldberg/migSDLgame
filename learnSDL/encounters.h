#pragma once
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "encounterClass.h"
#include <vector>

bool loadData();

const encounter * getEncounter(unsigned index);

void deleteEncounters();

