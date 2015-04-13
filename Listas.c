#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listas.h"

void vacia(Lista *lista)
{
    lista->longitud = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
}

int esVacia(Lista lista)
{
    int retorno;
    if(lista.primero == NULL || lista.longitud == 0)
    {
        if(lista.longitud == 0 && lista.primero == NULL)
        {
             retorno = 1;
        }else
        {
            retorno = -1;
        }

    }else
    {
        retorno = 0;
    }
    return(retorno);
}

void insertar(Lista * lista, Tipo elemento, int posicion)
{
    Nodo * nuevo, * actual, * siguiente;
    int i;
    if(posicion < 1 || posicion > lista->longitud + 1)
    {
        fprintf(stderr, "Error: Se intento insertar un elemento en una posicion invalida de la lista\n");
    }else
    {
         if((nuevo = (Nodo *) malloc(sizeof(Nodo))) == NULL)
        {
            fprintf(stderr, "Error: Malloc termino inesperadamente\n");
        }else
        {
            nuevo->informacion = elemento;
            nuevo->siguiente = NULL;
            if(posicion == 1)
            {
               nuevo->siguiente = lista->primero;
               lista->primero = nuevo;
            }else
            {
                actual = lista->primero;
                for(i = 2; i < posicion; i++)
                {
                    actual = actual->siguiente;
                }
                siguiente = actual->siguiente;
                actual->siguiente = nuevo;
                nuevo->siguiente = siguiente;
            }
            lista->longitud = lista->longitud + 1;
        }
    }
}

void eliminar(Lista *lista, int posicion)
{
    Nodo * actual, * anterior, * siguiente;
    int i;
    if(posicion < 1 || posicion > lista->longitud)
    {
        fprintf(stderr, "Error: se intento eliminar un elemento en una posicion invalida de la lista o la lista ya esta vacia\n");
    }else
    {
        if(posicion == 1)
        {
            actual = lista->primero;
            lista->primero = actual->siguiente;
            free(actual);
        }else
        {
            actual = lista->primero;
            for(i = 2; i < posicion; i++)
            {
                actual = actual->siguiente;
            }
            anterior = actual;
            actual = actual->siguiente;
            siguiente = actual->siguiente;
            anterior->siguiente = siguiente;
            free(actual);
        }
        lista->longitud = lista->longitud - 1;
    }
}

void consultar(Lista lista, int posicion, Tipo *retorno)
{
    Nodo * indice;
    int i;
    if(posicion < 1 || posicion > lista.longitud)
    {
        fprintf(stderr, "Error: Se intento consultar una posicion inexistente de la lista\n");
    }else
    {
        if(posicion == 1)
        {
            (*retorno) = lista.primero->informacion;
        }else
        {
            indice = lista.primero;
            for(i = 2; i <= posicion; i++)
            {
                indice = indice->siguiente;
            }
            (*retorno) = (indice->informacion);
        }
    }
}

int longitud(Lista lista)
{
    return(lista.longitud);
}

void imprimir(Lista lista)
{
    Nodo * indice;

    if(lista.primero == NULL)
    {
        fprintf(stderr, "Error: La lista que se desea imprimir esta vacia\n");
    }else
    {
        indice = lista.primero;
        while(indice != NULL)
        {
            printf("numero de receta: %04d \n", indice->informacion.receta.codigo);
            indice = indice->siguiente;
        }
        printf("\n");
    }
}
