#include "sharedFunctions.h"

int main(int argc, char *argv[]) {
    char *cadena = NULL;
    int estado = 0;
    int cant_octales = 0;
    int cant_decimales = 0;
    int cant_hexadecimales = 0;
    int cant_no_reconocidas = 0;

    if (argc < 2) {
        printf("*** Programa: Clasificador de tipos de numeros ***");
        printf("\n\n Modo de uso:");
        printf("\n\t Opcion 1: Ingrese cadena con numeros separados por #");
        printf("\n\t Opcion 2: Ingrese nombre de archivo (misma carpeta de %s)\n", argv[0]);
        return 1;
    }

    // Determinar si el argumento es un archivo o una cadena directa
    if (esArchivo(argv[1])) {
        cadena = archivoToVariable(argv[1]);
        if (cadena == NULL) {
            printf("Error al leer el archivo.\n");
            return 1;
        }
    } else {
        cadena = argv[1];
    }

    for (int i = 0; cadena[i] != '\0'; i++) {
        char caracter = cadena[i];
        
        if (caracter == '#') {
            // Reiniciar estado al encontrar un separador
            estado = 0;
            continue;
        }

        estado = automataFinitoDeterministico(estado, caracter);

        // Si el próximo caracter es un separador o el fin de la cadena, procesar el estado
        if (cadena[i+1] == '#' || cadena[i+1] == '\0') {
            switch (estado) {
                case DECIMAL:
                    cant_decimales++;
                    break;
                case OCTAL:
                    cant_octales++;
                    break;
                case HEXADECIMAL:
                    cant_hexadecimales++;
                    break;
                default:
                    cant_no_reconocidas++;
                    break;
            }
            estado = 0;  // Reiniciar estado para el próximo número
        }
    }

    printf("\n\tCadena a analizar: %s\n\n", cadena);
    printf("*** Resultado ***\n");
    printf("\n\tDecimales: %d\n\tOctales: %d\n\tHexadecimales: %d\n\tNo reconocidos: %d\n",
           cant_decimales, cant_octales, cant_hexadecimales, cant_no_reconocidas);
    
    // Liberar memoria si fue asignada dinámicamente
    if (esArchivo(argv[1]) && cadena) {
        free(cadena);
    }

    return 0;
}
