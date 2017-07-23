/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

// auxiliares: 
int llenarFila(int, int, int board[DIM_MAX][DIM_MAX]);
void invertir1y2(int board[DIM_MAX][DIM_MAX], int f, int c);
bool esPar(int n);
void buscarPos(int tile, int board[DIM_MAX][DIM_MAX], int pos[2]);
void buscar(int tile, int fila, int board[DIM_MAX][DIM_MAX],  int pos[2]);
bool bordeaCero(int pos[2], int board[DIM_MAX][DIM_MAX], int posCero[2]);
bool ceroADerecha(int board[DIM_MAX][DIM_MAX], int pos[2]);
bool ceroAIzquierda(int board[DIM_MAX][DIM_MAX], int pos[2]);
bool ceroAbajo(int board[DIM_MAX][DIM_MAX], int pos[2]);
bool ceroArriba(int board[DIM_MAX][DIM_MAX], int pos[2]);
bool ceroA(int board[DIM_MAX][DIM_MAX], int pos[2], int f, int c);
bool perteneceAlTablero(int f, int c, int d);
void swapPos(int posA[2], int posB[2], int board[DIM_MAX][DIM_MAX]);//me parece que no hace falta que pase el tablero, puedo acceder directamente, está en el scope global.
bool filaOK(int f, int k);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int(" ");
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int k = d*d - 1;
    int fila;
    for (fila = 0; fila < d; fila++){
    	k = llenarFila(fila, k, board);
    	//eprintf("k: %i\n", k);
    }
}

void invertir1y2(int board[DIM_MAX][DIM_MAX], int f, int c){
		board[f][c] = 1;
		board[f][c+1] = 2;
}

bool esPar(int n){
	return n % 2 == 0;
}

/*
gcc -ggdb3 -O0 -std=c11 -Wall -Werror -o fifteen fifteen.c -lcs50 -lm
fifteen.c: In function ‘init’:
fifteen.c:165:6: error: passing argument 3 of ‘llenarFila’ from incompatible pointer type [-Werror]
      k = llenarFila(fila, k, board);
      ^
fifteen.c:39:5: note: expected ‘int **’ but argument is of type ‘int (*)[9]’

¿y si en vez de pasarle todo board, le paso la fila?
*/
//pensar un poco más y mejorar esta función
int llenarFila(int f, int k, int board[DIM_MAX][DIM_MAX]){
	for (int col = 0; col < d; col++){
		//si k no es menor o igual que 0 y si d no es par: asignar k a board[f,col]
		// si k es 2 y si d es par: asignar 1 a board[f,c] y 2 a board[f, c+1] y salir del loop
		if (k == 2 && esPar(d)){
			invertir1y2(board, f, col);
			k = k - 2;
			break;
		} //else if (f == d - 1 && col == d - 1) {
	    	//poner _ en la última celda
			//board[f][col] = 0;//¿el carácter se puede tomar como int?
		//} 
/////////¿cómo es que se llega a poner un 0 en la última celda?////////
		else {
			board[f][col] = k;
			//eprintf("fila, columna: %i,%i\n", f, col);
			k--;
		}
	}
	return k;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    /* para cada celda de board mostrarla por pantalla, con el espaciado adecuado*/
    
           for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (board[i][j] < 10){
                	//agregar un espacio
                	printf(" ");
                }
                if (board[i][j] == 0){
	                printf("_");
                } else {
                    printf("%i", board[i][j]);
                }

                if (j < d - 1)
                {
                    printf("|");
                }
            }
            printf("\n");
        } 
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
 
 //me falta que mueva la ficha si es posible
bool move(int tile)
{
    // hay que buscar en qué posición del tablero está la ficha. Acá se usa búsqueda lineal porque se van desordenando las fichas con los movimientos.
    //para guardar las posiciones
    int pos[2]; //se lo voy a pasar a la función de búsqueda que va a modificarlo y poner en pos[0] la fila y en pos[1] la columna donde está tile.
    //tengo que buscar en todo el tablero, pero puedo hacerlo por fila
    buscarPos(tile, board, pos);
    
    int posCero[2];
    
    bool res = bordeaCero(pos, board, posCero);
    //no alcanza con saber si bordeaCero, sino hacia dónde moverse si se puede
    // necesito que bordeaCero también guarde dónde está el cero
    
    if (res){ //si bordeaCero, entonces mover la ficha ahí
    	//hacer un swap entre pos y posCero
/*    	eprintf("pos: %i, %i\n", pos[0], pos[1]);*/
/*   	   	eprintf("posCero: %i, %i\n", posCero[0], posCero[1]);*/
/*   	   	eprintf("ficha: %i\n", board[pos[0]][pos[1]]);*/
/*   	   	eprintf("0: %i\n", board[posCero[0]][posCero[1]]);   	   	*/
    	swapPos(pos, posCero, board);
    }
    
    return res;
}

void buscarPos(int tile, int board[DIM_MAX][DIM_MAX], int pos[2]){
	//búsqueda lineal por cada fila, usar una función que busque en una fila y que termine la búsqueda cuando encuentre tile
	for (int f = 0; f < d; f++){
		buscar(tile, f, board, pos); // tal vez el board no hace falta pasarlo, así como tampoco paso d...
	}
}

void buscar(int tile, int fila, int board[DIM_MAX][DIM_MAX],  int pos[2]){
	for (int c = 0; c < d; c++){
		if (board[fila][c] == tile){
			pos[0] = fila;
			pos[1] = c;
		}
	}
}

bool bordeaCero(int pos[2], int board[DIM_MAX][DIM_MAX], int posCero[2]){
    //ahora tengo que chequear si arriba o abajo o a la izquierda o a la derecha de la posición f,c está el 0
    //ojo que tal vez si f,c está en la primera fila no tiene sentido preguntar por arriba, y si está en la primera columna no tiene sentido preguntar por la izquierda, y si está en la última fila no preguntar por abajo y si está en la última columna no preguntar por la derecha. Así:
    // Si f es 0 no preguntar por f - 1
    // si f es d - 1 no preguntar por f+1
    // si c es 0 no preguntar por c - 1
    // si c es d - 1 no preguntar por c + 1
    
    bool res;

//esto iría bien con un switch?

/*ENCUENTRA MAL LA POSICIÓN DEL CERO*/

    if (ceroAbajo(board, pos)){
    	res = true;
    	posCero[0] = pos[0] + 1;
    	posCero[1] = pos[1];
    } else if (ceroArriba(board, pos)){
    	res = true;
    	posCero[0] = pos[0] - 1;
    	posCero[1] = pos[1];
    } else if (ceroADerecha(board, pos)){
    	res = true;
    	posCero[0] = pos[0];
    	posCero[1] = pos[1] + 1;
    } else if (ceroAIzquierda(board, pos)){
    	res = true;
    	posCero[0] = pos[0];
    	posCero[1] = pos[1] - 1;
    } else {
	    res = false;
    }
    
    return res;
}

//ESTABAN MAL LAS FUNCIONES CEROADERECHA, ETC.

bool ceroADerecha(int board[DIM_MAX][DIM_MAX], int pos[2]){
//	if (hayDerecha(pos)){
//		return board[pos[0] + 1][pos[1]] == 0; //se fija si a la derecha de pos está vacío.
//	}
	return ceroA(board, pos, pos[0], pos[1] + 1);
}

bool ceroAIzquierda(int board[DIM_MAX][DIM_MAX], int pos[2]){
	return ceroA(board, pos, pos[0], pos[1] - 1);
}

bool ceroAbajo(int board[DIM_MAX][DIM_MAX], int pos[2]){
	return ceroA(board, pos, pos[0] + 1, pos[1]);
}

bool ceroArriba(int board[DIM_MAX][DIM_MAX], int pos[2]){
	return ceroA(board, pos, pos[0] - 1, pos[1]);
}

bool ceroA(int board[DIM_MAX][DIM_MAX], int pos[2], int f, int c){//le pasás la posición de la ficha y la posición donde querés chequear si está el cero, además del tablero
	//si f,c pertenece al board
	if (perteneceAlTablero(f, c, d)){ //chequea si f y c están dentro de las dimensiones del tablero
		return board[f][c] == 0;		
	}
	return false;
}

bool perteneceAlTablero(int f, int c, int d){
	//si f es mayor o igual que 0 y menor que d y c es mayor o igual que 0 y menor que d, entonces, f,c está dentro del tablero
	return (f >= 0 && f < d && c >= 0 && c < d);
}


void swapPos(int posA[2], int posB[2], int board[DIM_MAX][DIM_MAX]){
	//modifica board
	int ficha = board[posA[0]][posA[1]]; //guardo la ficha que está en A
	//escribo en A la ficha que está en posB del board
	//finalmente escribo en posB del board la ficha guarda antes
	board[posA[0]][posA[1]] = board[posB[0]][posB[1]];
	board[posB[0]][posB[1]] = ficha;
	//eprintf("ficha: %i\n", ficha); //¿por qué si ficha es 2, no queda modificada en el tablero? Revisar.
	//eprintf("board[posB]: %i\n", board[posB[0]][posB[1]]); //¿por qué si ficha es 2, no queda modificada en el tablero? Revisar.
	//queda modificada la posA pero no la posB, en algún momento lo que se escribe acá en posB del tablero en otro lado se sobreescribe con un 0.
//	NO ENTIENDO
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
 //el plan es similar a init pero en vez de llenar fila tenés que chequear que todas las filas estén ok, y vas avanzando el k afuera, con cada vuelta k suma d y se lo seguís pasando a chequearFila pero no devolvés en chequearFila el valor de k sino si la fila estaba ok.
 int k = 1;
 for (int f = 0; f < d; f++){
	if (!filaOK(f, k)){
		return false;
	}
	k = k + d;
 }
 //si llegaste acá es porque todas las filas estaban ok, entonces ganaste
 return true;
}

bool filaOK(int f, int k){
	bool res = true;
//chequea para cada celda c de board[f][c] si contiene a la ficha k, con k variable
	for (int c = 0; c < d; c++){
	//si la celda es la última de abajo a la derecha chequear si hay un 0
		if (f == d-1 && c == d -1){
			res = res && (board[f][c] == 0);
		} else {
			res = res && (board[f][c] == k);
		}
		k++;
	}
	return res;
}
