#include "pila.h"
#include "lista.h"

/*
	PILA
		|A| desapilar/apilar
		|B|
		|C|
		|D|
		|E|
		 |
		NULL
		 

	struct lista{
	nodo_t *inicio;
	nodo_t *ultimo;
	size_t cantidad;	
	};

*/

pila_t *pila_crear()
{
	return (pila_t *)
		lista_crear(); //uso el TDA lista_t para hacer el tipo pila_t
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	return (pila_t *)lista_insertar_en_posicion(
		(lista_t *)pila, elemento,
		0); //inserte de un lado , el mismo lado donde debe deapilar
}

void *pila_desapilar(pila_t *pila)
{
	return lista_quitar_de_posicion((lista_t *)pila, 0);
}

void *pila_tope(pila_t *pila)
{
	return lista_elemento_en_posicion((lista_t *)pila, 0);
}

size_t pila_tamanio(pila_t *pila)
{
	if (pila == NULL)
		return 0;

	return lista_tamanio((lista_t *)pila);
}

bool pila_vacia(pila_t *pila)
{
	if (lista_vacia((lista_t *)pila))
		return true;

	return false;
}

void pila_destruir(pila_t *pila)
{
	lista_destruir((lista_t *)pila);
}
