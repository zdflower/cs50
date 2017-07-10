#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

//ver cómo escribir una versión que use arrays de char, o string, cómo ir agregando caracteres... y que crack devuelve una string con el password

/*
bool esElPassword(int ac, string args[]){
	
}
*/

/*
CÓMO GENERO UN ARRAY CON LOS CARACTERES QUE VOY COMBINANDO
CÓMO OBTENGO UN ARRAY DE 2 CHAR A PARTIR DEL INPUT POR LÍNEA DE COMANDOS
CÓMO CONCATENO DOS ARRAY DE CHAR, O CÓMO AGREGO UN CHAR A UN ARRAY DE CHAR
*/

void combinacionesDeHasta4LetrasMym(){
    //generar passwords desde 1 hasta 4 caracteres alfabéticos en maýsculas y minúsculas
    //usar crypt(pass, salt) y comparar el resultado con hash. tomar salt de los dos primeros caracteres de hash
    
    //IDEA 1
    //hacer 4 loops anidados
    //para cada i de "0 a 52" (no es exactamente así)
        //generar el hash con algo similar a crypt(i, hash[0:2]) y comparar con el hash dado
        //si son iguales devolver i
        //continuar con los passwords de dos caracteres
        //para cada j de "0 a 52"
           //generar el hash con algo similar a crypt(i concatenado con j, hash[0:2]) y comparar con el hash dado
           //si son iguales devolver i concatenado con j
           //para cada k de "0 a 52"
              //generar el hash con algo similar a crypt(i concatenado con j concatenado con k, hash[0:2]) y comparar con el hash dado
              //si son iguales devolver i concatenado con j concatenado con k
              //para cada l de 0 a 52
                //generar el hash con algo similar a crypt(i concatenado con j concatenado con k concatenado con l, hash[0:2]) y comparar con el hash dado
                //si son iguales devolver i concatenado con j concatenado con k concatenado con l


/*	se podría poner en una función ¿recursiva? ¿conviene? ¿es necesario? el loop con el chequeo de si es alfabético y mostrar ... no sé
	si no, pensar de qué otro modo más claro se puede hacer, cuáles serían las ventajas y desventajas, por ejemplo, tal vez se pueda hacer más modularizado con funciones pero también aumentando la complejidad algorítmica (o el tiempo de ejecución o la cantidad de operaciones), o por otro lado, más feo de ver y leer, pero se hace una sóla vez cada cosa y entonces la cantidad de operaciones es menor.
*/
	for (char c = 'A'; c <= 'z'; c++){
	//filtrar los que no son alfabéticos y están entre 'Z' y 'a'
		//passwords de un carácter
		if(isalpha(c)){
			printf("%c\n", c);
			for (char d = 'A'; d <= 'z'; d++){
				//passwords de dos caracteres
				if (isalpha(d)){
					printf("%c%c\n", c, d);
					for (char e = 'A'; e <= 'z'; e++){
						//passwords de tres caracteres
						if (isalpha(e)){
							printf("%c%c%c\n", c, d, e);
							for (char f = 'A'; f <= 'z'; f++){
								//passwords de 4 caracteres
								if (isalpha(f)){
									printf("%c%c%c%c\n", c, d, e, f);
								}
							}
						}
					}
				}
			}
		}
	}
}

/*
void mostrarCadena(char [] s){
	int slen = strlen(s);
	for (int i = 0; i < slen; i++){
		printf("%c", s[i]);
	}
}

*/

//Se supone que las claves son alfabéticas de 1 a 4 caracteres como máximo y que el algoritmo de encriptación está basado en DES.
int main(int argc, string argv[]){
    //chequear que se obtuvo exactamente un argumento por línea de comandos, si no mostrar un mensaje de error y devolver 1, si está todo bien, continuar
    //si se obtuvo un argumento válido
        //crackearlo y mostrar el password

	combinacionesDeHasta4LetrasMym();
}

//compilar con
// clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow crack.c -lcrypt -lcs50 -lm -o crack
