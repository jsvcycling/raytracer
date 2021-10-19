CC=cc
CFLAGS=-std=c99 -pedantic -Wall -g -c
LDFLAGS=-lm
SRCS=camera.c color.c main.c shape.c utils.c
OBJS=$(SRCS:%.c=%.o)

.PHONY: all clean run

all: $(OBJS) $(SRCS)
	$(CC) $(LDFLAGS) $(OBJS) -o raytracer

clean:
	rm -f *.o
	rm -f *.ppm
	rm -f raytracer

run: all
	./raytracer > image.ppm

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

