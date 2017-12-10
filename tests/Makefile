# Change this variable to the path of your GTest sources
GOOGLE_TEST_DIR := ../googletest

CXX := g++

BUILD_DIR := build
BIN_DIR := bin
OUT_NAME := tests
OUT_PATH := $(BIN_DIR)/$(OUT_NAME)
INCLUDE_DIR := include

GTEST_INCLUDE := $(abspath $(GOOGLE_TEST_DIR)/googletest/include)
GTEST_LIB_DIR := $(abspath $(GOOGLE_TEST_DIR)/build/googlemock/gtest)
GTEST_LIB := libgtest.a
LINK_FLAGS := -L$(GTEST_LIB_DIR) -lgtest -pthread

TARGET_DIR := ../code
TARGET_INCLUDE := $(abspath $(TARGET_DIR)/include)
TARGET_BUILD_DIR := $(TARGET_DIR)/build

SRC := $(patsubst ./%,%, $(shell find . -type f -name "*.cpp"))
OBJ := $(patsubst %.cpp,%.o, $(SRC))
OBJ_WITH_DIR := $(addprefix $(BUILD_DIR)/, $(OBJ))
TARGET_OBJ = $(shell find $(TARGET_BUILD_DIR) -type f -name "*.o")

CXX_FLAGS := -I$(GTEST_INCLUDE) -I$(TARGET_INCLUDE) -I$(INCLUDE_DIR) -g


main-build: $(OBJ) build-test-target
	mkdir -p $(dir $(OUT_PATH))
	$(CXX) $(CXX_FLAGS) -o $(OUT_PATH) $(OBJ_WITH_DIR) $(TARGET_OBJ) \
		$(LINK_FLAGS)

build-test-target:
	cd $(TARGET_DIR) && make build-obj

$(OBJ): %.o: %.cpp
	mkdir -p $(dir $(BUILD_DIR)/$@)
	$(CXX) -c $(CXX_FLAGS) -o $(BUILD_DIR)/$@ $<

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
