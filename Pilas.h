#ifndef PILA_H
#define PILA_H

#ifndef NOMBRE_MAXIMO
#define NOMBRE_MAXIMO 30
#endif // NOMBRE_MAXIMO

#ifndef TEXTO_MAXIMO
#define TEXTO_MAXIMO 160
#endif // TEXTO_MAXIMO

#ifndef LONGITUD_FECHA
#define LONGITUD_FECHA 11
#endif // LONGITUD_FECHA


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

void vaciaP(Pila *);
int esVaciaP(Pila );
void apilar(Pila *, Comentario );
void desapilar(Pila *);
void tope(Pila , Comentario *, int *);
void destruirP(Pila *);


#endif
