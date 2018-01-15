%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #define YYERROR_VERBOSE
%}

%code requires {
  #include "ast.h"
  #include "main.h"
}

%parse-param { Program** program }
%union {
  uint val;
  char* str;
  Program* prog;
  Instruction* inst;
  RepeatInstruction* rept;
  AtomicInstruction* atmc;
}

%token <val> TOKEN_UINT
%token       TOKEN_LEFT
%token       TOKEN_RIGHT
%token       TOKEN_FORWARD
%token       TOKEN_REPEAT
%token       TOKEN_L_BRACKET
%token       TOKEN_R_BRACKET

%type <prog> result
%type <prog> program
%type <inst> instruction
%type <rept> repeatInstruction
%type <atmc> atomicInstruction
%type <val>  value

%%

result
  :program              { *program = $1; }

program
  :instruction          { $$ = newProgram(NULL, $1); }
  |program instruction  { $$ = newProgram($1, $2); }
  ;

instruction
  :atomicInstruction    { $$ = asInstruction($1); }
  |repeatInstruction    { $$ = asInstruction($1); }
  ;

repeatInstruction
  :TOKEN_REPEAT value TOKEN_L_BRACKET program TOKEN_R_BRACKET
                        { $$ = newRepeatInstruction($2, $4); }
  ;

atomicInstruction
  :TOKEN_FORWARD value  { $$ = newAtomicInstruction(FORWARD, $2); }
  |TOKEN_LEFT value     { $$ = newAtomicInstruction(LEFT, $2); }
  |TOKEN_RIGHT value    { $$ = newAtomicInstruction(RIGHT, $2); }
  ;

value
  :TOKEN_UINT           { $$ = $1; }

%%

int yyerror(YYSTYPE *locp, char const *msg) {
  if (strlen(locp->str) > 0) {
    fprintf(stderr, "\n[Fatal]: %s \"%s\"\n", msg, locp->str);
  } else {
    fprintf(stderr, "\n[Fatal]: %s\n", msg);
  }
  exit(EXIT_FAILURE);
}
