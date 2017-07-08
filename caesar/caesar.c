#include <stdlib.h> //para el atoi
#include <stdio.h>
#include <cs50.h>
#include <string.h>

const string ALFABETO = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char codificar(char c, int key){
//si no es alfabético c tiene que quedar igual
//los alfabéticos son del 65 al 90 y del 97 al 122
//ojo que se tiene que respetar la mayúscula o minúscula
	char res = c;
	//chequeo si c es alfabético
	//hay una función isalpha que está en la biblioteca ctype.h
	if (c >= 'A' && c <= 'Z'){ 
		res = (((c + key) - 'A') % strlen(ALFABETO)) + 'A'; 
	} else if (c >= 'a' && c <= 'z'){
		res = (((c + key) - 'a') % strlen(ALFABETO)) + 'a';
	}
	return res;
}

/*
escribí algo mal porque tanto para "hola" como para "HOLA" con la clave 1 el resultado es ZGDS 
*/

void ascii(){
	for (char c = 'A'; c <= 'z'; c++){
		printf("%c: %i\n", c, c);
	}
}

void caesar(string txt, int key){
	int len = strlen(txt);
	for (int i = 0; i < len; i++){
		printf("%c", codificar(txt[i], key));
	}
	printf("\n");
}

int main(int argc, string argv[]){
	//ascii();
	//testear codificar

	//toma un argumento que es la clave
	
	//ojo que da error de tipo si uso strlen con argv, para saber la cantidad de argumentos usar directamente argc que es la cantidad de argumentos de argv
	
	//ojo que los elementos de argv son de tipo string

	if (argc == 2){//es decir ./caesar y la clave
		//hay que chequear que se haya pasado exactamente un argumento (además del nombre del ejecutable), ni nada ni más de uno (en estos casos se muestra un mensaje de error y se devuelve 1)
		//pide input para el texto a codificar
		string plaintext = get_string("plaintext: ");
		//mostrar el texto cifrado con esa clave
		printf("ciphertext: ");
		caesar(plaintext, atoi(argv[1]));//acá tengo que convertir el argumentos que proviene de argv de string a int. atoi está en stdlib.h
		return 0;
	} else {
		printf("ERROR: se requiere un argumento.\n");
		return 1;
	}
	//test de codificar
}
