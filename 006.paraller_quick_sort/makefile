obj=paraller_quick_sort.o

prog:$(obj)
	g++ -g -o $@ $(obj) -lpthread
	/bin/rm -f $(obj)

%.o:%.cpp
	g++ -g -c $^

.PHONY=clean
clean:
	/bin/rm -f prog $(obj)
