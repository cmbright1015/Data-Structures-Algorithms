# Makefile for QuickSort and Input Generator
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

TARGETS = Bright_Caleb_QuickSort Bright_Caleb_InputFileGenerator

all: $(TARGETS)

Bright_Caleb_QuickSort: Bright_Caleb_QuickSort.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

Bright_Caleb_InputFileGenerator: Bright_Caleb_InputFileGenerator.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

Bright_Caleb_automated: Bright_Caleb_automated.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) *.o

wipe:
	rm -f Bright_Caleb_input_*.txt Bright_Caleb_output_*.txt
	rm -f Bright_Caleb_executionTime.txt Bright_Caleb_averageExecutionTime.txt

reset: clean wipe

.PHONY: all clean wipe reset