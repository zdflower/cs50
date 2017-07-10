#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

string crack(string hash){
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
}

//Se supone que las claves son alfabéticas de 1 a 4 caracteres como máximo y que el algoritmo de encriptación está basado en DES.
int main(int argc, string argv[]){
    //chequear que se obtuvo exactamente un argumento por línea de comandos, si no mostrar un mensaje de error y devolver 1, si está todo bien, continuar
    //si se obtuvo un argumento válido
        //crackearlo y mostrar el password
        printf(crack(argv[1]));
}

//compilar con
// clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow crack.c -lcrypt -lcs50 -lm -o crack
