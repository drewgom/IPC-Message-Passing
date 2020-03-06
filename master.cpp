// Name: Andrew Gomez
// Class: CECS 326
// Assignment: Assignment 2
// Due Date: Mar 3rd, 2020
// master.cpp

#include "main.h"

using namespace std;

int main()	{
	string PROCESS_NAME = "(master)";

	// The first thing we want the master process to do is to state:
	// 		- That it is the master
	//		- Its PID
	//		- That it is beginning execution
	cout << PROCESS_NAME << "Master - PID: " << getpid() << " - begins execution." << endl;

	// Creates the message queue for sender and receiver
	// We do this call to get a new messsage queue.
	// The parameters are passed in as follows:
	// 		key = IPC_PRIVATE
	//			- This creates a new messge queue
	//		msgflg = 0600
	//			- I just used 0600 because that means that the queue will give read and write permission to this queue

	int qid = msgget(IPC_PRIVATE, 0600);
	// Since we need to have the qid saved as a C string later for both exec calls, I declared it right here

	char charqid[50];
	sprintf(charqid,"%d", qid);

	// Once we have our message queue, we can have the child programs communicate via the queue.
	cout << PROCESS_NAME << "Message Queue with QID " << qid << " created." << endl;

	// To create the receiver, we we fork our current process.
	// fork() creates a duplicate of the current process, and returns:
	// 		- -1 if something went wrong
	//		- 0 if we are the child process that was just created
	//		- our PID otherwise
	pid_t senderPID = fork();

	// If we are in this scenario, then we have had some error creating a new process

	if (senderPID < 0)	{
		cout << "ERROR: could not fork to create sender" << endl;
		exit(0);
	}

	// If the senderPID is 0, then that means this current iteration of master was created to become the sender.
	// Since that is the case, we will make an exec call to turn this process in to sender instead
	// exec works by taking our current process and replacing the code and data with the code and data of another process.
	// there are many variations of exec, but the version I used was execvp, which takes in two arguments:
	//  - The path to the file that we want to take over this process - in this case, it is ./sender
	//	- The command line arguments for the program that you are giving control to
	else if (senderPID == 0)	{
		// This is creating the arguments that we are going to send in to sender
	

		char *sendargV[] = {(char*)"./sender",charqid, NULL};
		// Here, we make the exec call
		execvp(sendargV[0], sendargV);
	}



	// If the senderPID is >0, then we konw that this version of this process is the parent.
	// We will need to repeat the process to get the receiver running as well. 

	pid_t receiverPID = fork();

	if (receiverPID < 0)	{
		cout << "ERROR: could not fork to create receiver" << endl;
		exit(0);
	}

	else if (receiverPID == 0)	{

		char *sendargV[] = {(char*)"./receiver",charqid, NULL};
		execvp(sendargV[0], sendargV);
	}

	// If the receiverPID is >0, then we konw that this version of this process is the parent.
	//Now, we can display the process ID for each of the children - becuase we know the id's.

	cout << PROCESS_NAME << "The sender's PID is " << senderPID << endl;
	cout << PROCESS_NAME << "The receiver's PID is " << receiverPID << endl;
	// If we are the parent, then we want to wait for the child's completion
	while(wait(NULL) != -1);
	// Once our child is complete, we are finished
	cout << "Parent is finished!" << endl;

	// Here, we need to remove the message queue that way it isnt hogging up part of our system
	// The arguments we passed in to msgctl:
	//		- the id of the queue that you want to control - which is qid
	//		- the command that you want to initiate - we want to do an IPC removal by ID - the code for that is IPC_RMID
	//		- the msqid data structure for the message that you are going to manipulate in some of the operation - we dont need that, since
	//		  we are removing the queue rather than editing an existing message buffer
	msgctl(qid, IPC_RMID, NULL);
	exit(0);
}