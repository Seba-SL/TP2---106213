<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP2

## Repositorio de Sebastian Nahuel Lazo - 106213 - slazo@fi.uba.ar

- Para compilar:

```bash
make main
```

- Para ejecutar:

```bash
./main
```

- Para ejecutar con valgrind:
```bash
make
```
---
##  Implementación de juego 

Este ultimo trabajo práctico consta de utilizar los TDA´s creados a lo largo de la cursada para la implementación de un juego que haga uso de estos para manejar datos del mismo.

Estructuras utilizadas para implementar la lógica del juego y del adversario:


![este drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/6fe1621c-7db1-4d48-a574-fb8351692626)



Se uso el TDA lista_t para guardar pokemons disponibles 

Se uso el TDA abb_t para guardar las jugadas disponibles

Se uso el TDA hash_t para guardar los comandos y sus funciones



![estructuras drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/8a3596ee-a383-4e7c-816b-8fdbfcb4ff6f)



El usuario interactua con el juego a traves de una interfaz de usuario implementada con el TDA menu_t:

Principales operaciones del TDA menu_t
![menu_t drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/518bb1f2-f4e9-43d3-9470-10919f54e562)

Flujo del menu
![flujoMenu drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/fdfc9b2b-9649-46bf-93d7-cda0cf93ac67)


Imagenes de la interfaz 

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/003c41c7-d623-438b-b1ff-8461041700a4)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/39b6df15-9346-49c4-84bf-731d6156714a)

Principales operaciones del TDA juego_t
![juego_t drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/473ffdd5-06bd-4369-ad21-f04832b46e4f)

Imagenes de la ejecucion del juego:

Carga de archivo valida y consulta de pokemon:

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/bbf08756-309e-4733-970c-4dfb761cc02b)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/c50ed4fa-2fee-4d48-8165-e318243c4093)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/03cd4011-cd88-4dc4-8055-2278c7f5580e)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/52744594-10d4-4e0b-9011-825e8d769c7f)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/aebb18de-06c2-478e-833a-55bbd5561dac)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/ce80760b-7cb8-40eb-8f41-b04f87984bde)


Análisis de la complejidad de funciones

juego_jugar_turno():
```c
resultado_jugada_t juego_jugar_turno(juego_t *juego, jugada_t jugada_jugador1,jugada_t jugada_jugador2)
{
	resultado_jugada_t resultado;
	resultado.jugador1 = ATAQUE_ERROR;
	resultado.jugador2 = ATAQUE_ERROR;

	if (!juego)
		return resultado;

	if (!jugada_disponible(juego->jugadores[JUGADOR1].jugadas_disponibles,jugada_jugador1))  //ejecuta abb_quitar 2 veces , una con el nombre del pokemon y otra con la del ataque O(N/2)
	{
		return resultado;
	}

	if (!jugada_disponible(juego->jugadores[JUGADOR2].jugadas_disponibles,jugada_jugador2))
	{
		return resultado;
	}

	//saca los pokemones en sus mochilas , si es q existen
	pokemon_t *pkm1 = lista_buscar_elemento(juego->jugadores[JUGADOR1].sus_pokemones, comparar_nombres,jugada_jugador1.pokemon);  //en peor de los casos en O(N)
	pokemon_t *pkm2 = lista_buscar_elemento(juego->jugadores[JUGADOR2].sus_pokemones, comparar_nombres,jugada_jugador2.pokemon);  //en peor de los casos en O(N)

	if (!pkm1 || !pkm2)
		return resultado;

	//los pokemons tienen esos ataques?
	const ataque_t *atk1 =
		pokemon_buscar_ataque(pkm1, jugada_jugador1.ataque);  //O(N)
	const ataque_t *atk2 =
		pokemon_buscar_ataque(pkm2, jugada_jugador2.ataque); //O(N)

	if (!atk1 || !atk2)
		return resultado;

	asignar_resultado(&resultado.jugador1, atk1, pkm2); //O(1)  Asignacion
	asignar_resultado(&resultado.jugador2, atk2, pkm1);  //O(1)  Asignacion

	asignar_puntaje(&juego->jugadores[JUGADOR1].puntaje, atk1,resultado.jugador1); //O(1)  Asignacion
	asignar_puntaje(&juego->jugadores[JUGADOR2].puntaje, atk2,resultado.jugador2); //O(1)  Asignacion

	juego->cantidad_movimientos--; //O(1)  Asignaciones

	return resultado;
}
```

Esta funcion analizada con notación big O es de complejidad O(N)

T(N): 4*O(N/2) + 4*O(N) + K*O(1)

Resulta en : T(N)-> O(N)

juego_seleccionar_pokemon():
Esta funcion hace uso de pokemon_buscar() dos veces , siendo esta de compledidad O(N) en notacion big O , como utiliza otras funciones de inserción , estas tendran una complejidad menor ,por lo tanto la complejidad final en el análisis es de complejidad O(N).

Adversario.c
```c
jugada_t adversario_proxima_jugada(adversario_t *adversario)
{
	//aca voy a obtener mi elemento de mi jugadas disponibles
	void *pareja_;

	//primero adquiero una jugada disponible:
	abb_recorrer(adversario->jugadas_disponibles, INORDEN, &pareja_, 1);//O(N)

	pareja_t *pareja = pareja_;
	//obtengo de esa jugada disponible el nombre del pokemon y su ataque
	const char *nombre_pokemon = pareja->ataque->nombre;
	const char *nombre_ataque = pokemon_nombre(pareja->pokemon);

	//copio en mi jugada el NOMBRE DEL POKEMON y el NOMBRE DEL ATAQUE
	jugada_t jugada;
	strcpy(jugada.ataque, nombre_pokemon);
	strcpy(jugada.pokemon, nombre_ataque);

	//quito de jugadas diponibles la jugada que acabo de devolver
	abb_quitar(adversario->jugadas_disponibles, pareja); // log(n)
	adversario->buffer = pareja;
	return jugada;
}
```
Complejidad O(N)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/dbe54a14-ce61-4f43-ad4e-0e821bf42016)

</div>

<iframe width="560" height="315" src="https://www.youtube.com/embed/jlvFh7KnUPQ?si=_jPmQeVeUHRGUESM" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
