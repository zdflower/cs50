#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>


//revisar a ver si funciona lo mejor posible
//ver si realmente sale una vez que encontró el password
//NO TERMINA UNA VEZ QUE ENCUENTRA EL PASSWORD

//ver cómo escribir una versión que use arrays de char, o string, cómo ir agregando caracteres... y que crack devuelve una string con el password

//para comparar dos strings usar strcmpr o similar de la biblioteca string.h

///////////////////////////////////
//¿cómo devolver un array creado localmente? el problema es que creás una variable para un array de algo y es un puntero y después devolvés eso pero cuando salís de la función esa variable local ya no está más... algo así vimos en un taller en algoritmos 2 en c++, no me acuerdo cómo se resolvía, ¿tenía que ver con las referencias? ¿cómo es en c?
/////////////////////////////////

/*
CÓMO GENERO UN ARRAY CON LOS CARACTERES QUE VOY COMBINANDO
CÓMO OBTENGO UN ARRAY DE 2 CHAR A PARTIR DEL INPUT POR LÍNEA DE COMANDOS
CÓMO CONCATENO DOS ARRAY DE CHAR, O CÓMO AGREGO UN CHAR A UN ARRAY DE CHAR
*/


bool esElPassword(string p, string hash){
	//printf("entro en la función esElPassword\n");
	
	char salt[3];
	salt[0] = hash[0];
	salt[1]= hash[1]; 
	salt[2] = '\0';
	
    char* hash_p = crypt(p, salt);
	//printf("hash_p: %s\n", hash_p);
	
	//printf("%s == %s: %o\n", hash_p, hash, (strcmp(hash_p, hash) == 0));
	
	if (strcmp(hash_p, hash) == 0){
		//printf("son iguales\n");
		return true;
	}
	//printf("son distintos\n");
	return false;
}



/* ME PARECE QUE EL PROBLEMA ESTÁ ACÁ, PORQUE ESELPASSWORD DEVUELVE BIEN QUE SON DISTINTOS
PERO NO LO ENCUENTRA Y NO PUEDE SER, DEBO HABER MODIFICADO ALGO RESPECTO DE LA FUNCIÓN QUE GENERABA TODOS LOS PASSWORDS DE 1 A 4 CARACTERES YA QUE ESA FUNCIÓN ESTABA BIEN ...
*/

/*
estaba mal que los if encerraran los for anidados, así como no se cumplía que para el primer caso, de passwords de 1 caracter, nunca llegaba a los otros for...

*/
void crack(char p[], string hash){
	//printf("entro en la función crack\n");
//p tiene tamaño 5
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


/* voy a generar todas las claves de 1 y 2 caracteres y las voy a mostrar por pantalla 
	después voy a pensar cómo reescribirlo para que sea más legible y "mantenible" y disminuir la redundancia
	
	//se podría poner en una función ¿recursiva? ¿conviene? ¿es necesario? el loop con el chequeo de si es alfabético y mostrar ... no sé
	//si no, pensar de qué otro modo más claro se puede hacer, cuáles serían las ventajas y desventajas, por ejemplo, tal vez se pueda hacer más modularizado con funciones pero también aumentando la complejidad algorítmica (o el tiempo de ejecución o la cantidad de operaciones), o por otro lado, más feo de ver y leer, pero se hace una sóla vez cada cosa y entonces la cantidad de operaciones es menor.
*/
	for (char c = 'A'; c <= 'z'; c++){
		//cómo ir marcando el progreso de la búsqueda?
	//filtrar los que no son alfabéticos y están entre 'Z' y 'a'
		//passwords de un carácter
		//char p[5]; //quiero que tenga 4 caracteres
		//parece que el último tiene que ser '\0'
		p[0] = c;
		p[1] = '\0';
		if(isalpha(c) && esElPassword(p, hash)){//ACÁ ESELPASSWORD TENDRÍA QUE TOMAR UNA CADENA Y YO LE TENDRÍA QUE PASAR UNA CADENA DE UN CARACTER
			//printf("%c\n", c);
			printf("%s\n", p);
			break;
		}
		for (char d = 'A'; d <= 'z'; d++){
			//passwords de dos caracteres
			//acá tengo que agregarle un carácter a p y después pasarle a eselpassword una subcadena con los dos primeros caracteres de p
			p[1] = d;
			p[2] = '\0';
			if (isalpha(d) && esElPassword(p, hash)){ //escribo la subcadena en la notación de python incluyendo el primer índice, excluyendo el último
				//printf("%c%c\n", c, d);
				printf("%s\n", p);
				break;
			}
			for (char e = 'A'; e <= 'z'; e++){
				//passwords de tres caracteres
				p[2] = e;
				p[3] = '\0';
				if (isalpha(e) && esElPassword(p, hash)){
					//printf("%c%c%c\n", c, d, e);
					printf("%s\n", p);
					break;
				}
				for (char f = 'A'; f <= 'z'; f++){
					//passwords de 4 caracteres
					p[3] = f;
					p[4] = '\0';
					if (isalpha(f) && esElPassword(p, hash)){
						//printf("%c%c%c%c\n", c, d, e, f);
						printf("%s\n", p);
						break;
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

      char p[5];
      crack(p, argv[1]);

/* 
	printf("%i\n", strcmp("50pe4e2XTIS/g", "50fkUxYHbnXGw")); //esto, correctamente, devuelve 1, no son iguales
	//¿por qué en la función esElPassword el resultado es siempre 0? ¿qué problema tiene?
    printf("%o\n", esElPassword("AA", "50fkUxYHbnXGw"));
*/	

/*
	string hash = "50fkUxYHbnXGw";
	string p = "rofl";
	char salt[3];
	salt[0] = hash[0];
	salt[1]= hash[1]; 
	salt[2] = '\0';
	
    char* hash_p = crypt(p, salt);
	printf("hash_p: %s\n", hash_p);
	int res = strcmp(hash_p, hash);
	//printf ("res: %i\n", res);
	printf("%s == %s: %o\n", hash_p, hash, res == 0);

*/

/*
//res == 0 me da 0, PORQUE 0 ES falso Y TRUE ES 1
 
	bool coso = 1 == 1;
	
	printf("%i == %i : %o", 1, 1, coso);
*/
}

//compilar con
// clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow crack.c -lcrypt -lcs50 -lm -o crack


/*
Resultados obtenidos:

		hash				password				
andi:50.jPgLzVirkc			hi
jason:50YHuxoCN9Jkc			JH
malan:50QvlJWn2qJGE			NOPE
mzlatkova:50CPlMDLT06yY		ha
patrick:50WUNAFdX/yjA		Yale
rbowden:50fkUxYHbnXGw       rofl
summer:50C6B0oz0HWzo		FTW
stelios:50nq4RV/NVU0I		ABC
wmartin:50vtwu4ujL.Dk		haha
zamyla:50i2t3sOSAZtk		lol



*/
