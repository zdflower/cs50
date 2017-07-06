#include <stdio.h>
#include <cs50.h>
#include <string.h> //para poder usar por ejemplo strlen

void iniciales(string name){
//¿no hay un método de cadenas como split que parte una cadena por los espacios y te devuelve un array de cadenas?

//guardar el primer carácter de name, luego recorrer el resto letra a letra, detectar el espacio antes de la siguiente palabra, guardar la letra posterior a un espacio, devolver el resultado de este procedimiento.

//no funciona, no sé cómo concatenar caracteres en una string en c

/*
    string res = "";
    strcat(res, name[0]);
    return res;

*/

//otra es que directamente vaya mostrando las iniciales por pantalla a medida que las encuentra en vez de armar una cadena de resultado con ellas.
    int len = strlen(name);
    //mostrar el primer carácter
    printf("%c", name[0]);
    for (int i = 1; i < len - 1; i++){ //para poder chequear el siguiente y que el siguiente exista
        if(name[i] == ' '){
        printf("%c", name[i+1]);
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
