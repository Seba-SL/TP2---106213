#ifndef MENU_H_
#define MENU_H_

#include <juego.h>

typedef struct menu menu_t;

menu_t* crear_menu();

void menu_agregar_comando(menu_t *m);

void menu_destruir(menu_t *m);


#endif // MENU_H_