#----------------------------------------------------#
CXX		  := g++
CXX_FLAGS := -std=c++20 #-Wno-nullability-completeness

PXX		  := python3

BUILD	:= build
SRC		:= src
INCLUDE	:= -I/opt/homebrew/include -I/include #-I/opt/homebrew/lib/vcpkg/installed/arm64-osx/include
LIB		:= /opt/homebrew/lib

LIBRARIES	:= #-lcurl #-lDataTable 
EXECUTABLE	:= main
#----------------------------------------------------#

all: $(BUILD)/$(EXECUTABLE)

run: clean all
	clear
	./$(BUILD)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

refresh:
	$(PXX) $(SRC)/getStockData.py

clean:
	-rm $(BUILD)/*