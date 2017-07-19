/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"


// revisar y aclarar las dudas, explicar cada parte, ver cómo mejorar o hacer cambios y que siga funcionando

//declaración de la interfaz de funciones auxiliares
void swap(int i, int j, int values[]);
void insertarEnOrden(int i, int values[]);
int calcularMedio(int inicio, int final);

/**
 * Returns true if value is in array of n values, else false.
 */
bool linearSearch(int value, int values[], int n)
{
    //búsqueda lineal, O(n)
    
    int i = 0;
    //mientras i no haya llegado al final y el valor actual no sea el que estabas buscando seguí
    while (i < n && values[i] != value){
	    i++;
    }
    //si i es más chico que n es porque encontraste lo que buscabas, sino no. Esto último incluye el caso en que n sea negativo, porque como i empieza en 0, si n es negativo no entra en el loop y al chequear si i es más chico que n da falso y es el caso en que no encontraste lo que buscabas.
    if (i < n){
    	return true;
    } // no hace falta el else porque si entró en el if, con return sale de la función y no vuelve.
    return false; //acá llega sólo si i >= n
}

/*
Búsqueda binaria
*/
bool search(int value, int values[], int n)
{
    // búsqueda binaria, O(log n)
    
    //establecer inicio y fin del espacio de búsqueda
    int inicio = 0;
    int final = n - 1; // ¿qué conviene? ¿qué es correcto? ¿n o n-1? ¿ambos?
    //calcular medio
    int medio = calcularMedio(inicio, final); //me parece que no importa si la cantidad de elementos del array es par o no
    //tenés que ciclar, con cada vuelta, chequeás si el que está en el medio es el value y si no partís en dos el espacio de búsqueda y seguís en la parte que corresponde, dependiendo de si el del medio es mayor o menor que lo que buscás.
    //termina cuando inicio y final están juntos, si value está tiene que ser en inicio o en final, si no no está.
    while ( (inicio + 1) != final && values[medio] != value){
    	//inicio y final no están uno al lado del otro y no encontré a value en el medio
    	
    	//chequear si values[medio] es mayor o menor que value y cambiar inicio o final y medio
    	if (values[medio] > value){
    		//es más grande, buscar adelante
    		final = medio;
    	} else {
    		//es más chico, buscar atrás
    		inicio = medio;
    	}
    	
    	//calcular medio
		medio = calcularMedio(inicio, final);
    }
    // o value está en medio, o en inicio, o en final
    // o no está.
	if (values[medio] == value || values[final] == value || values[inicio] == value){
		return true;
	} else {
		return false;
	}
}

int calcularMedio(int inicio, int final){
	return (final - inicio) / 2 + inicio;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // insertion sort
    /*
    1 <= i <= n, donde n es la longitud del array values
    Al comienzo todo el array está desordenado, con cada vuelta, hay uno más en la parte ordenada que será la de la izquierda. Y se va corriendo el índice hasta llegar a n, cuando no vuelve a entrar en el loop
    La manera de insertar ordenado es que para cada elemento que mirás lo tenés que ubicar donde corresponde en la parte ordenada. Esto lo resuelve una función auxiliar que se llama en cada vuelta. Va a ser otro loop.
    */
	int i = 1;
	while (i < n){
		insertarEnOrden(i, values);
		i++;
	}
    return; //no devuelve nada, modifica el array values
}


/*
inserta donde corresponde el i-ésimo elemento de values en la parte ordenada, es decir desde el índice 0 hasta i, sin incluir y deja desde 0 hasta i inclusive en orden de menor a mayor.
modifica values.
*/
void insertarEnOrden(int i, int values[]){
	for (int j = 0; j < i; j++){
		//¿es el j-ésimo mayor que el i-ésimo? si es así, swapear entre j e i
		if ( values[j] > values[i]){
			swap(i, j, values);
		}
	}
}

/*
intercambia los elementos i-ésimo y j-ésimo del array
modifica el array
*/

void swap(int i, int j, int values[]){
	//tenés que guardar temporalmente un valor
	int temp = values[j]; //salvás el valor que hay en j
	values[j] = values[i]; //en j ponés el valor que está en i, así sobreescribís lo que había en j, por eso lo guardamos antes en una variable
	//ahora guardamos lo que había antes en j y lo ponemos en i
	values[i] = temp;
}
