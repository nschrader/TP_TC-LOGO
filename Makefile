CC 		= gcc
LEX 	= flex
YACC 	= bison

PROGRAM	= tc-logo
LEXERS 	= tc-logo.l
PARSERS = tc-logo.y
SOURCES = ast.c
HEADERS = ${SOURCES:.c=.h}
TOKENS 	= ${PARSERS}.h

SRC = ${LEXERS}.c ${PARSERS}.c ${SOURCES}
HDR = ${HEADERS} ${TOKENS}
OBJ = ${SRC:.c=.o}

.PHONY: clean

all:		${OBJ}
	${CC} ${OBJ} -o ${PROGRAM}

%.o:		%.c ${HDR}
	${CC} ${CFLAGS} -c $< -o $@

%.l.c:	%.l
	${LEX} --outfile=$@ $<

%.y.c:	%.y
	${YACC} --output=$@ --defines=${@:.c=.h} $<

%.y.h:	%.y.c
	true #If there are tokens to be generated in a header, Bison did it already

clean:
	rm -rf *.l.c *.y.c *.y.h *.o ${PROGRAM}
