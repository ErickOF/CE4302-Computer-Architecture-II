CC=gcc

SAXPY_DIR=01-saxpy
SAXPY_FILE=$(SAXPY_DIR)/saxpy
SAXPY_C=$(SAXPY_FILE).c

SAXPY_CL_FILE=$(SAXPY_DIR)/saxpy_gpu
SAXPY_CL_C=$(SAXPY_CL_FILE).c

MAT_MULT_DIR=02-mat-mult
MAT_MULT_FILE=$(MAT_MULT_DIR)/mat_mult
MAT_MULT_C=$(MAT_MULT_FILE).c

FLAGS=-lOpenCL -lm


saxpy:
		@# Compilation
		$(CC) -o $(SAXPY_FILE) $(SAXPY_C) $(FLAGS)
		$(CC) -o $(SAXPY_CL_FILE) $(SAXPY_CL_C) $(FLAGS)
		@# Execution
		./$(SAXPY_FILE)
		./$(SAXPY_CL_FILE)
		@# Clean
		rm -f $(SAXPY_FILE)
		rm -f $(SAXPY_CL_FILE)

mat-mult:
		$(CC) -o $(MAT_MULT_FILE) $(MAT_MULT_C) $(FLAGS)
		./$(MAT_MULT_FILE)
		rm -f $(MAT_MULT_FILE)
