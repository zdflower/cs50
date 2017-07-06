#include <cs50.h>
#include <stdio.h>

int calcularBotellas(int min){
	return 12 * min;
}

int main(void){
	int minutos = get_int("Minutos: ");
	printf("Botellas: %i\n", calcularBotellas(minutos));
}
