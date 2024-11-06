#ifndef SHARED_FUNCTIONS_H_
#define SHARED_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    DECIMAL = 2,
    OCTAL = 3,
    HEXADECIMAL = 5
} tipoNumero;

/**
* @fn esArchivo
* @brief Indica si una cadena corresponde a un nombre de archivo en la misma carpeta.
*/
int esArchivo(char *valor);

/**
* @fn archivoToVariable
* @brief Devuelve contenido de un archivo como string.
*/
char *archivoToVariable(char *valor);

/**
* @fn esSigno
* @brief Indica si caracter corresponde con "+" o "-".
*/
int esSigno(char caracter);

/**
* @fn esSigno
* @brief Indica si caracter es "x" o "X".
*/
int esEquis(char caracter);

/**
* @fn esCero
* @brief Indica si caracter es "0".
*/
int esCero(char caracter);

/**
* @fn esRango1a7
* @brief Indica si caracter pertenece al rango [1-7]".
*/
int esRango1a7(char caracter);

/**
* @fn esRango8a9
* @brief Indica si caracter pertenece al rango [8-9]".
*/
int esRango8a9(char caracter);

/**
* @fn esRangoAaF
* @brief Indica si caracter pertenece al rango [A-F] (hexadecimal)".
*/
int esRangoAaF(char caracter);

/**
* @fn esDecimal
* @brief Indica si caracter es decimal".
*/
int esDecimal(char caracter);

/**
* @fn tipoCaracter
* @brief Indica tipo de caracter (numero que representa caracter en tabla de transiciones)".
*/
int tipoCaracter(char caracter);

/**
* @fn automataFinitoDeterministico
* @brief Devuelve estado al que transiciona el automata desde estadoInicial y con caracterRecibido".
*/
int automataFinitoDeterministico(int estadoInicial, char caracter);

/**
* @fn stringToInt
* @brief Convierte un string de un numero entero y devuelve el entero correspondiente".
*/
int stringToInt(char *cadena);

/**
* @fn analizadorLexicoNumeros
* @brief Convierte un string de un numero entero y devuelve el entero correspondiente".
*/
int analizadorLexicoNumeros(char *cadena);

#endif /* SHARED_FUNCTIONS_H_ */


