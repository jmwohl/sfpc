# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

#LFLAGS = -L/usr/local/lib

LIBS = -lopencv_core -lopencv_highgui -lopencv_imgproc

# the build target executable:
TARGET = ErodeDilate

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LIBS) -v

clean:
	$(RM) $(TARGET)
	$(RM) -R $(TARGET).dSYM

run: 
	./$(TARGET) lena.jpg
