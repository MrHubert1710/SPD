out: main.o lista.o kolejka.o
	g++ -o out main.o lista.o kolejka.o

main.o: main.cpp lista.hpp
	g++ -c main.cpp

lista.o: lista.cpp lista.hpp debug.hpp
	g++ -c lista.cpp

kolejka.o: kolejka.cpp kolejka.hpp debug.hpp
	g++ -c kolejka.cpp

clean :
	rm *.o out