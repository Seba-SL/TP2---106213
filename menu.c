
#include "menu.h"

typedef struct menu
{
    char *usuario;


} menu_t;

menu_t* crear_menu();

void menu_agregar_comando(menu_t *m,char* comando,char*descripcion , void f(juego_t *),juego_t *contexto);

void ejecutar_comando(menu_t * m , char* comando, juego_t  *juego);

void menu_destruir(menu_t *m)
{
    free(m);
}