#include "src/pokemon.h"
#include "src/ataque.h"
#include "src/juego.h"
#include "src/lista.h"
#include "src/adversario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/menu.h"

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

/*************************************************** Funciones auxiliares  ********************************************************************/

void bienvenida();
void mensaje_cargando();
bool pedir_archivo(void * archivo);
void mostrar_pokemon_disponibles(juego_t * juego);
void jugador_seleccionar_pokemon(juego_t *juego, char * eleccionJugador1,char * eleccionJugador2,char * eleccionJugador3);
jugada_t jugador_pedir_nombre_y_ataque();
void dibujar_pkm(char * pkm_nombre);

//jugada_t jugador_pedir_nombre_y_ataque(juego_t* juego ,JUGADOR jugador);

/*********************************************************************************************************************************************/


int main(int argc,  char *argv[])
{
    menu_t *nueva_partida = crear_menu();
	juego_t *juego = juego_crear();

    char *archivo = NULL;
    
	bienvenida();

    menu_agregar_comando(nueva_partida,"c","Ingresar archivo",pedir_archivo,(void *)archivo);
	//Pide al usuario un nombre de archivo de pokemones


	if(juego_cargar_pokemon(juego, archivo) != TODO_OK)
        return MENU_ERROR;

	
	//Crea un adversario que será utilizado como jugador 2
	//adversario_t *adversario =
	//	adversario_crear(juego_listar_pokemon(juego));

	//Mostrar el listado de pokemones por consola para que el usuario sepa las opciones que tiene
	mostrar_pokemon_disponibles(juego);

    

	free(archivo);
    menu_destruir(nueva_partida);
	juego_destruir(juego);
}


bool pedir_archivo(void* archivo)
{
	char *nombre_archivo = malloc(sizeof(char)*MAX_NOMBRE_ARCHIVO);

    if(nombre_archivo == NULL)return false;

	puts(MSJ_PEDIR_ARCHIVO);

	
	fscanf(stdin,"%s",nombre_archivo);

	mensaje_cargando();

    
	archivo =  nombre_archivo;

    return true;
}


bool imprimir_nombre_pkm(void* pokemon ,void* posicion)
{

	pokemon_t * pkm = pokemon;

	printf("\n %d %s ",*(int*)posicion , pokemon_nombre(pkm));

	(*(int *)posicion )++;

	return true;

}

 void mostrar_pokemon_disponibles(juego_t * juego)
 {
	if(juego == NULL)return ;


	lista_t *lista_pkm = juego_listar_pokemon(juego);

	size_t *posiciones = calloc(1,sizeof(size_t));


	lista_con_cada_elemento(lista_pkm,imprimir_nombre_pkm,posiciones);

	printf("\n\n\n \t\t Cantidad de pokemons disponibles : %zu\n",lista_tamanio(lista_pkm));

	
	free(posiciones);
 }

 void jugador_seleccionar_pokemon(juego_t *juego, char * eleccionJugador1,char * eleccionJugador2,char * eleccionJugador3)
 {
	lista_t *lista_pkm = juego_listar_pokemon(juego);

	puts("Selecciona tres Pokemons!");

	int pkm1_p = -1,pkm2_p = -1 , pkm3_p = -1;

	int tope = (int )lista_tamanio(lista_pkm);

	
		puts("Selecciona el primero!");
		fscanf(stdin,"%d",	&pkm1_p);
	
		

			while(pkm1_p < 0)
			{
			
				puts("Selecciona una posicion valida!");
				fscanf(stdin,"%d",	&pkm1_p);
				
			}

	

		puts("Selecciona el segundo!");
		fscanf(stdin,"%d",	&pkm2_p);
		
				
			while(pkm2_p < 0 || pkm2_p == pkm1_p)
			{
				puts("Selecciona una posicion valida!");
				fscanf(stdin,"%d",	&pkm2_p);
				
				
			}


		puts("Selecciona el tercero!");
		fscanf(stdin,"%d",	&pkm3_p);
		
				
		while(pkm3_p < 0 || pkm3_p == pkm1_p ||  pkm3_p == pkm2_p )
		{
			puts("Selecciona una posicion valida!");
			fscanf(stdin,"%d",	&pkm3_p);
			
			
		}

		if(pkm1_p > tope || pkm2_p > tope || pkm1_p > tope)
		{
			puts("Ingrese valores validos!");
			jugador_seleccionar_pokemon(juego,eleccionJugador1,eleccionJugador2,eleccionJugador3);
			return;
		}

		

	
		eleccionJugador1 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm1_p));

		dibujar_pkm(eleccionJugador1);

		eleccionJugador2 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm2_p));

		dibujar_pkm(eleccionJugador2);

		eleccionJugador3 = (char*)pokemon_nombre(lista_elemento_en_posicion(lista_pkm,(size_t)pkm3_p));

		dibujar_pkm(eleccionJugador3);

			
 }


 void bienvenida()
{

	printf("                                           ,'\\ \n");
	printf("             _.----.        ____         ,'  _\\   ___    ___     ____ \n");
	printf("         _,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`. \n");
	printf("         \\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  | \n");
	printf("          \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  | \n");
	printf("           \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  | \n");
	printf("            \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     | \n");
	printf("             \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    | \n");
	printf("              \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   | \n");
	printf("               \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   | \n");
	printf("                \\_.-'       |__|    `-._ |              '-.|     '-.| |   | \n");
	printf("                                        `'                            '-._|\n\n");


}

void dibujar_pikachu();
void dibujar_charmander();
void dibujar_larvitar();
void dibujar_cacnea();
void dibujar_Togepi();
void dibujar_Floatzel();

void dibujar_pkm(char * pkm_nombre)
{
	if( strcmp("Pikachu",pkm_nombre) == 0 )
		dibujar_pikachu();
	
	if( strcmp("Charmander",pkm_nombre) == 0 )
		dibujar_charmander();
	
	if( strcmp("Larvitar",pkm_nombre) == 0 )
		dibujar_larvitar();

	if( strcmp("Cacnea",pkm_nombre) == 0 )
		dibujar_cacnea();
	
	if( strcmp("Togepi",pkm_nombre) == 0 )
		dibujar_Togepi();

	if( strcmp("Floatzel",pkm_nombre) == 0 )
		dibujar_Floatzel();
		
}

void dibujar_Floatzel()
{
	printf("\n");
    printf("                                                 ,--''''-.\n");
    printf("                                               ..    `'  `\n");
    printf("                                                '    .'...'\n");
    printf("                                            '  ,'::     |\n");
    printf("                                               ,..-Y-'  /--\n");
    printf("                                    .              |' _.'\n");
    printf("                                  .' .______ ,-'\"|  ,'\n");
    printf("                           /,  ,. '-'     .-' .\" | '\n");
    printf("                          /  \"'  ' -=L;'\\'    `-.'.\n");
    printf("             ,,          /__       ],L_/'        .'            |\\\n");
    printf("       |`.  '\\  _,          |         .        ,'          =-. `|\n");
    printf("       `. ,' |.`            '`-v      `'-.    |             | -,..\n");
    printf("        _:  \" `\\,.     ___    _'|  ,-,_-  `-..'          .]---> _`'\n");
    printf("      . ___.   ' /'--.  -.=[----`, |   '-  ,'                | </\n");
    printf("             ]..b--`. -'- , ----`` |'--v -'            __-- ' ,,\n");
    printf("            .'|    <\\]``,[ -    '\\\\._  |'  '''`- _  _,|    `''|\n");
    printf("   \\\" ''L     |   X`.  ` /--,    |  -`.:_ `.    ' TX_,.:'..  ,|\n");
    printf("   `   |       \"` =. ----  _|    |      ` _ `\\ |=:| /   '-\\ --'\n");
    printf("   |.   `.          '''-..L    _,'      .' `,.``-() Y.-[ .'\n");
    printf("   '    .            _. _.. -]-,..-,'    v.   \\|  ` '`'\n");
    printf("`.'       `.        ' ---.'- /-[  .',_   -.   ,)L\n");
    printf("  |       .'      __,...-`=..__       '   '     '.\n");
    printf("   ,\"', .'      -`... _-'      `.     ` ,'      | `.\n");
    printf("       .`            .'          .     '        |   \\\n");
    printf("         '           |           |             .'    .\n");
    printf("        \\ `.         '           '            ,'     |\n");
    printf("         \\  `.        `         /           .'     _.'\n");
    printf("          '.  `-.     /`__    ,'.._______,-'--...-` `.\n");
    printf("            `.   `--..'J  \"'.'         ,'       `._\\` ``-...\n");
    printf("              `.   .'   `'|'        _,'          |    _    \"-.\n");
    printf("                `.'|  ..  |     _,-'             `-._| '.---.'\n");
    printf("                / _,_/  |-`---\"'                     `-..|\n");
    printf("               `-\"   | .'\n");
    printf("                     -'\n");

}

void dibujar_Togepi()
{
	printf("                    __.._\n");
    printf("                ,--'     \"`-._    _,.-,--------.\n");
    printf("    ________ ,-'              `-\"'   /     _.-'|\n");
    printf(" ,-'  '     :                       .    ,'    '\n");
    printf("|    '     j      _.._              |  ,'     j\n");
    printf("L   /      |    .'    `.            |.'      /\n");
    printf(" \\ j       |    `.,'   |           ,'       /    _\n");
    printf("  .|      ,'\\         /           '.___    / _.-\" |\n");
    printf("   `    .'   `-.....-'                 `- +-'    /\n");
    printf("    `. ,'                                `.     <__\n");
    printf("      `.             .\\ \\                 |   ___ ,'\n");
    printf("      |     | #      || |                  ,\"\"   \"`.\n");
    printf("      |     | #      `'_/                   .       `.\n");
    printf("     ,'     `.         ,-\"\".                L         `.\n");
    printf("    /     (__)       _  \"\"\"                  :\"\"-.      .\n");
    printf("   /             \\\"'u|         |/            |    \\     |\n");
    printf("  .               \\  |         |           | |     |    |\n");
    printf("  |     _          `-'        j           /  |     '    |\n");
    printf("  L      `.                   |          /   |   ,'     '\n");
    printf("   \\       `.                ,'         /    |_,'      /\n");
    printf("    `.   ,.<'                `+--.    ,'     /       ,'\n");
    printf("      `./`._'                 '_.`._,'      j      _,\n");
    printf("        /\"'                      \"          |   _,'\n");
    printf("       /   `._              .              '..-'\n");
    printf("      j       `-._           `            /\n");
    printf("      |        _,'`\"--........+.         /\n");
    printf("      ,\"-.._,-'                 `.  .-._/\n");
    printf("      '---'                       `+__,' \n");
		puts("                   ");
}

void dibujar_cacnea()
{
	   printf("                                            _,.---.\n");
        printf("                                        _,-'       `.\n");
        printf("                                     _,'  ,          \\\n");
        printf("                                   ,'  _,'   .        `.\n");
        printf("                                  /  ,'     ,'          `.\n");
        printf("         __                       .,'    _,'              `.\n");
        printf("    _,..'  `-....___              :    ,'     '             \\\n");
        printf("  ,'   /            :             /`.,'      /               `\n");
        printf(" /    /  ._         |         __..|  `.    .'       ,         `.\n");
        printf(" |   |   ,'\"--._    |      ,-'    `-._`.,-'       ,:            .\n");
        printf(".'\\   \\     _,'.    `'___.'           `\"`.     _,' /            |\n");
        printf("|  \\   \\---'       ,\"'  .-\"\"'\"----.       `.  '  ,'             |\n");
        printf(" `. `-.'          /    /                    `-..^._             '\n");
        printf("   |._|    _.    /    /                            `._           .\n");
        printf("   `...:--'--+..'   ,'                              /            |\n");
        printf("       '._  `|   ,-'       _..._                   j     \\       |\n");
        printf("         |` |   /       ,-'     `-.__              |      L      |\n");
        printf("         |  |  /      ,'                           |      |      |\n");
        printf("         |_,'        /         _,-                  .     |      |\n");
        printf("        ,'  ,   |  ,'        ,|            ,..._     \\    |      '\n");
        printf("       ,     \\ j  '       _.\" |           /     `-.__'    '    ,'\n");
        printf("        +._   '|       ,'|    |          /        ,'    .'    /\n");
        printf("        |  `._  `-' .:|  |    '.       -'        '           j\n");
        printf("        '    |`    ' |'  |     |                             |\n");
        printf("         `.  |       |--'     _|        .                    |\n");
        printf("           \\ |       '----'\"\"\"           \\      __,....-+----'\n");
        printf("           | '                            `---\"\"      .'\n");
        printf("           `. `.                                     ,\n");
        printf("             `\" \\_...-\"\"\"'--..         _+          ,'\n");
        printf("                  '            -.'  `-'  `.  .\"-..'\n");
        printf("                   `-..._            _____,.'\n");
        printf("                         `--.....,-\"' \n");

}

void dibujar_larvitar()
{
		printf("                        _.-\".\n");
        printf("                ..-\"\"`.'    '..__,\n");
        printf("                `-. .'     /  ,.`.\n");
        printf("                  ,'      '`. .'  `.\n");
        printf("                 /       .-'        `....\n");
        printf("              ..'.      .\\             .|\n");
        printf("              .`./      | `.            '.\n");
        printf("              |         |  .\\       /|    \\\n");
        printf("             .'         |)  `\\       '   (_`\n");
        printf("            ,|          |    `.            |\n");
        printf("             |          |  _,.-.           |\n");
        printf("             |          |,'     \\          |\n");
        printf("             |          |        \\         |\n");
        printf("             |      \\,  '.        \\        |\n");
        printf("             '           |         `._     |\n");
        printf("              \\          |            `-..,+___\n");
        printf("               \\         |          /       |  `.\n");
        printf("                \\        '         / ,      '    \\\n");
        printf("                 \\      ,  _      /.'      /|    `-.\n");
        printf("                  `.   .    `-.    __     ' |     .'\n");
        printf("                    `..'   -\"'  .-\"| |  ,'  |    |  '-..\n");
        printf("                    /`.        (_`.`\" \\'    |_.-'-\"'-. .`.\n");
        printf("                   .   \\       `._. `\".|    |         `|  .\n");
        printf("                   |    \\`----\"\"`.`. / |,.-\"'`-.        `. '\n");
        printf("                   |     \\        `-+-\"   /     \\         \\ \\\n");
        printf("                  ,'     _\\ ___..-'      .       \\         \\ \\\n");
        printf("                  j\"._,-\".'`.       _.-\"'|     _  \\         . \\\n");
        printf("                 / ,'   /    `.._,-'    _| _.-'   `.        |  \\\n");
        printf("               .' '    ._      `-..__.-\"_|'        |        `..\"`.\n");
        printf("   _..      _,'\"-/     | `-._   .'   `\"' `.      __|        /|  | \\_\n");
        printf(" .'   `--\"\"' _.-'    .-|     `.'          '._  .`  `.      / |  |.'|\n");
        printf(".  \\ .\"\\ _,-'        `.'..-.-'           /   `.-._   .     `.|./__.'\n");
        printf("|`.` | /\"               |.'             / _.'     `-.|\n");
        printf("`_|.'`'                                `-' \n");
        printf("\n");
}

void dibujar_pikachu()
{

    printf("                                             ,-.\n");
    printf("                                          _.|  '\n");
    printf("  Gracias por elegirme Chabon/a!          .'  | /\n");
    printf("                                      ,'    |'\n");
    printf("                                     /      /\n");
    printf("                       _..----\"\"---.'      /\n");
    printf(" _.....---------...,-\"\"                  ,'\n");
    printf(" `-._  \\                                /\n");
    printf("     `-.+_            __           ,--. .\n");
    printf("          `-.._     .:  ).        (`--\"| \\\n");
    printf("               7    | `\" |         `...'  \\\n");
    printf("               |     `--'     '+\"        ,\". ,\"\"-\n");
    printf("               |   _...        .____     | |/    '\n");
    printf("          _.   |  .    `.  '--\"   /      `./     j\n");
    printf("         \\' `-.|  '     |   `.   /        /     /\n");
    printf("         '     `-. `---\"      `-\"        /     /\n");
    printf("          \\       `.                  _,'     /\n");
    printf("           \\        `                        .\n");
    printf("            \\                                j\n");
    printf("             \\                              /\n");
    printf("              `.                           .\n");
    printf("                +                          \\\n");
    printf("                |                           L\n");
    printf("                |                           |\n");
    printf("                |  _ /,                     |\n");
    printf("                | | L)'..                   |\n");
    printf("                | .    | `                  |\n");
    printf("                '  \\'   L                   '\n");
    printf("                 \\  \\   |                  j\n");
    printf("                  `. `__'                 /\n");
    printf("                _,.--.---........__      /\n");
    printf("               ---.,'---`         |   -j\"\n");
    printf("                .-'  '....__      L    |\n");
    printf("              \"\"--..    _,-'       \\ l||\n");
    printf("                  ,-'  .....------. `||'\n");
    printf("               _,'                /\n");
    printf("             ,'                  /\n");
    printf("            '---------+-        /\n");
    printf("                     /         /\n");
    printf("                   .'         /\n");
    printf("                 .'          /\n");
    printf("               ,'           /\n");
    printf("             _'....----\"\"\"\"\" \n");

}

void dibujar_charmander()
{


printf("	                     ,-'`\\											\n");
printf("                  _,\"'    j 											\n");
printf("           __....+       /               . 								\n");
printf("       ,-'\"             /               ; `-._.'. 						\n");
printf("      /                (              ,'       .'						\n");
printf("     |            _.    \\             \\   ---._ `-.					\n");
printf("     ,|    ,   _.'  Y    \\             `- ,'   \\   `.`.				\n");
printf("     l'    \\ ,'._,\\ `.    .              /       ,--. l				\n");
printf("  .,-        `._  |  |    |              \\       _   l .				\n");
printf(" /              `*--'    /              .'       ``. |  )				\n");
printf(".\\    ,                 |                .        \\ `. '				\n");
printf("`.                .     |                '._  __   ;. \'				\n");
printf("  `-..--------...'       \\                  `'  `-*'.  \\				\n");
printf("      `......___          `._                        |  \\				\n");
printf("               /`            `..                     |   .				\n");
printf("              /|                `-.                  |    L				\n");
printf("             / |               \\   `._               .    |			\n");
printf("           ,'  |,-\"-.   .       .     `.            /     |			\n");
printf("         ,'    |     '   \\      |       `.         /      |			\n");
printf("       ,'     /|       \\  .     |         .       /       |			\n");
printf("     ,'      / |        \\  .    +          \\    ,'       .'			\n");
printf("    .       .  |         \\ |     \\         \\_,'        / j			\n");
printf("    |       |  L          `|      .          `        ,' '				\n");
printf("    |    _. |   \\          /      |           .     .' ,'				\n");
printf("    |   /  `|    \\        .       |  /        |   ,' .'				\n");
printf("    |   ,-..\\     -.     ,        | /         |,.' ,'					\n");
printf("    `. |___,`    /  `.   /`.       '          |  .'						\n");
printf("      '-`-'     j     ` /.*7-..../|          ,`-'						\n");
printf("                |        .'  / _/_|          .							\n");
printf("                `,       `*'/*'    \\          `.						\n");
printf("                  `,       '.       `.         |						\n");
printf("             __,.-'         `.        \'       |						\n");
printf("            /_,-'\\          ,'        |        _.						\n");
printf("             |___.---.   ,-'        .-':,-\"`\\,' .						\n");
printf("                  L,.--\"'           '-' |  ,' `-.\\					\n");
printf("                                        `.' 							\n");
printf(" 				¿Que hay que prender fuego?								\n");

}


void mensaje_cargando()
{
  printf("\n");
  printf("   ____ \n");  
  printf("  / ___|__ _ _ __ __ _  __ _ _ __    __| | ___     ___ __ _ _ __| |_ _   _  ___| |__   ___       \n");
  printf(" | |   / _` | '__/ _` |/ _` | '_ \\ / _` |/ _ \\   / __/ _` | '__| __| | | |/ __| '_ \\ / _ \\      \n");
  printf(" | |__| (_| | | | (_| | (_| | | | | (_| | (_) | | (_| (_| | |  | |_| |_| | (__| | | | (_) | _ _    \n");
  printf("  \\____\\__,_|_|  \\__, |\\__,_|_| |_|\\__,_|\\___/   \\___\\__,_|_|   \\__|\\__,_|\\___|_| |_|\\___(_|_|_)    \n");
  printf("                  |___/         \n");                                                                 
 printf("\n");

}