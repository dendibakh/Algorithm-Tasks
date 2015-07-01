.NOTPARALLEL:

# defining variables
BUILD_TOOL = g++
ARCHIVE_TOOL = ar

COMPILE_FLAGS = -c -Wall -Werror

EXE_NAME = BurrowsWheelerCompression
HEADER_DIR = ./src/h/
SOURCES_DIR = ./src/

LIB_NAME = BurrowsWheeler
LIB_SOURCES_DIR = ./src/BurrowsWheelerLib/

TEST_NAME = BurrowsWheelerTest
TEST_SOURCES_DIR = ./test/
TEST_HEADER_DIR = ./test/h/

OBJ_DIR = ./obj/

ADD_LIBRARIES_DIR = ./lib/
ADD_LIBRARIES = gtest_main

ADD_HEADERS_DIR = ./include/
GTEST_HEADERS = ./include/gtest/*.h \
                ./include/gtest/internal/*.h

# BurrowsWheelerLib objects
LIB_SOURCES = $(wildcard $(LIB_SOURCES_DIR)*.cpp)
LIB_OBJECTS = $(subst $(LIB_SOURCES_DIR),$(OBJ_DIR),$(LIB_SOURCES:%.cpp=%.o))
LIB_FILENAMES = $(subst $(LIB_SOURCES_DIR),,$(LIB_SOURCES:%.cpp=%))

# tests objects
TEST_SOURCES = $(wildcard $(TEST_SOURCES_DIR)*.cpp)
TEST_OBJECTS = $(subst $(TEST_SOURCES_DIR),$(OBJ_DIR),$(TEST_SOURCES:%.cpp=%.o))
TEST_FILENAMES = $(subst $(TEST_SOURCES_DIR),,$(TEST_SOURCES:%.cpp=%))

# labels definition
all: clean BurrowsWheelerLib tests run_tests

.PHONY: all BurrowsWheelerLib tests clean run_tests

clean:
	rm -r -f $(OBJ_DIR)
	mkdir $(OBJ_DIR)

#building BurrowsWheelerLib
BurrowsWheelerLib: $(LIB_FILENAMES) build_lib

$(LIB_FILENAMES):
	$(BUILD_TOOL) -I$(HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(LIB_SOURCES_DIR)$@.cpp

build_lib:
	$(ARCHIVE_TOOL) rcs $(OBJ_DIR)lib$(LIB_NAME).a $(LIB_OBJECTS)

#building tests
tests: $(TEST_FILENAMES) build_tests

$(TEST_FILENAMES):
	$(BUILD_TOOL) -I$(ADD_HEADERS_DIR) -I$(HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(TEST_SOURCES_DIR)$@.cpp

build_tests:
	$(BUILD_TOOL) -lpthread -o $(OBJ_DIR)$(TEST_NAME) $(TEST_OBJECTS) -L$(ADD_LIBRARIES_DIR) -l$(ADD_LIBRARIES) -L$(OBJ_DIR) -l$(LIB_NAME)
	
#execute tests
run_tests:
	$(OBJ_DIR)$(TEST_NAME)
