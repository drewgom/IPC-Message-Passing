// Name: Andrew Gomez
// Class: CECS 326
// Assignment: Assignment 2
// Due Date: Mar 3rd, 2020
// sender.cpp

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])	{
	string PROCESS_NAME = "(sender)";
	// The first thing we want the sender process to do is to state:
	// 		- That it is the sender
	//		- Its PID
	//		- That it is beginning execution
	cout << PROCESS_NAME << "Sender - PID: " << getpid() << " - begins execution." << endl;

	cout << PROCESS_NAME << "Message queue is " << argv[1] << endl;
	

	// The sender prompts the user for a line to send as a message
	exit(0);
}

