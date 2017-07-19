#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

//sort no ordena bien

//EL PROBLEMA ESTÁ EN INSERTARENORDEN
//parece que swap está ok


void swap(int i, int j, int values[]);
void insertarEnOrden(int i, int values[]);
void sort(int values[], int n);
void testSwap();
void testSortSinArgs();
void testSort(int ar[], int n);
void testInsertar();

int main(int argc, string argv[])
{
	int arr[] = {2728,29785,54710,22019,37059,115,12293,64909,49184,24004};
	testSort(arr, 10);	
	//testSwap();
	//testInsertar();
}

void testSwap(){
	int arr[2];
	arr[0] = 3;
	arr[1] = 9;
	printf("%i, %i\n", arr[0], arr[1]);
	swap(0, 1, arr);
	printf("%i, %i\n", arr[0], arr[1]);
}

void testInsertar(){
	int n = 5;
	int arr[] = {2, 3, 8, 25, 1}; //acá falla, porque intercambia las posiciones del 2 y el 1. ¿Qué debería hacer en vez de este intercambio?
	insertarEnOrden(4, arr);
	for (int i = 0; i < n; i++){
		printf("%i\n", arr[i]);
	}
}

void testSortSinArgs(){
	int n = 7; //testeo con 8 números
	int arr[n];
	for (int i = 0; i < n; i++){
		arr[i] = get_int("Número: ");
	}
	sort(arr, n);
	
	//mostrar el arr ordenado (con suerte)
	for (int i = 0; i < n; i++){
		printf("%i\n", arr[i]);
	}
}

void testSort(int arr[], int n){
	sort(arr, n);
	
	//mostrar el arr ordenado (con suerte)
	for (int i = 0; i < n; i++){
		printf("%i\n", arr[i]);
	}

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
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
inserta donde corresponde el i-ésimo elemento de values en la parte ordenada, es decir desde el índice 0 hasta i, sin incluir.
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
