#include <stdio.h>
#include <stdlib.h>
#include "Pilas.h"

void vaciaP(Pila *P){
	P->primero = NULL;
}

int esVaciaP(Pila P){
	return(P.primero==NULL);
}

void apilar(Pila *P, Comentario e){
	NodoPila *nuevo;
	nuevo = (NodoPila *) malloc(sizeof(NodoPila));
	nuevo->informacion = e;
	nuevo->siguiente = P->primero;
	P->primero = nuevo;
}

void desapilar(Pila *P){
	NodoPila *aux;
	if(P->primero != NULL){
		aux = P->primero->siguiente;
		free(P->primero);
		P->primero = aux;
	}
}

void tope(Pila P, Comentario *e, int *error){
	if(P.primero != NULL) (*e) = P.primero->informacion;
	else *error = 1;
}

void destruirP(Pila *P){
	NodoPila *aux;
	aux = P->primero;
	while(aux!=NULL){
		aux = aux->siguiente;
		free(P->primero);
		P->primero = aux;
	}
}

