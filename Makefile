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

# Caminho do SFML (ajuste se necessário)
ifeq ($(UNAME_S),Linux)
    SFML_INCLUDE = 
    SFML_LIB = 
else
	CXXFLAGS += -I/mingw64/include
	LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
endif

# Flags
CXXFLAGS = -Wall -Wextra -std=c++17 -DPROGRAM_VERSION=\"$(VERSION_NAME)\"
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Nome do executável
ifeq ($(UNAME_S),Linux)
    TARGET = $(BIN_DIR)/$(VERSION_NAME)
else
    TARGET = $(BIN_DIR)/$(VERSION_NAME).exe
endif

# Encontrar arquivos fonte (.cpp) com caminhos relativos
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Regra padrão
all: prepare $(TARGET)

# Criar diretórios necessários
prepare:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compilar cada arquivo fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

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

