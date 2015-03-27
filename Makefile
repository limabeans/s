default:
	gcc -o server -Wall server.c

run:
	./server

clean:
	rm -f server
