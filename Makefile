all: main

CXX = g++
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp JeuDeLaVie.cpp ModeConsole.cpp ModeGraphique.cpp
HEADERS = JeuDeLaVie.h ModeConsole.h ModeGraphique.h

main: $(SRCS) $(HEADERS)
	$(CXX) $(SRCS) -o launch $(CXXFLAGS)

build: main

clean:
	rm -f launch
	rm -f output_*.txt