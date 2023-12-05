#include <stdlib.h>
#include "pokemon.h"
#include "tipo.h"
#include "ataque.h"
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#define MAX_NOMBRE 30
#define CANTIDAD_ATAQUES 3

struct pokemon {
	char nombre[MAX_NOMBRE];
	enum TIPO tipo;
	struct ataque Ataques[CANTIDAD_ATAQUES];
};

struct info_pokemon {
	pokemon_t *pokemones;
	size_t cantidad;
};

//**************Funciones auxiliares ************
bool cargar_pokemon(FILE *fo, pokemon_t *pokemon_n);
bool ordenarAlfabeto_pokemones(informacion_pokemon_t *ip);
enum TIPO asignarTipo(char inicialTipo);
bool copiarPokemon(pokemon_t *copia, pokemon_t *original);
//**********************************************

informacion_pokemon_t *pokemon_cargar_archivo(const char *path)
{
	FILE *fo;
	informacion_pokemon_t *ip;
	pokemon_t *pokemon_n, pkm_aux;

	if (path == NULL) {
		return NULL;
	}

	ip = (informacion_pokemon_t *)malloc(sizeof(informacion_pokemon_t));

	if (ip == NULL) {
		return NULL;
	}

	// inicializacion
	ip->pokemones = NULL;
	ip->cantidad = 0;

	fo = fopen(path, "r");

	if (fo == NULL) {
		free(ip);

		return NULL;
	}

	if (!cargar_pokemon(fo, &pkm_aux)) {
		fclose(fo);
		free(ip);
		return NULL;
	}

	pokemon_n = (pokemon_t *)malloc(sizeof(pokemon_t));

	if (pokemon_n == NULL) {
		fclose(fo);
		pokemon_destruir_todo(ip);
		return NULL;
	}

	copiarPokemon(pokemon_n, &pkm_aux);

	// actualizo ip
	ip->pokemones =
		pokemon_n; // apunto al primer pokemon del arreglo dinamico
	ip->cantidad++; // sumo al primero

	//mientras el archivo no termine ,  verificaar si hay uno mas y  ahi recien ahi pedir
	while (!feof(fo)) {
		//carga en stack
		if (!cargar_pokemon(fo, &pkm_aux)) {
			fclose(fo);

			return ip;
		}
		//si carga bien pide memoria en HEAP para cargar el proximo
		pokemon_n = (pokemon_t *)realloc(
			pokemon_n, (ip->cantidad + 1) * sizeof(pokemon_t));

		if (pokemon_n == NULL) {
			// no libero ip , ya que el primero se cargo correctamente y permanece apuntando a ese mismo
			fclose(fo);
			return ip;
		}

		ip->pokemones =
			pokemon_n; // apunta al primer pokemon en el nuevo bloque de memoria asignado por realloc

		if (!copiarPokemon(pokemon_n + ip->cantidad, &pkm_aux)) {
			// reasigno memoria sin el bloque nuevo sin cargar
			pokemon_n = (pokemon_t *)realloc(
				pokemon_n, (ip->cantidad) * sizeof(pokemon_t));

			if (pokemon_n == NULL) {
				// no libero ip , ya que el primero se cargo correctamente y permanece apuntando a ese mismo
				fclose(fo);
				free(ip);
				return NULL;
			}

			// no libero ip , ya que el primero se cargo correctamente y permanece apuntando a ese mismo
			fclose(fo);

			return ip;
		}

		ip->cantidad++; // incrementa cantidad de pokemones cargados
	}

	if (!ordenarAlfabeto_pokemones(ip)) {
		fclose(fo);
		free(ip);
		return NULL;
	}

	fclose(fo);
	return ip;
}
bool cargar_pokemon(FILE *fo, pokemon_t *pokemon_n)
{
	char tipoInicial; // variable auxiliar para asignar tipo
	int aux;

	aux = fscanf(fo, "%[^;];%c\n", pokemon_n->nombre, &tipoInicial);

	if (pokemon_n->nombre[0] == '\0' ||
	    tipoInicial == '\0') { // Si algun dato esta vacio devuelvo false

		return false;
	}

	pokemon_n->tipo = asignarTipo(tipoInicial);

	// 0 1 2
	for (int j = 0; j < CANTIDAD_ATAQUES; j++) {
		aux = fscanf(fo, "%[^;];%c;%u\n", pokemon_n->Ataques[j].nombre,
			     &tipoInicial, &pokemon_n->Ataques[j].poder);

		if (aux != CANTIDAD_ATAQUES) {
			return false;
		}

		pokemon_n->Ataques[j].tipo = asignarTipo(tipoInicial);

		if (pokemon_n->Ataques[j].tipo == -1) {
			return false;
		}
	}

	return true;
}
enum TIPO asignarTipo(char inicialTipo)
{
	switch (inicialTipo) {
	case 'N':
		return NORMAL;

	case 'F':
		return FUEGO;

	case 'A':
		return AGUA;

	case 'P':
		return PLANTA;

	case 'E':
		return ELECTRICO;

	case 'R':
		return ROCA;

	default:
		return -1;
	}
}

bool ordenarAlfabeto_pokemones(informacion_pokemon_t *ip)
{
	bool ordenados = true;
	pokemon_t aux_pkm;

	do {
		ordenados = true;

		for (int i = 0; i < ip->cantidad - 1; i++) {
			if (strcmp(ip->pokemones[i].nombre,
				   ip->pokemones[i + 1].nombre) > 0) {
				ordenados = false;

				// Intercambia pokemones
				copiarPokemon(&aux_pkm, &ip->pokemones[i + 1]);
				copiarPokemon(&ip->pokemones[i + 1],
					      &ip->pokemones[i]);
				copiarPokemon(&ip->pokemones[i], &aux_pkm);
			}
		}
	} while (!ordenados);

	return ordenados;
}

bool copiarPokemon(pokemon_t *copia, pokemon_t *original)
{
	if (copia == NULL || original == NULL) {
		fprintf(stderr, "\n ERROR EN EL PROCESO \n");
		return false;
	}

	strcpy(copia->nombre, original->nombre);
	copia->tipo = original->tipo;

	for (int i = 0; i < CANTIDAD_ATAQUES; i++) {
		strcpy(copia->Ataques[i].nombre, original->Ataques[i].nombre);
		copia->Ataques[i].tipo = original->Ataques[i].tipo;
		copia->Ataques[i].poder = original->Ataques[i].poder;
	}

	return true;
}
pokemon_t *pokemon_buscar(informacion_pokemon_t *ip, const char *nombre)
{
	if (ip == NULL || nombre == NULL) {
		return NULL;
	}

	for (int i = 0; i < ip->cantidad; i++) {
		if (!strcmp(nombre, ip->pokemones[i].nombre)) {
			return ip->pokemones + i;
		}
	}

	return NULL;
}

int pokemon_cantidad(informacion_pokemon_t *ip)
{
	if (ip == NULL)
		return 0;
	return (int)ip->cantidad;
}

const char *pokemon_nombre(pokemon_t *pokemon)
{
	if (pokemon == NULL) {
		return NULL;
	} else
		return pokemon->nombre;
}

enum TIPO pokemon_tipo(pokemon_t *pokemon)
{
	if (pokemon == NULL) {
		fprintf(stderr, "\nERRROR AL CONSULTAR TIPO\n");
		return NORMAL;
	} else
		return pokemon->tipo;
}

const struct ataque *pokemon_buscar_ataque(pokemon_t *pokemon,
					   const char *nombre)
{
	if (pokemon == NULL) {
		return NULL;
	} else {
		for (int i = 0; i < CANTIDAD_ATAQUES; i++) {
			if (!strcmp(nombre, pokemon->Ataques[i].nombre)) {
				return pokemon->Ataques + i;
			}
		}
	}

	return NULL;
}

int con_cada_pokemon(informacion_pokemon_t *ip, void (*f)(pokemon_t *, void *),
		     void *aux)
{
	if (f == NULL || ip == NULL) {
		return 0;
	}

	int cantidad_operados = 0;

	for (int i = 0; i < ip->cantidad; i++) {
		(*f)(ip->pokemones + i, aux);
		cantidad_operados++;
	}

	return cantidad_operados;
}

int con_cada_ataque(pokemon_t *pokemon,
		    void (*f)(const struct ataque *, void *), void *aux)
{
	if (f == NULL || pokemon == NULL) {
		return 0;
	}

	int cantidad_operados = 0;

	for (int i = 0; i < CANTIDAD_ATAQUES; i++) {
		(*f)(pokemon->Ataques + i, aux);
		cantidad_operados++;
	}

	return cantidad_operados;
}

void pokemon_destruir_todo(informacion_pokemon_t *ip)
{
	if (ip == NULL) {
		return;
	}
	// libero HEAP
	free(ip->pokemones); // libero vector dinamico
	free(ip); // libero memoria asignada a la variable indice
}
