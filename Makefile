LDFLAGS = -shared -L./smac-alloc
TARGET = rsvidx.so
CSOURCES = $(shell echo src/*.c)
SMAC_SOURCES = $(shell echo smac-alloc/src/*.c)
FLAGS = -O3 -I./src/include -fPIC

OBJECTS = $(CSOURCES:.c=_c.o)
SMAC_OBJECTS = $(SMAC_SOURCES:.c=_c.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(SMAC_OBJECTS)
	gcc $(FLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(SMAC_OBJECTS)

%_c.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm $(OBJECTS) $(SMAC_OBJECTS) $(TARGET)
