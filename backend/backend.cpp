/***********************************************************************
 * File: backend.cpp
 * Author: 廖廷安
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
		if (!global->isConnected())
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}
		string str;
		while (*global >> str)
		{
			cout << str << endl;
		}
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
	// the program will stock when run() is called , so thread is needed to run the loop
	server.run(4444);
	timer_thread.join(); // don't really know why this is needed
	return 0;
}

