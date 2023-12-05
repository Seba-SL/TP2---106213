#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define FACTOR_CARGA_MAXIMO 0.7
#define SEMILLA_FUNCION_HASH 20

typedef struct nodo {
	void *valor;
	char *clave;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	size_t capacidad; /* total de posiciones en la tabla HASH*/
	nodo_t **tabla_hash; //vector dinamico
	size_t total;
};

size_t funcion_hash(const char *clave, size_t capacidad);
nodo_t *crear_nodo_hash(const char *clave, void *elemento, nodo_t *siguiente);
nodo_t *extraer_nodo(nodo_t *actual, const char *clave, bool eliminado);
nodo_t *buscar_nodo_para_insertar(nodo_t *actual, const char *clave);
hash_t *re_hash(hash_t *hash);
void nodo_insertar_en_tabla(nodo_t **tabla_nueva, size_t n_nuevo, nodo_t *nodo);

nodo_t *crear_nodo_hash(const char *clave, void *elemento, nodo_t *siguiente)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));

	if (!nodo)
		return NULL;

	if (!(nodo->clave = malloc(sizeof(char) * (strlen(clave) + 1)))) {
		free(nodo);

		return NULL;
	}

	strcpy(nodo->clave, clave);

	nodo->valor = elemento;
	nodo->siguiente = siguiente;

	return nodo;
}

hash_t *hash_crear(size_t capacidad)
{
	if (capacidad < 3)
		capacidad = 3;

	hash_t *nuevo_hash = (hash_t *)malloc(sizeof(hash_t));

	if (nuevo_hash == NULL)
		return NULL;

	nuevo_hash->tabla_hash = calloc(1, sizeof(void *) * capacidad);

	if (nuevo_hash->tabla_hash == NULL) {
		free(nuevo_hash);
		return NULL;
	}

	nuevo_hash->capacidad = capacidad;
	nuevo_hash->total = 0;

	return nuevo_hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;

	//la tabla se agranda en caso de que el factor lo complu
	if ((((float)hash->total + 1) / (float)hash->capacidad) >=
	    FACTOR_CARGA_MAXIMO) {
		hash = re_hash(hash); //rehash

		if (hash == NULL)
			return NULL;
	}

	size_t posicion = funcion_hash(clave, hash->capacidad);

	//Si la posicion en la tabla esta vacia
	if (hash->tabla_hash[posicion] == NULL) {
		hash->tabla_hash[posicion] = crear_nodo_hash(clave, elemento, NULL);
		hash->total++;

		if (anterior != NULL)
			*anterior = NULL;

		return hash;
	}

	//si ya esta en la tabla se reemplaza
	nodo_t *actual =
		buscar_nodo_para_insertar(hash->tabla_hash[posicion], clave);
	//devuelve el coincidente en clave o el ultimo nodo

	//Si es el coincidente
	if (!strcmp(actual->clave, clave)) {
		if (anterior != NULL)
			*anterior = actual->valor;

		actual->valor = elemento;
		return hash;
	}

	//si es el ultimo
	actual->siguiente = crear_nodo_hash(clave, elemento, NULL);

	hash->total++;

	if (anterior != NULL)
		*anterior = NULL;

	return hash;
}

hash_t *re_hash(hash_t *hash)
{
	nodo_t **nueva_tabla =
		calloc(1, sizeof(nodo_t *) * (hash->capacidad) * 2);
	if (nueva_tabla == NULL)
		return false;

	for (size_t i = 0; i < hash->capacidad; i++)
		nodo_insertar_en_tabla(nueva_tabla, (hash->capacidad) * 2,
				       hash->tabla_hash[i]);

	free(hash->tabla_hash);

	hash->tabla_hash = nueva_tabla;

	hash->capacidad = (hash->capacidad) * 2;

	return hash;
}

void nodo_insertar_en_tabla(nodo_t **tabla_nueva, size_t n_nuevo, nodo_t *nodo)
{
	if (nodo == NULL)
		return;

	size_t posicion = funcion_hash(nodo->clave, n_nuevo);

	nodo_t *siguiente = nodo->siguiente;

	nodo_t *aux = tabla_nueva[posicion];
	tabla_nueva[posicion] = nodo;
	nodo->siguiente = aux;

	nodo_insertar_en_tabla(tabla_nueva, n_nuevo, siguiente);
}

nodo_t *buscar_nodo_para_insertar(nodo_t *actual, const char *clave)
{
	if (actual == NULL || clave == NULL)
		return NULL;

	//itera hasta el coincidente o el ultimo
	while (actual->siguiente != NULL && strcmp(actual->clave, clave) != 0) {
		actual = actual->siguiente;
	}

	return actual;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t posicion = funcion_hash(clave, hash->capacidad);

	//reasigna los nodos y devuelve el que quiero eliminar
	nodo_t *a_borrar =
		extraer_nodo(hash->tabla_hash[posicion], clave, true);

	//No lo encuentra
	if (a_borrar == NULL)
		return NULL;

	//lo encuentra
	void *elemento = a_borrar->valor;

	if (a_borrar == hash->tabla_hash[posicion]) {
		hash->tabla_hash[posicion] = a_borrar->siguiente;
	}

	free(a_borrar->clave);
	free(a_borrar);

	hash->total--;
	return elemento;
}

nodo_t *extraer_nodo(nodo_t *actual, const char *clave, bool eliminado)
{
	if (actual == NULL || clave == NULL)
		return NULL;

	nodo_t *anterior = actual;

	//devuelve el ultimo o el coincidente
	while (actual->siguiente != NULL && strcmp(actual->clave, clave) != 0) {
		anterior = actual;
		actual = actual->siguiente;
	}

	// si es el que quiero extraer
	if (!strcmp(actual->clave, clave)) {
		//si lo quiero eliminar reasigno el anterior con el siguiente en la lista
		if (eliminado) {
			anterior->siguiente = actual->siguiente;
		}

		return actual;
	}

	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t posicion = funcion_hash(clave, hash->capacidad);

	nodo_t *obtenido =
		extraer_nodo(hash->tabla_hash[posicion], clave, false);

	if (obtenido != NULL)
		return obtenido->valor;

	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t posicion = funcion_hash(clave, hash->capacidad);

	//devuelve el nodo encontrado o NULL
	nodo_t *actual = extraer_nodo(hash->tabla_hash[posicion], clave, false);

	if (actual == NULL)
		return false;

	return true;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;

	return hash->total;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for (int i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->tabla_hash[i]; // la primera posición

		while (actual != NULL) // si el actual es != NULL ,borra y itera
		{
			if (destructor != NULL) // si la función != NULL
				destructor(
					actual->valor); // ejecuta la funcion con el elemento en argumento

			nodo_t *borrar =
				actual; // guardo referencia para liberar despues

			actual = actual->siguiente; // paso al siguiente

			free(borrar->clave); //libero clave en HEAP
			free(borrar); // libero nodo

			// y vuelve con el siguiente
		}
	}

	free(hash->tabla_hash);

	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if (hash == NULL || f == NULL)
		return 0;

	size_t n = 0;
	bool check = true;

	for (int i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->tabla_hash[i]; // la primera posición

		while (actual != NULL) // si el actual es != NULL ,borra y itera
		{
			if (f != NULL &&
			    actual->clave != NULL) // si la función != NULL
			{
				check = f(
					actual->clave, actual->valor,
					aux); // ejecuta la funcion con el elemento en argumento
				n++;
				if (!check)
					return n;
			}

			actual = actual->siguiente; // paso al siguiente
		}
	}

	return n;
}

size_t funcion_hash(const char *clave, size_t capacidad)
{
	size_t hash = SEMILLA_FUNCION_HASH;
	size_t c;

	while ((c = (size_t)*clave)) {
		hash = ((hash << 5) + hash) + c;
		clave++;
	}

	return hash % capacidad;
}
