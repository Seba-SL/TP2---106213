#include "src/pokemon.h"
#include "src/ataque.h"
#include "src/juego.h"
#include "src/lista.h"
#include "src/adversario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOMBRE 30
#define MAX_NOMBRE_ARCHIVO 50

#define MSJ_PEDIR_ARCHIVO "Ingrese el archivo donde se encuentran sus pokemones"

/**
* Este main debe ser modificado para que el usuario pueda jugar el juego. Las
* instrucciones existentes son solamente a modo ilustrativo del funcionamiento
* muy alto nivel del juego.
*
* Las interacciones deben realizarse por entrada/salida estandar y estar validadas.
*
* Se aconseja en todo momento mostrar información relevante para el jugador (por
* ejemplo, mostrar puntaje actual y movimientos disponibles) para hacer que el
* juego sea facil de utilizar.

*/


void bienvenida();
char* pedir_archivo();
void mostrar_pokemon_disponibles(juego_t * juego);
void jugador_seleccionar_pokemon(juego_t *juego, char * eleccionJugador1,char * eleccionJugador2,char * eleccionJugador3);
jugada_t jugador_pedir_nombre_y_ataque();


int main(int argc, char *argv[])
{

	juego_t *juego = juego_crear();

	bienvenida();

	//Pide al usuario un nombre de archivo de pokemones
	char *archivo = pedir_archivo();

	juego_cargar_pokemon(juego, archivo);

	
	//Crea un adversario que será utilizado como jugador 2
	//adversario_t *adversario =
	//	adversario_crear(juego_listar_pokemon(juego));

	//Mostrar el listado de pokemones por consola para que el usuario sepa las opciones que tiene
	mostrar_pokemon_disponibles(juego);

	
	//Pedirle al jugador por consola que ingrese los 3 nombres de pokemon que quiere utilizar
	char *eleccionJugador1 = NULL, *eleccionJugador2 = NULL, *eleccionJugador3 = NULL;
	jugador_seleccionar_pokemon(juego, eleccionJugador1,eleccionJugador2,eleccionJugador1);


		//Seleccionar los pokemon de los jugadoresd 
	juego_seleccionar_pokemon(juego, JUGADOR1, eleccionJugador1,eleccionJugador2, eleccionJugador3);


	//Pedirle al jugador por consola que ingrese los 3 nombres de pokemon que quiere utilizar
	char *eleccion_adversario1 = NULL, *eleccion_adversario2 = NULL, *eleccion_adversario3 = NULL;
	jugador_seleccionar_pokemon(juego, eleccion_adversario1,eleccion_adversario2,eleccion_adversario3);


		//Seleccionar los pokemon de los jugadoresd 
	juego_seleccionar_pokemon(juego, JUGADOR2, eleccion_adversario1,eleccion_adversario2, eleccion_adversario3);




	while (!juego_finalizado(juego)) {
		resultado_jugada_t resultado_ronda;

		//Pide al jugador que ingrese por consola el pokemon y ataque para la siguiente ronda
		jugada_t jugada_jugador = jugador_pedir_nombre_y_ataque();

		//Pide al adversario que informe el pokemon y ataque para la siguiente ronda
		jugada_t jugada_adversario =
			 jugador_pedir_nombre_y_ataque();

		//jugar la ronda y después comprobar que esté todo ok, si no, volver a pedir la jugada del jugador
		resultado_ronda = juego_jugar_turno(juego, jugada_jugador,
						    jugada_adversario);

		//Si se pudo jugar el turno, le informo al adversario la jugada realizada por el jugador
		//adversario_informar_jugada(adversario, jugada_jugador);

		 printf("\nRonda:P1 %d P2 %d \n",resultado_ronda.jugador1,resultado_ronda.jugador2);
	}


	free(eleccionJugador1);
	free(eleccionJugador2);
	free(eleccionJugador3);
	juego_destruir(juego);
}

jugada_t jugador_pedir_nombre_y_ataque()
{
	jugada_t nueva;

	strcpy(nueva.pokemon,"Pikachu");
	strcpy(nueva.ataque,"Latigo");

	return nueva;
}

char*  pedir_archivo()
{
	char *nombre_archivo = malloc(sizeof(char)*MAX_NOMBRE_ARCHIVO);

	puts(MSJ_PEDIR_ARCHIVO);

	
	fscanf(stdin,"%s",nombre_archivo);

	printf("\n \t\t        Cargando cartucho.....\n\n");

	return nombre_archivo;
}



bool imprimir_nombre_pkm(void* pokemon ,void* contexto)
{

	pokemon_t * pkm = pokemon;

	printf("\n %s ", pokemon_nombre(pkm));

	return true;

}

 void mostrar_pokemon_disponibles(juego_t * juego)
 {
	if(juego == NULL)return ;


	lista_t *lista_pkm = juego_listar_pokemon(juego);


	lista_con_cada_elemento(lista_pkm,imprimir_nombre_pkm,NULL);

	printf("\n\n\n \t\t Cantidad de pokemons disponibles : %zu\n",lista_tamanio(lista_pkm));

	

 }

 void jugador_seleccionar_pokemon(juego_t *juego, char * eleccionJugador1,char * eleccionJugador2,char * eleccionJugador3)
 {
	puts("Seleccione 3 pokemons para guardar en su mochila!");

	eleccionJugador1 = malloc(sizeof(char)*MAX_NOMBRE);
	eleccionJugador2 = malloc(sizeof(char)*MAX_NOMBRE);
	eleccionJugador3 = malloc(sizeof(char)*MAX_NOMBRE);

	
		puts("Selecciona el nombre del primero");
		fscanf(stdin,"%s",	eleccionJugador1);


		puts("Selecciona el nombre del segundo,recuerda que no puedes tener repetidos");
		fscanf(stdin,"%s",	eleccionJugador2);

		while(strcmp(eleccionJugador1,eleccionJugador2) == 0)
			{
				puts("Selecciona un nombre distinto!!!!");
				fscanf(stdin,"%s",	eleccionJugador1);
			}

		if(strcmp("Charmander",eleccionJugador1) != 0 && strcmp("Charmander",eleccionJugador2) != 0  )
			puts("¿todavia no elegiste a el dragoncito? ");


		puts("Aca viene el tercerooooooo  ");
		fscanf(stdin,"%s",	eleccionJugador3);

			
		while( strcmp(eleccionJugador1,eleccionJugador3) == 0 ||  strcmp(eleccionJugador2,eleccionJugador3) == 0)
			{
				
					puts("Selecciona un nombre distinto!!!!");
					fscanf(stdin,"%s",	eleccionJugador1);
				
			}
 }


 void bienvenida()
{

	printf("                                  ,'\\ \n");
	printf("    _.----.        ____         ,'  _\\   ___    ___     ____ \n");
	printf("_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`. \n");
	printf("\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  | \n");
	printf(" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  | \n");
	printf("  \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  | \n");
	printf("   \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     | \n");
	printf("    \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    | \n");
	printf("     \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   | \n");
	printf("      \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   | \n");
	printf("       \\_.-'       |__|    `-._ |              '-.|     '-.| |   | \n");
	printf("                               `'                            '-._|\n");


}