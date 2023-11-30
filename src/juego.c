#include "juego.h"
#include "lista.h"
#include "tipo.h"
#include <stdbool.h>
#include "pokemon.h"
#include "ataque.h"

#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 30

typedef struct jugador jugador_t;

struct jugador{
	char Nombre[MAX_NOMBRE];
	pokemon_t *sus_pokemones[3];
	int puntaje;
};

struct juego 
{
	jugada_t jugada;
	resultado_jugada_t resultado_jugada;
	
	lista_t * lista_pokemones;

	jugador_t jugadores[2];

	size_t cantidad_movimientos;
};


enum TIPO asignar_tipo( char inicialTipo);
RESULTADO_ATAQUE asignar_efectividad(enum TIPO atk_pkm1,enum TIPO tipo_pkm2);

juego_t *juego_crear()
{	

	juego_t  *nuevo_juego = calloc(1,sizeof(juego_t) ) ;

	if(nuevo_juego == NULL)
		return NULL;

	nuevo_juego->lista_pokemones = lista_crear();

	if(nuevo_juego->lista_pokemones == NULL)return NULL;

	nuevo_juego->cantidad_movimientos = 9;

	

	return nuevo_juego;

}

 void insertar_en_lista (pokemon_t *actual , void * lista)
 {
	if(actual == NULL || lista == NULL)return;

	lista_t * lista_pkm = lista;

	lista_insertar(lista_pkm,actual);
 }

JUEGO_ESTADO juego_cargar_pokemon(juego_t *juego, char *archivo)
{
	if(juego == NULL || archivo == NULL)return ERROR_GENERAL;

	informacion_pokemon_t * pokemones = pokemon_cargar_archivo(archivo);

	if(pokemones == NULL)return ERROR_GENERAL;

	if(pokemon_cantidad(pokemones) < 4)return POKEMON_INSUFICIENTES;

	con_cada_pokemon(pokemones,insertar_en_lista,juego->lista_pokemones);


	if(lista_tamanio(juego->lista_pokemones) < 4)return POKEMON_INSUFICIENTES;

	
	if(juego->lista_pokemones == NULL)return ERROR_GENERAL;

	
	

	return TODO_OK;
}

lista_t *juego_listar_pokemon(juego_t *juego)
{
	if( juego == NULL )
		return NULL;
	
	return juego->lista_pokemones ;
}


int comparar_nombres(void *actual, void * objetivo)
{
	

	pokemon_t * actual_pkm = actual;

	char * obj_nombre = objetivo;

	return strcmp(pokemon_nombre(actual_pkm),obj_nombre);

}

bool pokemones_existen(juego_t * juego ,const char *nombre1, const char *nombre2,const char *nombre3)
{
	bool check1,check2,check3;

	check1 = lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,(void*)nombre1);

	check2= lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,(void*)nombre2) ;
	
	check3= lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,(void*)nombre3) ;

	return (check1 && check2 && check3);

}

bool pokemones_iguales(const char* nombre1,const char*nombre2,const char* nombre3)
{
	if(strcmp(nombre1,nombre2) == 0)return true;
	if(strcmp(nombre1,nombre3) == 0)return true;
	if(strcmp(nombre3,nombre2) == 0)return true;

	return false;
}

JUEGO_ESTADO juego_seleccionar_pokemon(juego_t *juego, JUGADOR jugador,const char *nombre1, const char *nombre2,const char *nombre3)
{
	if(juego == NULL || lista_vacia(juego->lista_pokemones))return ERROR_GENERAL; 

	if( nombre1 == NULL || nombre2 == NULL || nombre3 == NULL)return POKEMON_INEXISTENTE;

	

	if(pokemones_iguales(nombre1,nombre2,nombre3))
		return POKEMON_REPETIDO;

	if(	!pokemones_existen(juego,nombre1,nombre2,nombre3)	)
		return POKEMON_INEXISTENTE;

	jugador_t  jugador_actual = juego->jugadores[jugador];

	if(jugador_actual.Nombre != jugador_actual.Nombre)
	{
		return ERROR_GENERAL;
	}


	jugador_actual.sus_pokemones[0] =(pokemon_t *) lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,(void*)nombre1);


	jugador_actual.sus_pokemones[1] =(pokemon_t *) lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,(void*)nombre2);

	jugador_actual.sus_pokemones[2] =(pokemon_t *) lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,(void*)nombre3);



	return TODO_OK;
}


resultado_jugada_t asignar_resultado(enum TIPO tipo_pkm1,enum TIPO tipo_pkm2,enum TIPO atk_pkm1,enum TIPO atk_pkm2)
{
	resultado_jugada_t resultado;

	resultado.jugador1 = asignar_efectividad(atk_pkm1,tipo_pkm2);
	resultado.jugador2 = asignar_efectividad(atk_pkm2,tipo_pkm1);

	
	return resultado;
}

resultado_jugada_t juego_jugar_turno(juego_t *juego, jugada_t jugada_jugador1,jugada_t jugada_jugador2)
{
	resultado_jugada_t resultado;

	resultado.jugador1 = ATAQUE_ERROR;
	resultado.jugador2 = ATAQUE_ERROR;

	if(juego == NULL)return resultado;

	pokemon_t *pkm_1 = lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,jugada_jugador1.pokemon);
	pokemon_t *pkm_2 = lista_buscar_elemento(juego->lista_pokemones,comparar_nombres,jugada_jugador2.pokemon);

	enum TIPO tipo_pkm1 = pokemon_tipo(pkm_1);
	enum TIPO atk_pkm1 = asignar_tipo(jugada_jugador1.ataque[0]);
	
	enum TIPO tipo_pkm2 = pokemon_tipo(pkm_2);
	enum TIPO atk_pkm2 = asignar_tipo(jugada_jugador2.ataque[0]);

	if(atk_pkm1 == NORMAL && atk_pkm2 == NORMAL)
	{ 
		resultado.jugador1 = ATAQUE_REGULAR;
		resultado.jugador1 = ATAQUE_REGULAR;
			return resultado;
	}

	return asignar_resultado(tipo_pkm1,tipo_pkm2,atk_pkm1,atk_pkm2);

	
}

int juego_obtener_puntaje(juego_t *juego, JUGADOR jugador)
{
	if(juego == NULL)
		return 0;

	return juego->jugadores[jugador].puntaje;
}

bool juego_finalizado(juego_t *juego)
{
	if(juego == NULL)return true;

	if (juego->cantidad_movimientos == 0)return true;

	return false;
}

void juego_destruir(juego_t *juego)
{
	
	lista_destruir_todo(juego->lista_pokemones, NULL);
	free(juego);

}


enum TIPO asignar_tipo( char inicialTipo)
{
    //NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO, ROCA

    switch(inicialTipo)
    {
        case 'N':
            return NORMAL;
            break;
		
		case 'n':
            return NORMAL;
            break;

        case 'F':
            return FUEGO;
            break;
		
		case 'f':
            return FUEGO;
            break;
        
        
        case 'A':
            return AGUA;
            break;
		
		case 'a':
            return AGUA;
            break;


        case 'P':
            return PLANTA;
            break;
  		
		case 'p':
            return PLANTA;
            break;	
        
		case 'E':
            return ELECTRICO;
            break;
		case 'e':
            return ELECTRICO;
            break;

        case 'R':
            return ROCA;
            break;
        
		case 'r':
            return ROCA;
            break;
        
        
        default : 
            return NORMAL;

    }

}


RESULTADO_ATAQUE asignar_efectividad(enum TIPO atk_pkm1,enum TIPO tipo_pkm2)
{

if(atk_pkm1 == FUEGO)
	{
		if(tipo_pkm2 == PLANTA)
		{	
			return ATAQUE_EFECTIVO;
		}

		if(tipo_pkm2 == AGUA)
		{	
			return  ATAQUE_INEFECTIVO;
		}

	}

	if(atk_pkm1 == PLANTA)
	{
		if(tipo_pkm2 == ROCA)
		{	
			return ATAQUE_EFECTIVO;
		}

		if(tipo_pkm2 == FUEGO)
		{	
			return ATAQUE_INEFECTIVO;
		}

	}

	
	if(atk_pkm1 == ROCA)
	{
		if(tipo_pkm2 == ELECTRICO)
		{	
			return ATAQUE_EFECTIVO;
		}

		if(tipo_pkm2 == PLANTA)
		{	
			return ATAQUE_INEFECTIVO;
		}

	}

	if(atk_pkm1 == ELECTRICO)
	{
		if(tipo_pkm2 == AGUA)
		{	
			return ATAQUE_EFECTIVO;
		}

		if(tipo_pkm2 == ROCA)
		{	
			return ATAQUE_INEFECTIVO;
		}

	}

	if(atk_pkm1 == AGUA)
	{
		if(tipo_pkm2 == FUEGO)
		{	
			return ATAQUE_EFECTIVO;
		}

		if(tipo_pkm2 == ELECTRICO)
		{	
			return ATAQUE_INEFECTIVO;
		}

	}

	return ATAQUE_REGULAR;
	
}
