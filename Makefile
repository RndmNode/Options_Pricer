#----------------------------------------------------#
CXX		  	:= g++
CXX_FLAGS 	:= -std=c++20

PXX		  	:= python3

BUILD	  	:= build
SRC		  	:= src
INCLUDE	  	:= -I/opt/homebrew/include -I/include
LIB		  	:= /opt/homebrew/lib

LIBRARIES	:= -lmatplot -lpthread
EXECUTABLE	:= main
#----------------------------------------------------#

all: $(BUILD)/$(EXECUTABLE)

# clean build, refresh stock data, and run everything
run: clean refresh_stock_data all
	clear
	./$(BUILD)/$(EXECUTABLE)

# just run .cpp
test: clean all
	clear
	./$(BUILD)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

# use python for api call to get latest stock data
refresh_stock_data:
	clear
	$(PXX) $(SRC)/getStockData.py

# clear out the last build
clean:
	-rm $(BUILD)/*