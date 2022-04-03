CC=gcc

all: build

build: tema1.c
	$(CC) -o tema1 tema1.c -lm -g -Wall

clean: 
	rm tema1