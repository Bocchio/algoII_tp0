CXX = g++
CPPFLAGS = -std=c++98 -Wall -pedantic-errors

main: main.o cmdline.o vector.hpp complex.hpp dft.hpp
	$(CXX) $^ -o $@

cmdline.o: cmdline.cpp
	$(CXX) -c $(CPPFLAGS) $^ -o $@

main.o: main.cpp complex.hpp vector.hpp dft.hpp
	$(CXX) -c $(CPPFLAGS) $< -o $@