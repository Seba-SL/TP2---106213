#ifndef GRAFICAS_H_
#define GRAFICAS_H_

#include <stdio.h>
#include <string.h>

#define MSJ_PEDIR_ARCHIVO "Ingrese el archivo donde se encuentran sus pokemones"
#define LIMPIAR_PANTALLA "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nn\n\n\n\n\n\n\n\n"
#define ESPACIO_MEDIO "\n\n\n\n\n\n\n\n\n\n\n\n"

//Mensajes  y dibujos
void bienvenida();
void mensaje_cargando();
void mensaje_cargado_con_exito();
void carga_invalida();
void dibujar_pkm(char * pkm_nombre);



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

#endif // GRAFICAS_H_