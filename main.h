// Name: Andrew Gomez
// Class: CECS 326
// Assignment: Assignment 2
// Due Date: Mar 3rd, 2020
// main.h


//Here, we will include all the necessary header files
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


// We are going to use this to indicate the message channel to both the receiver and the sender, instead of hard coding the message type
const int MESSAGE_CHANNEL = 113;

// Here is the definition we are going to use for a buffer
struct buf {
	long mtype;
	char interprocess_message[100];
};