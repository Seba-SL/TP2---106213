#ifndef MENU_H_
#define MENU_H_

#include "juego.h"
#include <stdio.h>

typedef struct menu menu_t;
typedef struct info informacion_comando_t;

typedef enum {MENU_OK,MENU_INEXISTENTE,MENU_ERROR,MENU_SALIR}MENU_RESULTADO;

/*Crea el menu para la aplicación pasada por parametro*/
menu_t* crear_menu(void *aplicacion);

/*Agrega un comando,su descripción y su accion a el menu*/
MENU_RESULTADO menu_agregar_comando(menu_t *m,char* comando,char*descripcion , bool f(void *) );

/*Ejecuta el comando*/
MENU_RESULTADO menu_ejecutar_comando(menu_t *menu,char*comando,void *contexto);

/*Iterador interno de los comandos del menu*/
void menu_con_cada_comando( menu_t *m   , void (*f)(char*descripcion ,  bool(*c)(void*)   ), void *contexto  );

/*Da el nombre de usuario asignado a la aplicación*/
char *dar_nombre_usuario(menu_t *m);

/* Muestra todos los comandos y su descripcion*/
void mostrar_menu(menu_t *m);

/*Entrega la aplicación asociada*/
void * entregar_app(menu_t *menu);

/*asigna el nombre del archivo asociado a la aplicación*/
MENU_RESULTADO asignar_archivo_menu(menu_t *m,char* archivo);

/*entrega el nombre del archivo*/
char* entregar_nombre_archivo(menu_t *m);

/*Destruye tda*/
void menu_destruir(menu_t *m);


#endif // MENU_H_