a.out: sender receiver master.cpp main.h
	g++ master.cpp
sender: sender.cpp main.h
	g++ -o sender sender.cpp
receiver: receiver.cpp main.h
	g++ -o receiver receiver.cpp