# Nome do programa (usa o nome do diretório atual)
VERSION_NAME := $(notdir $(CURDIR))

# Detectar sistema operacional
UNAME_S := $(shell uname -s)

# Compilador
CXX = g++

# Diretórios padrão
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Configurações específicas por plataforma
ifeq ($(UNAME_S),Linux)
    # Configurações para Linux
    SFML_INCLUDE = 
    SFML_LIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
    TARGET = $(BIN_DIR)/$(VERSION_NAME)
    CXXFLAGS += -I/usr/include/SFML
else
    # Configurações para Windows (MSYS2 UCRT64)
    SFML_INCLUDE = -I/mingw64/include
    SFML_LIB = -L/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
    TARGET = $(BIN_DIR)/$(VERSION_NAME).exe
    CXXFLAGS += -I/mingw64/include
    LDFLAGS += -static-libgcc -static-libstdc++
endif

# Flags comuns
CXXFLAGS += -Wall -Wextra -std=c++17 -DPROGRAM_VERSION=\"$(VERSION_NAME)\"
DEBUG_FLAGS = -g
LDFLAGS += $(SFML_LIB)

# Encontrar arquivos fonte (.cpp) com caminhos relativos
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Regra padrão
all: prepare $(TARGET)

# Regra para build com debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: all


# Criar diretórios necessários
prepare:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compilar cada arquivo fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

# Linkar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos de build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Build limpo!"

.PHONY: all prepare run clean
