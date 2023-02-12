CXXFLAGS = 

main.exe: main.o 
	g++ main.o -o main.exe	-std=c++0x

main.o: main.cpp
	g++ -c main.cpp -o main.o	-std=c++0x

.PHONY: clean

clean:
	rm *.exe *.o