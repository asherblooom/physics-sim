TARGET_EXEC := phys-sim
CXX:=g++
INC_DIR:=include/
CXXFLAGS:=-I$(INC_DIR) -Wall -Wextra -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++20 -ggdb3
OBJ_DIR:=./obj
SRC_DIR:=./src

GLAD_OBJ := $(OBJ_DIR)/glad.o
GLAD_SRC := $(SRC_DIR)/glad.c

# Find all the C++ files we want to compile
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
# get a list of object files we want to compile by removing the 
# paths from the source files and then substituing .cpp for .o
_OBJS := $(patsubst %.cpp,%.o,$(notdir $(SRCS)))
# add the object directory to the front of the object files
OBJS := $(_OBJS:%=$(OBJ_DIR)/%)

.PHONY: main

main: obj $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS) $(GLAD_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) -c

obj: 
	mkdir -p obj

# compiles the glad library
$(GLAD_OBJ): $(GLAD_SRC) 
	$(CXX) -I$(INC_DIR) $< -o $@ -c


.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(TARGET_EXEC)


