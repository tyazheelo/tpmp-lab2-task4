CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c11
TARGET = company_analyzer

# Директории
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

# Исходные файлы
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET_PATH = $(BIN_DIR)/$(TARGET)

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJECTS) | $(BIN_DIR) $(OBJ_DIR)
	$(CC) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET_PATH)
	./$(TARGET_PATH)

.PHONY: all clean run
