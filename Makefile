CC=cc
CFLAGS=-ggdb3 -c -Wall -std=c11
LDFLAGS=-pthread
SOURCES=main.c queue.c thread_routines.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=executable

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
