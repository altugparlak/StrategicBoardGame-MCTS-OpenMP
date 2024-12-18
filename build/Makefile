CC = clang
CFLAGS = -fopenmp -lstdc++

HEADERS_INCLUDE = "$(shell pwd)/../include"

OPENMP_INCLUDE_PATH = "$(shell brew --prefix libomp)/include"
OPENMP_LIBRARY_PATH = "$(shell brew --prefix libomp)/lib"

TARGET = main.exe

SRC = ../src/main.cpp ../src/Mcst.cpp ../src/McstNode.cpp ../tester/UnitTester.cpp
INCLUDE_FLAGS = -I$(HEADERS_INCLUDE) -I$(OPENMP_INCLUDE_PATH)

$(TARGET): $(SRC)
	CPATH=$(OPENMP_INCLUDE_PATH) LIBRARY_PATH=$(OPENMP_LIBRARY_PATH) \
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(INCLUDE_FLAGS)

clean:
	rm -f $(TARGET)
