%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#ifndef yywrap
static int yywrap(void) { return 1; }
#endif
%}

INICIO inicio
FIN fin
LEER leer 
ESCRIBIR escribir
identificador  {Letra}({letraODigito}){0,31}
Letra          [a-zA-Z]
Digito         [0-9]
letraODigito   ({Letra}|{Digito})
constante      {Digito}+
asignacion     (:=)

%%
{INICIO} {return(INICIO);}
{FIN} {return(FIN);}
{LEER} {return(LEER);}
{ESCRIBIR} {return(ESCRIBIR);}
{identificador}       {yylval.id = strdup(yytext);return(identificador);}
{constante} 	      {yylval.cte = atoi(yytext); return(constante);}

"+" {return (suma);}
"-" {return (resta);}
{asignacion}          { return(asignacion); }
"("       {return (APAR);}
")"        {return (CPAR);}
[ \t\n]+ ;   // Ignora espacios y saltos de línea
"," {return(COMA);}
";" {return(PUNTOCOMA);}
.            ECHO;
%%

