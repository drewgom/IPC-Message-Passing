a.out: sender receiver
	g++ master.cpp
sender:
	g++ -o sender sender.cpp
receiver:
	g++ -o receiver receiver.cpp