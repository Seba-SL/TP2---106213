#include "lista.h"
#include "juego.h"
#include "adversario.h"
#include "pokemon.h"

#define NOMBRE_MAXIMO 20

typedef struct adversario 
{
	char nombre[NOMBRE_MAXIMO];
	lista_t *pokemones;

	int b_ganadas;
    int b_perdidas;
    int b_empatadas;

}adversario_t;

adversario_t *adversario_crear(lista_t *pokemon)
{
	if(pokemon == NULL)
		return NULL;

	
}

bool adversario_seleccionar_pokemon(adversario_t *adversario, char **nombre1,
				    char **nombre2, char **nombre3)
{
	return false;
}

bool adversario_pokemon_seleccionado(adversario_t *adversario, char *nombre1,
				     char *nombre2, char *nombre3)
{
	return false;
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
}
