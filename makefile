out: main.o lista.o
	g++ -o out main.o lista.o

main.o: main.cpp lista.hpp
	g++ -c main.cpp

lista.o: lista.cpp lista.hpp debug.hpp
	g++ -c lista.cpp
   
clean :
	rm *.o out