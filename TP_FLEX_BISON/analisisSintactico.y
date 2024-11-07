%{
#include <stdlib.h>
#include <stdio.h>
int yylex();
void yyerror(const char *s);
extern FILE *yyin;
%}
%token INICIO FIN LEER ESCRIBIR identificador PUNTOCOMA COMA constante operadorAditivo asignacion APAR CPAR

%%
programa: INICIO listaDeSentencias FIN;

listaDeSentencias:
                sentencia PUNTOCOMA
                | listaDeSentencias sentencia PUNTOCOMA // para hacerla recursiva en caso de varias sentencias
                ;

sentencia:
        LEER APAR expresion CPAR
        |ESCRIBIR APAR expresion CPAR
        |identificador asignacion expresion
        ;

expresion:
        APAR expresion CPAR
        | expresion operador expresion
        | identificador
        | constante
        ;

operador: 
        COMA
        | operadorAditivo
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
    
    if (yyparse() == 0) {
        printf("Análisis completado con éxito.\n");
    } else {
        printf("Se encontraron errores en el análisis.\n");
    }

    fclose(yyin);
    return 0;
} 
