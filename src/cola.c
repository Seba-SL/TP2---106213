#include "cola.h"
#include "lista.h"

/*    COLA               equivalente en lista
		|A| desencolar  	posicion 0
		|B|
		|C|
		|D|
		|E| encolar   		ultimo elemento 
		 |
		NULL
*/

cola_t *cola_crear()
{
	return (cola_t *)lista_crear();
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	return (cola_t *)lista_insertar((lista_t *)cola, elemento);
}

void *cola_desencolar(cola_t *cola)
{
	return lista_quitar_de_posicion((lista_t *)cola, 0);
}

void *cola_frente(cola_t *cola)
{
	return lista_elemento_en_posicion((lista_t *)cola, 0);
}

size_t cola_tamanio(cola_t *cola)
{
	return lista_tamanio((lista_t *)cola);
}

bool cola_vacia(cola_t *cola)
{
	return lista_vacia((lista_t *)cola);
}

void cola_destruir(cola_t *cola)
{
	lista_destruir((lista_t *)cola);
}