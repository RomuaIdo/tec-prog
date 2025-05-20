FROM archlinux:latest

# Instalar dependências do sistema
RUN pacman -Sy --noconfirm base-devel git cmake \
    sfml

# Criar diretório de trabalho
WORKDIR /app

# Copiar arquivos do projeto
COPY . .

# Compilar o projeto por padrão
RUN make

# Comando para executar o jogo (pode ser alterado se necessário)
CMD ["make", "run"]

