#ifndef GRAFICAS_H_
#define GRAFICAS_H_

#include <stdio.h>
#include <string.h>

#define MSJ_PEDIR_ARCHIVO "Ingrese el archivo donde se encuentran sus pokemones\n"
#define MSJ_NO_HAY_POKEMONES_CARGADOS "No hay Pokemones cargados\n"
#define MENSAJE_FIN_PARTIDA "Fin de la partida!"
#define MENSAJE_ERROR "Error en ejecucion"
#define LIMPIAR_PANTALLA "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
#define ESPACIO_MEDIO "\n\n\n\n\n\n\n\n\n\n\n\n"

char* tipos[] = {" NORMAL","FUEGO","AGUA", "PLANTA", "ELECTRICO", "ROCA"};


//Mensajes  y dibujos
void bienvenida();
void reglas_del_juego();
void mensaje_cargando();
void mensaje_cargado_con_exito();
void carga_invalida();
void dibujar_pkm(char * pkm_nombre);
void batallan(size_t n);
void pierde();
void gana();


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

 void mensaje_cargado_con_exito()
 {
    puts(LIMPIAR_PANTALLA);
   
    printf("  _____           _              _                        _ _     _       _ \n");
    printf(" / ____|         | |            | |                      | (_)   | |     | |\n");
    printf("| |     __ _ _ __| |_ _   _  ___| |__   ___   __   ____ _| |_  __| | ___ | |\n");
    printf("| |    / _` | '__| __| | | |/ __| '_ \\ / _ \\  \\ \\ / / _` | | |/ _` |/ _ \\| |\n");
    printf("| |___| (_| | |  | |_| |_| | (__| | | | (_) |  \\ V / (_| | | | (_| | (_) |_|\n");
    printf(" \\_____\\__,_|_|   \\__|\\__,_|\\___|_| |_|\\___/    \\_/ \\__,_|_|_|\\__,_|\\___/(_)\n\n");
   
 }

 void carga_invalida()
 {
    puts(LIMPIAR_PANTALLA);
   
    printf("  _____           _              _             _                 _ _     _       _ \n");
    printf(" / ____|         | |            | |           (_)               | (_)   | |     | |\n");
    printf("| |     __ _ _ __| |_ _   _  ___| |__   ___    _ _ ____   ____ _| |_  __| | ___ | |\n");
    printf("| |    / _` | '__| __| | | |/ __| '_ \\ / _ \\  | | '_ \\ \\ / / _` | | |/ _` |/ _ \\| |\n");
    printf("| |___| (_| | |  | |_| |_| | (__| | | | (_) | | | | | \\ V / (_| | | | (_| | (_) |_|\n");
    printf(" \\_____\\__,_|_|   \\__|\\__,_|\\___|_| |_|\\___/  |_|_| |_|\\_/ \\__,_|_|_|\\__,_|\\___/(_)\n\n");
 }

void pierde()
{
  printf("\n _   _                                    _                     \n");
  printf("| \\ | | ___    ___  ___   _ __  _   _  __| | ___    _ __   __ _ \n");
  printf("|  \\| |/ _ \\  / __|/ _ \\ | '_ \\| | | |/ _` |/ _ \\  | '_ \\ / _` |\n");
  printf("| |\\  | (_) | \\__ \\  __/ | |_) | |_| | (_| | (_) | | |_) | (_| |\n");
  printf("|_| \\_|\\___/  |___/\\___| | .__/ \\__,_|\\__,_|\\___/  | .__/ \\__,_|\n");
  printf("                         |_|                       |_|          \n\n");

}

void gana()
{
printf("\n  ____                       _       _ \n");
  printf(" / ___| __ _ _ __   __ _ ___| |_ ___| |\n");
  printf("| |  _ / _` | '_ \\ / _` / __| __/ _ \\ |\n");
  printf("| |_| | (_| | | | | (_| \\__ \\ ||  __/_|\n");
  printf(" \\____|\\__,_|_| |_|\\__,_|___/\\__\\___(_)\n\n");

}


void batalla1()
{
  printf("              .\n");
  printf("              .\n");
  printf("              |					\n");
  printf("     .               /				\n");
  printf("      \\       I     				\n");
  printf("                  /\n");
  printf("        \\  ,g88R_\n");
  printf("          d888(`  ).                   _\n");
  printf(" -  --==  888(     ).=--           .+(`  )`.\n");
  printf(")         Y8P(       '`.          :(   .    )\n");
  printf("        .+(`(      .   )     .--  `.  (    ) )\n");
  printf("       ((    (..__.:'-'   .=(   )   ` _`  ) )\n");
  printf("`.     `(       ) )       (   .  )     (   )  ._\n");
  printf("  )      ` __.:'   )     (   (   ))     `-'.:(`  )\n");
  printf(")  )  ( )       --'       `- __.'         :(      ))\n");
  printf(".-'  (_.'          .')                    `(    )  )\n");
  printf("                  (_  )                     ` __.:'\n");
  printf("\n--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._.-a:f--.\n\n");

}

void batalla2()
{
   printf("   ((  \"####@@!!$$    ))\n");
  printf("       `#####@@!$$`  ))\n");
  printf("    ((  '####@!!$:\n");
  printf("   ((  ,####@!!$:   ))\n");
  printf("       .###@!!$:\n");
  printf("       `##@@!$:\n");
  printf("        `#@!!$\n");
  printf("  !@#    `#@!$:       @#$\n");
  printf("   #$     `#@!$:       !@!.\n");
  printf("            '@!$:\n");
  printf("        '`\\   \"!$: /`'\n");
  printf("           '\\  '!: /'\n");
  printf("             \"\\ : /\"\n");
  printf("  -.\"-/\\\\-.\"//.-\"/:`\\.\"-...S\".\"-=_\\\n");
  printf("\" -.\"-.\\\"-.\"//.-\".`-.\"_\\-.\".-\".-//\n");
  printf(".-'  (_.'          .')                    `(    )  )\n");
  printf("                  (_  )                     ` __.:'\n");
  printf("\n--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._.-a:f--.\n\n");

}

void batallan(size_t n)
{

  switch(n)
  {
    case 0:
       batalla1();
       break;
   
    case 1:
     batalla2();
      break;

    case 3:
     batalla2();
      break;

   
    default:
      batalla1();
      break;
  }
 
}

void reglas_del_juego()
{
  puts("Reglas del juego\n");

  printf("Al principio del juego se le presenta a los jugadores un listado de los pokemon disponibles.\n");
  printf("el jugador selecciona 3 pokemon de los disponibles.\n");
  printf("Los 3 pokemon deben ser diferentes, no se puede repetir pokemon\n");
  printf("Ambos jugadores realizan su elección sin conocer la elección del otro jugador\n");
  printf("Una vez seleccionados los pokemon por ambos usuario, se informan las elecciones.\n");
  printf("Los primeros 2 pokemon seleccionados por el usuario son pokemon propios mientras que el tercer pokemon debe ser asignado como tercer pokemon del otro jugador\n");
  printf("Por ejemplo, el jugador 1 selecciona A, B y C; el jugador 2 selecciona D, E y F. El equipo final del jugador 1 está formado por A, B y F, mientras que el equipo de jugador 2 queda D, E y C.\n");
  printf("Si bien cada jugador debe seleccionar 3 pokemon diferentes, es posible que en el equipo final queden pokemon duplicados (ya que el tercer pokemon es elegido secretamente por el otro jugador)\n");
  printf("El juego se desarrolla por rondas. Como cada jugador tiene 3 pokemon y cada pokemon tiene 3 ataques, la cantidad de rondas del juego siempre es 9.\n");
  printf("En cada ronda cada jugador decide un pokemon y un ataque de ese pokemon.\n");
  printf("Los pokemon seleccionados se enfrentan.\n");
  printf("Se le asigna a cada jugador un puntaje que se calcula en base al poder del ataque y el tipo del ataque y del pokemon adversario.\n");
  printf("Una vez utilizado un ataque de un pokemon, este no puede ser utilizado nunca mas durante el juego.\n");
  printf("Al finalizar el juego, gana el jugador con mas puntos.\n\n");



    char buffer;

    puts("");

    scanf("%c",&buffer);
    fflush(stdin);

   

}

#endif // GRAFICAS_H_