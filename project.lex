%{
#include <math.h>
#include "project.tab.h"
%}

%option yylineno
%option noyywrap
DIGIT	[0-9]
LETTER	[a-zA-Z]

%%
[\n]						;										
[\t ]+						;
mainprog					{ return KW_MAIN;		}
function					{ return KW_FUNC;		}
procedure					{ return KW_PROC;		}
begin						{ return KW_BEGIN;		}
end							{ return KW_END;		}
int							{ return KW_INT;		}
float						{ return KW_FLOAT;		}
if							{ return KW_IF;			}
then						{ return KW_THEN;		}
else						{ return KW_ELSE;		}
elif						{ return KW_ELIF;		}
nop							{ return KW_NOP;		}
for							{ return KW_FOR;		}
while						{ return KW_WHILE;		}
return						{ return KW_RETURN;		}
print						{ return KW_PRINT;		}
in							{ return KW_IN;			}
{DIGIT}+					{ 
	yylval.ival = atoi(yytext);
	return INTEGER;
							}
{DIGIT}+"."{DIGIT}+			{
	yylval.fval = atof(yytext);
	return FLOAT;
							}
{LETTER}({LETTER}|{DIGIT})*	{ yylval.sval = strdup(yytext); return ID;			}
"+"							{ yylval.sval = strdup(yytext); return OP_ADD;		}
"-"							{ yylval.sval = strdup(yytext); return OP_SUB;		}
"*"							{ yylval.sval = strdup(yytext); return OP_MUL;		}
"/"							{ yylval.sval = strdup(yytext); return OP_DIV;		}
"<"							{ yylval.sval = strdup(yytext); return OP_LT;		}
"<="						{ yylval.sval = strdup(yytext); return OP_LE;		}
">="						{ yylval.sval = strdup(yytext); return OP_GE;		}
">"							{ yylval.sval = strdup(yytext); return OP_GT;		}
"=="						{ yylval.sval = strdup(yytext); return OP_EQUAL;	}
"!="						{ yylval.sval = strdup(yytext); return OP_NOTEQ;	}
"!"							{ yylval.sval = strdup(yytext); return OP_NEG;		}
";"							{ yylval.sval = strdup(yytext); return DL_SMCOLON;	}
"."							{ yylval.sval = strdup(yytext); return DL_DOT;		}
","							{ yylval.sval = strdup(yytext); return DL_COMMA;	}
"="							{ yylval.sval = strdup(yytext); return DL_ASSIGN;	}
"("							{ yylval.sval = strdup(yytext); return DL_LPAREN;	}
")"							{ yylval.sval = strdup(yytext); return DL_RPAREN;	}
"["							{ yylval.sval = strdup(yytext); return DL_LBRACK;	}
"]"							{ yylval.sval = strdup(yytext); return DL_RBRACK;	}
":"							{ yylval.sval = strdup(yytext); return DL_COLON;	}
.							{ return strdup(strdup(yytext))[0];		}
%%
