CC = g++
CPPFLAGS += -Wall -Werror -pedantic-errors -I/usr/include/freetype2 #-g -rdynamic
LDLIBS += -lm -lglfw -lGL -lftgl
PROG = gusgrav

OBJS = point2d.o \
	   vector2d.o \
	   universe.o \
	   universe_mgr.o \
	   main.o


all: $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS) $(LDLIBS)

.PHONY: clean

clean:
	-rm $(PROG) $(OBJS)

