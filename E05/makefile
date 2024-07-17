CC = g++
CFLAGS = -Wall -O3 --std=c++11

all: main.exe main2.exe main3.exe main4.exe

main.exe : main.o random.o funzioni.o Posizione.o
	$(CC) random.o funzioni.o main.o Posizione.o -o main.exe

main2.exe : main2.o random.o funzioni.o Posizione.o
	$(CC) random.o funzioni.o main2.o Posizione.o -o main2.exe

main3.exe : main3.o random.o funzioni.o Posizione.o
	$(CC) random.o funzioni.o main3.o Posizione.o -o main3.exe

main4.exe : main4.o random.o funzioni.o Posizione.o
	$(CC) random.o funzioni.o main4.o Posizione.o -o main4.exe

main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

main2.o : main2.cpp
	$(CC) -c main2.cpp -o main2.o $(CFLAGS)

main3.o : main3.cpp
	$(CC) -c main3.cpp -o main3.o $(CFLAGS)

main4.o : main4.cpp
	$(CC) -c main4.cpp -o main4.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)

Posizione.o : Posizione.cpp Posizione.h
	$(CC) -c Posizione.cpp -o Posizione.o $(CFLAGS)

clean :
	rm -f *.o main.exe main2.exe main3.exe main4.exe seed.out

run_main: main.exe
	./main.exe

run_main2: main2.exe
	./main2.exe

run_main3: main3.exe
	./main3.exe

run_main4: main4.exe
	./main4.exe
