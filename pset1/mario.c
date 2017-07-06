#include <stdio.h>
#include <cs50.h>

int pedirAltura(){
	int altura = -1;//para que permita el 0, por la condición, así entra al menos 1 vez al ciclo.
	int intentos = 0;
	//está mal esta condición: altura < 1 || altura > 23 || intentos < 5
	while ((altura < 0 || altura > 23) && intentos < 5){ //¿tendría que chequear el tipo de altura?
		intentos++;
		altura = get_int("Height: (mayor que 0, menor que 23): ");
		//intentos++;
		//printf("intentos: %i\n", intentos);
		/* ¿ por qué no cuenta como intentos cuando ingresás algo distinto de un entero? 
		Porque no sale nunca de get_int() a menos que entres un entero, así sólo cuenta cuando ingresaste enteros.
		*/
	}
	//obtuviste un entero positivo menor que 23 y mayor que 0.
	//printf("intentos: %i\n", intentos);
	if (intentos >= 5){
		return -1;
	} else {
		return altura;
	}
}

void generarEscalon(int i, int offset){
//i es el número del escalón
//offset es la cantidad de espacios necesarios para alinear el escalón a la derecha

//como no sé cómo concatenar cadenas, porque de la forma habitual en otros lenguajes no me deja...
// hice un loop para generar los espacios necesarios para la alineación a la derecha
// y después otro loop para generar la cantidad de hashtags requeridos por el escalón
//finalmente agregué el carácter de nueva línea.

//ojo que el escalón 1 es ##

	for ( int j = offset - i; j > 0 ; j-- ){
	   printf(" ");	
	}


//j empieza en 0, y llega hasta i+1 y cuando j es igual a i + 1 no entra en el loop.
// de esta manera, para i igual a 1, se genera el escalón "##" y así
	for ( int j = 0; j < i + 1; j++ ){
	   printf("#");	
	}
	printf("\n");

}

void generarEscalera(int altura){
		for (int i = 1; i <= altura; i++){
			generarEscalon(i, altura);
		}
}

int main(void) {
	int altura = pedirAltura();
    //printf("Altura: %i\n", altura);
	if (altura == -1){
		printf("no se ingresó una altura adecuada");
	} else {
		generarEscalera(altura);
	}
}
