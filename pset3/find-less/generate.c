/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // si la cantidad de argumentos no es 2 ni 3 mostrar mensaje de cómo se usa el programa y devolver 1 para indicar error
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // convertir el primer argumento después del nombre del programa a integer
    int n = atoi(argv[1]);

    // si hay 3 argumentos, es decir si se indicó la cantidad de números a generar y además una semilla
    // llamás a srand48 y le pasás la semilla, para que se la pase a drand48 después, o para que la use drand48 después cuando se lo llame, srand48 inicializa drand48 con la semilla.
    // si no llamás a srand48 y le pasás time(NULL) ¿por qué? ¿qué hace?
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // generar n números con drand48 y lo multiplica por el límite para obtener valores más altos, ya que drand48 devuelve nonnegative double-precision floating-point values distribuidos uniformemente entre [0.0 y 1.0). Después castea el resultado a entero, lo que debe hacer que se pierda la parte decimal
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
