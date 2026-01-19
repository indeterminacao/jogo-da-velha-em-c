NOME_PROJETO = jogo_da_velha
CC = gcc
FONTES = main.c funcs.c

all:
	$(CC) $(FONTES) -o $(NOME_PROJETO)

clean:
	rm -f $(NOME_PROJETO) $(NOME_PROJETO).exe