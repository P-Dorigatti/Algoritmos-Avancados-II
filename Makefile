# Nome do compilador
CXX = g++

# Flags do compilador (ativa avisos de erro e define a versão do C++)
CXXFLAGS = -Wall -Wextra -std=c++17

# Nome do arquivo executável final que será gerado
TARGET = meu_programa

# Encontra automaticamente todos os arquivos .cpp na pasta atual
SRCS = $(wildcard *.cpp)

# Transforma a lista de .cpp em uma lista de arquivos objeto (.o)
OBJS = $(SRCS:.cpp=.o)

# A regra padrão que será executada ao digitar apenas "make"
all: $(TARGET)

# Regra para "linkar" os arquivos objeto e gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar cada arquivo .cpp em um arquivo objeto .o separadamente
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar o projeto (apagar executável e arquivos .o)
clean:
	rm -f $(OBJS) $(TARGET)