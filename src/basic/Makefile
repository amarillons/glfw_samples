ifeq ($(shell uname),Linux)
# for Linux
LIB += -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm -lpthread
endif

ifeq ($(shell uname),Darwin)
# for Mac 
LIB += -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework Carbon -L/usr/local/lib/ -lglfw
endif

CC = gcc 
OPT += -O3 -Wall 
# OPT += -Wno-deprecated
OBJS1 = donothing.o 
OBJS2 = dodecagon.o

all: prog1 prog2
#
prog1:
	$(CC) $(OPT) $(PREDEF) -c nothing.c
	$(CC) $(OBJS1) $(LIB) -o nothing
prog2:
	$(CC) $(OPT) $(PREDEF) -c dodecagon.c
	$(CC) $(OBJS2) $(LIB) -o dodecagon

clean:
	rm -vf *.o

