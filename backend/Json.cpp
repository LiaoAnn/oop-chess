/***********************************************************************
 * File: Json.cpp
 * Author: 譚秉家
 * Create Date: 2023/05/10
 * Editor: 劉耀恩
 * Update Date: 2023/05/17
 * Description: Tools for json
************************************************************************/
#include "Json.h"

/**
 * Intent: Convert string to json
 * Pre: str is a valid json string
 * Post: return a json object
 */
json stringToJson(string str)
{
	json j;
	if (!json::accept(str)) return nullptr;

	j = json::parse(str, nullptr, false);
	//cout << j.dump() << endl;
	return j;
}
