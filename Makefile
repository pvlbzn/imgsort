all:
	g++ -std=c++14 image.cpp main.cpp `pkg-config --cflags --libs opencv` -o out