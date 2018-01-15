CC 			= gcc -g -I${DEPS_DIR} -I. -DTEST_CASE -Wall
LDFLAGS = -lcunit -lm
TESTS		= ast_test.c instruction_test.c svg_test.c memory_leak.c
DEPS_DIR= ../${MAIN_DIR}
DEPS		= ast.c instruction.c svg.c

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

%.c.o: %.c ${HDR} ${DPH}
	${CC} -c $< -o $@

clean:
	rm -rf *.c.o ${EXE}
