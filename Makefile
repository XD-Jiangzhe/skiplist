CC=g++
CXX_FLAG=-g -std=c++11 
target=main

$(target):skiptest.cc skiplist.o
	$(CC) $(CXX_FLAG) $^ -o $(target) 

skiplist.o:
	$(CC) $(CXX_FLAG) -c skiplist.cc 

clean:
	rm -rf *.o $(target)