CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o random.o function.o wavefunction.o
	$(CC) random.o function.o main.o wavefunction.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS)
wavefunction.o : wavefunction.cpp wavefunction.h
	$(CC) -c wavefunction.cpp -o wavefunction.o $(CFLAGS)
	
clean :
	rm *.o main.exe seed.out

run : main.exe
	./main.exe