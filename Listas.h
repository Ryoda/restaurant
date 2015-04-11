#ifndef LISTA_USERS_H_INCLUDED
#define LISTA_USERS_H_INCLUDED

#ifndef DESCRIPCION_MAXIMA
#define DESCRIPCION_MAXIMA 160
#endif // TEXTO_MAXIMO

#ifndef TEXTO_MAXIMO
#define TEXTO_MAXIMO 500
#endif // TEXTO_MAXIMO

#ifndef NOMBRE_MAXIMO
#define NOMBRE_MAXIMO 50
#endif // NOMBRE_MAXIMO

#ifndef INGREDIENTES_MAX
#define INGREDIENTES_MAX 70
#endif // INGREDIENTES_MAX

#ifndef PASOS_MAX
#define PASOS_MAX 15
#endif // PASOS_MAX

#ifndef MAX_TAGS
#define MAX_TAGS 15
#endif // MAX_PATH

#ifndef LONGITUD_FECHA
#define LONGITUD_FECHA 11
#endif // LONGITUD_FECHA

//Tipos de dato

#ifndef STRUCT_PILA  //Pila de comentarios
#define STRUCT_PILA
typedef struct
{
    char username[NOMBRE_MAXIMO], texto[TEXTO_MAXIMO], fecha[LONGITUD_FECHA];
    float rating;
}Comentario;

typedef struct _NodoPila
{
    Comentario informacion;
    struct _NodoPila * siguiente;
}NodoPila;

typedef struct{
    NodoPila *primero;
}Pila;
#endif // STRUCT_PILA

typedef struct
{
    unsigned short int codigo;
    char nombre[NOMBRE_MAXIMO], descripcion[DESCRIPCION_MAXIMA], pasos[PASOS_MAX][DESCRIPCION_MAXIMA], ingredientes[INGREDIENTES_MAX][DESCRIPCION_MAXIMA], tags[MAX_TAGS][NOMBRE_MAXIMO], username[NOMBRE_MAXIMO];
    float rating;
    Pila comentarios;
}Receta;

typedef struct
{
    char username[NOMBRE_MAXIMO];
    float rating;
    int cantidadRecetas;
}Usuario;

//union para los datos Receta, Usuario y Compentario
typedef union
{
    Receta receta;
    Usuario usuario;
}Tipo;

typedef struct _Nodo
{
    Tipo informacion;
    struct _Nodo * siguiente;
}Nodo;

typedef struct
{
    int longitud;
    Nodo * primero, *ultimo;
}Lista;



void vacia(Lista *);
int esVacia(Lista);
void insertar(Lista *, Tipo, int);
void eliminar(Lista *, int);
void consultar(Lista, int, Tipo*);
void destruir(Lista *);
void imprimir(Lista);
int longitud(Lista);

#endif // LISTAS_H_INCLUDED
