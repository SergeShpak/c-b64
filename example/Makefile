CC := gcc
BUILD_DIR := build
BIN_DIR := bin
OUT := b64_example
OUT_PATH := $(BIN_DIR)/$(OUT)
B64_ROOT := ../
INCLUDE_DIR := $(B64_ROOT)/include
CFLAGS := -g -Wall -Wpedantic -I$(INCLUDE_DIR)
B64_SRC := $(patsubst $(B64_ROOT)/%.c,%.c, \
	$(shell find $(B64_ROOT)/src -type f -name "*.c"))
B64_OBJ := $(patsubst %.c,%.o, $(B64_SRC))
B64_OBJ_WITH_DIR := $(patsubst %.o,$(BUILD_DIR)/%.o, $(B64_OBJ))
EXAMPLE_SRC := $(patsubst ./%,%, $(shell find . -type f -name "*.c"))
EXAMPLE_OBJ := $(patsubst %.c,%.o, $(EXAMPLE_SRC))
EXAMPLE_OBJ_WITH_DIR := $(patsubst %.o,$(BUILD_DIR)/%.o, $(EXAMPLE_OBJ))

.PHONY: all

all: main-build

.PHONY: main-build

main-build: $(B64_OBJ) $(EXAMPLE_OBJ) 
	mkdir -p $(dir $(OUT_PATH))
	$(CC) $(CFLAGS) -o $(OUT_PATH) $(B64_OBJ_WITH_DIR) \
		$(EXAMPLE_OBJ_WITH_DIR)

$(B64_OBJ): %.o: $(B64_ROOT)/%.c
	mkdir -p $(dir $(BUILD_DIR)/$@)
	$(CC) -c $(CFLAGS) -o $(BUILD_DIR)/$@ $<

$(EXAMPLE_OBJ): %.o: %.c
	mkdir -p $(dir $(BUILD_DIR)/$@)
	$(CC) -c $(CFLAGS) -o $(BUILD_DIR)/$@ $<


.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
