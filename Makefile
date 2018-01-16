export MAIN_DIR = main
export TEST_DIR = test
export PROGRAM	= tlc
export RUNNER	= runner.c

.PHONY: main test install doc clean

all: main test install doc

main:
	${MAKE} -C ${MAIN_DIR}

test:
	${MAKE} -C ${TEST_DIR}

install: main
	cp ${MAIN_DIR}/${PROGRAM} .

cunit:
	./compile_cunit

doc:
	doxygen

clean:
	${MAKE} -C ${MAIN_DIR} clean
	${MAKE} -C ${TEST_DIR} clean
	rm -rf *.svg ${PROGRAM} CUnit-2.1-3/ html/
