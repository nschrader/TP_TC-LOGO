%{
  #include "tc-logo.y.h"
%}

%option noyywrap

UNIT       [1-9][0-9]*
LEFT       (?i:"LEFT")
RIGHT      (?i:"RIGHT")
REPEAT     (?i:"REPEAT")
FORWARD    (?i:"FORWARD")
L_BRACKET  \[
R_BRACKET  \]
BLANK      [ \r\n\t]*
DEFAULT    .|\n

%%

{UNIT}       { yylval.val = atoi(yytext); return TOKEN_UINT; }
{LEFT}       { return TOKEN_LEFT; }
{RIGHT}      { return TOKEN_RIGHT; }
{REPEAT}     { return TOKEN_REPEAT; }
{FORWARD}    { return TOKEN_FORWARD; }
{L_BRACKET}  { return TOKEN_L_BRACKET; }
{R_BRACKET}  { return TOKEN_R_BRACKET; }
{BLANK}      { }
{DEFAULT}    { YYSTYPE r; r.str = yytext; yyerror(&r, "Unrecognized character"); }

%%
