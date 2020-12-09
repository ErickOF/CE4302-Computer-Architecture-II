CC=gcc

DEVICES_FILE=devices
DEVICES_C=$(DEVICES_FILE).c

HELLO_FILE=hello
HELLO_C=$(HELLO_FILE).c

FLAGS=-lOpenCL


devices:
		$(CC) -o $(DEVICES_FILE) $(DEVICES_C) $(FLAGS)
		./$(DEVICES_FILE)
		rm -f $(DEVICES_FILE)

hello:
		$(CC) -o $(HELLO_FILE) $(HELLO_C) $(FLAGS)
		./$(HELLO_FILE)
		rm -f $(HELLO_FILE)
