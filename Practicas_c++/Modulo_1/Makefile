CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++11
DEPS = lugar.hpp trazado.hpp
OBJ = lugar.o trazado.o

ifeq ($(OS),Windows_NT) 
RM=del /Q /F
EXT=.exe
else
RM=rm -rf
EXT=
endif

all: test_trazado optimizar_trazado

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_trazado: $(OBJ) test_trazado.o
	$(CC) -o $@ $^ $(CFLAGS)

optimizar_trazado: $(OBJ) optimizar_trazado.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-$(RM) test_trazado$(EXT) optimizar_trazado$(EXT) *.o

optimizar: optimizar_trazado
	./optimizar_trazado

test: test_trazado
	./test_trazado

.PHONY: clean all test optimizar

