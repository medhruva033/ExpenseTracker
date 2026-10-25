CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude

SOURCES = src/main.cpp src/Transaction.cpp src/ExpenseTracker.cpp src/Utils.cpp

TARGET = expense_tracker.exe

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	del /Q $(TARGET) 2>NUL