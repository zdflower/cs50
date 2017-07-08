#include <stdio.h>
#include <cs50.h>
#include <string.h> //para poder usar por ejemplo strlen
#include <ctype.h> //para poder usar toupper

void iniciales(string name){
//ir mostrando las iniciales por pantalla a medida que las encuentra

//puede haber espacios al comienzo, en el medio y al final.

    int len = strlen(name);
//encontrar el primer carácter que no sea un espacio y mostrarlo
//luego seguir hasta encontrar un espacio y seguir hasta el primero que no es un espacio y mostrarlo...
   
   // habría que considerar el caso de que no hubiera espacios al comienzo

   //si el primer elemento no es un espacio, entonces mostrarlo.
	if (name[0] != ' '){
		printf("%c", toupper(name[0]));
	}

	//para el resto
    for (int i = 1; i < len; i++){ //voy a empezar en el segundo elemento, y voy a chequear si el actual no es un espacio y el anterior es un espacio, y en ese caso voy a mostrar el carácter actual, si no nada.
		if (name[i] != ' ' && name[i-1] == ' '){
        	printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
}

int main(void){
    //pedir input, se supone que el usuario ingresa letras y espacios.
    string name = get_string("Name: ");
    //mostrar las iniciales de las palabras ingresadas
    //printf("%s\n", iniciales(name));
    iniciales(name);
}

//compilar con gcc -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow initials.c -lcs50 -lm -o initials

//o con c50make initials
