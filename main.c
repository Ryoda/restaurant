#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listas.h"
#include "Pilas.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

void aviso(int);
int getLine (char *, size_t, FILE *);
void crear_Usuario(Lista *, char *);
void consultar_Usuario(Lista ,char *);
void buscar_Receta(Lista, char (*)[NOMBRE_MAXIMO]);
void leer_Receta(Lista,int);
void puntuar_Receta(Lista*, int, float);
void comentar_Receta(Lista *, int, char *, char *, char *, float);

int main()
{
    FILE *fusers, *fcoments, *frecipes;
    Lista users, recetas;
    Tipo tipo_aux;
    char cadena_auxiliar[TEXTO_MAXIMO], aux_char, palabras_clave[MAX_TAGS][NOMBRE_MAXIMO], *ptr_aux, parada[2];
    int cantidad_usuarios,cantidad_recetas,cantidad_comentarios,i,n,j, control_lectura, receta_id;
    float media;
    Comentario coment_aux;
    //inicializacion de variables
    fusers = fopen("usuarios.in","r");
    fcoments = fopen("comentarios.in", "r");
    frecipes = fopen("recetas.in", "r");
    vacia(&users);
    vacia(&recetas);

    printf("Cargando...\n");

    for( i = 0; i < MAX_TAGS; i++)
    {
        palabras_clave[i][0] = '\0';
    }
    //      Lectura de Variables

    //lectura de usuarios
    fscanf(fusers,"%d", &cantidad_usuarios);
    getLine(cadena_auxiliar,1, fusers); // leyendo el \n luego de la lectura del fscanf del entero
    for(i = 1; i <= cantidad_usuarios; i++)
    {
        getLine(cadena_auxiliar,NOMBRE_MAXIMO, fusers);
        crear_Usuario(&users, cadena_auxiliar);
    }

    //lectura de recetas
    fscanf(frecipes, "%d", &cantidad_recetas);
    getLine(cadena_auxiliar, NOMBRE_MAXIMO, frecipes); //leyendo el \n que queda luego de que fscanf lee el entero
    for(i = 1; i <= cantidad_recetas; i++)
    {
        tipo_aux.receta.codigo = i-1;

        control_lectura = getLine(tipo_aux.receta.username, NOMBRE_MAXIMO, frecipes);

        control_lectura = getLine(tipo_aux.receta.nombre, NOMBRE_MAXIMO, frecipes);

        control_lectura = getLine(tipo_aux.receta.descripcion, DESCRIPCION_MAXIMA, frecipes);

        fscanf(frecipes, "%d", &n);

        getc(frecipes);//getLine(cadena_auxiliar, 1, frecipes); //leyendo el \n que queda luego de que fscanf lee el entero

        for(j = 0; j < INGREDIENTES_MAX; j++)
        {
            if(j < n)
                getLine(tipo_aux.receta.ingredientes[j], INGREDIENTES_MAX, frecipes);
            else
                tipo_aux.receta.ingredientes[j][0] = '\0';
        }

        fscanf(frecipes,"%d",&n);


        for(j = 0; j < MAX_TAGS; j++)
        {
            if(j < n)
            {
                fscanf(frecipes,"%s", tipo_aux.receta.tags[j]);
            }else
            {
                tipo_aux.receta.tags[j][0] = '\0';  //se marcan como vacios el resto de los tags inicializandolos con \0
            }
        }

        j = 0;

        getc(frecipes);//getLine(cadena_auxiliar, 1,frecipes); // leyendo el \n que queda luego de que fscanf lee el ultimo tag

        getLine(cadena_auxiliar, TEXTO_MAXIMO, frecipes);

        while(strcmp(cadena_auxiliar, "Fin") != 0)
        {
            strcpy(tipo_aux.receta.pasos[j], cadena_auxiliar);
            getLine(cadena_auxiliar, TEXTO_MAXIMO, frecipes);
            j++;
        }
        for( ;j < PASOS_MAX;j++)
            tipo_aux.receta.pasos[j][0] = '\0'; //se marcan como vacios el resto de los pasos inicializandolos con \0

        vaciaP(&tipo_aux.receta.comentarios); // inicializa la pila de comentarios de cada receta

        tipo_aux.receta.rating = 0;


        insertar(&recetas, tipo_aux, i);
    }

    //lectura de comentarios
    fscanf(fcoments,"%d", &cantidad_comentarios);

    getLine(cadena_auxiliar, TEXTO_MAXIMO, fcoments); //leyendo el \n que queda luego del scanf

    for(i = 0; i < cantidad_comentarios; i++)
    {
        fscanf( fcoments, "%c", &aux_char);
        printf("%c\n", aux_char);
        getLine(cadena_auxiliar, TEXTO_MAXIMO, fcoments); //leyendo el \n que queda luego del scanf

        fscanf(fcoments,"%d", &receta_id);

        consultar(recetas, receta_id + 1, &tipo_aux); //se consulta de la lista, la receta a la que se desea comentar, para introducir
                                                      //el comentario en la Pila de comentarios

        fscanf(fcoments, "%s", cadena_auxiliar); // lectura del nombre del usuario que hace el comentario, en caso de hacerlo

        fscanf(fcoments, "%f", &media); //lectura de la puntuacion que le coloca


            if(tipo_aux.receta.rating == 0)
            {
                tipo_aux.receta.rating = media; //inicializacion del promedio
            }else
            {
                tipo_aux.receta.rating = (tipo_aux.receta.rating + media) / 2; // calculo del promedio
            }

            if(aux_char == 'C')
            {
                memset(coment_aux.texto, '\0', TEXTO_MAXIMO); //inicializamos el texto en coment_aux para evitar que el strcat no concatene con el comentario anterior
                //almacenar los datos del comentario

                strcpy(coment_aux.username, cadena_auxiliar); //almacenar el nombre del usuario que comento

                coment_aux.rating = media; //almacenar la puntuacion
                //se continua con la lectura

                getLine(cadena_auxiliar, TEXTO_MAXIMO, fcoments); //leyendo el \n que queda luego del scanf

                getLine(cadena_auxiliar, LONGITUD_FECHA, fcoments); //leyendo la fecha

                strcpy(coment_aux.fecha, cadena_auxiliar); //almacenando la fecha

                //ahora a leer el texto del comentario

                getLine(cadena_auxiliar, TEXTO_MAXIMO, fcoments);

                while(strcmp(cadena_auxiliar, "Fin") != 0)
                {
                    strcat(coment_aux.texto, "\n");
                    strcat(coment_aux.texto, cadena_auxiliar);
                    getLine(cadena_auxiliar, TEXTO_MAXIMO, fcoments);
                }
                    apilar(&tipo_aux.receta.comentarios, coment_aux); //se apila en los comentarios
            }

            if(aux_char == 'P')
            {
                getLine(cadena_auxiliar, TEXTO_MAXIMO, fcoments); //leyendo el \n que queda luego del scanf
            }

            eliminar(&recetas, receta_id + 1); //se elimina la vieja receta en la lista

            insertar(&recetas, tipo_aux, receta_id + 1); //se agrega la misma receta actualizada
    }

    i = 0;
    j = 0; //leyendo las palabras clave introducidas por la terminal

    parada[0] = ' ';

    printf("Listo\n");
    printf("Introduzca las palabras clave de lo que desea buscar:\n");
    getLine(cadena_auxiliar, 500, stdin);

    ptr_aux = strtok(cadena_auxiliar, parada);

        while((ptr_aux) != NULL)
        {
            strcpy(palabras_clave[j], ptr_aux);
            j++;
            ptr_aux = strtok(NULL, parada);
        }

    buscar_Receta(recetas, palabras_clave);

    printf("Introduzca el numero de la receta que desea leer:\n");

    scanf("%d", &n);

    leer_Receta(recetas, n);

    printf("Introduzca la puntuacion:\n");

    puntuar_Receta();


    return 0;
} // FIN DEL MAIN

void crear_Usuario(Lista * users,char username[])
{
        Usuario * user;
        Tipo auxiliar;
        if((user = (Usuario *) malloc(sizeof(Usuario))) == NULL)
        {
                printf("error en Crear_Usuario(): malloc termino inesperadamente\n");
        }else
        {
            strcpy(user->username, username);//user->username = username;
            user->cantidadRecetas = 0;
            user->rating = 0;
            auxiliar.usuario = *user;
            insertar(users, auxiliar, longitud(*users) + 1);
        }
}

void consultar_Usuario(Lista users,char *username)
{
    int encontrado = 0, i = 1;
    Tipo auxiliar;
    while(!encontrado && i <= longitud(users))
    {
        consultar(users,i, &auxiliar);
        if(strcmp(username,auxiliar.usuario.username) == 0)
        {
            encontrado = 1;
        }else
        {
            i++;
        }
    }
    if(!encontrado)
    {
        printf("El usuario que se intento consultar no existe en la lista\n");
    }else
    {
        printf("nombre de usuario: %s \n", auxiliar.usuario.username);
        printf("recetas: %d \n", auxiliar.usuario.cantidadRecetas);
        printf("rating: %.2f \n", auxiliar.usuario.rating);
    }

}

void buscar_Receta(Lista recetas, char (*palabras_clave)[NOMBRE_MAXIMO])
{
        int i,j,k;
        Tipo tipo_aux;
        Lista encontradas;
        vacia(&encontradas);
        i = 0;
    while(palabras_clave[i][0] != '\0')
    {
        for(j = 1; j <= longitud(recetas);j++)
        {
            consultar(recetas, j, &tipo_aux);
            k = 0;
            while(tipo_aux.receta.tags[k][0] != '\0' )
            {
                if(strcmp(palabras_clave[i], tipo_aux.receta.tags[k]) == 0)
                {
                    insertar(&encontradas, tipo_aux, longitud(encontradas) + 1);
                }
                k++;
            }
        }
        i++;
    }

    imprimir(encontradas);
}

void leer_Receta(Lista recetas, int n)
{
    Tipo tipo_aux;
    Pila pila_aux;
    Comentario coment_aux;
    int i, advertencia;
    vaciaP(&pila_aux);
    consultar(recetas, n+1, &tipo_aux);

    printf("nombre de la receta: %s\n", tipo_aux.receta.nombre);
    printf("descripcion de la receta %s\n", tipo_aux.receta.descripcion);
    printf("usuario que publico la receta: %s\n", tipo_aux.receta.username);
    printf("Rating de la receta: %.2f \n", tipo_aux.receta.rating);
    printf("Lista de Ingredientes:\n");
    i = 0;

    while(tipo_aux.receta.ingredientes[i][0] != '\0')
    {
        printf("%s\n",tipo_aux.receta.ingredientes[i]);
        i++;
    }
    printf("\n");

    i = 0;
    printf("Pasos a seguir para realizar la receta: \n");
    while(tipo_aux.receta.pasos[i][0] != '\0')
    {
        printf("%s\n", tipo_aux.receta.pasos[i]);
        i++;
    }
    i = 0;
    printf("Palabras Clave para buscar la receta:\n");
    while(tipo_aux.receta.tags[i][0] != '\0')
    {
        printf("%s\n", tipo_aux.receta.tags[i]);
        i++;
    }
    printf("\n");

    printf("Lista de comentarios: \n");
    while(!esVaciaP(tipo_aux.receta.comentarios)) //se va imprimiendo el tope, apilando en una pila auxiliar y desapilando de la principal
    {
        tope(tipo_aux.receta.comentarios, &coment_aux, &advertencia);
        printf("publicante: %s, ",coment_aux.username);
        printf("rating: %.2f ,",coment_aux.rating);
        printf("\n fecha: %s\n", coment_aux.fecha);
        printf("Comentario: %s \n", coment_aux.texto);
        apilar(&pila_aux, coment_aux);
        desapilar(&tipo_aux.receta.comentarios);
    }
    while(!esVaciaP(pila_aux)) //reapilamos lo que estaba en la pila auxiliar en la pila de comentarios original
    {
        tope(pila_aux, &coment_aux, &advertencia);
        apilar(&tipo_aux.receta.comentarios, coment_aux);
        desapilar(&pila_aux);
    }
}

void puntuar_Receta(Lista *recetas, int i, float puntuacion)
{
    Tipo tipo_aux;
    consultar(*recetas, i + 1, &tipo_aux);
    tipo_aux.receta.rating = (tipo_aux.receta.rating + puntuacion) / 2;
    eliminar(recetas, i + 1);
    insertar(recetas, tipo_aux, i + 1);
}

void comentar_Receta(Lista *recetas, int i, char *usuario, char *fecha, char *texto, float puntuacion)
{
    Tipo tipo_aux;
    Comentario coment_aux;
    consultar(*recetas, i + 1, &tipo_aux);
    strcpy(coment_aux.username, usuario);
    strcpy(coment_aux.fecha, fecha);
    strcpy(coment_aux.texto, texto);
    coment_aux.rating = puntuacion;

    eliminar(recetas, i + 1);
    insertar(recetas, tipo_aux, i + 1);

}

//Funcion para la lectura segura de una linea completa de caracteres, incluyendo espacios hasta el caracter de control de nueva linea, con control de desbordamientos de buffer

int getLine (char *buff, size_t sz, FILE *fr)
{
  int ch, extra, retorno;
  size_t len;

  // Get line with overrun protection.

  if (fgets (buff, sz, fr) == NULL)
  {
        retorno = NO_INPUT;
  }else
  {
      len = strlen (buff);
      if (buff[len-1] != '\n') {
        // Consume characters to line end.

        extra = 0;
        while ((ch = getc(fr)) != '\n') {
          if (ch == EOF) break;
          extra = 1;
        }

        // If extra was just newline, okay.

        retorno = (extra == 1) ? TOO_LONG : OK;
      }else
      {
        retorno = OK;
      }
        // Remove newline.
        buff[len-1] = '\0';
  }

  // Line without newline is too long.

  return retorno;
}


void aviso(int control_lectura)
{
    switch (control_lectura)
    {
        case 0 :
            fprintf(stderr, "lectura sin sobreflujo\n");
            break;
        case 1:
            fprintf(stderr, "Sin datos\n");
            break;
        case 2:
            fprintf(stderr, "Demasiados caracteres en la linea\n");
            break;
    }

}

