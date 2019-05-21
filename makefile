all:
	g++ -c -std=c++11 *.cc 
	g++ *.o -std=c++11 -g -o test

clear: 
	rm -f *.o
	rm -f test
