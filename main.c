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
#define MAX_LINEA 20
#define CANTIDAD_ATAQUES 3
#define TIEMPO_DELAY 10000000
#define TIEMPO_DELAY2 1500000

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

typedef struct 
{
    juego_t *juego;

    char * eleccionJugador1;
    char * eleccionJugador2;
    char * eleccionJugador3;
    
    jugada_t jugada_actual;  //pokemon[20] y ataque[]
   
}elecciones_t;



/*************************************************** Funciones auxiliares  ********************************************************************/

//funciones de los comandos
bool pedir_archivo(void * menu);
bool mostrar_pokemon_disponibles(void * menu);
bool jugar(void * menu);
bool salir_juego(void * menu) ;
bool informacion_pokemones(void *menu);


//auxiliares
void jugador_seleccionar_pokemon( elecciones_t * elecciones);
jugada_t elige_jugada_j1(menu_t *menu,juego_t *juego,char*p1,char*p2,char*p3);

JUEGO_ESTADO precompetencia(menu_t *menu ,juego_t *juego, elecciones_t * jugador1 , adversario_t * adversario,char * eleccion_adversario1, char * eleccion_adversario2, char * eleccion_adversario3);
JUEGO_ESTADO competencia(menu_t *menu,juego_t *juego, elecciones_t * jugador1 ,adversario_t*rival);
void delay(int d);
void vaciar_cargas_anteriores(lista_t * cargados);
void vuelve_a_pedir(int *pkm1_p , char * buffer);
int comparar_nombres_en_juego(void* pkm_actual ,void * objetivo );
void mostrar_ataques(const struct ataque *atk, void *n);
bool imprimir_nombre_pkm(void* pokemon ,void* posicion);
bool imprimir_info_pkm(void* pokemon ,void* posicion);

void destruir_elecciones(elecciones_t *elecciones);



/*********************************************************************************************************************************************/



int main(int argc,  char *argv[])
{
    juego_t *juego = juego_crear();

    puts(LIMPIAR_PANTALLA);

    menu_t *nueva_partida = crear_menu((void *) juego);
	   
    MENU_RESULTADO estado = MENU_OK;


    char *linea = malloc(sizeof(char)*MAX_LINEA);

    estado =  menu_agregar_comando(nueva_partida,"c","Cargar archivo",pedir_archivo);
    
    estado =  menu_agregar_comando(nueva_partida,"v","Ver pokemones",mostrar_pokemon_disponibles);

    estado =  menu_agregar_comando(nueva_partida,"s","salir",salir_juego);

    estado = menu_agregar_comando(nueva_partida,"j","Jugar",jugar);

    estado = menu_agregar_comando(nueva_partida,"i","Ver informacion de los pokemones",informacion_pokemones);

    puts(LIMPIAR_PANTALLA);
    bienvenida();

   

    printf("Hola entrenador %s bienvenido/a al mundo Pokemon!\n",dar_nombre_usuario(nueva_partida));


    delay(TIEMPO_DELAY);

    puts(LIMPIAR_PANTALLA);


    if(estado != MENU_OK)
    {
        puts(MENSAJE_ERROR);
        return ERROR_GENERAL;
    }

   
    while(!juego_finalizado(juego) && estado != MENU_SALIR)
    {
       

        switch (estado)
        {
        case MENU_INEXISTENTE:
            
            puts(LIMPIAR_PANTALLA);
            bienvenida();
            mostrar_menu(nueva_partida);
            printf("\nComando inexistente , %s re ingrese un comando valido\n\n",dar_nombre_usuario(nueva_partida));
            break;
        
        default:
           
            bienvenida();
            mostrar_menu(nueva_partida);
            puts("Ingrese comandos a continuacion");
            break;
        }
      
       
        fgets(linea,MAX_LINEA,stdin);
        puts(LIMPIAR_PANTALLA);
        linea[strlen(linea)-1] = 0;
        puts(LIMPIAR_PANTALLA);

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








/*        PRINCIPALES     */

/*Asigna y carga el archivo para las partidas*/

bool pedir_archivo(void* menu)
{
    JUEGO_ESTADO estado = TODO_OK;
  
    if(!menu)
     {

          return MENU_ERROR;
     }

   
    bienvenida();

	char *nombre_archivo = malloc(sizeof(char)*MAX_NOMBRE_ARCHIVO);
    lista_t *l_pkm = juego_listar_pokemon(entregar_app(menu));

    if(nombre_archivo == NULL)
        {
            
            vaciar_cargas_anteriores(l_pkm);

            carga_invalida();
            return MENU_ERROR;
        }
    
   

	puts(MSJ_PEDIR_ARCHIVO);

	 
    fgets(nombre_archivo,MAX_NOMBRE_ARCHIVO,stdin);
	
    nombre_archivo[strlen(nombre_archivo)-1] = 0;

	mensaje_cargando();

    
    estado = asignar_archivo_menu(menu,nombre_archivo);

    estado = juego_cargar_pokemon((juego_t*)entregar_app(menu),entregar_nombre_archivo(menu));

    if(estado == TODO_OK)
    {
        mensaje_cargado_con_exito();
        
    }
    
    if(estado == ERROR_GENERAL)
    {   
        
        carga_invalida();
        return true;
    }

    return true;
}


void vaciar_cargas_anteriores(lista_t * cargados)
{
    int tam =  (int)lista_tamanio(cargados);

    for(int i=0; i < tam ; i++)
    {
       lista_quitar(cargados);

    }


}

/*     Muestra los pokemones                  */
 bool mostrar_pokemon_disponibles(void * menu)
 {
	if(menu == NULL )
    {
        puts(MENSAJE_ERROR);
        return false;
    }

	lista_t *lista_pkm = juego_listar_pokemon((juego_t*)entregar_app(menu));
	
     if(entregar_nombre_archivo(menu) == NULL || lista_vacia(lista_pkm))
    {
        puts(MSJ_NO_HAY_POKEMONES_CARGADOS);
        return true;
    }

    bienvenida();

    size_t *posiciones = calloc(1,sizeof(size_t));
    int pkm_eleccion = 0;
    
    do{
	
    *posiciones = 0;
    lista_con_cada_elemento(lista_pkm,imprimir_nombre_pkm,posiciones);

	printf("\n\t\t Cantidad de pokemons disponibles : %zu\n",lista_tamanio(lista_pkm));
    
    puts("ingrese la posicion del que quieres observar mas de cerca, para sali ingrese -1");

    char buffer[MAX_LINEA];
    fgets(buffer,MAX_LINEA,stdin);
    pkm_eleccion = atoi(buffer);


    while(pkm_eleccion >= lista_tamanio(lista_pkm)  &&  pkm_eleccion != -1)
    {
        
        puts("ingrese pokemon valido");     

        fgets(buffer,MAX_LINEA,stdin);
        pkm_eleccion = atoi(buffer);
    }

    if(pkm_eleccion != -1)
    {
        pokemon_t * a_observar_pkm = lista_elemento_en_posicion(lista_pkm,(size_t)pkm_eleccion);

        dibujar_pkm((char*)pokemon_nombre(a_observar_pkm));

        con_cada_ataque(a_observar_pkm,mostrar_ataques,NULL);

    }
	
    }while(pkm_eleccion != -1);

    puts(LIMPIAR_PANTALLA);
	free(posiciones);

    return true;
 }


/*          Informacion de pokemones y reglas del juego                */
bool informacion_pokemones(void *menu)
{   
    menu_t *menuu = menu;
    juego_t * juego = entregar_app(menuu);

    if(!entregar_nombre_archivo(menuu) || lista_vacia(juego_listar_pokemon(juego)))
    {
        puts(LIMPIAR_PANTALLA);
        puts("No hay pokemons cargados en el juego");
        return true;
    }

    lista_t *lista_pkm = juego_listar_pokemon(juego);

    size_t *posiciones = calloc(1,sizeof(size_t));

    lista_con_cada_elemento(lista_pkm,imprimir_info_pkm,posiciones);

    	
	free(posiciones);

    puts("\n");

    return true;
    
}


/*             Partida    */

bool jugar(void* menu)
{
    menu_t * menu_ = menu;

    if(menu == NULL || !entregar_app(menu) || lista_vacia(juego_listar_pokemon(entregar_app(menu_))))
    {
       puts("No se puede jugar sin pokemones disponibles!");
       return true;
    }

    bienvenida();
    
    JUEGO_ESTADO estado = TODO_OK;

    juego_t * juego = entregar_app(menu);
   
    elecciones_t *jugador1_e = calloc(1,sizeof(elecciones_t));
   
    adversario_t *rival = adversario_crear(juego_listar_pokemon((juego_t*)juego)); //TODO_OK = 0 , 
    
        
    char *eleccion_adversario1 = NULL, *eleccion_adversario2 = NULL, *eleccion_adversario3 = NULL;
    
	eleccion_adversario1 = calloc(1,sizeof(char)*MAX_NOMBRE);
	eleccion_adversario2 = calloc(1,sizeof(char)*MAX_NOMBRE);
	eleccion_adversario3 = calloc(1,sizeof(char)*MAX_NOMBRE);
    
    jugador1_e->juego = juego;

    estado = precompetencia(menu,juego,jugador1_e,rival,eleccion_adversario1,eleccion_adversario2,eleccion_adversario3);

    estado = competencia(menu,juego,jugador1_e,rival);
 
   
    adversario_destruir(rival);
   
    destruir_elecciones(jugador1_e);
    free(eleccion_adversario1);
    free(eleccion_adversario2);
    free(eleccion_adversario3);
    puts(MENSAJE_FIN_PARTIDA);
    return !estado;

}

JUEGO_ESTADO precompetencia(menu_t *menu ,juego_t *juego, elecciones_t * jugador1 , adversario_t * adversario,char * eleccion_adversario1, char * eleccion_adversario2, char * eleccion_adversario3)
{
    int * posiciones = calloc(1,sizeof(int));

    printf("\n\nTurno de elegir pokemones del entrenador %s\n\n\n",dar_nombre_usuario(menu));
  
    //muestro los pokemones disponibles
    lista_con_cada_elemento(juego_listar_pokemon(juego),imprimir_nombre_pkm,posiciones);

    //le pido al usuario que elija 3 y los guardo en los campos de jugador1
    jugador_seleccionar_pokemon(jugador1);
    
    //aca le asigno los dos primeros y el tercero va a jugador 2 
    JUEGO_ESTADO estado = juego_seleccionar_pokemon(juego,JUGADOR1,jugador1->eleccionJugador1,jugador1->eleccionJugador2,jugador1->eleccionJugador3);

    if(estado != TODO_OK)
       { 
       
         adversario_destruir(adversario); 
         free(jugador1); 
         free(posiciones);
         return false;
       }
     

    //Esto lo completa de forma automatica
    adversario_seleccionar_pokemon(adversario,&eleccion_adversario1,&eleccion_adversario2,&eleccion_adversario3);

    //Aca le guarda en juego_t  e intercambia 
    estado = juego_seleccionar_pokemon(juego,JUGADOR2,jugador1->eleccionJugador1,jugador1->eleccionJugador2,jugador1->eleccionJugador3);

    //Aca le guardo al adversario el tercero q le ortorga el primero
    adversario_pokemon_seleccionado(adversario,jugador1->eleccionJugador1,jugador1->eleccionJugador2,jugador1->eleccionJugador3);


    strcpy(jugador1->eleccionJugador3, eleccion_adversario3);

    
    dibujar_pkm(jugador1->eleccionJugador3);
    puts("Fulbo?");
    delay(TIEMPO_DELAY2);
    
    printf("\nBueno %s , lamento decirte que el adversario te robo el tercer pokemon , conformate con %s\n",dar_nombre_usuario(menu),jugador1->eleccionJugador3);

    if(estado != TODO_OK)
    { 
        free(posiciones);
        return false;
    }


    printf("\nTurno de elegir pokemones del adversario \n");

    
    
    free(posiciones);
    return estado;
}


JUEGO_ESTADO competencia(menu_t *menu,juego_t *juego,elecciones_t *elecciones_j1,adversario_t*rival)
{
    if(!menu || !juego || !elecciones_j1 || !rival)
    { 
         return ERROR_GENERAL;
    }
    
	resultado_jugada_t resultado_ronda;
    size_t ronda_n = 0;
    lista_t *pkm_disponibles = juego_listar_pokemon(juego);

    if(lista_vacia(pkm_disponibles))
    {
        return ERROR_GENERAL;
    }

	resultado_ronda.jugador1 = ATAQUE_REGULAR;
	resultado_ronda.jugador2 = ATAQUE_REGULAR;

    
    puts("aca hay competencia");

	while( !juego_finalizado(juego) && ronda_n < 9)
	{
        //Pide al jugador que ingrese por consola el pokemon y ataque para la siguiente ronda
        jugada_t juagada1 = elige_jugada_j1(menu,juego,elecciones_j1->eleccionJugador1,elecciones_j1->eleccionJugador2,elecciones_j1->eleccionJugador3);

	
		//Pide al adversario que informe el pokemon y ataque para la siguiente ronda
		jugada_t jugada_adversario = adversario_proxima_jugada(rival);


        
        printf("\nEl adversario eligio %s y su ataque %s\n",jugada_adversario.pokemon,jugada_adversario.ataque);
        //jugador_pedir_nombre_y_ataque( juego,JUGADOR2 );

		//jugar la ronda y después comprobar que esté todo ok, si no, volver a pedir la jugada del jugador

        printf("Estoy enviando a juego_jugar_turno \nesto essto deberia ser un pokemon %s \nesto un ataque %s\n",juagada1.pokemon,juagada1.ataque);
		resultado_ronda = juego_jugar_turno(juego, juagada1, jugada_adversario);


        if(resultado_ronda.jugador1 == ATAQUE_ERROR && resultado_ronda.jugador2 == ATAQUE_ERROR)
            puts("indique ataques validos");
        
		//Si se pudo jugar el turno, le informo al adversario la jugada realizada por el jugador
		//adversario_informar_jugada(adversario, jugada_jugador);

		 printf("\nRonda %zu:P1 %d P2 %d \n",ronda_n,juego_obtener_puntaje(juego,JUGADOR1),juego_obtener_puntaje(juego,JUGADOR2));
         ronda_n++;
	}
   
    if( juego_obtener_puntaje(juego,JUGADOR1) < juego_obtener_puntaje(juego,JUGADOR2) )
    {
         pierde();
    }else gana();



    printf("\n\n\tResultado Partida:\nJugador 1 %d\nAdversario %d\n", juego_obtener_puntaje(juego,JUGADOR1), juego_obtener_puntaje(juego,JUGADOR2));

    return TODO_OK;
}


jugada_t elige_jugada_j1(menu_t *menu,juego_t *juego,char*p1,char*p2,char*p3)
{
    jugada_t jugada_actual = {"",""};
    char buffer[MAX_LINEA];
    lista_t *pkm_disponibles = juego_listar_pokemon(juego);
        
    printf("\nTurno de %s , elegi tu pokemon a usar!\n",dar_nombre_usuario(menu));

    printf("\n[0]: %s  [1]: %s [2]: %s\n\n",p1,p2,p3 );
   
    fgets(buffer,MAX_LINEA,stdin);
    int pkm_eleccion = atoi(buffer);

    while(pkm_eleccion > 2 || pkm_eleccion < 0)
    {
      
        puts("ingrese pokemon valido");     
        fgets(buffer,MAX_LINEA,stdin);
        pkm_eleccion = atoi(buffer);
    }

    
       
    switch (pkm_eleccion)
    {
        case 0:
            strcpy(jugada_actual.pokemon,p1);
            break;
        case 1:
            strcpy(jugada_actual.pokemon,p2);
            break;

        case 2:
            strcpy(jugada_actual.pokemon,p3);
            break;  
        
        default:
            break;
    }

    pokemon_t *pkm_elegido = lista_buscar_elemento(pkm_disponibles,comparar_nombres_en_juego,jugada_actual.pokemon);
    
  
    con_cada_ataque(pkm_elegido,mostrar_ataques,NULL);
    printf("\nElegi que ataque usara!\n");

    fgets(buffer,MAX_LINEA,stdin);
    buffer[strlen(buffer)-1] = 0;
    const struct ataque * ataque_elegido = pokemon_buscar_ataque(pkm_elegido,(const char*)buffer);
       
    while(ataque_elegido == NULL)
    {
        puts("ese sabes que no lo tengo che,pedime otro ");
        fgets(buffer,MAX_LINEA,stdin);
        buffer[strlen(buffer)-1] = 0;
        ataque_elegido = pokemon_buscar_ataque(pkm_elegido,buffer);
    }

    
    strcpy(jugada_actual.ataque,ataque_elegido->nombre);

    puts(LIMPIAR_PANTALLA);

    return jugada_actual;
    
    
}


 void jugador_seleccionar_pokemon( elecciones_t * elecciones)
 {
    
	lista_t *lista_pkm = juego_listar_pokemon(elecciones->juego);

	puts("\nSelecciona tres Pokemons!");

	int pkm1_p = -1,pkm2_p = -1 , pkm3_p = -1;

	int tope = (int )lista_tamanio(lista_pkm);

    char buffer[MAX_LINEA];
	
		puts("Selecciona el primero!");
		
        fgets(buffer,MAX_LINEA,stdin);

        pkm1_p = atoi(buffer);
       
		while(pkm1_p < 0)
		{
		
			 vuelve_a_pedir(&pkm1_p,buffer);
				
		}

		puts("Selecciona el segundo!");
		fgets(buffer,MAX_LINEA,stdin);
        pkm2_p = atoi(buffer);
		
				
		while(pkm2_p < 0 || pkm2_p == pkm1_p)
		{
			 vuelve_a_pedir(&pkm2_p,buffer);				
		}


		puts("Selecciona el tercero!");
		fgets(buffer,MAX_LINEA,stdin);
        pkm3_p = atoi(buffer);
		
				
		while(pkm3_p < 0 || pkm3_p == pkm1_p ||  pkm3_p == pkm2_p )
		{
			
            vuelve_a_pedir(&pkm3_p,buffer);
			
		}
       

		if(pkm1_p > tope || pkm2_p > tope || pkm1_p > tope)
		{
			puts("Ingrese valores validos!");
			jugador_seleccionar_pokemon( elecciones);
			return;
		}

		

	
		elecciones->eleccionJugador1 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm1_p));

		dibujar_pkm(elecciones->eleccionJugador1);
        delay(TIEMPO_DELAY2);

		elecciones->eleccionJugador2 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm2_p));

		dibujar_pkm(elecciones->eleccionJugador2);
        delay(TIEMPO_DELAY2);

		elecciones->eleccionJugador3 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm3_p));

			
 }




//SIMPLES

void vuelve_a_pedir(int *pkm1_p , char * buffer)
{
    puts("Selecciona una posicion valida!");
	fgets(buffer,MAX_LINEA,stdin);
    *pkm1_p = atoi(buffer);
}


void delay(int d)
{
      for(int i = 0; i < d ; i++)
    {
       
    }
}

bool salir_juego(void *menu ) 
{
    return false;
}


bool imprimir_nombre_pkm(void* pokemon ,void* posicion)
{

	pokemon_t * pkm = pokemon;

	printf("\n [%d]: %s ",*(int*)posicion , pokemon_nombre(pkm));

	(*(int *)posicion)++;

	return true;

}

void mostrar_ataques(const struct ataque *atk, void *n)
{
   
    printf("\n\tAtaque: %s ( Poder: %u |Tipo: %s )\n ",atk->nombre,atk->poder,tipos[atk->tipo]);
    
}

bool imprimir_info_pkm(void* pokemon ,void* posicion)
{

	pokemon_t * pkm = pokemon;

	printf("\n [%d]: %s     tipo: %s\n",*(int*)posicion , pokemon_nombre(pkm),tipos[pokemon_tipo(pkm)]);

    con_cada_ataque(pkm,mostrar_ataques,NULL);
    
    printf("\n");

	(*(int *)posicion)++;

	return true;

}

int comparar_nombres_en_juego(void* pkm_actual ,void * objetivo )
{
	return strcmp(pokemon_nombre(pkm_actual),objetivo);
}


 

void destruir_elecciones(elecciones_t *elecciones)
{

    free(elecciones);

}