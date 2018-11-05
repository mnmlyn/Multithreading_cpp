srcfile=main.cpp 001.firstMultithreadProgram.cpp 002.RAII_join.cpp 003.multithread_program1.cpp
prog:$(srcfile)
	g++ -g -std=c11 -o prog $(srcfile)
