%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tablaDeSimbolos.h"

int valorId(char* id);
int yylex();
void yyerror(const char *s);
extern FILE *yyin;
%}


%token INICIO FIN LEER ESCRIBIR PUNTOCOMA COMA suma resta asignacion APAR CPAR
%token <id> identificador
%token <cte> constante

%union {
    char* id;
    int cte;
}

%type <cte> expresion expresiones simbolo
%type <id> listaID

%%

programa: INICIO listaDeSentencias FIN;

listaDeSentencias:
                sentencia PUNTOCOMA
                | listaDeSentencias sentencia PUNTOCOMA // para hacerla recursiva en caso de varias sentencias
                ;

sentencia:
        LEER APAR listaID CPAR
        |ESCRIBIR APAR expresiones CPAR
        |identificador asignacion expresion {agregarATablaDeSimbolos($1,$3);}
        ;

listaID:
    identificador 
    | listaID COMA identificador
    ;

expresiones:
    expresion
    | expresiones COMA expresion
    ;

expresion:
    simbolo {$$ = $1;}
    | expresion suma simbolo  {$$ = $1 + $3;}
    | expresion resta simbolo  {$$ = $1 - $3;}
    ;

simbolo: 
    constante  {$$ = $1;}
    | identificador {$$ = valorId($1);}
    | APAR expresion CPAR {$$ = $2;}
    ;
%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <archivo_de_entrada>\n", argv[0]);
        return 1;
    }

    FILE *archivo = fopen(argv[1], "r");
    if (!archivo) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }
    yyin = archivo;
    
    iniciarTabla();
    
    if (yyparse() == 0) {
        printf("Análisis completado con éxito.\n");
    } else {
        printf("Se encontraron errores en el análisis.\n");
    }

    fclose(yyin);
    return 0;
} 
