CC 			= gcc
CFLAGS  = -g -I..
LDFLAGS = -lcunit
RUNNER	= runner.c
TESTS		= ast_test.c
DEPS_DIR= ../
DEPS		= ast.c

DPS = ${foreach DEP, ${DEPS}, ${DEPS_DIR}${DEP}}
SRC = ${RUNNER} ${TESTS} ${DPS}
HDR = ${TESTS:.c=.h} ${DPS:.c=.h}
EXE = ${RUNNER:.c=}
OBJ = ${SRC:.c=.c.o}

.PHONY: 		clean
.PRECIOUS: 	%.c.o

all: runner
	./${EXE}

runner:		${OBJ}
	${CC} ${LDFLAGS} ${OBJ} -o ${EXE}

%.c.o: %.c ${HDR}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -rf *.c.o ${RUNNER}
