/***********************************************************************
 * File: Json.h
 * Author: BING-JIA TAN (B11115001)
 * Create Date: 2023-05-16
 * Editor: BING-JIA TAN (B11115001)
 * Update Date: 2023-05-16
 * Description: Implement json tools
************************************************************************/
#pragma once

#include <iostream>
#include <json.hpp>
#include "game.h"

using namespace std;
using json = nlohmann::json;

json stringToJson(string);
