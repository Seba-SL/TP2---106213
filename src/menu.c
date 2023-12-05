
#include "menu.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CAPACIDAD_COMANDOS_INICIAL 3
#define MAX_CLAVE 10
#define MENSAJE_PEDIR_USUARIO "Ingrese su nombre de usuario"
#define MAX_NOMBRE 30

struct info {
	char *descripcion;
	bool (*funcion)(void *);
};

typedef struct {
	void *contexto;
	void (*f)(char *descripcion,
		  bool (*c)(void *)); //esto es los valores de la tabla hash

} datos_iterador_t;

struct menu {
	void *aplicacion; // donde guardo el juego
	char usuario[MAX_NOMBRE]; //
	hash_t *comandos; //  comandos (clave) y los valores son del tipo data_iterador_t
	char *archivo_auxiliar; //archivo donde se cargan los pokemones
};

//le paso el juego
menu_t *crear_menu(void *aplicacion)
{
	if (aplicacion == NULL)
		return NULL;

	menu_t *menu_nuevo = calloc(1, sizeof(menu_t));
	if (menu_nuevo == NULL)
		return NULL;

	menu_nuevo->comandos = hash_crear(CAPACIDAD_COMANDOS_INICIAL);

	if (menu_nuevo->comandos == NULL) {
		free(menu_nuevo);
		return NULL;
	}

	menu_nuevo->aplicacion = aplicacion;

	puts(MENSAJE_PEDIR_USUARIO);

	fgets(menu_nuevo->usuario, MAX_NOMBRE, stdin);

	menu_nuevo->usuario[strlen(menu_nuevo->usuario) - 1] = 0;

	return menu_nuevo;
}

MENU_RESULTADO menu_agregar_comando(menu_t *m, char *comando, char *descripcion,
				    bool f(void *))
{
	if (!m || !comando || !f)
		return MENU_ERROR;

	char clave[MAX_CLAVE];

	strcpy(clave, comando);

	informacion_comando_t *info_comando =
		malloc(sizeof(informacion_comando_t));

	info_comando->descripcion = descripcion;
	info_comando->funcion = f;
	//valor
	m->comandos = hash_insertar(m->comandos, clave, info_comando, NULL);

	if (m->comandos == NULL || hash_cantidad(m->comandos) == 0 ||
	    !hash_contiene(m->comandos, clave)) {
		return MENU_ERROR;
	}

	return MENU_OK;
}

//bool pedir_archivo(void* archivo)            menu , comando ,menu                      archivho/juego
MENU_RESULTADO menu_ejecutar_comando(menu_t *menu, char *comando,
				     void *contexto)
{
	informacion_comando_t *info_comando =
		hash_obtener(menu->comandos, comando);

	if (info_comando == NULL) {
		return MENU_INEXISTENTE;
	}

	if (info_comando->funcion(contexto)) {
		return MENU_OK;
	}

	if (!info_comando->funcion(contexto)) {
		return MENU_SALIR;
	}

	return MENU_ERROR;
}

bool funcion(const char *clave, void *valor, void *aux)
{
	informacion_comando_t *info = valor;
	datos_iterador_t *datos_it = aux;

	datos_it->f(info->descripcion, info->funcion);

	return true;
}

void menu_con_cada_comando(menu_t *m,
			   void (*f)(char *descripcion, bool (*c)(void *)),
			   void *contexto)
{
	datos_iterador_t datos_iterad;

	datos_iterad.contexto = contexto;
	datos_iterad.f = f;

	hash_con_cada_clave(m->comandos, funcion, &datos_iterad);
}

bool mostrar_comandos(const char *clave, void *valor, void *aux)
{
	informacion_comando_t *info_comando = valor;

	printf("[%s] %s \t", (char *)clave, (char *)info_comando->descripcion);

	return true;
}

void mostrar_menu(menu_t *m)
{
	if (!m || !m->comandos) {
		return;
	}

	//clave es c , j ,i , s
	//clave , valor->descripicion
	//clave , valor->funcion
	hash_con_cada_clave(m->comandos, mostrar_comandos, NULL);
	printf("\n\n");
}

void *entregar_app(menu_t *menu)
{
	if (menu == NULL || menu->aplicacion == NULL)
		return NULL;

	return menu->aplicacion;
}

MENU_RESULTADO asignar_archivo_menu(menu_t *m, char *archivo)
{
	if (!m) {
		return MENU_ERROR;
	}

	m->archivo_auxiliar = archivo;

	return MENU_OK;
}

char *entregar_nombre_archivo(menu_t *m)
{
	if (!m)
		return NULL;

	return m->archivo_auxiliar;
}

char *dar_nombre_usuario(menu_t *m)
{
	if (m == NULL)
		return NULL;

	return m->usuario;
}

void menu_destruir(menu_t *m)
{
	free(m->archivo_auxiliar);
	hash_destruir_todo(m->comandos, free);
	free(m);
}