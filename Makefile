CC      ?= gcc
CFLAGS  ?= -O2 -march=native
CFLAGS  += -std=c11 -D_DEFAULT_SOURCE -Wall -Wextra -Wpedantic -Isrc -MMD -MP
LDLIBS  := -lm

TARGET  := sdfr
BUILD   := build

SRC     := $(wildcard src/*.c src/*/*.c)
OBJ     := $(patsubst %.c,$(BUILD)/%.o,$(SRC))
DEP     := $(OBJ:.o=.d)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

-include $(DEP)
