.NOTPARALLEL:

# defining variables
BUILD_TOOL = g++
ARCHIVE_TOOL = ar

COMPILE_FLAGS = -c -Wall -Werror

EXE_NAME = BurrowsWheelerCompression
SOURCES_DIR = ./src/

LIB_NAME = BurrowsWheeler
LIB_SOURCES_DIR = ./src/BurrowsWheelerLib/
HEADER_DIR = $(LIB_SOURCES_DIR)/h/

TEST_NAME = BurrowsWheelerTest
TEST_SOURCES_DIR = ./test/

OBJ_DIR = ./obj/

ADD_LIBRARIES_DIR = -L./lib/
#ADD_LIBRARIES = -lgtest_main
ADD_LIBRARIES = -lgmock_main

ADD_HEADERS_DIR = ./include/

# BurrowsWheelerCompression objects
EXE_SOURCES = $(wildcard $(SOURCES_DIR)*.cpp)
EXE_OBJECTS = $(subst $(SOURCES_DIR),$(OBJ_DIR),$(EXE_SOURCES:%.cpp=%.o))
EXE_FILENAMES = $(subst $(SOURCES_DIR),,$(EXE_SOURCES:%.cpp=%))

# BurrowsWheelerLib objects
LIB_SOURCES = $(wildcard $(LIB_SOURCES_DIR)*.cpp)
LIB_OBJECTS = $(subst $(LIB_SOURCES_DIR),$(OBJ_DIR),$(LIB_SOURCES:%.cpp=%.o))
LIB_FILENAMES = $(subst $(LIB_SOURCES_DIR),,$(LIB_SOURCES:%.cpp=%))

# tests objects
TEST_SOURCES = $(wildcard $(TEST_SOURCES_DIR)*.cpp)
TEST_OBJECTS = $(subst $(TEST_SOURCES_DIR),$(OBJ_DIR),$(TEST_SOURCES:%.cpp=%.o))
TEST_FILENAMES = $(subst $(TEST_SOURCES_DIR),,$(TEST_SOURCES:%.cpp=%))

# labels definition
all: clean BurrowsWheelerLib tests run_tests BurrowsWheelerCompressionExe

.PHONY: all BurrowsWheelerLib tests clean run_tests BurrowsWheelerCompressionExe

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
	$(BUILD_TOOL) -lpthread -o $(OBJ_DIR)$(TEST_NAME) $(TEST_OBJECTS) $(ADD_LIBRARIES_DIR) $(ADD_LIBRARIES) -L$(OBJ_DIR) -l$(LIB_NAME)
	
#execute tests
run_tests:
	$(OBJ_DIR)$(TEST_NAME)

#build BurrowsWheelerCompression executable
BurrowsWheelerCompressionExe: $(EXE_FILENAMES) build_executable

$(EXE_FILENAMES):
	$(BUILD_TOOL) -I$(ADD_HEADERS_DIR) -I$(HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(SOURCES_DIR)$@.cpp

build_executable:
	$(BUILD_TOOL) -lpthread -o $(OBJ_DIR)$(EXE_NAME) $(EXE_OBJECTS) -L$(OBJ_DIR) -l$(LIB_NAME)
