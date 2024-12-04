all: main

CXX = g++
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp GameOfLife.cpp ConsoleMode.cpp GraphicsMode.cpp
HEADERS = GameOfLife.h ConsoleMode.h GraphicsMode.h

main: $(SRCS) $(HEADERS)
	$(CXX) $(SRCS) -o game_of_life $(CXXFLAGS)

build: main

clean:
	rm -f game_of_life
	rm -f output_*.txt