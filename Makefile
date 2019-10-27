OBJS=main.cpp Program.cpp Entity.cpp Glider.cpp Manager.cpp utils.cpp Enemy.cpp

CC=g++

INCLUDE_PATHS= -I/usr/local/include

LIBRARY_PATHS= -L/usr/local/lib 

COMPILER_FLAGS=-Wall -Werror --std=c++11

LINKER_FLAGS=-framework OpenGL -lglfw -lglew

TARGET=sourbuddy

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TARGET)