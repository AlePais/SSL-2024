

void agregarATablaDeSimbolos(char *id , int valor);
int reconocerIDconValor(char *id);
void iniciarTabla();
int buscarEspacioVacio();
int buscarId(char *id);

typedef struct{
    char id[32];
    int valor;
}tabla;