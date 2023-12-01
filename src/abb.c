#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

/*		Funciones auxiliares  			*/
nodo_abb_t *insertar_nodo(nodo_abb_t *padre, void *elemento,
			  abb_comparador comparador);
void *nodo_buscar_rec(nodo_abb_t *padre, void *elemento,
		      abb_comparador comparador);
nodo_abb_t *nodo_quitar(nodo_abb_t *nodo, void *elemento,
			abb_comparador comparador, void **extraido);
nodo_abb_t *extraer_predecesor_inorden(nodo_abb_t *nodo, nodo_abb_t **extraido);

void recorrido_inorden(nodo_abb_t *padre, bool (*funcion)(void *, void *),
		       void *aux, size_t *cantidad, bool *iterar);
void recorrido_preorden(nodo_abb_t *padre, bool (*funcion)(void *, void *),
			void *aux, size_t *cantidad, bool *iterar);
void recorrido_postorden(nodo_abb_t *padre, bool (*funcion)(void *, void *),
			 void *aux, size_t *cantidad, bool *iterar);

size_t llenar_array_inorden(nodo_abb_t *nodo, void **array,
			    size_t tamanio_array);
size_t llenar_array_preorden(nodo_abb_t *nodo, void **array,
			     size_t tamanio_array);
size_t llenar_array_postorden(nodo_abb_t *nodo, void **array,
			      size_t tamanio_array);

/*					Funciones crear										*/

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL)
		return NULL;

	abb_t *nuevo_arbol = malloc(sizeof(abb_t));
	if (nuevo_arbol == NULL)
		return NULL;

	nuevo_arbol->comparador = comparador;
	nuevo_arbol->nodo_raiz = NULL;
	nuevo_arbol->tamanio = 0;

	return nuevo_arbol;
}

nodo_abb_t *crear_nodo_abb(void *elemento, nodo_abb_t *izquierdo,
		       nodo_abb_t *derecho)
{
	nodo_abb_t *nuevo_nodo = malloc(sizeof(nodo_abb_t));

	if (nuevo_nodo == NULL)
		return NULL;

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->derecha = derecho;
	nuevo_nodo->izquierda = izquierdo;

	return nuevo_nodo;
}

/*								Funciones insertar																				*/

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	if (abb_vacio(arbol)) {
		arbol->nodo_raiz = crear_nodo_abb(elemento, NULL, NULL);
		arbol->tamanio++;

		return arbol;
	}

	int comp = arbol->comparador(elemento, arbol->nodo_raiz->elemento);

	if (comp > 0) {
		arbol->nodo_raiz->derecha = insertar_nodo(
			arbol->nodo_raiz->derecha, elemento, arbol->comparador);

	} else {
		arbol->nodo_raiz->izquierda =
			insertar_nodo(arbol->nodo_raiz->izquierda, elemento,
				      arbol->comparador);
	}

	arbol->tamanio++;
	return arbol;
}

nodo_abb_t *insertar_nodo(nodo_abb_t *padre, void *elemento,
			  abb_comparador comparador)
{
	if (padre == NULL) {
		return crear_nodo_abb(elemento, NULL, NULL);
	}

	int comp = comparador(elemento, padre->elemento);

	if (comp > 0) {
		padre->derecha =
			insertar_nodo(padre->derecha, elemento, comparador);

	} else {
		padre->izquierda =
			insertar_nodo(padre->izquierda, elemento, comparador);
	}

	return padre;
}

/*							Funciones para quitar																*/

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol))
		return NULL;

	if (elemento != NULL && abb_buscar(arbol, elemento) == NULL)
		return NULL;

	void *extraido;

	arbol->nodo_raiz = nodo_quitar(arbol->nodo_raiz, elemento,
				       arbol->comparador, &extraido);

	if (elemento != NULL && extraido == NULL)
		return NULL;

	arbol->tamanio--;

	return extraido;
}

nodo_abb_t *extraer_predecesor_inorden(nodo_abb_t *nodo, nodo_abb_t **extraido)
{
	if (nodo->derecha == NULL) {
		*extraido = nodo;
		return nodo->izquierda;
	}

	nodo->derecha = extraer_predecesor_inorden(nodo->derecha, extraido);

	return nodo;
}

nodo_abb_t *nodo_quitar(nodo_abb_t *nodo, void *elemento,
			abb_comparador comparador, void **extraido)
{
	if (nodo == NULL)
		return NULL;

	int comp = comparador(elemento, nodo->elemento);

	if (comp == 0) {
		*extraido = nodo->elemento;

		if (nodo->izquierda != NULL && nodo->derecha != NULL) {
			nodo_abb_t *nodo_predecesor;
			nodo->izquierda = extraer_predecesor_inorden(
				nodo->izquierda, &nodo_predecesor);
			nodo->elemento = nodo_predecesor->elemento;
			free(nodo_predecesor);
			return nodo;
		}

		if (nodo->izquierda == NULL && nodo->derecha == NULL) {
			free(nodo);
			return NULL;
		}
		if (nodo->izquierda != NULL && nodo->derecha == NULL) {
			nodo_abb_t *aux = nodo->izquierda;
			free(nodo);
			return aux;
		}
		if (nodo->izquierda == NULL && nodo->derecha != NULL) {
			nodo_abb_t *aux = nodo->derecha;
			free(nodo);
			return aux;
		}
	}

	if (comp > 0)
		nodo->derecha = nodo_quitar(nodo->derecha, elemento, comparador,
					    extraido);

	nodo->izquierda =
		nodo_quitar(nodo->izquierda, elemento, comparador, extraido);

	return nodo;
}

/*							Funciones de consultas																				*/

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol)) {
		return NULL;
	}

	int comp = arbol->comparador(elemento, arbol->nodo_raiz->elemento);

	if (comp == 0)
		return arbol->nodo_raiz->elemento;

	if (comp > 0) {
		return nodo_buscar_rec(arbol->nodo_raiz->derecha, elemento,
				       arbol->comparador);
	}

	return nodo_buscar_rec(arbol->nodo_raiz->izquierda, elemento,
			       arbol->comparador);
}

void *nodo_buscar_rec(nodo_abb_t *padre, void *elemento,
		      abb_comparador comparador)
{
	if (padre == NULL)
		return NULL;

	int comp = comparador(elemento, padre->elemento);

	if (comp == 0)
		return padre->elemento;

	if (comp > 0) {
		return nodo_buscar_rec(padre->derecha, elemento, comparador);
	}

	return nodo_buscar_rec(padre->izquierda, elemento, comparador);
}

bool abb_vacio(abb_t *arbol)
{
	if (arbol == NULL || arbol->nodo_raiz == NULL) {
		return true;
	}

	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (abb_vacio(arbol))
		return 0;

	return arbol->tamanio;
}

/*						Funciones de recorrido																										*/

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (abb_vacio(arbol) || funcion == NULL)
		return 0;

	size_t cantidad = 0;
	bool iterar = true;

	switch (recorrido) {
	case INORDEN:
		recorrido_inorden(arbol->nodo_raiz, funcion, aux, &cantidad,
				  &iterar);
		break;

	case PREORDEN:
		recorrido_preorden(arbol->nodo_raiz, funcion, aux, &cantidad,
				   &iterar);
		break;

	case POSTORDEN:
		recorrido_postorden(arbol->nodo_raiz, funcion, aux, &cantidad,
				    &iterar);
		break;

	default:
		break;
	}

	return cantidad;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (abb_vacio(arbol) || array == NULL || tamanio_array == 0)
		return 0;

	size_t cantidad = 0;

	switch (recorrido) {
	case INORDEN:
		cantidad = llenar_array_inorden(arbol->nodo_raiz, array,
						tamanio_array);
		return cantidad;

	case PREORDEN:

		cantidad = llenar_array_preorden(arbol->nodo_raiz, array,
						 tamanio_array);
		return cantidad;

	case POSTORDEN:
		cantidad = llenar_array_postorden(arbol->nodo_raiz, array,
						  tamanio_array);
		return cantidad;

	default:
		break;
	}

	return cantidad;
}

/* 				Funciones que ejecutan la funcion en cada elemento del arbol 					*/

void recorrido_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
		       void *aux, size_t *cantidad, bool *iterar)
{
	if (nodo == NULL || *iterar == false)
		return; // si es NULL el nodo sale

	recorrido_inorden(nodo->izquierda, funcion, aux, cantidad, iterar);

	if (*iterar != true)
		return;

	if (funcion(nodo->elemento, aux) == false) {
		(*cantidad)++;
		*iterar = false;
		return;
	}

	(*cantidad)++;

	recorrido_inorden(nodo->derecha, funcion, aux, cantidad, iterar);
}

void recorrido_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			void *aux, size_t *cantidad, bool *iterar)
{
	if (nodo == NULL || *iterar == false)
		return; // si es NULL el nodo sale

	if (funcion(nodo->elemento, aux) == false) {
		(*cantidad)++;
		*iterar = false;
		return;
	}

	(*cantidad)++;

	recorrido_preorden(nodo->izquierda, funcion, aux, cantidad, iterar);

	if (*iterar == true)
		recorrido_preorden(nodo->derecha, funcion, aux, cantidad,
				   iterar);
}

void recorrido_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			 void *aux, size_t *cantidad, bool *iterar)
{
	if (nodo == NULL || *iterar == false)
		return; // si es NULL el nodo sale

	recorrido_postorden(nodo->izquierda, funcion, aux, cantidad, iterar);

	if (*iterar != true)
		return;

	recorrido_postorden(nodo->derecha, funcion, aux, cantidad, iterar);

	if (*iterar != true)
		return;

	if (!funcion(nodo->elemento, aux)) {
		(*cantidad)++;
		*iterar = false;
		return;
	}
	(*cantidad)++;
}

/* 				Funciones que rellenan el array					*/

size_t llenar_array_inorden(nodo_abb_t *nodo, void **array,
			    size_t tamanio_array)
{
	size_t cantidad = 0;

	if (nodo == NULL)
		return cantidad;

	if (cantidad < tamanio_array) {
		cantidad += llenar_array_inorden(nodo->izquierda,
						 array + cantidad,
						 tamanio_array - cantidad);

		if (cantidad < tamanio_array)
			array[cantidad++] = nodo->elemento;

		cantidad += llenar_array_inorden(nodo->derecha,
						 array + cantidad,
						 tamanio_array - cantidad);
	}

	return cantidad;
}

size_t llenar_array_preorden(nodo_abb_t *nodo, void **array,
			     size_t tamanio_array)
{
	size_t cantidad = 0;

	if (nodo == NULL)
		return cantidad;

	if (cantidad < tamanio_array) {
		if (cantidad < tamanio_array)
			array[cantidad++] = nodo->elemento;

		cantidad += llenar_array_preorden(nodo->izquierda,
						  array + cantidad,
						  tamanio_array - cantidad);
		cantidad += llenar_array_preorden(nodo->derecha,
						  array + cantidad,
						  tamanio_array - cantidad);
	}

	return cantidad;
}

size_t llenar_array_postorden(nodo_abb_t *nodo, void **array,
			      size_t tamanio_array)
{
	size_t cantidad = 0;

	if (nodo == NULL)
		return cantidad;

	if (cantidad < tamanio_array) {
		cantidad += llenar_array_postorden(nodo->izquierda,
						   array + cantidad,
						   tamanio_array - cantidad);
		cantidad += llenar_array_postorden(nodo->derecha,
						   array + cantidad,
						   tamanio_array - cantidad);

		if (cantidad < tamanio_array)
			array[cantidad++] = nodo->elemento;
	}

	return cantidad;
}

/*						Funciones de destrucción												*/

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

void destruir_nodos(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;

	destruir_nodos(nodo->izquierda, destructor);
	destruir_nodos(nodo->derecha, destructor);

	if (destructor)
		destructor(nodo->elemento);

	free(nodo);
	return;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;

	destruir_nodos(arbol->nodo_raiz, destructor);

	free(arbol);
}
