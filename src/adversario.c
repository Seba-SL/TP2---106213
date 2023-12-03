#include "lista.h"
#include "juego.h"
#include "adversario.h"
#include "pokemon.h"
#include <stdlib.h>
#include "hash.h"
#include <string.h>

struct adversario 
{	
	hash_t *su_tablita_hash;
	lista_t *sus_pokemones;

};


adversario_t *adversario_crear(lista_t *pokemon)
{
	if(pokemon == NULL)
		return NULL;

	adversario_t *nuevo_adversario = calloc(1,sizeof(adversario_t));
	
	nuevo_adversario->sus_pokemones = pokemon;


	nuevo_adversario->su_tablita_hash = hash_crear(lista_tamanio(nuevo_adversario->sus_pokemones));
	
	if(nuevo_adversario->su_tablita_hash)
		return NULL;

	return nuevo_adversario;
}

bool adversario_seleccionar_pokemon(adversario_t *adversario, char **nombre1,char **nombre2, char **nombre3)
{
	if(!adversario )
		return NULL;

	lista_t * sus_pkms = adversario->sus_pokemones;

	size_t pos1,pos2,pos3;

	pos1 = (size_t)rand() % (lista_tamanio(sus_pkms)+1);

	pos2 = (size_t)rand() % (lista_tamanio(sus_pkms)+1);

	while(pos2 == pos1)
		pos2 = (size_t)rand() % (lista_tamanio(sus_pkms)+1);

	pos2 = ( size_t) rand() % (lista_tamanio(sus_pkms)+1);

	while(pos2 == pos3 || pos3 == pos1)
		pos3 = (size_t)rand() % (lista_tamanio(sus_pkms)+1);

	pokemon_t *pkm1 =  lista_elemento_en_posicion(sus_pkms,pos1);
	
	pokemon_t *pkm2 =  lista_elemento_en_posicion(sus_pkms,pos2);
	
	pokemon_t *pkm3 =  lista_elemento_en_posicion(sus_pkms,pos3);

	if(pkm1 == NULL || pkm2 == NULL || pkm3 == NULL)
		return false;

	strcpy(*nombre1, pokemon_nombre(pkm1));
	strcpy(*nombre2, pokemon_nombre(pkm2));
	strcpy(*nombre3, pokemon_nombre(pkm3));

	return true;
}

bool adversario_pokemon_seleccionado(adversario_t *adversario, char *nombre1,char *nombre2, char *nombre3)
{
	return true;
}

jugada_t adversario_proxima_jugada(adversario_t *adversario)
{
	jugada_t j = { .ataque = "", .pokemon = "" };
	return j;
}

void adversario_informar_jugada(adversario_t *a, jugada_t j)
{

}

void adversario_destruir(adversario_t *adversario)
{

	hash_destruir(adversario->su_tablita_hash);
	
	free(adversario);
}
