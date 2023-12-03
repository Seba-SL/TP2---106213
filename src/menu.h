#ifndef MENU_H_
#define MENU_H_

#include "juego.h"
#include <stdio.h>

typedef struct menu menu_t;
typedef struct info informacion_comando_t;

typedef enum {MENU_OK,MENU_INEXISTENTE,MENU_ERROR,MENU_SALIR}MENU_RESULTADO;

menu_t* crear_menu();

MENU_RESULTADO menu_agregar_comando(menu_t *m,char* comando,char*descripcion , bool f(void *) );

MENU_RESULTADO menu_ejecutar_comando(menu_t *menu,char*comando,void *contexto);


void menu_con_cada_comando( menu_t *m   , void (*f)(char*descripcion ,  bool(*c)(void*)   ), void *contexto  );


char *dar_nombre_usuario(menu_t *m);

void mostrar_menu(menu_t *m);

void * entregar_app(menu_t *menu);


MENU_RESULTADO asignar_archivo_menu(menu_t *m,char* archivo);


char* entregar_nombre_archivo(menu_t *m);

void menu_destruir(menu_t *m);


#endif // MENU_H_