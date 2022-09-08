#include "lista.h"
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct nodo {
	void* dato;
	struct nodo* proximo;
} nodo_t;


struct lista {
	nodo_t* primero;
	nodo_t* ultimo;
	size_t largo;
};

struct lista_iter {
	lista_t* lista;
	nodo_t* actual;
	nodo_t* anterior;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

static nodo_t* nodo_crear(void* dato) {
	nodo_t* nodo = calloc(1, sizeof(nodo_t));
	nodo->dato = dato;
	return nodo;
}


static bool lista_insertar_primero_ultimo(lista_t* lista, void* dato, bool al_final) {
	nodo_t* nodo_nuevo = nodo_crear(dato);
	if (!nodo_nuevo) return false;
	if (lista_esta_vacia(lista)) {
		lista->primero = nodo_nuevo;
		lista->ultimo = nodo_nuevo;
		lista->largo += 1;
		return true;
	}
	if (al_final) {
		lista->ultimo->proximo = nodo_nuevo;
		lista->ultimo = nodo_nuevo;
		lista->largo += 1;
		return true;
	}
	nodo_nuevo->proximo = lista->primero;
	lista->primero = nodo_nuevo;
	lista->largo += 1;
	return true;
}


/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra) {
	nodo_t* nodo = lista->primero;
	bool seguir_iterando = true;
	while (seguir_iterando && nodo) {
		seguir_iterando = visitar(nodo->dato, extra);
		nodo = nodo->proximo;
	}
}


/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t* lista_iter_crear(lista_t* lista) {
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (!iter) return NULL;
	iter->actual = lista->primero;
	iter->anterior = NULL;
	iter->lista = lista;
	return iter;
}


bool lista_iter_avanzar(lista_iter_t* iter) {
	if (iter->actual == NULL) return false;
	iter->anterior = iter->actual;
	iter->actual = iter->actual->proximo;
	return true;
}


void* lista_iter_ver_actual(const lista_iter_t* iter) {
	if (!iter->actual) return NULL;
	return iter->actual->dato;
}


bool lista_iter_al_final(const lista_iter_t* iter) {
	return (iter->actual == NULL);
}


void lista_iter_destruir(lista_iter_t* iter) {
	free(iter);
}


bool lista_iter_insertar(lista_iter_t* iter, void* dato) {
	nodo_t* nodo_nuevo = nodo_crear(dato);
	if (!nodo_nuevo) return false;
	nodo_nuevo->proximo = iter->actual;
	if (iter->anterior == NULL) {
		iter->lista->primero = nodo_nuevo;	
	}
	else {
		iter->anterior->proximo = nodo_nuevo;
	}
	if (!iter->actual) iter->lista->ultimo = nodo_nuevo;
	iter->actual = nodo_nuevo; 
	iter->lista->largo += 1;
	return true;
}


void* lista_iter_borrar(lista_iter_t* iter) {
	if (lista_iter_al_final(iter)) return NULL;
	void* dato = iter->actual->dato;
	nodo_t* prox = iter->actual->proximo;
	if (iter->anterior == NULL) {
		iter->lista->primero = iter->actual->proximo;
	}
	else {
		iter->anterior->proximo = iter->actual->proximo;
	}
	if (!prox) iter->lista->ultimo = iter->anterior;
	free(iter->actual);
	iter->actual = prox;
	iter->lista->largo -= 1;
	return dato;

}


/* ******************************************************************
 *                      PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(void) {
	lista_t* lista = calloc(1, sizeof(lista_t));
	return lista;
}


bool lista_esta_vacia(const lista_t* lista) {
	return lista->largo == 0;
}


bool lista_insertar_primero(lista_t* lista, void* dato) {
	return lista_insertar_primero_ultimo(lista, dato, false);
}


bool lista_insertar_ultimo(lista_t* lista, void* dato) {
	return lista_insertar_primero_ultimo(lista, dato, true);
}


void* lista_borrar_primero(lista_t* lista) {
	if (lista_esta_vacia(lista)) return NULL;
	void* dato = lista->primero->dato;
	nodo_t* prox = lista->primero->proximo;
	free(lista->primero);
	lista->primero = prox;
	if (!lista->primero) lista->ultimo = NULL;
	lista->largo -= 1;
	return dato;
}


void* lista_ver_primero(const lista_t* lista) {
	if (lista_esta_vacia(lista)) return NULL;
	return lista->primero->dato;
}


void* lista_ver_ultimo(const lista_t* lista) {
	if (lista_esta_vacia(lista)) return NULL;
	return lista->ultimo->dato;
}


size_t lista_largo(const lista_t* lista) {
	return lista->largo;
}


void lista_destruir(lista_t* lista, void (*destruir_dato)(void*)) {
	while (!lista_esta_vacia(lista)) {
		void* dato = lista_borrar_primero(lista);
		if (destruir_dato) destruir_dato(dato);
	}
	free(lista);
}