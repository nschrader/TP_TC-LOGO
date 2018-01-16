CC 			= gcc
CFLAGS 	= -g -Wall -I${DEPS_DIR} -I. -I.. -DTEST_CASE
LDFLAGS = -lm
CUNIT_A	= ../CUnit/libcunit.a
CUNIT_SO= -lcunit
TESTS		= ast_test.c instruction_test.c svg_test.c memory_leak.c misc.c
DEPS_DIR= ../${MAIN_DIR}
DEPS		= ast.c instruction.c svg.c

DPS = ${foreach DEP, ${DEPS}, ${DEPS_DIR}/${DEP}}
DPH = ${DPS:.c=.h}
SRC = ${RUNNER} ${TESTS}
HDR = ${TESTS:.c=.h}
EXE = ${RUNNER:.c=}
OBJ = ${SRC:.c=.c.o} ${DPS}

.PHONY: 		clean cunit
.PRECIOUS: 	%.c.o

all: runner
	./${EXE}

runner:	${OBJ}
	if [ -f "${CUNIT_A}" ]; \
	then ${CC} ${CFLAGS} ${LDFLAGS} ${OBJ} -o ${EXE} ${CUNIT_A}; \
	else ${CC} ${CFLAGS} ${LDFLAGS} ${CUNIT_SO} ${OBJ} -o ${EXE}; \
	fi

%.c.o: %.c ${HDR} ${DPH}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf *.c.o ${EXE}
