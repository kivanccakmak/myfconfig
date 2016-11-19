CC=gcc
TARGET=myfconfig

SOURCES += $(wildcard *.c)
HEADERS += $(wildcard *.h)

default: all

all: $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET)

clean:
	rm -rf $(TARGET)
