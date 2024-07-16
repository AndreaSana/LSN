CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : random.o function.o position.o city.o travel.o gen_function.o TSP.o main.o
	$(CC) random.o function.o position.o city.o travel.o gen_function.o TSP.o main.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
position.o : position.cpp position.h
	$(CC) -c position.cpp -o position.o $(CFLAGS)
city.o : city.cpp city.h
	$(CC) -c city.cpp -o city.o $(CFLAGS)
travel.o : travel.cpp travel.h
	$(CC) -c travel.cpp -o travel.o $(CFLAGS)
TSP.o : TSP.cpp TSP.h
	$(CC) -c TSP.cpp -o TSP.o $(CFLAGS)
function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS)
gen_function.o : gen_function.cpp gen_function.h
	$(CC) -c gen_function.cpp -o gen_function.o $(CFLAGS)
	
clean :
	rm *.o main.exe *.dat
make run :
	./main.exe
