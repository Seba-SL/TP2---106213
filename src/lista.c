#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>




typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *inicio;
	nodo_t *ultimo;
	size_t cantidad;
};

struct lista_iterador {
	nodo_t *actual;
};

/***********************    Funciónes Auxiliares   ********************/

void *eliminar_primero(lista_t *lista);
void *eliminar_segundo(lista_t *lista, size_t posicion);
nodo_t *asignar_nodo_posicion(lista_t *lista,size_t posicion);

/**********************************************************************************************************/

/***********************  Funciónes Crear   ***************************/

lista_t *lista_crear()
{
	// pido memoria para la lista ,calloc lo inicializa en NULL y 0
	return (lista_t *)calloc(
		1,
		sizeof(lista_t)); // crea una lista inicializada a NULL, si no se pudo asignar memoria retorna NULL
}

nodo_t *crear_nodo(void *elemento, nodo_t *siguiente)
{
	nodo_t *nodo = (nodo_t *)malloc(sizeof(nodo_t)); // asigna memoria
	if (nodo == NULL)
		return NULL;

	// inicializa
	nodo->elemento = elemento;
	nodo->siguiente = siguiente;

	return nodo;
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	// si la lista es invalida devuelve NULL
	if (lista == NULL)
		return NULL;

	// asigna memoria para el iterador y verifico
	lista_iterador_t *iterador =
		(lista_iterador_t *)malloc(sizeof(lista_iterador_t));
	if (iterador == NULL)
		return NULL;

	iterador->actual = lista->inicio;

	return iterador;
}

/**********************************************************************************************************/

/*****************************  Funciónes Destruir   *****************************************************/

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;

	nodo_t *actual = lista->inicio; 
	nodo_t *borrar; 

	while (actual) 
	{
		if (funcion) 
			funcion(actual->elemento);

		borrar = actual; 

		actual =
			actual->siguiente; 

		free(borrar);
	}

	free(lista); 
}

/**********************************************************************************************************/

/***********************  Funciónes Insertar   **********************/

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL)return NULL; 

	nodo_t *nodo = crear_nodo(elemento,NULL); 
	
	if (nodo == NULL)return NULL; 

	if (lista_vacia(lista)){
		lista->inicio = nodo;
		lista->ultimo = nodo;
		lista->cantidad++; 
		return lista; 
	}

	lista->ultimo->siguiente = nodo;
	lista->ultimo = nodo; 
	lista->cantidad++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL)
		return NULL; 

	if (posicion >=lista_tamanio(lista)) 
		return lista_insertar(lista, elemento); 

	
	nodo_t *actual = asignar_nodo_posicion(lista,posicion);

	lista->cantidad++;

	if (posicion == 0) 
	{
		nodo_t *nuevo_nodo = crear_nodo(elemento, actual);
		if (!nuevo_nodo)
			return NULL;
		lista->inicio = nuevo_nodo;
		return lista;
	}

	nodo_t *nuevo_nodo = crear_nodo(elemento,actual->siguiente); 

	if (!nuevo_nodo)
		return NULL;

	actual->siguiente =
		nuevo_nodo; 

	return lista;
}

nodo_t *asignar_ultimo_nodo(lista_t *lista,size_t posicion)
{
	if(lista == NULL)return NULL;

	nodo_t *actual = lista->inicio;

	size_t i = 1;
	
	
	while (actual && i < posicion) {
		actual = actual->siguiente;
		i++;
	}

	return actual;
	
}

/**********************************************************************************************************/

/***********************  Funciónes Consultas   **********************/

bool lista_vacia(lista_t *lista)
{
	if (lista == NULL)return true;
	
	if (NULL == lista->inicio) {
		return true;
	}

	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if (lista == NULL)
		return 0;

	return lista->cantidad;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (iterador == NULL)
		return false;

	return iterador->actual; 
}

/**********************************************************************************************************/

/***********************  Funciónes Quitar   **********************/

void *lista_quitar(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;
	// si no es vacia , el primer nodo no sera NULL

	if (lista_tamanio(lista) == 1) {
		nodo_t *borrar = lista->inicio;
		void *elemento = lista->inicio->elemento;
		free(borrar);

		lista->inicio = NULL;
		lista->ultimo = NULL;
		lista->cantidad--;

		return elemento;
	}

	
	nodo_t *anteultimo = asignar_nodo_posicion(lista,lista_tamanio(lista) - 1);
	void *elemento = lista_ultimo(lista); // guardo lo que tiene Z

	nodo_t *borrar_nodo = anteultimo->siguiente;
	// tengo anteultimo  = C
	anteultimo->siguiente = NULL; // C->NULL

	lista->ultimo = anteultimo; // asigno C como el nuevo ultimo

	free(borrar_nodo);

	lista->cantidad--;

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista)
		return NULL; // si la lista es null o vacia

	if (posicion == 0) {
		return eliminar_primero(
			lista); // quita el ultimo ,devuelve su elemento y reasigna el ultimo
	}

	if (posicion >=
	    lista_tamanio(
		    lista)) // si se pide una posicion mayor al tamaño o de igual tamaño
	{
		return lista_quitar(
			lista); // quita el ultimo ,devuelve su elemento y reasigna el ultimo
	}

	if (posicion == 1) {
		return eliminar_segundo(
			lista,
			posicion); // elimina la segunda posicion reasignando los campos inicio/ultimo de la lista al primero
	}

	nodo_t *anterior = lista->inicio; // apunto al primero antes de iterar
	size_t i = 1; // para asignar al primero
	// A->B->C->D->E->NULL
	while (anterior != NULL && i < posicion) {
		anterior = anterior->siguiente;
		i++;
	}
	// el siguiente no puede ser null , ya que posicion no coincide con el ultimo en este caso

	void *elemento =
		anterior->siguiente
			->elemento; // guardo el elemento del nodo a eliminar

	nodo_t *borrar_nodo = anterior->siguiente;

	anterior->siguiente =
		borrar_nodo
			->siguiente; // re asgino el siguiente del anterior para que apunte al siguiente del eliminado

	free(borrar_nodo); // borro nodo
	lista->cantidad--; // disminuyo cantidad
	return elemento;
}

void *eliminar_primero(lista_t *lista)
{
	if (lista == NULL || lista_vacia(lista))
		return NULL;

	void *elemento = lista->inicio->elemento;
	nodo_t *borrar = lista->inicio;

	// si la lista tiene 1 solo elemento
	if (lista_tamanio(lista) == 1) {
		lista->inicio = NULL;
		lista->ultimo = NULL;
		lista->cantidad--;

		free(borrar);
		return elemento;
	}

	// si la lista tiene mas de un elemento
	lista->inicio = borrar->siguiente;
	free(borrar);

	lista->cantidad--;

	return elemento;
}

void *eliminar_segundo(lista_t *lista, size_t posicion)
{
	void *elemento = lista_elemento_en_posicion(
		lista, posicion); // guardo el elemento del nodo a eliminar
	nodo_t *anterior = lista->inicio;
	nodo_t *borrar = anterior->siguiente;

	//   B(b) , guarde b , para retornarla
	// A-  -C->D->E->NULL quito B y hago que A sHleñale a C

	// siguiente de A ahora es el q le sigue a la posicion 1
	lista->inicio->siguiente = anterior->siguiente->siguiente;

	// borro el 1
	free(borrar);
	lista->cantidad--; // disminuyo cantidad
	return elemento;
}

/******************************************************************************************/

/***********************  Funciónes Extraer   **********************/

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL)
		return NULL;

	if (lista_vacia(lista) || lista_tamanio(lista) < posicion + 1)
		return NULL;

	nodo_t *actual = asignar_nodo_posicion(lista,posicion);

	return actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista == NULL || comparador == NULL)
		return NULL; 

	nodo_t *actual = lista->inicio, *aux; 

	while (actual != NULL) 
	{
		if (comparador(actual->elemento, contexto) == 0) {
			return actual->elemento;
		}

		aux = actual->siguiente;

		actual = aux;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	// si la lista es vacia devuelve NULL ,si no el primer elemento
	return lista_vacia(lista) ? NULL : lista->inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	// si la lista es vacia devuelve NULL ,si no el ultimo elemento
	return lista_vacia(lista) ? NULL : lista->ultimo->elemento;
}





/***********************  Funciónes Iteraciónes   **********************/

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!lista_iterador_tiene_siguiente(iterador))
		return false;

	return (iterador->actual = iterador->actual->siguiente);
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (iterador == NULL || iterador->actual == NULL)
		return NULL;

	return iterador->actual->elemento;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (lista == NULL || lista_vacia(lista) || funcion == NULL)
		return 0;

	size_t cantidad_elementos_iterados = 0;
	bool check = true;

	
	nodo_t *actual = lista->inicio;

	while (actual != NULL && check && cantidad_elementos_iterados < lista_tamanio(lista)) 
	{
		check = funcion(
			actual->elemento,
			contexto); 
		actual = actual->siguiente; 

		cantidad_elementos_iterados++;
	}

	return cantidad_elementos_iterados;
}

