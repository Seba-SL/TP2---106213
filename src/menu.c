
#include "menu.h"
#include "hash.h"
#include <stdlib.h>

#define CAPACIDAD_COMANDOS_INICIAL 3

 struct menu
{
    char *usuario;
    hash_t *comandos;

};



struct info
{
	char *descripcion;
    bool (*funcion)(juego_t *);
};

typedef struct 
{
    void *contexto;
    void (*f)(char*descripcion ,  bool(*c)(juego_t*)   );

}datos_iterador_t;



menu_t* crear_menu()
{
    menu_t *menu_nuevo = calloc( 1 , sizeof(menu_t));
        if(menu_nuevo == NULL)return NULL;
    

    menu_nuevo->comandos = hash_crear(CAPACIDAD_COMANDOS_INICIAL);
        if(menu_nuevo->comandos == NULL)
            {
                free(menu_nuevo);
                return NULL;
            }   


    return menu_nuevo;

}

void menu_agregar_comando(menu_t *m,char* comando,char*descripcion , bool f(void *),juego_t *contexto)
{
    informacion_comando_t *info_comando = malloc( sizeof(informacion_comando_t) );
    
    info_comando->descripcion = descripcion;
    info_comando->funcion = f;

    hash_insertar(m->comandos,comando,info_comando,NULL);
}

MENU_RESULTADO menu_ejecutar_comando(menu_t *menu,char*comando,void *contexto)
{
    informacion_comando_t *info_comando = hash_obtener(menu->comandos,comando);

    if(info_comando == NULL)
        return MENU_INEXISTENTE;


    if(info_comando->funcion(contexto))
        return MENU_OK;
    
    return MENU_ERROR;
}


bool funcion (const char *clave, void *valor, void *aux)
{
    informacion_comando_t *info = valor;
    datos_iterador_t *datos_it = aux;

    datos_it->f(info->descripcion,info->funcion);
   
   
    return true;
}

void menu_con_cada_comando( menu_t *m   , void (*f)(char*descripcion ,  bool(*c)(juego_t*)   ), void *contexto  )
{
    datos_iterador_t datos_iterad ;

    datos_iterad.contexto = contexto;
    datos_iterad.f = f;

    hash_con_cada_clave(m->comandos,funcion,&datos_iterad);
}



void menu_destruir(menu_t *m)
{
    hash_destruir_todo(m->comandos,NULL);
    free(m);
}