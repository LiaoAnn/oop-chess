/***********************************************************************
 * File: Json.h
 * Author: 譚秉家
 * Create Date: 2023/05/16
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Implement json tools
************************************************************************/
#pragma once

#include <iostream>
#include <json.hpp>
#include "Game.h"

using namespace std;
using json = nlohmann::json;

json stringToJson(string);
