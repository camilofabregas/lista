#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DECLARACION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct lista;
typedef struct lista lista_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera la lista hasta que haya una condicion que detenga la iteracion.
// Pre: recibe la lista, la funcion visitar (que sirve de condicion de 
// corte para la iteracion), y un puntero extra. 
// Que visitar devuelva true significa que la iteracion sigue, false que se detenga.
void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra);


/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador.
// Pre: recibe la lista creada con lista_crear().
// Post: devuelve un puntero al iterador creado.
lista_iter_t* lista_iter_crear(lista_t* lista);


// Avanza al elemento de la lista.
// Pre: recibe el iterador.
// Post: devuelve true si pudo avanzar, o false si no (esta al final)
bool lista_iter_avanzar(lista_iter_t* iter);


// Muestra el dato de la posicion actual del iterador.
// Pre: recibe el iterador.
// Post: devuelve el dato del nodo al que apunta el iterador en ese momento
void* lista_iter_ver_actual(const lista_iter_t* iter);


// Indica si el iterador se encuentra al final de la lista.
// Pre: recibe el iterador.
// Post: devuelve true si esta al final de la lista, false si no.
// El iterador esta al final si apunta a NULL.
bool lista_iter_al_final(const lista_iter_t* iter);


// Destruye el iterador creado.
// Pre: recibe el iterador.
void lista_iter_destruir(lista_iter_t* iter);


// Inserta en la lista el dato que esta en la posicion actual del iterador.
// Pre: recibe el iterador y el dato a insertar.
// Post: devuelve true si lo pudo insertar, o false si no.
bool lista_iter_insertar(lista_iter_t* iter, void* dato);


// Borra de la lista el dato que esta en la posicion actual del iterador. 
// Pre: recibe el iterador.
// Post: devuelve el dato eliminado de la lista o NULL si esta vacia.
void* lista_iter_borrar(lista_iter_t* iter);


/* ******************************************************************
 *                      PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista
// Post: devuelve una lista vacia.
lista_t* lista_crear(void);


// Chequea si la lista esta vacia o no.
// Pre: recibe la lista.
// Post: devuelve true si la lista esta vacia, false si no.
bool lista_esta_vacia(const lista_t* lista);


// Inserta un dato en la primera posicion de la lista.
// Pre: recibe la lista y el dato a insertar.
// Post: devuelve true si se pudo insertar el elemento, false si no.
bool lista_insertar_primero(lista_t* lista, void* dato);


// Inserta un dato en la ultima posicion de la lista.
// Pre: recibe la lista y el dato a insertar.
// Post: devuelve true si se pudo insertar el elemento, false si no.
bool lista_insertar_ultimo(lista_t* lista, void* dato);


// Borra el primer elemento de la lista.
// Pre: recibe la lista.
// Post: devuelve el elemento eliminado o NULL si la lista esta vacia.
void* lista_borrar_primero(lista_t* lista);


// Muestra el primer elemento de la lista.
// Pre: recibe la lista.
// Post: devuelve el primer elemento de la lista.
void* lista_ver_primero(const lista_t* lista);


// Muestra el ultimo elemento de la lista.
// Pre: recibe la lista.
// Post: devuelve el ultimo elemento de la lista.
void* lista_ver_ultimo(const lista_t* lista);


// Muestra el largo de la lista.
// Pre: recibe la lista.
// Post: devuelve el largo de la lista.
size_t lista_largo(const lista_t* lista);


// Destruye la lista. Si se recibe la funcion destruir_dato, se destruyen todos
// los elementos con dicha funcion. Si se recibe NULL, no se los elimina.
// Pre: recibe la lista y la funcion destruir_dato (o NULL).
void lista_destruir(lista_t* lista, void (*destruir_dato)(void*));


#endif // LISTA_H