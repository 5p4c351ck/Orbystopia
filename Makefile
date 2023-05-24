CC = gcc

TARGET = Orbystopia
SOURCES = main.c character.c grid.c items.c narrators.c choice.c
OBJECTS =$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

%.0: %.c
	$(CC) -c $< $@

clean:
	rm $(OBJECTS)
