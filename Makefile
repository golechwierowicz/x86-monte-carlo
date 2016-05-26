CC=gcc
CFLAGS= -m64 
LFLAGS= -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf
OUT=out.o

all : main.o monte_carlo.o
	$(CC) $(CFLAGS) -o $(OUT) main.o monte_carlo.o $(LFLAGS)
	./$(OUT)

main.o : main.c
	$(CC) -g $(CFLAGS) -c main.c -o main.o

monte_carlo.o : monte_carlo.s
	nasm -g -f macho64 monte_carlo.s

clean:
	rm *.o && ls
	
