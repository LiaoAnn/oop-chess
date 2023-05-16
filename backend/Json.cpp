/***********************************************************************
 * File: Json.cpp
 * Author: BING-JIA TAN (B11115001)
 * Create Date: 2023-05-16
 * Editor: BING-JIA TAN (B11115001)
 * Update Date: 2023-05-16
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
