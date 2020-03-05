// Name: Andrew Gomez
// Class: CECS 326
// Assignment: Assignment 2
// Due Date: Mar 3rd, 2020
// reciever.cpp

#include "main.h"

using namespace std;

int main(int argc, char *argv[])	{
	string PROCESS_NAME = "(receiver)";
	// The first thing we want the sender process to do is to state:
	// 		- That it is the sender
	//		- Its PID
	//		- That it is beginning execution
	cout << PROCESS_NAME << "Receiver - PID: " << getpid() << " - begins execution." << endl;

	cout << PROCESS_NAME << "Message queue ID is " << argv[1] << endl;

	// Once we have stated which process we are, it is time to receive message

	buf message_buffer;
	int size = sizeof(message_buffer)-sizeof(long);
	message_buffer.mtype = MESSAGE_CHANNEL;

	// To receive a message, we set the arguments equal to the following values:
	//		- Queue ID - an integer version of the queue ID that was passed in to the process
	//		- Pointer to message buffer - we are going to have this pointer set to the address of the buffer that we are receiving
	//		- size - we know that the size is going to be the size of the message buffer we defined - since that was what was sent. Thus, we will use that
	//		- message type - we know that the message we sent was of type 113 - so, we use a 113 to indicate to the message buffer that we want messages from there
	//		- message flags - we don't have any, so we leave that as zero
	msgrcv(stoi(argv[1]), (struct msgbuf *)&message_buffer, size, MESSAGE_CHANNEL, 0);

	cout << PROCESS_NAME << "Received the message. . ." << endl;
	cout << PROCESS_NAME << "message says: " << message_buffer.interprocess_message << endl;
	exit(0);
}