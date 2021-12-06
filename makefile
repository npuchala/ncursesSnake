a.out: main.o Segment.o
	g++ -g main.o -lncurses -pthread Segment.o -o a.out 

main.o: main.cpp Segment.h
	g++ -c -g main.cpp -lncurses -pthread

Segment.o: Segment.cpp Segment.h
	g++ -c -g Segment.cpp

clean:
	rm -f *.o a.out *.save.* *.save
