CC = gcc
EXEC = bin/yann03
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
	del /F /Q bin\yann03.exe