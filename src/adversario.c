#include "lista.h"
#include "juego.h"
#include "adversario.h"
#include "pokemon.h"

#include <stdlib.h>
#include "abb.h"
#include <string.h>
#include <time.h>
#include "ataque.h"




typedef struct {
	pokemon_t *pokemon;
	const struct ataque *ataque;
} pareja_t;



struct adversario {
	lista_t *lista_pokemones;

	abb_t *pokemones_adversario;
	abb_t *pokemones_jugador;

	abb_t *jugadas_disponibles;

	pareja_t *buffer;
};

typedef struct {
	abb_t *arbol;
	pokemon_t *pokemon;
} disponible_t;





/*                 Auxiliares 										*/
int comparador_pokemones_lista_adv(void *a, void *b);
int comparador_pokemones_abb(void *a, void *b);
int comparador_pareja_abb(void *a, void *b);
pareja_t *crear_pareja(pokemon_t *pokemon, const struct ataque *ataque);
void llenar_parejas_en_arbol(const struct ataque *ataque, void *aux);
void destruir_pareja(void *aux);







adversario_t *adversario_crear(lista_t *pokemon) //listo
{
	if (pokemon == NULL)
		return NULL;

	adversario_t *adversario = calloc(1, sizeof(adversario_t));
	if (adversario == NULL)
		return NULL;

	adversario->lista_pokemones = pokemon;
	adversario->pokemones_adversario = abb_crear(comparador_pokemones_abb);
	adversario->pokemones_jugador = abb_crear(comparador_pokemones_abb);
	adversario->jugadas_disponibles = abb_crear(comparador_pareja_abb);

	return adversario;
}

bool adversario_seleccionar_pokemon(adversario_t *adversario, char **nombre1, char **nombre2, char **nombre3) //listo
{
	if (adversario == NULL)
		return false;

	pokemon_t *poke1_adversario = (pokemon_t *)lista_elemento_en_posicion(
		adversario->lista_pokemones, 0);
	pokemon_t *poke2_adversario = (pokemon_t *)lista_elemento_en_posicion(
		adversario->lista_pokemones, 1);
	pokemon_t *poke3_jugador = (pokemon_t *)lista_elemento_en_posicion(
		adversario->lista_pokemones, 2);

	if (poke1_adversario == NULL || poke2_adversario == NULL ||
	    poke3_jugador == NULL)
		return false;

	*nombre1 = (char *)pokemon_nombre(poke1_adversario);
	*nombre2 = (char *)pokemon_nombre(poke2_adversario);
	*nombre3 = (char *)pokemon_nombre(poke3_jugador);

	if (*nombre1 == NULL || *nombre2 == NULL || *nombre3 == NULL)
		return false;

	//inserto el poke1 y poke2 en adversario
	abb_insertar(adversario->pokemones_adversario, poke1_adversario);
	abb_insertar(adversario->pokemones_adversario, poke2_adversario);
	abb_insertar(adversario->pokemones_jugador, poke2_adversario);

	//inserto las jugadas diponibles(pokemon y ataque) en el arbol
	disponible_t dispo1 = { .arbol = adversario->jugadas_disponibles,
				.pokemon = poke1_adversario };
	disponible_t dispo2 = { .arbol = adversario->jugadas_disponibles,
				.pokemon = poke2_adversario };
	con_cada_ataque(poke1_adversario, llenar_parejas_en_arbol, &dispo1);
	con_cada_ataque(poke2_adversario, llenar_parejas_en_arbol, &dispo2);
	return true;
}

bool adversario_pokemon_seleccionado(adversario_t *adversario, char *nombre1,
				     char *nombre2, char *nombre3) //listo
{
	if (adversario == NULL || nombre3 == NULL)
		return false;

	//busco el pokemon segun su nombre
	pokemon_t *poke1_jugador = (pokemon_t *)lista_buscar_elemento(
		adversario->lista_pokemones, comparador_pokemones_lista_adv,
		nombre1);
	pokemon_t *poke2_jugador = (pokemon_t *)lista_buscar_elemento(
		adversario->lista_pokemones, comparador_pokemones_lista_adv,
		nombre2);
	pokemon_t *poke3_adversario = (pokemon_t *)lista_buscar_elemento(
		adversario->lista_pokemones, comparador_pokemones_lista_adv,
		nombre3);

	//inserto el poke3
	abb_insertar(adversario->pokemones_jugador, poke1_jugador);
	abb_insertar(adversario->pokemones_jugador, poke2_jugador);
	abb_insertar(adversario->pokemones_adversario, poke3_adversario);

	disponible_t dispo3 = { .arbol = adversario->jugadas_disponibles,
				.pokemon = poke3_adversario };
	con_cada_ataque(poke3_adversario, llenar_parejas_en_arbol, &dispo3);
	return true;
}

jugada_t adversario_proxima_jugada(adversario_t *adversario)
{
	//aca voy a obtener mi elemento de mi jugadas disponibles
	void *pareja_;

	//primero adquiero una jugada disponible:
	abb_recorrer(adversario->jugadas_disponibles, INORDEN, &pareja_, 1);

	pareja_t *pareja = pareja_;
	//obtengo de esa jugada disponible el nombre del pokemon y su ataque
	const char *nombre_pokemon = pareja->ataque->nombre;
	const char *nombre_ataque = pokemon_nombre(pareja->pokemon);

	//copio en mi jugada el NOMBRE DEL POKEMON y el NOMBRE DEL ATAQUE
	jugada_t jugada;
	strcpy(jugada.ataque, nombre_pokemon);
	strcpy(jugada.pokemon, nombre_ataque);

	//quito de jugadas diponibles la jugada que acabo de devolver
	abb_quitar(adversario->jugadas_disponibles, pareja);
	adversario->buffer = pareja;
	return jugada;
}

void adversario_informar_jugada(adversario_t *a, jugada_t j)
{
	pareja_t *pareja = a->buffer;
	if (strcmp(j.pokemon, "invalido") == 0) {
		abb_insertar(a->jugadas_disponibles, pareja);
		return;
	}
	free(pareja);
	return;
}

void adversario_destruir(adversario_t *adversario)
{
	abb_destruir(adversario->pokemones_adversario);
	abb_destruir(adversario->pokemones_jugador);
	abb_destruir_todo(adversario->jugadas_disponibles, destruir_pareja);
	free(adversario);
}


int comparador_pokemones_lista_adv(void *a, void *b)
{
	pokemon_t *pokemon = a;
	char *nombre_pokemon = b;
	return strcmp(pokemon_nombre(pokemon), nombre_pokemon);
}
int comparador_pokemones_abb(void *a, void *b)
{
	return strcmp(pokemon_nombre((pokemon_t *)a),
		      pokemon_nombre((pokemon_t *)b));
}
int comparador_pareja_abb(void *a, void *b)
{
	pareja_t *pareja1 = (pareja_t *)a;
	pareja_t *pareja2 = (pareja_t *)b;
	return strcmp(pareja1->ataque->nombre, pareja2->ataque->nombre);
}

pareja_t *crear_pareja(pokemon_t *pokemon, const struct ataque *ataque)
{
	pareja_t *pareja = calloc(1, sizeof(pareja_t));
	if (pareja == NULL)
		return NULL;

	pareja->pokemon = pokemon;
	pareja->ataque = ataque;
	return pareja;
}
void llenar_parejas_en_arbol(const struct ataque *ataque, void *aux)
{
	disponible_t *dispo = aux;

	pareja_t *p = crear_pareja(dispo->pokemon, ataque);
	if (p == NULL)
		return;

	abb_insertar(dispo->arbol, p);
}
void destruir_pareja(void *aux)
{
	if (aux == NULL)
		return;
	free((pareja_t *)aux);
}
//---------------------------------------------------------
