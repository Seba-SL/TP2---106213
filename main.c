#include "src/pokemon.h"
#include "src/ataque.h"
#include "src/lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/juego.h"
#include "src/adversario.h"
#include "src/graficas.h"
#include "src/menu.h"

#define MAX_NOMBRE 30
#define MAX_NOMBRE_ARCHIVO 50
#define MAX_LINEA 30


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

typedef struct e
{
    juego_t *juego;
    char * eleccionJugador1;
    char * eleccionJugador2;
    char * eleccionJugador3;
    
    jugada_t jugada_actual;
   
}elecciones_t;



/*************************************************** Funciones auxiliares  ********************************************************************/

//funciones de los comandos
bool pedir_archivo(void * menu);
bool mostrar_pokemon_disponibles(void * menu);
bool jugar(void * menu);
bool salir_juego(void * menu) ;


//auxiliares
void jugador_seleccionar_pokemon( elecciones_t * elecciones);

JUEGO_ESTADO precompetencia(menu_t *menu ,juego_t *juego, elecciones_t * jugador1 , adversario_t * adversario);


JUEGO_ESTADO competencia(menu_t *menu,juego_t *juego);



/*********************************************************************************************************************************************/



int main(int argc,  char *argv[])
{
    juego_t *juego = juego_crear();
    menu_t *nueva_partida = crear_menu((void *) juego);
	   
    MENU_RESULTADO estado = MENU_OK;

    char *linea = malloc(sizeof(char)*MAX_LINEA);

    estado =  menu_agregar_comando(nueva_partida,"c","Ingresar archivo",pedir_archivo);
    
    estado =  menu_agregar_comando(nueva_partida,"v","Ver pokemones",mostrar_pokemon_disponibles);

    estado =  menu_agregar_comando(nueva_partida,"s","salir",salir_juego);

    estado = menu_agregar_comando(nueva_partida,"j","Jugar",jugar);

    bienvenida();

    printf("Hola entrenador %s bienvenido al mundo Pokemon!\n",dar_nombre_usuario(nueva_partida));

    if(estado != MENU_OK)
    {
        puts("Error al ingresar comando");
        return ERROR_GENERAL;
    }

   
    while(!juego_finalizado(juego) && estado != MENU_SALIR)
    {
        switch (estado)
        {
        case MENU_INEXISTENTE:
            puts(LIMPIAR_PANTALLA);
            bienvenida();
            printf("\nComando inexistente , %s re ingrese un comando valido\n\n",dar_nombre_usuario(nueva_partida));
            break;
        
        default:
             puts("Ingrese comandos a continuacion");
            break;
        }
      
        mostrar_menu(nueva_partida);
        fgets(linea,MAX_LINEA,stdin);
        linea[strlen(linea)-1] = 0;

        estado =  menu_ejecutar_comando(nueva_partida,linea,nueva_partida);

    }
	
    if( estado ==  MENU_ERROR )
    {
        free(linea);
        menu_destruir(nueva_partida);
	    juego_destruir(juego);
        return MENU_ERROR;
    }
    

    printf("\n Chau entrendador %s , gracias por batallar!\n",dar_nombre_usuario(nueva_partida));
          
    free(linea);
    menu_destruir(nueva_partida);
	juego_destruir(juego);
}


bool salir_juego(void *menu ) 
{
    return false;
}


bool pedir_archivo(void* menu)
{
    JUEGO_ESTADO estado = TODO_OK;
  
    if(!menu)
     {
          return false;
     }

	char *nombre_archivo = malloc(sizeof(char)*MAX_NOMBRE_ARCHIVO);

    if(nombre_archivo == NULL)
        {
            return false;
        }

	puts(MSJ_PEDIR_ARCHIVO);

	 
    fgets(nombre_archivo,MAX_NOMBRE_ARCHIVO,stdin);
	
    nombre_archivo[strlen(nombre_archivo)-1] = 0;

	mensaje_cargando();

    
    estado = asignar_archivo_menu(menu,nombre_archivo);

    estado = juego_cargar_pokemon((juego_t*)entregar_app(menu),entregar_nombre_archivo(menu));

    if(estado == TODO_OK)
        mensaje_cargado_con_exito();
    
    if(estado == ERROR_GENERAL)
    {
        carga_invalida();
    }

    return !estado;
}


bool imprimir_nombre_pkm(void* pokemon ,void* posicion)
{

	pokemon_t * pkm = pokemon;

	printf("\n %d %s ",*(int*)posicion , pokemon_nombre(pkm));

	(*(int *)posicion)++;

	return true;

}

 bool mostrar_pokemon_disponibles(void * menu)
 {
	if(menu == NULL)
        return false;


	lista_t *lista_pkm = juego_listar_pokemon((juego_t*)entregar_app(menu));

	size_t *posiciones = calloc(1,sizeof(size_t));


	lista_con_cada_elemento(lista_pkm,imprimir_nombre_pkm,posiciones);

	printf("\n\n\n \t\t Cantidad de pokemons disponibles : %zu\n",lista_tamanio(lista_pkm));

	
	free(posiciones);

    return true;
 }


bool jugar(void* menu)
{
    if(menu == NULL || !entregar_app(menu))
       return false;

    JUEGO_ESTADO estado = TODO_OK;

    juego_t * juego = entregar_app(menu);
   
    elecciones_t *jugador1_e = calloc(1,sizeof(elecciones_t));
   
    adversario_t *rival = adversario_crear(juego_listar_pokemon((juego_t*)juego));
    
    if(jugador1_e == NULL || rival == NULL)
    { 
        adversario_destruir(rival);
         free(jugador1_e);
        return false;
    }
    

    jugador1_e->juego = juego;

    estado = precompetencia(menu,juego,jugador1_e,rival);

    estado = competencia(menu,juego);
 
    free(jugador1_e);
    adversario_destruir(rival);


    puts(MENSAJE_FIN_PARTIDA);
    return !estado;

}

JUEGO_ESTADO precompetencia(menu_t *menu ,juego_t *juego, elecciones_t * jugador1 , adversario_t * adversario)
{

    printf("\n\nTurno de elegir pokemones del entrenador %s\n\n\n",dar_nombre_usuario(menu));

    jugador_seleccionar_pokemon(jugador1);
    
    JUEGO_ESTADO estado = juego_seleccionar_pokemon(juego,JUGADOR1,jugador1->eleccionJugador1,jugador1->eleccionJugador2,jugador1->eleccionJugador3);

    if(estado != TODO_OK)
       { 
       
         adversario_destruir(adversario); 
         free(jugador1); 
         
         return false;
       }
     
    printf("\nTurno de elegir pokemones del adversario \n");
    
    char *eleccion_adversario1 = NULL, *eleccion_adversario2 = NULL, *eleccion_adversario3 = NULL;
    
	eleccion_adversario1 = calloc(1,sizeof(char)*MAX_NOMBRE);
	eleccion_adversario2 = calloc(1,sizeof(char)*MAX_NOMBRE);
	eleccion_adversario3 = calloc(1,sizeof(char)*MAX_NOMBRE);
    
    estado = adversario_seleccionar_pokemon(adversario,&eleccion_adversario1,&eleccion_adversario2,&eleccion_adversario3);

    estado = juego_seleccionar_pokemon(juego, JUGADOR2, eleccion_adversario1,eleccion_adversario2, eleccion_adversario3);

    if(estado != TODO_OK)
    { 
        adversario_destruir(adversario);
        free(jugador1); 
        return false;
    }

    free(eleccion_adversario1);
    free(eleccion_adversario2);
    free(eleccion_adversario3);

    return estado;
}

JUEGO_ESTADO competencia(menu_t *menu,juego_t *juego)
{
    if(!menu || !juego)
    { 
         return ERROR_GENERAL;
    }
    
	resultado_jugada_t resultado_ronda;
    size_t ronda_n = 0;

	resultado_ronda.jugador1 = ATAQUE_REGULAR;
	resultado_ronda.jugador2 = ATAQUE_REGULAR;

    
    puts("aca hay competencia");

	while( !juego_finalizado(juego))
	{
	
		//Pide al jugador que ingrese por consola el pokemon y ataque para la siguiente ronda
		jugada_t jugada_jugador;
            //HARDCODEADO!!!!!!!!!!!!!!!!
         strcpy(jugada_jugador.pokemon,"Pikachu");
         strcpy(jugada_jugador.ataque,"Latigo");

        //jugador_pedir_nombre_y_ataque( juego ,JUGADOR1);

		//Pide al adversario que informe el pokemon y ataque para la siguiente ronda
		jugada_t jugada_adversario;

         strcpy(jugada_adversario.pokemon,"Pikachu");
         strcpy(jugada_adversario.ataque,"Latigo");

        //jugador_pedir_nombre_y_ataque( juego,JUGADOR2 );

		//jugar la ronda y después comprobar que esté todo ok, si no, volver a pedir la jugada del jugador
		resultado_ronda = juego_jugar_turno(juego, jugada_jugador, jugada_adversario);


        if(resultado_ronda.jugador1 == ATAQUE_ERROR && resultado_ronda.jugador2 == ATAQUE_ERROR)
            puts("indique ataques validos");
        
		//Si se pudo jugar el turno, le informo al adversario la jugada realizada por el jugador
		//adversario_informar_jugada(adversario, jugada_jugador);

		 printf("\nRonda %zu:P1 %d P2 %d \n",ronda_n,juego_obtener_puntaje(juego,JUGADOR1),juego_obtener_puntaje(juego,JUGADOR2));
         ronda_n++;
	}
   

    printf("\n\n\tResultado ronda Partida:\nJugador 1 %d\nAdversario %d\n", juego_obtener_puntaje(juego,JUGADOR1), juego_obtener_puntaje(juego,JUGADOR2));

    return TODO_OK;
}

 void jugador_seleccionar_pokemon( elecciones_t * elecciones)
 {
    
	lista_t *lista_pkm = juego_listar_pokemon(elecciones->juego);

	puts("Selecciona tres Pokemons!");

	int pkm1_p = -1,pkm2_p = -1 , pkm3_p = -1;

	int tope = (int )lista_tamanio(lista_pkm);

    char buffer[MAX_LINEA];
	
		puts("Selecciona el primero!");
		//fscanf(stdin,"%d",	&pkm1_p);
        fgets(buffer,MAX_LINEA,stdin);

        pkm1_p = atoi(buffer);
       
			while(pkm1_p < 0)
			{
			
				puts("Selecciona una posicion valida!");
				fgets(buffer,MAX_LINEA,stdin);
                pkm1_p = atoi(buffer);
				
			}

	

		puts("Selecciona el segundo!");
		fgets(buffer,MAX_LINEA,stdin);
        pkm2_p = atoi(buffer);
		
				
			while(pkm2_p < 0 || pkm2_p == pkm1_p)
			{
				puts("Selecciona una posicion valida!");
				fgets(buffer,MAX_LINEA,stdin);
                 pkm2_p = atoi(buffer);
				
				
			}


		puts("Selecciona el tercero!");
		fgets(buffer,MAX_LINEA,stdin);
        pkm3_p = atoi(buffer);
		
		
				
		while(pkm3_p < 0 || pkm3_p == pkm1_p ||  pkm3_p == pkm2_p )
		{
			puts("Selecciona una posicion valida!");
			fgets(buffer,MAX_LINEA,stdin);
            pkm3_p = atoi(buffer);
		
			
			
		}

       

		if(pkm1_p > tope || pkm2_p > tope || pkm1_p > tope)
		{
			puts("Ingrese valores validos!");
			jugador_seleccionar_pokemon( elecciones);
			return;
		}

		

	
		elecciones->eleccionJugador1 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm1_p));

		dibujar_pkm(elecciones->eleccionJugador1);

		elecciones->eleccionJugador2 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm2_p));

		dibujar_pkm(elecciones->eleccionJugador2);

		elecciones->eleccionJugador3 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm3_p));

		dibujar_pkm(elecciones->eleccionJugador3);

			
 }
