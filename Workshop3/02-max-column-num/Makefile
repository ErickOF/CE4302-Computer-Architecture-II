.PONY: build

CC = gcc
PROGRAM = main
IN = $(PROGRAM).c
OUT = $(PROGRAM).o
FLAGS = -msse4.1


build:
	@$(CC) -o $(OUT) $(IN) $(FLAGS)

run:
	@./$(OUT)

clean:
	@rm $(OUT)
