#include <stdio.h>
#include <cs50.h>

/*
Luhn’s algorithm, you can determine if a credit card number is (syntactically) valid as follows:

Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.

Add the sum to the sum of the digits that weren’t multiplied by 2.

If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

¿por qué es de este modo el algoritmo? ¿por qué funciona? ¿cuál es la relación entre estos pasos y un número de tarjeta de crédito válido?

*/

//long long obtenerNumero(){
	//¿hay que chequear si el input es un entero positivo?
//}


int sumaDigitos(int x){
	//guardar en una variable la suma de los dígitos
	//mientras x sea mayor que 0 dividirlo por 10 y sumar el resto a la variable suma,
	int suma = 0;
	while (x > 0){
		suma += x % 10; //obtengo y sumo el dígito a los anteriores
		x = x / 10; // actualizo x
	}
	return suma;
}


bool checksumLuhn(long long n){
//algoritmo de Luhn
/*
Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.

Add the sum to the sum of the digits that weren’t multiplied by 2.

If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
*/


/*

guardás en una variable la suma de los dígitos en índices pares de n
guardás en otra variable la suma de los dígitos en índices impares de multiplicados por 2 y separados a su vez en dígitos
sumás ambos valores
te fijás si el resultado es congruente módulo 10

vas contando además en i las vueltas, mientras n sea mayor que 0, dividí n por 10 y guardá por un lado el resultado en n, y si i es impar el resto en una variable y si i es par el resto en otra variable
*/

	int i = 0;
	long long sinmultiplicar = 0; //los dígitos en índices pares
	long long multiplicadosPorDos = 0; //los dígitos en índices impares
	int digito = 0;
	while ( n > 0){
		digito = n % 10;
		if (i % 2 == 0){ // si i es par
			sinmultiplicar += digito;
		} else {
		    multiplicadosPorDos += sumaDigitos(digito * 2);
		}
		n = n / 10;
		i++;
	}
	return (sinmultiplicar + multiplicadosPorDos) % 10 == 0; //devuelve si el resultado termina en 0
}

int digitos(long long n){
/* Devuelve la cantidad de dígitos de n. */
//Otra idea es convertir n a string y contar la longitud (pero en la semana 1 todavía no se habló de arrays y strings)
//Una idea es ir dividiendo (con enteros, sin decimales) por 10 y contando cuántas veces lo podés hacer hasta que obtenés 0 de parte entera, inclusive.
	
	//mientras n sea mayor que 0, dividir n por 10 y asignar el resultado a n, mientras contar cada vuelta.
	int d = 0;
	while (n > 0){
		n = n / 10; //supongo que hace la división entera, es decir sin decimales
		d++;
	}
	//n <= 0
	
	return d;
}

int primerosDe(int d, long long n) {
//devuelve los primeros d dígitos de n, desde la izquierda

	int dn = digitos(n); //y le vas restando 1 con cada vuelta que le sacás dígitos a n
	// dividir (división entera) n por 10 hasta quedarte con la misma cantidad de dígitos que x
	while (dn > d){ //mientras la cantidad de dígitos de n sea mayor que la cantidad de dígitos de x (d) seguí.
		n = n / 10; //acá le vas sacando de a un dígito a n.
		dn--;// en vez de esto podría calcular con cada vuelta los dígitos de n, pero me parece que de este modo no hace falta.
	}	
	return n; //acá estaría haciendo una conversión implícita de long long a int. y devuelve los primeros d dígitos de n
}

bool empiezaCon(long long n, int x){
	/* indica si n empieza con x */

	//una idea es convertir ambos a string y comparar los caracteres de x con los primeros de n.
	
	//otra, sin usar strings, averiguar la cantidad de dígitos de x. Obtener los primeros dx números de n, por ejemplo si dx es 2, obtener los primeros dos dígitos de n, de izquierda a derecha. Compararlos con x.
	return x == primerosDe(digitos(x), n);
}

bool esMastercard(long long n){
//se supone que n ya pasó el test Luhn y ahora chequea que tenga la longitud y que empiece como un número de mastercard.
	return 16 == digitos(n) && (empiezaCon(n, 51) || empiezaCon(n, 52) || empiezaCon(n, 53) || empiezaCon(n, 54) || empiezaCon(n, 55));
}

bool esAmex(long long n){
//se supone que n ya pasó el test Luhn y ahora chequea que tenga la longitud y que empiece como un número de AMEX.

	return 15 == digitos(n) && (empiezaCon(n, 34) || empiezaCon(n, 37));
}

bool esVisa(long long n){
//se supone que n ya pasó el test Luhn y ahora chequea que tenga la longitud y que empiece como un número de VISA.
	int len = digitos(n);
	return (16 == len || 13 == len) && empiezaCon(n, 4);
}



string validarNumero(long long n){
//usar el algoritmo de Luhn para verificar si es sintácticamente válido (checksum).
// y después, si no es inválido, ver si puede ser de mastercard, amex o visa, o si no es de ninguno, inválido.


// inicializo con inválido, y va a quedar así si no pasa el test de luhn o si no es ni mastercard ni amex ni visa

	string res = "INVALID";

	if (checksumLuhn(n)){
		if (esMastercard(n)){
			res = "MASTERCARD";
		} else if (esAmex(n)){
			res =  "AMEX";
		} else if (esVisa(n)){
			res = "VISA";
		}
	}
	return res;
}

int main(void)
{
	//pedir input
	//ojo que no tiene en cuenta el 0 adelante, por ejemplo 0987654321 lo toma como 987654321.
	long long cardNumber = get_long_long("Number: ");//supongo que el usuario ingresa números? ¿no tengo que testear si son positivos?

	//Decidir si el número es válido y mostrar el resultado
	printf("%s\n", validarNumero(cardNumber));

/*	
	//test de digitos
	printf("La cantidad de digitos de %lli es %i\n", cardNumber, digitos(cardNumber));
	
	//test de primerosDe
	printf("Los primeros %i digitos de %lli son %i\n", 2, cardNumber, primerosDe(2, cardNumber));

	//test de empiezaCon
	printf("%lli empieza con %i? %o\n", cardNumber, 51, empiezaCon(cardNumber, 51));
	printf("%lli empieza con %i? %o\n ", cardNumber, 4, empiezaCon(cardNumber, 4));
	printf("%lli empieza con %i? %o\n ", cardNumber, 37, empiezaCon(cardNumber, 37));
	printf("%lli empieza con %i? %o\n ", cardNumber, 34 ,empiezaCon(cardNumber, 34));

	//test de esMastercard, esVisa y esAmex
	printf("%lli es visa? %o\n", cardNumber, esVisa(cardNumber));
	printf("%lli es mastercard? %o\n", cardNumber, esMastercard(cardNumber));
	printf("%lli es amex? %o\n", cardNumber, esAmex(cardNumber));

*/

	// test sumadigitos
	//int numero = get_int("Entero: ");
	//printf("la suma de los dígitos de %i es %i\n", numero, sumaDigitos(numero));


	return 0;		
}

