#include <ctype.h> // toupper e isalpha
#include <stdio.h> //para printf y el input/output
#include <cs50.h> //para los get_string y demás get_
#include <string.h> //para strlen

//considero que el alfabeto es el inglés, con 26 letras.
//pensar cómo sería para el castellano con la ñ y los acentos...

const int alphasize = 26;


bool sonTodosAlfa(string s){
	int slen = strlen(s);
	int i = 0;
	while (i < slen && isalpha(s[i])){ //si te faltan caracteres por chequear y el actual es alfabético, seguí con el próximo
		i++;
	}
	//acá: o son todos alfabéticos, caso de i igual a slen; o alguno no es alfabético, caso de i menor que slen
	//devolver i == slen
	return i == slen;
}

bool esClaveValida(int len, string args[]){//el bug está acá, debería recibir un array de strin y no una string como lo escribí
	//para devolver true, len tiene que ser 2 y args[1] tiene que contener sólo caracteres alfabéticos
	return len == 2 && sonTodosAlfa(args[1]);
}


char codificarUno(char c, char k){
	//se supone que c es alfabético

	//para codificar:
	//lo llevás al rango 0-25, le sumás la clave también llevada a rango 0-25, tomás módulo 26 y finalmente lo llevás al rango correspondiente para las letras

	//respetar mayúsculas y minúsculas
	
	//cuidado con la clave, que puede estar en cualquier estado de mayúscula y minúscula

	char res = ' ';
	if (c >= 'a' && c <= 'z'){
		//si está entre 'a' y 'z'...
		res = (((c - 'a') + (tolower(k) - 'a')) % alphasize) + 'a';//¿esto debiera ir en una función aparte?
		//hay que convertir acá la clave a minúscula, por si no lo fuera
	} else if (c >= 'A' && c <= 'Z'){
		//si está entre 'A' y 'Z' ...
		res = (((c - 'A') + (toupper(k) - 'A')) % alphasize) + 'A';//acá hay que convertir la clave a mayúscula, por si no lo fuera, si no, se puede dar la situación en que la clave está en minúscula pero el carácter en mayúscula y al sumarle a la mayúscula la minúscula se pierde la relación, no tienen que ver. Tal vez se puede resolver de otra manera...
	}
	return res;
}

void vigenere(string txt, string clave){

	//para cada caracter en txt codificarlo con el caracter de la clave correspondiente, ir variando el índice con el que accedés al caracter de la clave de modo que cuando el contador llegue a la longitud de la clave se resetee y vuelva a acceder a los caracteres del comienzo
	int txtlen = strlen(txt);
	int clavelen = strlen(clave);
	int j = 0; //índice para la clave
	for (int i = 0; i < txtlen; i++){
		//chequear si j supera la longitud de la clave y resetear en ese caso
		//si el caracter es alfabético
			//mostrar codificarUno(txt[i], clave[j])
			//incrementar j
		//si no es alfabético
			//mostrar txt[i]

		if(j >= clavelen){ //para volver al primer carácter de la clave
			j = 0;
		}

		if (isalpha(txt[i])){
			printf("%c", codificarUno(txt[i], clave[j]));
			j++; //pasar al siguiente caracter de la clave
		} else {
			printf("%c", txt[i]);
		}
	}
	printf("\n"); //terminar con un salto de línea
}

int main(int argc, string argv[]){

	//chequear si se recibió una clave válida por línea de comandos
	if (esClaveValida(argc, argv)){
		//pedir input para el plaintext
		string plaintext = get_string("plaintext: ");
		//mostrar el texto codificado
		printf("ciphertext: ");
		vigenere(plaintext, argv[1]);	
	} else {
		printf("ERROR: Debe incluir una clave alfabética.\n");
		return 1;
	}
	return 0;

/*
	//test codificarUno
	char c = get_char("character: ");
	char k = get_char("clave: ");
	printf("%c: %c\n", c, codificarUno(c, k));
*/

/*
	test de vigenere

	string txt = get_string("plaintext: ");
	string kw = get_string("clave: ");
	vigenere(txt, kw);
*/
}
