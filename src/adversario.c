#include "lista.h"
#include "juego.h"
#include "adversario.h"
#include "pokemon.h"
#include <stdlib.h>
#include <string.h>
#include "ataque.h"
#include "abb.h"

struct adversario
{

	lista_t *pokemones_disponibles;

	lista_t *sus_pokemones;

	abb_t *jugadas_disponibles;

};

typedef struct ataque ataque_t;

adversario_t *adversario_crear(lista_t *pokemon)
{
	if(pokemon == NULL)
		return NULL;

	adversario_t * adversario = calloc(1,sizeof(adversario_t ));

	adversario->sus_pokemones = lista_crear();
	if(adversario->sus_pokemones == NULL)
	{
		free(adversario);
		return NULL;
	}

	adversario->pokemones_disponibles = pokemon;

	return adversario;
}

void insertar_ataque_adversario( const ataque_t *ataque , void * arbol_disponibles)
{
	
	arbol_disponibles = abb_insertar(arbol_disponibles,(char*)ataque->nombre);

}



void asignar_jugadas_disponibles_en_adversario(abb_t *jugadas_disponibles,pokemon_t *pkm1)
{
	jugadas_disponibles = abb_insertar(jugadas_disponibles,(char*)pokemon_nombre(pkm1));

	con_cada_ataque(pkm1,insertar_ataque_adversario,jugadas_disponibles);

}

bool adversario_seleccionar_pokemon(adversario_t *adversario, char **nombre1,char **nombre2, char **nombre3)
{
	if(adversario == NULL)
		return false;

	lista_t *pokemones_disp = adversario->pokemones_disponibles;



	pokemon_t * pkm1 = lista_elemento_en_posicion(pokemones_disp,1);
	pokemon_t * pkm2 =  lista_elemento_en_posicion(pokemones_disp,4);
	pokemon_t * pkm3 =  lista_elemento_en_posicion(pokemones_disp,4);

	strcpy(*nombre1 ,pokemon_nombre(pkm1));
	strcpy(*nombre2 ,pokemon_nombre(pkm2));
	strcpy(*nombre3 ,pokemon_nombre(pkm3));
	

	lista_insertar(adversario->sus_pokemones,pkm1);
    lista_insertar(adversario->sus_pokemones,pkm2);
	
	asignar_jugadas_disponibles_en_adversario(adversario->jugadas_disponibles, pkm1);
	asignar_jugadas_disponibles_en_adversario(adversario->jugadas_disponibles, pkm2);

	return true;
}


int comparar_nombres_adversario(void* pkm_actual ,void * objetivo )
{
	return strcmp(pokemon_nombre(pkm_actual),objetivo);
}

bool adversario_pokemon_seleccionado(adversario_t *adversario, char *nombre1,char *nombre2, char *nombre3)
{
	if(nombre3 == NULL)
		return false;

	pokemon_t * pkm3 = lista_buscar_elemento(adversario->pokemones_disponibles,comparar_nombres_adversario,nombre3);

	
	lista_insertar(adversario->sus_pokemones,pkm3);

	adversario->jugadas_disponibles = abb_insertar(adversario->jugadas_disponibles,nombre3);
	con_cada_ataque(pkm3,insertar_ataque_adversario,adversario->jugadas_disponibles);


	return true;
}

void elige_ataque(const struct ataque *ataque_actual, void * nombre)
{
	strcpy(nombre,ataque_actual->nombre);

}
jugada_t adversario_proxima_jugada(adversario_t *adversario)
{
	jugada_t j = { .ataque = "", .pokemon = "" };

	
	size_t pos_aleatoria = 0;

	pokemon_t *pkm = lista_elemento_en_posicion(adversario->sus_pokemones,pos_aleatoria);

	//itera hasta conseguir un pokemon valido
	while(pkm == NULL )
	{
		pos_aleatoria++;
		pkm = lista_elemento_en_posicion(adversario->sus_pokemones,pos_aleatoria);
	}

	strcpy(j.pokemon,pokemon_nombre(pkm));

	//elije un ataque
	con_cada_ataque(pkm,elige_ataque,&j.ataque);


	return j;
}

void adversario_informar_jugada(adversario_t *a, jugada_t j)
{
}

void adversario_destruir(adversario_t *adversario)
{
	abb_destruir_todo(adversario->jugadas_disponibles,NULL);
	lista_destruir_todo(adversario->pokemones_disponibles,NULL);
	lista_destruir_todo(adversario->sus_pokemones,NULL);


	free(adversario);




}