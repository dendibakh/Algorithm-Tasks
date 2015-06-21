.NOTPARALLEL:

BUILD_TOOL = g++
ARCHIVE_TOOL = ar

COMPILE_FLAGS = -c -Wall -Werror

EXE_NAME = bigNumbers
EXE_SOURCES_DIR = ./src/
EXE_OBJ_DIR = ./obj/

EXE_SOURCES = $(wildcard $(EXE_SOURCES_DIR)*.cpp)
EXE_OBJECTS = $(subst $(EXE_SOURCES_DIR),$(EXE_OBJ_DIR),$(EXE_SOURCES:%.cpp=%.o))
EXE_FILENAMES = $(subst $(EXE_SOURCES_DIR),,$(EXE_SOURCES:%.cpp=%))

LIB_NAME = CppUnitLite
LIB_SOURCES_DIR = ./src/$(LIB_NAME)/
LIB_OBJ_DIR = ./obj/$(LIB_NAME)/

LIB_SOURCES = $(wildcard $(LIB_SOURCES_DIR)*.cpp)
LIB_OBJECTS = $(subst $(LIB_SOURCES_DIR),$(LIB_OBJ_DIR),$(LIB_SOURCES:%.cpp=%.o))
LIB_FILENAMES = $(subst $(LIB_SOURCES_DIR),,$(LIB_SOURCES:%.cpp=%))

EXE_INCLUDE_DIRS = $(LIB_SOURCES_DIR)

all: clean library executable execute

.PHONY: all library executable clean execute

clean:
	rm -r -f $(EXE_OBJ_DIR)
	mkdir $(EXE_OBJ_DIR)
	mkdir $(LIB_OBJ_DIR)

executable: $(EXE_FILENAMES) build_executable

$(EXE_FILENAMES):
	$(BUILD_TOOL) -I$(EXE_INCLUDE_DIRS) $(COMPILE_FLAGS) -o $(EXE_OBJ_DIR)$@.o $(EXE_SOURCES_DIR)$@.cpp

build_executable:
	$(BUILD_TOOL) -o $(EXE_OBJ_DIR)$(EXE_NAME) $(EXE_OBJECTS) -L$(LIB_OBJ_DIR) -l$(LIB_NAME) 
	

library: $(LIB_FILENAMES) build_achive

build_achive: $(LIB_OBJECTS)
	$(ARCHIVE_TOOL) rcs $(LIB_OBJ_DIR)lib$(LIB_NAME).a $(LIB_OBJECTS)

$(LIB_FILENAMES):
	$(BUILD_TOOL) $(COMPILE_FLAGS) -o $(LIB_OBJ_DIR)$@.o $(LIB_SOURCES_DIR)$@.cpp

execute:
	$(EXE_OBJ_DIR)$(EXE_NAME)