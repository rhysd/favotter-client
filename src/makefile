GXX = g++-4.6.2
CXXFLAGS = -std=c++0x -Wall -Wextra -O2 

favotter : main.o favotter.o
	$(GXX) -o favotter  main.o favotter.o -L /opt/local/lib -lboost_system-mt -lboost_thread-mt

favotter.o : favotter.cpp favotter.hpp 
	$(GXX) $(CXXFLAGS) -c favotter.cpp -L /opt/local/lib -lboost_system-mt -lboost_thread-mt

main.o : main.cpp favotter.hpp
	$(GXX) $(CXXFLAGS) -c main.cpp
