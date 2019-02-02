########################################################
# Makefile created by Matthew Baum for the Racing Game #
########################################################

# make some things easier to type and change
# i use these

CC=gcc
CFLAGS=-O3 -W -Wall -pedantic -ansi
LIBS=`sdl-config --libs` -lSDL_image

# compile the program
mapmaker: main.c map.a
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) main.o map.a $(LIBS) -o mapmaker

# the map library
map.a: error.c collision.c image.c tile.c map.c
	$(CC) $(CFLAGS) -c error.c collision.c image.c tile.c map.c
	ar rcs map.a error.o collision.o image.o tile.o map.o
	ranlib map.a

# fake clean target to remove all objects and the program
clean:
	rm *.o
	rm mapmaker
