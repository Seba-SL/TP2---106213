#include "lista.h"
#include "juego.h"
#include "adversario.h"
#include "pokemon.h"
#include <stdlib.h>
#include <string.h>
#include "ataque.h"

struct adversario
{
	lista_t *lista_pokemones;

	lista_t *mochila_adversario;
	lista_t *jugadas_disponibles; //lista de jugada_t (nombre de poke y nombre de ataque)

	lista_t *mochila_jugador;
};

void destructor_jugadas(void *jugada)
 {
	jugada_t *jugada_ = jugada;
	free(jugada_);
}

int compador_jugadas(void *jugada1, void *jugada2) {
	jugada_t *jugada1_ = jugada1;
	jugada_t *jugada2_ = jugada2;

	return strcmp(jugada1_->ataque, jugada2_->ataque);
}

adversario_t *adversario_crear(lista_t *pokemon)
{
	adversario_t *adversario = calloc(1, sizeof(adversario_t));
	if(adversario == NULL) 
		return NULL;

	adversario->lista_pokemones = pokemon;

	adversario->mochila_adversario = lista_crear();
	adversario->jugadas_disponibles = lista_crear();

	adversario->mochila_jugador = lista_crear();

	if(adversario->mochila_adversario == NULL || adversario->jugadas_disponibles == NULL || adversario->mochila_jugador == NULL) {
		adversario_destruir(adversario);
		return NULL;
	}

	return adversario;
}

jugada_t *jugada_crear(char *nombre_pkm, char *nombre_ataque) {
	jugada_t *jugada = malloc(sizeof(jugada_t));
	if(jugada == NULL) 
		return NULL;

	strcpy(jugada->pokemon, nombre_pkm);
	strcpy(jugada->ataque, nombre_ataque);

	return jugada;
}

typedef struct
 {
	char *nombre_pkm;
	lista_t *lista;
	bool *exito;
} para_listar_jugada_t;

void listar_jugada(const struct ataque *ataque, void *aux_)
 {
	para_listar_jugada_t *aux_ = aux_;

	jugada_t *jugada = jugada_crear(ataque->nombre, ataque->poder);
	
	if(jugada == NULL)
	{
		
		return;
	}

	if( lista_insertar( aux_->lista, (void*)jugada  ) == NULL	)
	{
		destructor_jugadas(jugada);
		
	}
}

bool jugada_a_lista(pokemon_t *pokemon, lista_t *lista) {

	para_listar_jugada_t aux = {.nombre_pkm = pokemon_nombre(pokemon), .lista = lista, .exito = true};

	con_cada_ataque(pokemon, listar_jugada, &aux);

	return aux.exito;
}

bool adversario_seleccionar_pokemon(adversario_t *adversario, char **nombre1,
				    char **nombre2, char **nombre3)
{
	if(adversario == NULL)
		return false;

	pokemon_t *pkm1_adversario = lista_elemento_en_posicion(adversario->lista_pokemones, 0);
	pokemon_t *pkm2_adversario = lista_elemento_en_posicion(adversario->lista_pokemones, 1); 
	pokemon_t *pkm3_jugador = lista_elemento_en_posicion(adversario->lista_pokemones, 2);


	if(jugada_a_lista(pkm1_adversario, adversario->jugadas_disponibles) == false)
		return false;

	if(jugada_a_lista(pkm2_adversario, adversario->jugadas_disponibles) == false)
		return false;
	
	if(pkm1_adversario == NULL || pkm2_adversario == NULL || pkm3_jugador == NULL)
		return false;

	*nombre1 = (char *)pokemon_nombre(pkm1_adversario);
	*nombre2 = (char *)pokemon_nombre(pkm2_adversario); 
	*nombre3 = (char *)pokemon_nombre(pkm3_jugador);

	if(lista_insertar(adversario->mochila_adversario, pkm1_adversario) == NULL) 
		return false;

	if(lista_insertar(adversario->mochila_adversario, pkm2_adversario) == NULL)
		return false;

	if(lista_insertar(adversario->mochila_jugador, pkm3_jugador) == NULL)
		return false;

	return true;
}

int comparar_con_nombre(void *pokemon, void *nombre) {
	pokemon_t *pokemon_ = pokemon;
	char *nombre_ = nombre;

	return strcmp(pokemon_nombre(pokemon_), nombre);
}

bool adversario_pokemon_seleccionado(adversario_t *adversario, char *nombre1,
				     char *nombre2, char *nombre3)
{
	if(adversario == NULL)
		return false;

	pokemon_t *pkm1_jugador = lista_buscar_elemento(adversario->lista_pokemones, comparar_con_nombre, nombre1);
	pokemon_t *pkm2_jugador = lista_buscar_elemento(adversario->lista_pokemones, comparar_con_nombre, nombre2);
	pokemon_t *pkm3_adversario = lista_buscar_elemento(adversario->lista_pokemones, comparar_con_nombre, nombre3);

	if(pkm1_jugador == NULL || pkm2_jugador == NULL || pkm3_adversario == NULL)
		return false;

	if(lista_insertar(adversario->mochila_jugador, pkm1_jugador) == NULL) 
		return false;

	if(lista_insertar(adversario->mochila_jugador, pkm2_jugador) == NULL)
		return false;

	if(lista_insertar(adversario->mochila_adversario, pkm3_adversario) == NULL) //agrego a la lista de adversario el ulitmo poke
		return false;

	if(jugada_a_lista(pkm3_adversario, adversario->jugadas_disponibles) == false) //agrego a la lista de jugadas_dispo las ultimas 3 cartas
		return false;

	return true;
}

#include <time.h>

jugada_t adversario_proxima_jugada(adversario_t *adversario)
{
	jugada_t prox_jugada = { .ataque = "", .pokemon = "" };

	if(adversario == NULL)
		return prox_jugada;

    srand(time(NULL));

	size_t pos_azar = (size_t)(		rand() % (lista_tamanio(adversario->jugadas_disponibles))	);

	jugada_t *aux = lista_quitar_de_posicion(adversario->jugadas_disponibles, pos_azar);

	prox_jugada = *aux;

	destructor_jugadas(aux);

	return prox_jugada; 
}

void adversario_informar_jugada(adversario_t *a, jugada_t j)
{
}

void adversario_destruir(adversario_t *adversario)
{
	lista_destruir(adversario->mochila_adversario);
	lista_destruir(adversario->jugadas_disponibles, destructor_jugadas);

	lista_destruir(adversario->mochila_jugador);

	free(adversario);
}
