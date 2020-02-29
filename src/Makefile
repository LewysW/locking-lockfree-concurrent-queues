all: clean locking lockfree

locking:
	g++ locking_queue/locking.cpp -o locking -std=c++17 -pthread

lockfree:
	g++ lock_free_queue/lockFree.cpp -o lockfree -std=c++17 -pthread

clean:
	rm -rf locking *.o lockfree
