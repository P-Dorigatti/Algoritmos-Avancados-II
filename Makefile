# Compilador e padrão da linguagem
CXX = g++

# A flag '-g' é crucial aqui: ela inclui os símbolos de debug para que o 
# Valgrind e o ASan mostrem a linha exata do código onde ocorreu o erro.
CXXFLAGS = -Wall -Wextra -Wshadow -O2 -std=c++17 -g

# Encontra todos os arquivos .cpp
SRCS = $(wildcard */*/*.cpp)

# Define o nome dos executáveis
TARGETS = $(SRCS:.cpp=.out)

# Regra padrão executada ao digitar apenas 'make'
all: $(TARGETS)

# Regra genérica de compilação
%.out: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Compilado: $@"

# ==========================================
# 1. VALGRIND (Análise dinâmica tradicional)
# ==========================================
# Como usar: make valgrind PROG=01_grafos/exercicio/solution.out
valgrind:
	@if [ -z "$(PROG)" ]; then \
		echo "Erro: Especifique o programa. Uso: make valgrind PROG=caminho/para/arquivo.out"; \
		exit 1; \
	fi
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROG)

# ==========================================
# 2. ADDRESS SANITIZER (Ferramenta moderna embutida no g++)
# ==========================================
# Como usar: make asan
# Isso recompila todo o projeto injetando verificadores de memória diretamente no binário.
asan: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer -O0
asan: clean all

# Limpeza
clean:
	rm -f $(TARGETS)
	@echo "Binários removidos."