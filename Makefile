#----------------------------------------------------#
CXX		  := g++
CXX_FLAGS := -std=c++20 -Wno-nullability-completeness

BUILD	:= build
SRC		:= src
INCLUDE	:= -I/opt/homebrew/include -I/include
LIB		:= /opt/homebrew/lib

LIBRARIES	:= -lcurl #-lDataTable 
EXECUTABLE	:= main
#----------------------------------------------------#

all: $(BUILD)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BUILD)/*