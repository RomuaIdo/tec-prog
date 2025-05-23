# Compiladores
ifeq ($(OS),Windows_NT)
    CXX = g++
    TARGET = bin/$(VERSION_NAME).exe
    SFML_PATH = C:/SFML-2.6.2
    LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
    CXXFLAGS += -I$(SFML_PATH)/include
else
    CC = gcc
    CXX = g++
    TARGET = bin/$(VERSION_NAME)
    LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
endif

# Flags
CFLAGS = -Wall -Wextra -std=c11 -DPROGRAM_VERSION=\"$(VERSION_NAME)\"
CXXFLAGS = -Wall -Wextra -std=c++17 -DPROGRAM_VERSION=\"$(VERSION_NAME)\"

# Nome do programa (usa nome do diretório atual)
VERSION_NAME := $(notdir $(CURDIR))

# Configuração de pastas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Encontrar arquivos fonte
ifeq ($(OS),Windows_NT)
    SRCS = $(shell powershell -Command "Get-ChildItem -Path $(SRC_DIR) -Recurse -Filter *.cpp | ForEach-Object { $$_.FullName }")
else
    SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
endif

# Gerar lista de objetos
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Regra padrão
all: prepare $(TARGET)

# Criar diretórios necessários
prepare:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Linkar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilar cada arquivo fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Build limpo!"

.PHONY: all prepare run clean
