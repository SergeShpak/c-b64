CC := gcc
BUILD_DIR := build
OUT_PATH := $(BIN_DIR)/$(OUT)
INCLUDE_DIR := include
CFLAGS := -g -Wall -Wpedantic -I$(INCLUDE_DIR)
SRC := $(patsubst ./%,%, $(shell find -type f -name "*.c"))
OBJ := $(patsubst %.c,%.o, $(SRC))
OBJ_WITH_DIR = $(addprefix $(BUILD_DIR)/,$(OBJ))

all: main-build

main-build: build-obj 

build-obj: $(OBJ)

$(OBJ): %.o: %.c
	mkdir -p $(dir $(BUILD_DIR)/$@)
	$(CC) -c $(CFLAGS) -o $(BUILD_DIR)/$@ $<

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
