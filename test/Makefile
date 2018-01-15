CC 			= gcc
CFLAGS  = -g -I${DEPS_DIR} -DTEST_CASE -Wall
LDFLAGS = -lcunit -lm
TESTS		= ast_test.c instruction_test.c memory_leak.c
DEPS_DIR= ../${MAIN_DIR}
DEPS		= ast.c instruction.c

DPS = ${foreach DEP, ${DEPS}, ${DEPS_DIR}/${DEP}}
DPH = ${DPS:.c=.h}
SRC = ${RUNNER} ${TESTS}
HDR = ${TESTS:.c=.h}
EXE = ${RUNNER:.c=}
OBJ = ${SRC:.c=.c.o} ${DPS}

.PHONY: 		clean
.PRECIOUS: 	%.c.o

all: runner
	./${EXE}

runner:		${OBJ}
	${CC} ${LDFLAGS} ${OBJ} -o ${EXE}

%.c.o: ${DEPS_DIR}/%.c ${HDR} ${DPH}
	${CC} -c ${CFLAGS} $< -o $@

%.c.o: ./%.c ${DPH}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -rf *.c.o ${EXE}
