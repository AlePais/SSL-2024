#include "sharedFunctions.h"

int esArchivo(char *valor) {
    FILE *archivo = fopen(valor, "r");
    if (archivo) {
        fclose(archivo);
        return 1;
    }
    return 0;
}

char *archivoToVariable(char *valor) {
    FILE *archivo = fopen(valor, "r");
    if (!archivo) return NULL;

    fseek(archivo, 0, SEEK_END);
    long tamanio = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char *contenido = malloc(tamanio + 1);
    if (!contenido) {  // Verificar si se asignó la memoria
        fclose(archivo);
        return NULL;
    }

    fread(contenido, 1, tamanio, archivo);
    contenido[tamanio] = '\0';
    fclose(archivo);
    return contenido;
}

int esSigno(char caracter) {
    return (caracter == '+' || caracter == '-');
}

int esEquis(char caracter) {
    return (caracter == 'x' || caracter == 'X');
}

int esCero(char caracter) {
    return (caracter == '0');
}

int esRango1a7(char caracter) {
    return (caracter >= '1' && caracter <= '7');
}

int esRango8a9(char caracter) {
    return (caracter >= '8' && caracter <= '9');
}

int esRangoAaF(char caracter) {
    return (caracter >= 'A' && caracter <= 'F');
}

int esDecimal(char caracter) {
    return (esCero(caracter) || esRango1a7(caracter) || esRango8a9(caracter));
}

int tipoCaracter(char caracter) {
    if (esSigno(caracter))
        return 0;
    if (esEquis(caracter))
        return 1;
    if (esCero(caracter))
        return 2;
    if (esRango1a7(caracter))
        return 3;
    if (esRango8a9(caracter))
        return 4; 
    if (esRangoAaF(caracter))
        return 5;
    return 6;  // Para cualquier otro tipo de carácter
}

int automataFinitoDeterministico(int estadoInicial, char caracterRecibido) {
    int tablaDeTransicion[7][7] = {
        {1, 6, 3, 2, 2, 6, 6},
        {6, 6, 2, 2, 2, 6, 6},
        {6, 6, 2, 2, 2, 6, 6},
        {6, 4, 3, 3, 6, 6, 6},
        {6, 6, 5, 5, 5, 5, 6},
        {6, 6, 5, 5, 5, 5, 6},
        {6, 6, 6, 6, 6, 6, 6}
    };

    int tipo_caracter = tipoCaracter(caracterRecibido);
    return tablaDeTransicion[estadoInicial][tipo_caracter];
}

int stringToInt(char *cadena){
	int numero = 0;
    int i = 0;

    while (cadena[i] != '\0') {
        numero = numero * 10 + (cadena[i] - '0');
        i++;
    }

    return numero;
}

    
int analizadorLexicoNumeros(char *cadena){
    int estado = 0;

    for (int i = 0; cadena[i] != '\0'; i++) {
        estado = automataFinitoDeterministico(estado, cadena[i]);
    }
    return estado;
}