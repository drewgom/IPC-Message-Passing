// Name: Andrew Gomez
// Class: CECS 326
// Assignment: Assignment 2
// Due Date: Mar 3rd, 2020
// sender.cpp

#include "main.h"

using namespace std;

// Here, we declare our buffer, like we did in use_msgQ.cpp

int main(int argc, char *argv[])	{
	string PROCESS_NAME = "(sender)";
	// The first thing we want the sender process to do is to state:
	// 		- That it is the sender
	//		- Its PID
	//		- That it is beginning execution
	cout << PROCESS_NAME << "Sender - PID: " << getpid() << " - begins execution." << endl;

	cout << PROCESS_NAME << "Message queue ID is " << argv[1] << endl;

	// The sender prompts the user for a line to send as a message
	cout << PROCESS_NAME << "Please enter a message: " << endl;
	string user_input;
	getline(cin, user_input);

	// Once we have the user input, we need to put it in a buffer and send the message
	buf message_buffer;
	int size = sizeof(message_buffer)-sizeof(long);
	message_buffer.mtype = MESSAGE_CHANNEL;
	strcpy(message_buffer.interprocess_message, user_input.c_str());

	// Now we send the message
	cout << PROCESS_NAME << "Sending the message. . ." << endl;

	// To send a message, we set the arguments equal to the following values:
	//		- Queue ID - an integer version of the queue ID that was passed in to the process
	//		- Pointer to message buffer - this is going to be the message buffer that we want to send to the queue
	//		- size - we know that the bytes in the struct that are not used for used for the size must be used for the message. Thus, we use that
	//		- message flags - we don't have any, so we leave that as zer0
	msgsnd(stoi(argv[1]), (struct msgbuf *)&message_buffer, size, 0);

	exit(0);
}

