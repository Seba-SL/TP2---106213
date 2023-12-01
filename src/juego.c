#include "juego.h"
#include "lista.h"
#include "tipo.h"
#include <stdbool.h>
#include "pokemon.h"
#include "ataque.h"

#include <string.h>

#include <stdlib.h>

#define CANTIDAD_MOVIMIENTOS 9
#define CANTIDAD_MIN_POKEMONES 4



typedef struct jugador
{
	lista_t *sus_pokemones;
	int puntaje;
	bool eligio_jugadores;

}jugador_t;


struct juego
{

	jugada_t jugada;
	resultado_jugada_t resultado_jugada;
	
	lista_t * lista_pokemones;

	informacion_pokemon_t *info_pokemones;

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

	juego->jugadores[JUGADOR1].sus_pokemones = lista_crear();
	juego->jugadores[JUGADOR2].sus_pokemones = lista_crear();

	juego->cantidad_movimientos = CANTIDAD_MOVIMIENTOS;

	juego->jugadores[JUGADOR1].eligio_jugadores = false;
	juego->jugadores[JUGADOR2].eligio_jugadores = false;

	return juego;
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
	if(!juego || !juego->lista_pokemones)
		return NULL;

	return juego->lista_pokemones;
}

bool coincidencias(const char* nombre1, const char*nombre2, const char*nombre3)
{
	if(strcmp(nombre1,nombre2) == 0 )
		return true;
	
	if(strcmp(nombre1,nombre3) == 0 )
		return true;

	if(strcmp(nombre3,nombre2) == 0 )
		return true;
	
	if(strcmp(nombre3,nombre1) == 0 )
		return true;
	

	return false;
}

JUEGO_ESTADO juego_seleccionar_pokemon(juego_t *juego, JUGADOR jugador, const char *nombre1, const char *nombre2,const char *nombre3)
{
	if(!juego || !nombre1 || !nombre2 || !nombre3)
		return ERROR_GENERAL;

	if(juego->jugadores[jugador].eligio_jugadores)
		return ERROR_GENERAL;

	if(coincidencias(nombre1,nombre2,nombre3))
		return POKEMON_REPETIDO;
	


	lista_t *mochila_pokemones = juego->jugadores[jugador].sus_pokemones;


	pokemon_t *pkm1 = pokemon_buscar(juego->info_pokemones,nombre1);
	
	pokemon_t *pkm2 = pokemon_buscar(juego->info_pokemones,nombre2);
	
	pokemon_t *pkm3 = pokemon_buscar(juego->info_pokemones,nombre3);
	
	if(pkm1 == NULL|| pkm2 == NULL || pkm3 == NULL)
	{
		return POKEMON_INEXISTENTE;
	}

	lista_insertar(mochila_pokemones,pkm1);
	lista_insertar(mochila_pokemones,pkm2);
	lista_insertar(mochila_pokemones,pkm3);
	

	if(lista_tamanio(mochila_pokemones) < CANTIDAD_MIN_POKEMONES)
		return POKEMON_INSUFICIENTES;
	

	juego->jugadores[jugador].eligio_jugadores = true;
	
	return TODO_OK;
}

resultado_jugada_t juego_jugar_turno(juego_t *juego, jugada_t jugada_jugador1,jugada_t jugada_jugador2)
{
	resultado_jugada_t resultado;
	resultado.jugador1 = ATAQUE_ERROR;
	resultado.jugador2 = ATAQUE_ERROR;
	return resultado;
}

int juego_obtener_puntaje(juego_t *juego, JUGADOR jugador)
{
	return juego->jugadores[jugador].puntaje;
}

bool juego_finalizado(juego_t *juego)
{
	if(juego->cantidad_movimientos == 0)
		return true;

	return false;
}

void juego_destruir(juego_t *juego)
{
	lista_destruir(juego->lista_pokemones);
	lista_destruir(juego->jugadores[JUGADOR1].sus_pokemones);
	lista_destruir(juego->jugadores[JUGADOR2].sus_pokemones);

	pokemon_destruir_todo(juego->info_pokemones);

	free(juego);
}
