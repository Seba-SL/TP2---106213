#include "juego.h"
#include "lista.h"
#include "tipo.h"
#include <stdbool.h>
#include "pokemon.h"
#include "ataque.h"

#include <stdlib.h>

typedef struct jugador
{
	lista_t *sus_pokemones;
	int puntaje;

}jugador_t;


struct juego
{

	jugada_t jugada;
	resultado_jugada_t resultado_jugada;
	
	lista_t * lista_pokemones;

	jugador_t jugadores[2];

	size_t cantidad_movimientos;

};


juego_t *juego_crear()
{
	juego_t *juego = calloc(1, sizeof(juego_t));

	if(!juego)return NULL;

	juego->lista_pokemones = lista_crear();

	if(!juego->lista_pokemones)
	{
		juego_destruir(juego);
		return NULL;
	}

	return NULL;
}

JUEGO_ESTADO juego_cargar_pokemon(juego_t *juego, char *archivo)
{
	return ERROR_GENERAL;
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
