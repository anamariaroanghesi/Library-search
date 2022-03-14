build:
	gcc -std=gnu99 -g -o tema3 -Wall tema3.c trie1.c trie2.c TBook.c

clean:
	rm -f *.o tema3