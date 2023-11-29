#include "juego.h"
#include "lista.h"
#include "tipo.h"
#include <stdbool.h>
#include "pokemon.h"
#include "ataque.h"

typedef struct juego 
{
	jugada_t jugada;
	resultado_jugada_t resultado_jugada;
	lista_t * lista_pokemones;
}juego_t;

juego_t *juego_crear()
{	

	juego_t  *nuevo_juego = malloc(sizeof(juego_t) ) ;

	if(nuevo_juego == NULL)
		return NULL;

	nuevo_juego->lista_pokemones = lista_crear();

	if(nuevo_juego->lista_pokemones == NULL)return NULL;

	return nuevo_juego;

}

JUEGO_ESTADO juego_cargar_pokemon(juego_t *juego, char *archivo)
{
	if(juego == NULL || archivo == NULL)return ERROR_GENERAL;

	juego->lista_pokemones = pokemon_cargar_archivo(archivo);

	if(juego->lista_pokemones == NULL)return ERROR_GENERAL;


	return TODO_OK;
}

lista_t *juego_listar_pokemon(juego_t *juego)
{
	return NULL;
}

JUEGO_ESTADO juego_seleccionar_pokemon(juego_t *juego, JUGADOR jugador,
				       const char *nombre1, const char *nombre2,
				       const char *nombre3)
{
	return TODO_OK;
}

resultado_jugada_t juego_jugar_turno(juego_t *juego, jugada_t jugada_jugador1,
				     jugada_t jugada_jugador2)
{
	resultado_jugada_t resultado;
	resultado.jugador1 = ATAQUE_ERROR;
	resultado.jugador2 = ATAQUE_ERROR;
	return resultado;
}

int juego_obtener_puntaje(juego_t *juego, JUGADOR jugador)
{
	return 0;
}

bool juego_finalizado(juego_t *juego)
{
	return true;
}

void juego_destruir(juego_t *juego)
{
}
