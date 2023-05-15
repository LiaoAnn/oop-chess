/***********************************************************************
 * File: backend.cpp
 * Author: 廖庭安
 * Create Date: 2023/05/10
 * Editor:
 * Update Date: 2023/05/15
 * Description:
***********************************************************************/
#include <iostream>
#include "WebSocketServer.h"
#include <thread>
#include <chrono>
using namespace std;
WebSocketServer* global;
void loop() {
	while (true) {
		string s;
		cin >> s;
		// prevent chinese input be sent to client
		if (s[0] < 0)
			continue;
		if (!global->send(s))
			cout << "send failed" << endl;		

		//===================================WARNING===============================
		//for release version don't put any thing here unless you want to slow down the program or really no other choice
		//=========================================================================
	}
}
int main()
{
	WebSocketServer server;
	global = &server; // set global pointer to server
	thread timer_thread(loop);
	timer_thread.join(); // don't really know why this is needed
	// the program will stock when run() is called , so thread is needed to run the loop
	server.run(9002); 	
	return 0;
}

