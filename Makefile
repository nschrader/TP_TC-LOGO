CC 		= gcc
LEX 	= flex
YACC 	= bison

CFLAGS  = -g
LDFLAGS = -lm
PROGRAM	= tc-logo
LEXERS 	= tc-logo.l
PARSERS = tc-logo.y
SOURCES = main.c ast.c instruction.c svg.c compiler.c
HEADERS = ${SOURCES:.c=.h}
TOKENS 	= ${PARSERS}.h ${LEXERS}.h

SRC = ${PARSERS}.c ${LEXERS}.c ${SOURCES}
HDR = ${HEADERS} ${TOKENS}
OBJ = ${SRC:.c=.o}

.PHONY: clean

all:		${OBJ} ${HDR}
	${CC} ${LDFLAGS} ${OBJ} -o ${PROGRAM}

%.l.c %.l.c:	%.l
	${LEX} --outfile=$<.c --header-file=$<.h $<

%.y.c %.y.h:	%.y
	${YACC} --output=$<.c --defines=$<.h $<

clean:
	rm -rf *.l.c *.l.h *.y.c *.y.h *.o *.svg ${PROGRAM}
