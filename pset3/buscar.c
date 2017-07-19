#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int calcularMedio(int inicio, int final);

void testSearch();

int main(void){
	
	testSearch();

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

/*NO ESTÁ ENTRANDO AL LOOP porque estaba mal la primera condición, cortaba porque no se cumplía que inicio + 1 == final, y en realidad tenía que cumplirse lo contrario*/

    //printf("1 + 1 == 2: %o\n", (1 + 1 == 2)); 1 significa true, 0 significa false
    	
    while ( (inicio + 1) != final && values[medio] != value){
    	//inicio y final no están uno al lado del otro y no encontré a value en el medio
    	
    	eprintf("values[medio]: %i, value: %i\n", values[medio], value);
    	
    	//chequear si values[medio] es mayor o menor que value y cambiar inicio o final y medio
    	if (values[medio] > value){
	    	eprintf("es más grande el del medio\n");
    		//es más grande, buscar adelante
    		final = medio;
    	} else {
	    	eprintf("es más chico el del medio\n");
    		//es más chico, buscar atrás
    		inicio = medio;
    	}
    	
    	//calcular medio
		medio = calcularMedio(inicio, final);
    }
    // o value está en medio, o en inicio, o en final
    // o no está.
	if (values[medio] == value || values[final] == value || values[inicio] == value){
    	eprintf("values[medio]: %i, values[final]: %i values[inicio]: %i\n", values[medio], values[final], values[inicio]);
		return true;
	} else {
		return false;
	}
}

int calcularMedio(int inicio, int final){
	return (final - inicio) / 2 + inicio;
}


void testSearch(){
//	printf("%i\n", calcularMedio(0, 6));
//	printf("%i\n", calcularMedio(0, calcularMedio(0, 6)));
//	printf("%i\n", calcularMedio(0, 6));
//	printf("%i\n", calcularMedio(0, 6));
	int arr[] = {1,2,3,5,6,8,25};
	search(2, arr, 7);
}
