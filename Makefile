TARGET_EXEC := phys-sim
CXX:=g++
LIB_DIR:=lib
CXXFLAGS:=-I$(LIB_DIR) -Wall -Wextra -Wno-unused-parameter -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++20
OBJ_DIR:=./obj
SRC_DIR:=./src

GLAD_OBJ := glad.o
IMGUI_BACKENDS := imgui_impl_glfw.o imgui_impl_opengl3.o
IMGUI_EXTRAS := imgui_stdlib.o

# Find all the C++ files we want to compile
SRCS := $(shell find $(SRC_DIR) -name '*.cpp') $(shell find $(LIB_DIR)/imgui -maxdepth 1 -name '*.cpp')
# get a list of object files we want to compile by removing the 
# paths from the source files and then substituing .cpp for .o
# and add other object files
_OBJS := $(patsubst %.cpp,%.o,$(notdir $(SRCS))) $(GLAD_OBJ) $(IMGUI_BACKENDS) $(IMGUI_EXTRAS)
# add the object directory to the front of the object files
OBJS := $(_OBJS:%=$(OBJ_DIR)/%)


.PHONY: main

main: obj $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

# compile sources not in base directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) -c

# compile sources in base directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) -c

# compile lib sources
$(OBJ_DIR)/%.o: $(LIB_DIR)/*/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) -c

$(OBJ_DIR)/%.o: $(LIB_DIR)/*/*/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) -c

$(OBJ_DIR)/%.o: $(LIB_DIR)/*/*/*/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) -c

obj: 
	mkdir -p obj



.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(TARGET_EXEC)


