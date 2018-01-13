split-array:split.cpp
	g++-5 -pg -g -Wall -o $@ $< -std=c++11
clean:
	rm -rf split-array
