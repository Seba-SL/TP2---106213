#include "juego.h"
#include "lista.h"
#include "tipo.h"
#include <stdbool.h>
#include "pokemon.h"
#include "ataque.h"
#include "abb.h"
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#define CANTIDAD_MOVIMIENTOS 9
#define CANTIDAD_MIN_POKEMONES 4
#define CANTIDAD_JUGADAS 9

typedef struct ataque ataque_t;



typedef struct jugador
{
	lista_t *sus_pokemones;
	int puntaje;
	bool eligio_jugadores;

	abb_t *jugadas_disponibles;
	
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

/************************************** Funciones auxiliares *******************************************************/

int comparador_abb( void *a, void *b);

void insertar_en_lista ( pokemon_t *actual , void *lista);

 
bool coincidencias( const char *nombre1, const char*nombre2, const char *nombre3);


void insertar_atk( const ataque_t *ataque , void *arbol_disponibles);


void asignar_jugadas_disponibles( abb_t *jugadas_disponibles , pokemon_t *pkm1);


int comparar_nombres( void* pkm_actual ,void * objetivo );


void asignar_resultado( RESULTADO_ATAQUE *resultado , const ataque_t *ataque , pokemon_t *oponente_pkm );


bool jugada_disponible(abb_t *disponibles ,jugada_t jugada_jugador);


void asignar_puntaje(int * puntaje , const ataque_t * ataque ,  RESULTADO_ATAQUE efectividad);


/******************************************************************************************************************/




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

	juego->jugadores[JUGADOR1].jugadas_disponibles = abb_crear(comparador_abb);
	juego->jugadores[JUGADOR2].jugadas_disponibles = abb_crear(comparador_abb);

	juego->cantidad_movimientos = CANTIDAD_MOVIMIENTOS;

	juego->jugadores[JUGADOR1].eligio_jugadores = false;
	juego->jugadores[JUGADOR2].eligio_jugadores = false;



	return juego;
}





JUEGO_ESTADO juego_cargar_pokemon(juego_t *juego, char *archivo)
{
	if(juego == NULL || archivo == NULL)return ERROR_GENERAL;

	juego->info_pokemones = pokemon_cargar_archivo(archivo);

	if(juego->info_pokemones  == NULL)return ERROR_GENERAL;


	if(pokemon_cantidad(juego->info_pokemones ) < CANTIDAD_MIN_POKEMONES)
	{	
		pokemon_destruir_todo(juego->info_pokemones);
		return POKEMON_INSUFICIENTES;
	}

	con_cada_pokemon(juego->info_pokemones ,insertar_en_lista,juego->lista_pokemones);


	if(lista_tamanio(juego->lista_pokemones) < CANTIDAD_MIN_POKEMONES)
	{
		lista_destruir_todo(juego->lista_pokemones,NULL);
		return POKEMON_INSUFICIENTES;
	}
	
	if(juego->lista_pokemones == NULL)return ERROR_GENERAL;


	return TODO_OK;
}




lista_t *juego_listar_pokemon(juego_t *juego)
{
	if(!juego || !juego->lista_pokemones)
		return NULL;

	return juego->lista_pokemones;
}





JUEGO_ESTADO juego_seleccionar_pokemon(juego_t *juego, JUGADOR jugador, const char *nombre1, const char *nombre2,const char *nombre3)
{
	//validaciones
	if(!juego || !nombre1 || !nombre2 || !nombre3)
		return ERROR_GENERAL;
	

	if(juego->jugadores[jugador].eligio_jugadores)
			return ERROR_GENERAL;
	

	if(coincidencias(nombre1,nombre2,nombre3))
			return POKEMON_REPETIDO;
	
	

	//apunto a la "mochila del jugador"
	lista_t *mochila_pokemones = juego->jugadores[jugador].sus_pokemones;


	//busco los pokemones
	pokemon_t *pkm1 = pokemon_buscar(juego->info_pokemones,nombre1);
	
	pokemon_t *pkm2 = pokemon_buscar(juego->info_pokemones,nombre2);
	
	pokemon_t *pkm3 = pokemon_buscar(juego->info_pokemones,nombre3);
	
	if(pkm1 == NULL|| pkm2 == NULL || pkm3 == NULL)
			return POKEMON_INEXISTENTE;
	
	//inserto 
	mochila_pokemones = lista_insertar(mochila_pokemones,pkm1);
	mochila_pokemones = lista_insertar(mochila_pokemones,pkm2);

	//el tercero va a el segundo jugador
	if(jugador == JUGADOR1)
		{
			juego->jugadores[JUGADOR2].sus_pokemones = lista_insertar(juego->jugadores[JUGADOR2].sus_pokemones,pkm3);
		}else juego->jugadores[JUGADOR1].sus_pokemones = lista_insertar(juego->jugadores[JUGADOR1].sus_pokemones,pkm3);
		
	asignar_jugadas_disponibles(juego->jugadores[jugador].jugadas_disponibles,pkm1);
	asignar_jugadas_disponibles(juego->jugadores[jugador].jugadas_disponibles,pkm2);


	if(jugador == JUGADOR1)
		{	
			asignar_jugadas_disponibles(juego->jugadores[JUGADOR2].jugadas_disponibles,pkm3);
			
		}else asignar_jugadas_disponibles(juego->jugadores[JUGADOR1].jugadas_disponibles,pkm3);;

	juego->jugadores[jugador].eligio_jugadores = true;
	
	return TODO_OK;
}


		
resultado_jugada_t juego_jugar_turno(juego_t *juego, jugada_t jugada_jugador1,jugada_t jugada_jugador2)
{
	resultado_jugada_t resultado;
	resultado.jugador1 = ATAQUE_ERROR;
	resultado.jugador2 = ATAQUE_ERROR;


	
	if(!juego)
		return resultado;

	if(!jugada_disponible(juego->jugadores[JUGADOR1].jugadas_disponibles,jugada_jugador1))
	{	
		
		return resultado;
	}

	if(!jugada_disponible(juego->jugadores[JUGADOR2].jugadas_disponibles,jugada_jugador2))
	{
		return resultado;
	}
	
	//saca los pokemones en sus mochilas , si es q existen
	pokemon_t *pkm1  = lista_buscar_elemento(juego->jugadores[JUGADOR1].sus_pokemones,comparar_nombres,jugada_jugador1.pokemon);
	pokemon_t *pkm2  = lista_buscar_elemento(juego->jugadores[JUGADOR2].sus_pokemones,comparar_nombres,jugada_jugador2.pokemon);

	
	if(!pkm1 || !pkm2)
		return resultado;

	//los pokemons tienen esos ataques?
	const ataque_t *atk1  = pokemon_buscar_ataque( pkm1 , jugada_jugador1.ataque);
	const ataque_t *atk2 = pokemon_buscar_ataque( pkm2 , jugada_jugador2.ataque); 

	if(!atk1 || !atk2 )
		return resultado;

	asignar_resultado( &resultado.jugador1 , atk1 , pkm2 );
	asignar_resultado( &resultado.jugador2 , atk2 , pkm1 );


	asignar_puntaje( &juego->jugadores[JUGADOR1].puntaje , atk1 ,  resultado.jugador1 );

	asignar_puntaje( &juego->jugadores[JUGADOR2].puntaje , atk2,  resultado.jugador2 );
	

	printf("puntaje q se suma en juego j1 : %d",juego->jugadores[JUGADOR2].puntaje);
	
	printf("puntaje q se suma en juego j2: %d",juego->jugadores[JUGADOR1].puntaje);

	
	juego->cantidad_movimientos--;

	return resultado;

}

int juego_obtener_puntaje(juego_t *juego, JUGADOR jugador)
{
	return juego->jugadores[jugador].puntaje;
}





bool juego_finalizado(juego_t *juego)
{

	if(juego->cantidad_movimientos > 0)
		return false;

	return true;
}





void juego_destruir(juego_t *juego)
{
	if(juego == NULL)return ;

	pokemon_destruir_todo(juego->info_pokemones);

	lista_destruir_todo(juego->lista_pokemones,NULL);
	lista_destruir_todo(juego->jugadores[JUGADOR1].sus_pokemones,NULL);
	lista_destruir_todo(juego->jugadores[JUGADOR2].sus_pokemones,NULL);

	abb_destruir_todo(juego->jugadores[JUGADOR1].jugadas_disponibles,NULL);
	
	abb_destruir_todo(juego->jugadores[JUGADOR2].jugadas_disponibles,NULL);
	

	free(juego);
}








/****************************Implementacion de auxiliares******************************/




 int comparador_abb(void *a, void *b)
 {
	return strcmp(a,b);
 }



 void insertar_en_lista (pokemon_t *actual , void * lista)
 {
	if(actual == NULL || lista == NULL)return;

	lista_t * lista_pkm = lista;

	lista_insertar(lista_pkm,actual);
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



void insertar_atk( const ataque_t *ataque , void * arbol_disponibles)
{
	
	arbol_disponibles = abb_insertar(arbol_disponibles,(char*)ataque->nombre);

}





void asignar_jugadas_disponibles(abb_t *jugadas_disponibles,pokemon_t *pkm1)
{
	jugadas_disponibles = abb_insertar(jugadas_disponibles,(char*)pokemon_nombre(pkm1));

	con_cada_ataque(pkm1,insertar_atk,jugadas_disponibles);

}


int comparar_nombres(void* pkm_actual ,void * objetivo )
{
	return strcmp(pokemon_nombre(pkm_actual),objetivo);
}



void asignar_resultado(RESULTADO_ATAQUE *resultado , const ataque_t *ataque ,pokemon_t *oponente_pkm )
{	
	

	if(ataque->tipo == FUEGO)
	{
		if(pokemon_tipo(oponente_pkm) == PLANTA)
		{	
			*resultado = ATAQUE_EFECTIVO;
			return;
		}

		if(pokemon_tipo(oponente_pkm) == AGUA)
		{	
			*resultado =  ATAQUE_INEFECTIVO;
			return;
		}

	}

	if(ataque->tipo == PLANTA)
	{
		if(pokemon_tipo(oponente_pkm) == ROCA)
		{	
			*resultado = ATAQUE_EFECTIVO;
			return;
		}

		if(pokemon_tipo(oponente_pkm) == FUEGO)
		{	
			*resultado = ATAQUE_INEFECTIVO;
			return;
		}

	}

	
	if(ataque->tipo == ROCA)
	{
		if(pokemon_tipo(oponente_pkm) == ELECTRICO)
		{	
			*resultado = ATAQUE_EFECTIVO;
			return;
		}

		if(pokemon_tipo(oponente_pkm) == PLANTA)
		{	
			*resultado = ATAQUE_INEFECTIVO;
			return;
		}

	}

	if(ataque->tipo == ELECTRICO)
	{
		if(pokemon_tipo(oponente_pkm) == AGUA)
		{	
			*resultado = ATAQUE_EFECTIVO;
			return;
		}

		if(pokemon_tipo(oponente_pkm) == ROCA)
		{	
			*resultado = ATAQUE_INEFECTIVO;
			return;
		}

	}

	if(ataque->tipo == AGUA)
	{
		if(pokemon_tipo(oponente_pkm) == FUEGO)
		{	
			*resultado = ATAQUE_EFECTIVO;
			return;
		}

		if(pokemon_tipo(oponente_pkm) == ELECTRICO)
		{	
			*resultado = ATAQUE_INEFECTIVO;
			return;

		}

	}

	if(ataque->tipo == NORMAL)
	{
		*resultado = ATAQUE_REGULAR;
		return ;
	}

	*resultado = ATAQUE_REGULAR;

}

float redondear(float numero) {
    int entero = (int)numero; // Obtenemos la parte entera del número
    float parte_decimal = numero -  (float)entero; // Obtenemos la parte decimal
    
    if (parte_decimal > 0) {
        return (float)entero + 1; // Si hay parte decimal, redondeamos hacia arriba sumando 1 a la parte entera
    } else {
        return numero; // Si es un número entero, lo dejamos sin modificar
    }
}


void asignar_puntaje(int * puntaje , const ataque_t * ataque ,  RESULTADO_ATAQUE efectividad)
{
	float aux = redondear((float)ataque->poder/((float)2));
	
	switch(efectividad)
	{
		case ATAQUE_EFECTIVO:
		
			*puntaje = *puntaje +  (int)ataque->poder*3;
			
			return ;
		
		case ATAQUE_INEFECTIVO:
			
			*puntaje = *puntaje + (int)aux ;
			
			return;
	
		default:
			
			*puntaje = *puntaje + (int) ataque->poder;
		
			return ;
	}


	
}

bool jugada_disponible(abb_t *disponibles ,jugada_t jugada_jugador)
{
	
	if( abb_quitar(disponibles,jugada_jugador.ataque) == NULL && abb_quitar(disponibles,jugada_jugador.pokemon) == NULL)
		return false;

	return true;
}

