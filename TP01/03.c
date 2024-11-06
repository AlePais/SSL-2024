#include "sharedFunctions.h"
#define MAX_PILA 100

// Pilas
char pila_operadores[MAX_PILA];
int tope_operadores = -1;

int pila_calculo[MAX_PILA];
int tope_calculo = -1;

// Funciones pila de operadores
void pushOperador(char operador) {
    if (tope_operadores < MAX_PILA - 1) {
        tope_operadores++;
        pila_operadores[tope_operadores] = operador;
    } else {
        printf("Error: La pila de operadores está llena.\n");
    }
}

char popOperador() {
    if (tope_operadores >= 0) {
        char operador = pila_operadores[tope_operadores];
        tope_operadores--;
        return operador;
    }
    return '\0';
}

int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

int esOperador(char caracter) {
    return (caracter == '(' || caracter == ')' || caracter == '+' || 
            caracter == '-' || caracter == '*' || caracter == '/');
}

int operar(char operador, int operando1, int operando2) {
    switch (operador) {
        case '+': return operando1 + operando2;
        case '-': return operando1 - operando2;
        case '*': return operando1 * operando2;
        case '/': 
            if (operando2 != 0) return operando1 / operando2;
            else {
                printf("Error: Division por cero.\n");
                return 0;
            }
        default:
            printf("Error: Operador desconocido '%c'.\n", operador);
            return 0;
    }
}

void pushCalculo(int numero) {
    if (tope_calculo < MAX_PILA - 1) {
        tope_calculo++;
        pila_calculo[tope_calculo] = numero;
    } else {
        printf("Error: La pila de cálculos está llena.\n");
    }
}

int popCalculo() {
    if (tope_calculo >= 0) {
        int numero = pila_calculo[tope_calculo];
        tope_calculo--;
        return numero;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    char *cadena = NULL;
    char RPN[MAX_PILA] = {0};
    int indiceAuxiliar = 0;
    char delimitadores[] = " ";

    int operando1, operando2;

    if (argc < 2) {
        printf("*** Programa: Obtener resultado de operacion ***");
        printf("\n\n Modo de uso:");
        printf("\n\t Opcion 1: Ingrese cadena");
        printf("\n\t Opcion 2: Ingrese nombre de archivo (misma carpeta de %s)\n", argv[0]);
        return 1;
    }

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
        if (esOperador(caracter)) {
            if (caracter == '(') {
                pushOperador(caracter);
            } else if (caracter == ')') {
                char operadorAuxiliar;
                while ((operadorAuxiliar = popOperador()) != '(') {
                    RPN[indiceAuxiliar++] = ' ';
                    RPN[indiceAuxiliar++] = operadorAuxiliar;
                }
            } else {
                // Mientras haya operadores en la pila con mayor o igual precedencia, los sacamos
                while (tope_operadores >= 0 && precedencia(pila_operadores[tope_operadores]) >= precedencia(caracter)) {
                    RPN[indiceAuxiliar++] = ' ';
                    RPN[indiceAuxiliar++] = popOperador();
                }
                pushOperador(caracter);
            }
            RPN[indiceAuxiliar++] = ' ';
        } else {
            RPN[indiceAuxiliar++] = caracter;
        }
    }

    // Vaciamos la pila de operadores
    while (tope_operadores != -1) {
        RPN[indiceAuxiliar++] = ' ';
        RPN[indiceAuxiliar++] = popOperador();
    }

    // Tokenizacion y cálculo en notacion polaca inversa
    char *token = strtok(RPN, delimitadores);
    int numero;
    pushCalculo(0);

    while (token != NULL) {
        if (esOperador(token[0])) {
            operando2 = popCalculo();
            operando1 = popCalculo();
            numero = operar(token[0], operando1, operando2);
            pushCalculo(numero);
        } else {
            if (analizadorLexicoNumeros(token) == DECIMAL) {
                pushCalculo(stringToInt(token));
            } else {
                printf("ERROR: no se reconoce TOKEN: %s.\n", token);
                return 0;
            }
        }
        token = strtok(NULL, delimitadores);
    }

    printf("\n\tOperacion a calcular: %s\n\n", cadena);
    printf("*** Resultado ***\n");
    printf("\n\t%s = %d\n", cadena, popCalculo());

    if (esArchivo(argv[1]) && cadena) {
        free(cadena);
    }

    return 0;
}
