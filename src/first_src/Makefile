LIB += -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework Carbon -framework CoreVideo -L/usr/local/lib/ -lglfw3
# LIB+= -framework IOKit -framework Carbon -framework Cocoa -framework CoreVideo -lglfw3

CC = g++
OPT += -O3 -Wall 
OBJS1 = a.o


prog1:
	$(CC) $(OPT) $(PREDEF) -c a.cpp
	$(CC) $(OBJS1) $(LIB) -o a.out



