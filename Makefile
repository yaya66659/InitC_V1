CC = gcc
EXEC = bin/progInitC
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

# Compilation
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

obj/%.o: src/%.c
	$(CC) -c $< -o $@

clean :
	for %%f in (obj\*.o)do del /F /Q "%%f"

cleanall : clean
	del /F /Q bin\progInitC.exe