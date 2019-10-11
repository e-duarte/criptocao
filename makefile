# makefile para a compilação do criptocão

#name of the project
PROJ_NAME=criptocao

#.c files
C_SOURCE=$(wildcard ./src/*.c)

#.h files
H_SOURCE=$(wildcard ./headers/*.h)

#Object files
OBJ=$(subst .c,.o,$(subst src,obj,$(C_SOURCE)))

#Compiler and linker
CC=gcc

#Flafs for compiler
CC_FLAGS=-c        \
         -W        \
		 -Wall     \
		 -ansi     \
		 -pedantic

#Command used at clean target
RM = rm -rf

#
#Compilation an linking
#

all: folder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o ./bin/$@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./obj/%.o: ./src/%.c ./headers/%.h
	@echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./obj/main.o: ./src/main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

folder:
	@ mkdir -p obj
	@ mkdir -p bin

clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@ $(RM) ./bin/* $(PROJ_NAME) *~
	@rmdir bin
	@rmdir obj
