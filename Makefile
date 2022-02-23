aes: *.c
	gcc -Wall aes.c keyscheduler.c math/GF28.c -o aes
clean:
	rm aes
