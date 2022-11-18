CC=g++
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c++17
OUTPUT=teapot
SOURCE=main.cpp

ifeq ($(OS),Windows_NT)
	# Windows
	CFLAGS+= -lglu32 -lfreeglut -lopengl32
else
	# Others
	OS := $(shell uname)
	ifeq ($(OS),Linux)
		# Linux
		CFLAGS+= -lglut -lGL -lGLU
	endif
	ifeq ($(OS),Darwin)
		# Mac
		CFLAGS+= -framework OpenGL -framework GLUT
	endif
endif

.PHONY: clean

teapot:$(SOURCE)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCE)

clean:
	rm -rf $(OUTPUT)

run:teapot
	./$(OUTPUT)
