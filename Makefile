CXX=g++
CFLAGS=-Wall -std=c++17 -O3 -pedantic -Wextra
INCLUDES=
LIBS=
TARGET=main
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all : $(TARGET)

clean :
	rm -f $(TARGET) $(OBJ)

$(TARGET) : $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<
