main.exe:dbms.o main.o
	g++ -o main.exe dbms.o main.o
dbms.o:dbms.cpp
	g++ -c dbms.cpp
main.o:main.cpp
	g++ -c main.cpp
clean:
	rm -rf *.o main.exe
