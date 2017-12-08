CC 		= gcc
LEX 	= flex
YACC 	= bison

PROGRAM	= tc-logo
LEXERS 	= tc-logo.l
PARSERS = tc-logo.y
SOURCES = main.c ast.c
HEADERS = ${SOURCES:.c=.h}
TOKENS 	= ${PARSERS}.h ${LEXERS}.h

SRC = ${LEXERS}.c ${PARSERS}.c ${SOURCES}
HDR = ${HEADERS} ${TOKENS}
OBJ = ${SRC:.c=.o}

.PHONY: clean

all:		${OBJ}
	${CC} ${OBJ} -o ${PROGRAM}

%.o:		%.c ${HDR}
	${CC} ${CFLAGS} -c $< -o $@

%.l.c %.l.h:	%.l
	${LEX} --outfile=$<.c --header-file=$<.h $<

%.y.c %.y.h:	%.y
	${YACC} --output=$<.c --defines=$<.h $<

clean:
	rm -rf *.l.c *.l.h *.y.c *.y.h *.o ${PROGRAM}
