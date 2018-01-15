CC 		= gcc
LEX 	= flex
YACC 	= bison

CFLAGS  = -g
LDFLAGS = -lm
LEXERS 	= tc-logo.l
PARSERS = tc-logo.y
SOURCES = main.c ast.c instruction.c svg.c compiler.c
HEADERS = ${SOURCES:.c=.h}
TOKENS 	= ${PARSERS:.y=.y.h} ${LEXERS:.l=.l.h}

SRC = ${PARSERS:.y=.y.c} ${LEXERS:.l=.l.c} ${SOURCES}
HDR = ${HEADERS} ${TOKENS}
OBJ = ${SRC:.c=.c.o}

.PHONY: 		clean
.PRECIOUS: 	%.l.c %.l.h %.y.c %.y.h %.c.o

all:		${OBJ}
	${CC} ${LDFLAGS} ${OBJ} -o ${PROGRAM}

%.c.o: %.c ${HDR}
	${CC} -c ${CFLAGS} $< -o $@

%.l.c %.l.h:	%.l
	${LEX} --outfile=$<.c --header-file=$<.h $<

%.y.c %.y.h:	%.y
	${YACC} --output=$<.c --defines=$<.h $<

clean:
	rm -rf *.l.c *.l.h *.y.c *.y.h *.c.o *.svg ${PROGRAM} html
