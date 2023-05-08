C_SOURCES = $(shell find . -name "*.c")
CPP_SOURCES = $(shell find . -name "*.cpp")
OBJ = ${C_SOURCES:.c=.o}
CPPOBJ = ${CPP_SOURCES:.cpp=.o}

CPPC = g++
CC = gcc
NAME = test
CPPFLAGS = -std=gnu++17 -O3 -Iinclude -Isrc -g -Wall
CFLAGS = -std=c11 -O0 -Iinclude -Isrc -g -Wall
LDFLAGS = -lGL -lglfw3 -ldl

all: ${NAME}

${NAME}: ${OBJ} ${CPPOBJ}
	${CPPC} -o ${NAME} ${OBJ} ${CPPOBJ} ${LDFLAGS}

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

%.o: %.cpp
	${CPPC} ${CPPFLAGS} -o $@ -c $<

run: ${NAME}
	./${NAME}

clean-obj:
	find . -name \*.o -type f -delete

clean: clean-obj
	rm ${NAME}
