srcfile=main.cpp 001.firstMultithreadProgram.cpp 002.RAII_join.cpp 003.multithread_program1.cpp 004.print12A34B.cpp
prog:$(srcfile)
	g++ -g -std=c++11 -pthread -o prog $(srcfile)
