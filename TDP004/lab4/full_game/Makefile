FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Weffc++ -g -I. -ICode -IYOUR_CODE_HERE
LIB = -lsfml-graphics -lsfml-system -lsfml-window

pacman: Code/main.cc game.o entity.o pacman.o ghost_wrapper.o grid.o student_code.o
	g++ $(FLAGS) -o pacman Code/main.cc game.o entity.o pacman.o ghost_wrapper.o grid.o student_code.o $(LIB)

student_code.o: $(shell find YOUR_CODE_HERE -type f)
	g++ -o student_code.o $(FLAGS) -c YOUR_CODE_HERE/*.cc

%.o: Code/%.cc Code/%.h
	g++ $(FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f *.o ./pacman
