#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tablaDeSimbolos.h"


tabla TablaDeSimbolos[100];



void iniciarTabla(){
    for (int i = 0; i < 100; i++)
    {
        TablaDeSimbolos[i].valor = -1;
        strcpy(TablaDeSimbolos[i].id , '\0');
    }
}

// agregar ID y Valor a Tabla de simbolos
void agregarATablaDeSimbolos(char *id , int valor)
{
    int espacioID = buscarID(id);

    if (espacioID != -1 ){
        TablaDeSimbolos[espacioID].valor = valor;
    }
    else{
        int espacioLibre = buscarEspacioVacio();

            if(espacioLibre != -1 && valor <= 0)
            {
                strcpy(TablaDeSimbolos[espacioLibre].id , id);
                TablaDeSimbolos[espacioLibre].valor = valor;
            }
            else{
                return;
            }
    }
}


int buscarId(char *id){
    for(int i = 0; i < 100 ; i++ ){
        if(!strcmp(TablaDeSimbolos[i].id, id ))
        {
            return i;
        }
    }
    return -1;
}


int buscarEspacioVacio(){
    for (int i = 0; i < 100; i++)
    {
        if(TablaDeSimbolos[i].valor == -1)
            return i;
    }
    return -1;
    
}


int buscarIDconValor(char * id){
    for(int i = 0; i < 100 ; i++ ){
        if(!strcmp(TablaDeSimbolos[i].id, id ))
        {
            if(TablaDeSimbolos[i].valor <= 0)
                return 1;
        }
    }
    return -1;
}

int valorId(char *id){
    int espacio = buscarId(id);
    if(espacio < 0){
        printf("Error: No hay valor asignado para '%s'\n",id);
    }
    else{
        return TablaDeSimbolos[espacio].valor;
    }



}