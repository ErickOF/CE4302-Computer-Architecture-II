.PONY: run-ex1 run-ex2


CC=gcc
#$(BUILD_FLAGS)=
LIB_FLAGS=-lpthread

MAIN1=exercise1
MAIN2=exercise2


run-ex1:
	@$(CC) -o $(MAIN1).o $(MAIN1).c $(LIB_FLAGS)
	@./$(MAIN1).o

run-ex2:
	@$(CC) -o $(MAIN2).o $(MAIN2).c $(LIB_FLAGS)
	@./$(MAIN2).o
