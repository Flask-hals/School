# Kompilator och flaggor
CC := g++
FLAGS := -std=e++17 -Wall -Wextra -Wpedantic -Werror -Weffc++
LIB := -lsfml-window -lsfml-graphics -lsfml-system

# Källfiler och målfil
SRC_DIR=src
SOURCES := $(shell find $(SRC_DIR) -name '*.cc')
TARGET := start

# Standardregel
all: $(TARGET)

# Kompilera målfilen
$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(LIB)

# valgrind: $(TARGET)
# 	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=suppressions.txt ./$(TARGET)


# Städa upp
clean:
	rm -f $(TARGET)