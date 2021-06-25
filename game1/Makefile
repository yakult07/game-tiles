all: compile link 

compile: 
		g++ -I src/include -c Game.cpp main.cpp
link:
		g++ Game.o main.o -o main -L src/lib -l sfml-Graphics -l sfml-window -l sfml-audio -l sfml-system -l sfml-network 		
