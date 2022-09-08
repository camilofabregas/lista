#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#define TAM_PILA 3
#define CANT_VOLUMEN 1000

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

void destruir_dato_pila(void* pila) {
	pila_destruir(pila);
}

bool sumar_todos(void* dato, void* extra) {
	*(int*) extra += *(int*) dato;
	return true;
}

bool imprimir_3_primeros(void* dato, void* extra) {
    *(int*) extra += 1;
    printf("El elemento numero %d es el %d\n", *(int*) extra, *(int*) dato);
    return (*(int*) extra < 3);
}


/* *****************************************************************
 *                    PRUEBAS UNITARIAS
 * *****************************************************************/

void pruebas_lista_vacia() {
	printf("\nINICIO DE PRUEBAS PARA LISTA VACIA\n");

    /* Declaro las variables a utilizar */
	lista_t* lista1 = lista_crear();
	lista_iter_t* iter1 = lista_iter_crear(lista1);

    /* Inicio de pruebas */
    print_test("Lista inicializada correctamente", lista1);
    print_test("Iterador inicializado correctamente", iter1);
    print_test("Lista esta vacia es verdadero", lista_esta_vacia(lista1));
    print_test("El largo de la lista es cero", lista_largo(lista1) == 0);
    print_test("Avanzar al siguiente elemento de una lista vacia es NULL", !lista_iter_avanzar(iter1));
    print_test("Ver el dato actual de una lista vacia es NULL", !lista_iter_ver_actual(iter1));
    print_test("En una lista vacia el iterador siempre esta al final", lista_iter_al_final(iter1));
    print_test("Ver primer elemento de la lista es NULL", !lista_ver_primero(lista1));
    print_test("Ver ultimo elemento de la lista es NULL", !lista_ver_ultimo(lista1));
    print_test("Eliminar el dato actual del iterador en una lista vacia es NULL", !lista_iter_borrar(iter1));
    print_test("Eliminar primer elemento es NULL", !lista_borrar_primero(lista1));

    /* Destruyo la cola y el iterador*/
    lista_destruir(lista1, NULL);
    print_test("Lista destruida", true);
    lista_iter_destruir(iter1);
    print_test("Iterador destruido", true);
}


void pruebas_lista_algunos_elementos() {
	printf("\nINICIO DE PRUEBAS PARA LISTA CON ALGUNOS ELEMENTOS\n");

    /* Declaro las variables a utilizar */
    lista_t* lista2 = lista_crear();
	int num1 = 3;
	int num2 = 5;
	void* nul1 = NULL;
	int num3 = 8;
	void* nul2 = NULL;

    /* Inicio de pruebas */
    print_test("Lista inicializada correctamente", lista2);
    print_test("Insertar numero 3 al principio de la lista", lista_insertar_primero(lista2, &num1));
    print_test("El primer elemento de la lista es 3", lista_ver_primero(lista2) == &num1);
    print_test("Insertar NULL al principio de la lista", lista_insertar_primero(lista2, nul1));
    print_test("El primer elemento de la lista es NULL", lista_ver_primero(lista2) == nul1);
    print_test("Insertar numero 5 al final de la lista", lista_insertar_ultimo(lista2, &num2));
    print_test("El ultimo elemento de la lista es 5", lista_ver_ultimo(lista2) == &num2);
    print_test("Insertar numero 8 al final de la lista", lista_insertar_ultimo(lista2, &num3));
    print_test("El ultimo elemento de la lista es 8", lista_ver_ultimo(lista2) == &num3);
    print_test("Insertar NULL al final de la lista", lista_insertar_ultimo(lista2, nul2));
    print_test("El ultimo elemento de la lista es NULL", lista_ver_ultimo(lista2) == nul2);
    print_test("El largo de la lista es 5", lista_largo(lista2) == 5);
    print_test("Lista esta vacia es falso", !lista_esta_vacia(lista2));
    print_test("Eliminar primero de la lista elimina a NULL", lista_borrar_primero(lista2) == nul1);
    print_test("El primer elemento de la lista es 3", lista_ver_primero(lista2) == &num1);
    print_test("Eliminar primero de la lista elimina a 3", lista_borrar_primero(lista2) == &num1);
    print_test("Eliminar primero de la lista elimina a 5", lista_borrar_primero(lista2) == &num2);
    print_test("Eliminar primero de la lista elimina a 8", lista_borrar_primero(lista2) == &num3);
    print_test("El primer elemento de la lista es NULL", lista_ver_primero(lista2) == nul2);
    print_test("El largo de la lista es 1", lista_largo(lista2) == 1);
    print_test("Eliminar primero de la lista elimina a NULL", lista_borrar_primero(lista2) == nul2);
    print_test("Lista esta vacia es verdadero", lista_esta_vacia(lista2));
    print_test("El largo de la lista es cero", lista_largo(lista2) == 0);
    

    /* Destruyo la cola y el iterador*/
    lista_destruir(lista2, NULL);
    print_test("Lista destruida", true);
}


void pruebas_iter_ext_algunos_elementos() {
	printf("\nINICIO DE PRUEBAS PARA ITERADOR EXTERNO CON ALGUNOS ELEMENTOS\n");

    /* Declaro las variables a utilizar */
	lista_t* lista3 = lista_crear();
	lista_iter_t* iter2 = lista_iter_crear(lista3);
	int num1 = 3;
	int num2 = 5;
	int num3 = 1;
	int num4 = 8;

    /* Inicio de pruebas */
    print_test("Lista inicializada correctamente", lista3);
    print_test("Iterador 1 inicializado correctamente", iter2);
    print_test("Insertar 3 en la posicion actual", lista_iter_insertar(iter2, &num1));
    print_test("Insertar 5 en la posicion actual", lista_iter_insertar(iter2, &num2));
    print_test("El iterador apunta a 5", lista_iter_ver_actual(iter2) == &num2);
    print_test("Eliminar elemento actual", lista_iter_borrar(iter2) == &num2);
    print_test("El iterador apunta a 3", lista_iter_ver_actual(iter2) == &num1);
    print_test("Eliminar elemento actual", lista_iter_borrar(iter2) == &num1);
    print_test("Lista esta vacia es verdadero", lista_esta_vacia(lista3));
    print_test("El iterador esta al final ya que la lista esta vacia", lista_iter_al_final(iter2));
    print_test("Ver actual es NULL ya que la lista esta vacia", !lista_iter_ver_actual(iter2));
    lista_iter_t* iter3 = lista_iter_crear(lista3);
    print_test("Iterador 2 inicializado correctamente", iter3);
    print_test("Ver actual con nuevo iter es NULL ya que la lista esta vacia", !lista_iter_ver_actual(iter2));
    print_test("Insertar 1 en la posicion actual", lista_iter_insertar(iter3, &num3));
    print_test("Avanzar una posicion", lista_iter_avanzar(iter3));
    print_test("Insertar 1 en la posicion actual", lista_iter_insertar(iter3, &num4));
    print_test("El iterador apunta al ultimo de la lista", lista_iter_ver_actual(iter3) == lista_ver_ultimo(lista3));


    /* Destruyo la cola y el iterador*/
    lista_destruir(lista3, NULL);
    print_test("Lista destruida", true);
    lista_iter_destruir(iter2);
    print_test("Iterador 1 destruido", true);
    lista_iter_destruir(iter3);
    print_test("Iterador 2 destruido", true);
}


void pruebas_iter_int_destruir_lista_free() {
	printf("\nINICIO DE PRUEBAS PARA ITERADOR INTERNO\n");

    /* Declaro las variables a utilizar */
	lista_t* lista4 = lista_crear();
	int* num1 = malloc(sizeof(int));
	int* num2 = malloc(sizeof(int));
	int* num3 = malloc(sizeof(int));
	int* num4 = malloc(sizeof(int));
	*num1 = 2;
	*num2 = 4;
	*num3 = 6;
	*num4 = 8;
	int suma = 0;

	/* Inicio de pruebas */
    print_test("Lista inicializada correctamente", lista4);
    printf("Los elementos insertados a continuacion provienen del heap\n");
    print_test("Insertar numero 2 al principio de la lista", lista_insertar_primero(lista4, num1));
    print_test("Insertar numero 4 al principio de la lista", lista_insertar_primero(lista4, num2));
    print_test("Insertar numero 6 al principio de la lista", lista_insertar_primero(lista4, num3));
    print_test("Insertar numero 8 al principio de la lista", lista_insertar_primero(lista4, num4));
    lista_iterar(lista4, sumar_todos, &suma);
    print_test("Sumar todos los elementos de la lista es igual a 20", suma == 20);

    /* Destruyo la cola y el iterador*/
    lista_destruir(lista4, free);
    print_test("Lista destruida (datos destruidos con free)", true);
}


void pruebas_iter_int_corte() {
    printf("\nINICIO DE PRUEBAS PARA ITERADOR INTERNO (CON CORTE)\n");

    /* Declaro las variables a utilizar */
    lista_t* lista5 = lista_crear();
    int* num1 = malloc(sizeof(int));
    int* num2 = malloc(sizeof(int));
    int* num3 = malloc(sizeof(int));
    int* num4 = malloc(sizeof(int));
    *num1 = 10;
    *num2 = 25;
    *num3 = 15;
    *num4 = 8;
    int contador = 0;

    /* Inicio de pruebas */
    print_test("Lista inicializada correctamente", lista5);
    printf("Los elementos insertados a continuacion provienen del heap\n");
    print_test("Insertar numero 10 al final de la lista", lista_insertar_ultimo(lista5, num1));
    print_test("Insertar numero 25 al final de la lista", lista_insertar_ultimo(lista5, num2));
    print_test("Insertar numero 15 al final de la lista", lista_insertar_ultimo(lista5, num3));
    print_test("Insertar numero 8 al final de la lista", lista_insertar_ultimo(lista5, num4));
    lista_iterar(lista5, imprimir_3_primeros, &contador);
    print_test("Se pudieron imprimir los 3 primeros elementos de la lista", contador == 3);

    /* Destruyo la cola y el iterador*/
    lista_destruir(lista5, free);
    print_test("Lista destruida (datos destruidos con free)", true);

}


void pruebas_lista_destruir_pila() {
	printf("\nINICIO DE PRUEBAS PARA DESTRUIR LISTA CON FUNCION PILA_DESTRUIR\n");

	/* Declaro las variables a utilizar */
   	lista_t* lista6 = lista_crear();;
    pila_t* pila = pila_crear();
    int elems[TAM_PILA]; // Vector con la cantidad de elementos de la pila
   	for (int i = 0; i < TAM_PILA; i++) {
   		elems[i] = i+1;
   		pila_apilar(pila, &elems[i]);
   	}

    /* Chequeo lista e inserto la pila */
    print_test("Lista inicializada correctamente", lista6 != NULL);
    print_test("Lista esta vacia es verdadero", lista_esta_vacia(lista6));
    print_test("Insertar pila al final de la lista es verdadero", lista_insertar_ultimo(lista6, pila));
    print_test("Lista esta vacia es falso", !lista_esta_vacia(lista6));

    /* Destruyo la lista*/
    lista_destruir(lista6, destruir_dato_pila);
    print_test("Lista destruida (dato destruido con pila_destruir)", true);
}


void pruebas_lista_volumen() {
    printf("\nINICIO DE PRUEBA DE VOLUMEN PARA LISTA\n");

    /* Declaro las variables a utilizar */
    lista_t* lista7 = lista_crear();
    int* vector = malloc(CANT_VOLUMEN * sizeof(int));
    bool insertar_volumen = true;
    bool eliminar_volumen = true;

    /* Chequeo lista e inserto los elementos del vector */
    print_test("Lista inicializada correctamente", lista7 != NULL);
    for (int i = 0; i < CANT_VOLUMEN && insertar_volumen; i++) {
        vector[i] = i+1;
        insertar_volumen = lista_insertar_primero(lista7, &vector[i]);
    }
    print_test("Insertar varios elementos al principio de la lista", insertar_volumen);
    print_test("El primer elemento de la lista es el ultimo agregado al principio", lista_ver_primero(lista7) == &vector[CANT_VOLUMEN-1]);
    print_test("El ultimo elemento de la lista es el primero agregado al principio", lista_ver_ultimo(lista7) == &vector[0]);
    print_test("Lista esta vacia es falso", !lista_esta_vacia(lista7));
    printf("El largo de la lista es %zu\n", lista_largo(lista7));
    for (int i = CANT_VOLUMEN - 1; i >= 0; i--) {
        int* eliminado = lista_borrar_primero(lista7);
        if (eliminado != &vector[i] || *eliminado == CANT_VOLUMEN - i) eliminar_volumen = false;
    }
    print_test("Todos los elementos fueron eliminados de la lista correctamente", eliminar_volumen);
    printf("El largo de la lista es %zu\n", lista_largo(lista7));
    print_test("Lista esta vacia es verdadero", lista_esta_vacia(lista7));


    /* Destruyo la lista y libero el vector*/
    lista_destruir(lista7, NULL);
    print_test("Lista destruida", true);
    free(vector);
}


void pruebas_lista_alumno(void) {
	pruebas_lista_vacia();
	pruebas_lista_algunos_elementos();
	pruebas_iter_ext_algunos_elementos();
	pruebas_iter_int_destruir_lista_free();
    pruebas_iter_int_corte();
	pruebas_lista_destruir_pila();
	pruebas_lista_volumen();
}