#include <stdio.h>
#include <cs50.h>
#include <math.h>

float cualEsElVuelto() {
	float vuelto = get_float("¿Cuál es el vuelto? ");
	while (vuelto < 0){
		vuelto = get_float("Debe ser una cantidad positiva. ¿Cuál es el vuelto? ");
	}
	//vuelto >= 0
	return vuelto;
}

int cuantasDe(int moneda, int vuelto){
 	int cant = 0;
	/*
	quiero chequear si el vuelto es mayor que moneda, para seguir entrando al loop y restando.
	*/
	
	while (vuelto - moneda >= 0 ){
		vuelto -= moneda;
		cant++;
	}
	//vuelto < moneda
	return cant;
}

int minimoMonedas(float vuelto){
    int dinero = round(vuelto * 100);//si no, hacía un redondeo para abajo, con round, en cambio, redondea al entero más cercano.
	//printf("Dinero: %i\n", dinero);
	int deVeinticinco = cuantasDe(25, dinero);
	//printf("De 25: %i\n", deVeinticinco);
	dinero -= deVeinticinco * 25;
	//printf("Vuelto restante: %i\n", dinero);
	int deDiez = cuantasDe(10, dinero);
	//printf("De 10: %i\n", deDiez);
	dinero -= deDiez * 10;
	//printf("Vuelto restante: %i\n", dinero);
	int deCinco = cuantasDe(5, dinero);
	//printf("De 5: %i\n", deCinco);
	dinero -= deCinco * 5;
	//printf("Vuelto restante: %i\n", dinero);
	int deUno = cuantasDe(1, dinero);
	//printf("De 1: %i\n", deUno);
	return deVeinticinco + deDiez + deCinco + deUno;
}

int main(void)
{
	//pedir input
	float vuelto = cualEsElVuelto();

	//calcular y mostrar la cantidad de monedas a devolver
	printf("%i\n", minimoMonedas(vuelto));


	//tests
	//printf("%f - %f: %f", 0.41 - 0.25 - 0.1 - 0.05, 0.01, 0.41 - 0.25 - 0.1 - 0.05 - 0.01);
	//printf("%i\n", cuantasDe(0.25, vuelto));
	//printf("%i\n", cuantasDe(0.10, vuelto - 0.25));
	//printf("%i\n", cuantasDe(0.05, vuelto - 0.25 - 0.10));
	//printf("%i\n", cuantasDe(0.01, 0.41 - 0.25 - 0.10 - 0.05));
	
}
