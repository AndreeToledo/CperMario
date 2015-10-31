 #include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


/*
Decidimos usar el siguiente texto para escribir el código.
Las dos excepciones que hicimos fueron el largo de las lineas
el cual pasa de 76 caracteres en algunos casos.
Y los corchetes van seguidos, en vez de en una linea nueva.
http://www.gnu.org/prep/standards/standards.pdf
*/
static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

void imprimirSprite (int valor){
	
	char sprites[10] = {'@', '#', '?', '0', '&', '*', '$', '|', 'o', '/' };

	switch (valor){
		case 0:
			printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, sprites[0]); //Cielo
			break;
		case 1:
		case 6:
			printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, sprites[0]); //Arbustos
			break;
		case 4:
			printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET, sprites[1]); //Suelo
			break;
		case 5:
		case 7:
			printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, sprites[1]); //Tubería
			break;
		case 8:
			printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET, sprites[1]); //Escaleras
			break;
		case 9:
			printf("%c", sprites[7]); //Asta Bandera
			break;
		case 10:
			printf("%c", sprites[9]); //Bandera
			break;
		case 11:
			printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET, sprites[1]); //Ladrillos
			break;
		case 12:
			printf(" "); //Imprime un espacio negro
			break;
		case 13:
			printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET, sprites[2]); //Cuadros de pregunta
			break;
		case 15:
			printf("%c", sprites[0]); //Nube
			break;
		case 16:
			printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, sprites[8]); //Punta Bandera
			break;
	}
}

int resultado_impacto(int sprite){
	int 	resultado = 0;

	if (sprite == 4 || sprite == 5 || sprite == 7 || sprite == 8 || sprite == 11 || sprite == 13)
	{
		resultado = 1;
	}

	printf("%i\n", resultado);
	return resultado;
}
int checar_colision(int posicioHorizontalMario, int posicionVerticalMario, char movimiento, int nivel[14][212]){
	int colision = 0;

	switch (movimiento){
		case 'w':
			if (resultado_impacto(nivel[posicioHorizontalMario][posicionVerticalMario]) == 1)
				colision = 1;
			break;
		case 'a':
			if (resultado_impacto(nivel[posicioHorizontalMario][posicionVerticalMario]) == 1)
				colision = 1;
			break;
		case 's':
			if (resultado_impacto(nivel[posicioHorizontalMario][posicionVerticalMario]) == 1)
				colision = 1;
				printf("%i\n", nivel[posicioHorizontalMario][posicionVerticalMario]);
			break;
		case 'd':
			if (resultado_impacto(nivel[posicioHorizontalMario][posicionVerticalMario]) == 1)
				colision = 1;
			break;
	}

	return colision;
}


void impresionMapa (int nivel[14][212], int j, int posicioHorizontalMario, int posicionVerticalMario, int posicionHorizontalMarioRelativa){
	int i, p;

	for (i = 0; i < 14; ++i)
	{
		for (p = 0; p < j; ++p)
		{
			if (p != posicionHorizontalMarioRelativa || i != posicionVerticalMario)
				imprimirSprite(nivel[i][p+posicioHorizontalMario-2]);
			else
				printf(ANSI_COLOR_RED "$" ANSI_COLOR_RESET);
		}
		printf("\n");
	}

	//printf("\n");

	/*for (i = 0; i < 14; ++i)
	{
		for (p = 0; p < j; ++p)
		{
			printf("%i", nivel[i][p]);
		}
		printf("\n");
	}
	*/
}

void salto(int posicioHorizontalMario, int posicionVerticalMario, int nivel1[14][212], int posicionHorizontalMarioRelativa){
	int i, j;

	for (i = 0; i < 5; ++i)
	{
		system ("clear");
		system ("cls");
		posicionVerticalMario--;
		impresionMapa (nivel1, 40, posicioHorizontalMario, posicionVerticalMario, posicionHorizontalMarioRelativa);
		for (int j = 0; j < 100000000; ++j)
		{
			/* code */
		}

	}

	for (i = 0; i < 5; ++i){
		system ("clear");
		system ("cls");
		posicionVerticalMario++;
		impresionMapa (nivel1, 40, posicioHorizontalMario, posicionVerticalMario, posicionHorizontalMarioRelativa);
		for (int j = 0; j < 100000000; ++j)
		{
		
		}

	}
}

void salto_atras(int posicioHorizontalMario, int posicionVerticalMario, int nivel1[14][212], int posicionHorizontalMarioRelativa){
	int i, j;

	for (i = 0; i < 2; ++i)
	{
		system ("clear");
		system ("cls");
		posicionVerticalMario--;
		posicionVerticalMario--;
		if(posicionHorizontalMarioRelativa > 0)
			posicionHorizontalMarioRelativa--;
		impresionMapa (nivel1, 40, posicioHorizontalMario, posicionVerticalMario, posicionHorizontalMarioRelativa);
		for (int j = 0; j < 100000000; ++j)
		{
			/* code */
		}

	}

	for (i = 0; i < 2; ++i){
		system ("clear");
		system ("cls");
		posicionVerticalMario++;
		posicionVerticalMario++;
		if(posicionHorizontalMarioRelativa > 0)
			posicionHorizontalMarioRelativa--;
		impresionMapa (nivel1, 40, posicioHorizontalMario, posicionVerticalMario, posicionHorizontalMarioRelativa);
		for (int j = 0; j < 100000000; ++j)
		{
		
		}

	}
}

void salto_adelante(int posicioHorizontalMario, int posicionVerticalMario, int nivel1[14][212], int posicionHorizontalMarioRelativa){
	int i, j;

	for (i = 0; i < 2; ++i)
	{
		system ("clear");
		system ("cls");
		posicionVerticalMario--;
		posicionVerticalMario--;
		posicioHorizontalMario++;
		if(posicionHorizontalMarioRelativa < 39)
			posicionHorizontalMarioRelativa++;
			posicionHorizontalMarioRelativa++;
		impresionMapa (nivel1, 40, posicioHorizontalMario, posicionVerticalMario, posicionHorizontalMarioRelativa);
		for (int j = 0; j < 100000000; ++j)
		{
			/* code */
		}

	}

	for (i = 0; i < 2; ++i){
		system ("clear");
		system ("cls");
		posicionVerticalMario++;
		posicionVerticalMario++;
		posicioHorizontalMario++;
		if(posicionHorizontalMarioRelativa < 39)
			posicionHorizontalMarioRelativa++;
		impresionMapa (nivel1, 40, posicioHorizontalMario, posicionVerticalMario, posicionHorizontalMarioRelativa);
		for (int j = 0; j < 100000000; ++j)
		{
		
		}

	}
}

int main()
{


	int 	i, j, posicioHorizontalMario = 2, posicionVerticalMario = 11, posicionHorizontalMarioRelativa = 2;
	char	movimiento, c;
	int 	accion;
	FILE*	mapa;
	mapa 	=fopen("Mapa.csv", "r");
	//int 	nivel1[14][212];

	int nivel1 [14][212] = {
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,15,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,11,11,11,11,11,11,11,0,0,0,11,11,11,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,0,0,0,11,11,11,0,0,0,0,11,13,13,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,0,0,0,0,0,0,0,0,9,0,0,0,0,11,11,11,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,11,13,11,13,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,13,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,11,13,0,0,0,0,13,0,0,13,0,0,13,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,11,11,0,0,0,0,0,0,8,0,0,8,0,0,0,0,0,0,0,0,0,0,8,8,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,11,11,13,11,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,0,0,0,0,0,0,0,0,9,0,0,0,0,11,11,11,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,5,7,0,0,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,8,8,0,0,0,0,0,0,0,0,8,8,8,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,9,0,0,0,11,11,11,11,11,0,0,0,0,0},
							{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,5,7,0,0,1,0,0,0,0,0,0,5,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,0,0,8,8,8,0,0,0,1,0,0,8,8,8,8,0,0,8,8,8,0,0,0,0,0,5,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,7,0,8,8,8,8,8,8,8,8,0,0,0,0,1,0,0,0,9,0,0,0,11,11,12,11,11,0,0,0,0,0},
							{0,1,1,1,0,0,0,0,0,0,0,6,6,6,0,0,1,0,0,0,0,0,0,6,0,0,0,5,7,0,0,0,0,0,0,0,0,5,7,0,0,6,6,0,0,5,7,0,1,1,1,0,0,0,0,0,5,7,0,6,6,6,0,0,1,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,6,6,6,0,0,1,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,6,6,8,8,8,8,0,1,1,1,8,8,8,8,8,0,0,8,8,8,8,0,0,1,0,5,7,0,0,0,6,0,0,0,0,0,0,0,0,0,0,5,7,8,8,8,8,8,8,8,8,8,0,0,0,1,1,1,0,0,8,0,0,0,11,11,12,11,11,0,0,0,0,0},
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
						 };

	/*//Obtencion de Mapa
	for (i = 0; i < 14; ++i)
	{
		for (j = 0; i < 212; ++j)
		{
			fscanf(mapa, "%i%c", &nivel1[i][j], &c);
			printf("%i\n", nivel1[i][j]);
		}
		fscanf(mapa, "\n");
	}*/

	
	//system("\"\"Perimetro20\\Dropbox\\Escuela\\FundamentosDeProgramacion\\ProyectoFinal\\SuperMarioBros.mp3");

	system("clear");
	//system("cls");
	printf("Cper Mario\n");
	printf("Instrucciones\n");
	printf("Oprime Q para ir  saltar hacia atras\n");
	printf("Oprime W para brincar\n");
	printf("Oprime E para saltar hacia adelante\n");
	printf("Oprime A para ir hacia atras\n");
	printf("Oprime D para ir hacia adelante\n");
	printf("Mario es el $ rojo\n");
	printf("Las @'s son de fondo\n");
	printf("Los #'s son solidos\n");
	printf("Oprime enter para comenzar\n\n");
	scanf("%*c");

	do{
		system ("clear");
		//system ("cls");


		impresionMapa(nivel1, 40, posicioHorizontalMario, posicionVerticalMario, posicionHorizontalMarioRelativa);

		movimiento = getch();

		switch (movimiento){

			case 'q':
				salto_atras(posicioHorizontalMario, posicionVerticalMario, nivel1, posicionHorizontalMarioRelativa);
				break;
			case 'w':
				salto(posicioHorizontalMario, posicionVerticalMario, nivel1, posicionHorizontalMarioRelativa);
				accion = 0;
				/*if (checar_colision(posicioHorizontalMario, posicionVerticalMario, movimiento, nivel1) == 1)
				{
					posicionVerticalMario++;
					accion = 0;
				}*/
				break;
			case 'e':
				salto_adelante(posicioHorizontalMario, posicionVerticalMario, nivel1, posicionHorizontalMarioRelativa);
				if (posicionHorizontalMarioRelativa < 31)
				{
					posicioHorizontalMario 				+= 5;
					posicionHorizontalMarioRelativa 	+= 5;
				}
				else{
					posicioHorizontalMario 				+= (39 - posicionHorizontalMarioRelativa);
					posicionHorizontalMarioRelativa 	+= (39 - posicionHorizontalMarioRelativa);
				}
				break;
			case 'a':
				posicioHorizontalMario--;
				if(posicionHorizontalMarioRelativa > 0)
					posicionHorizontalMarioRelativa--;
				accion = 1;
				/*if (checar_colision(posicioHorizontalMario, posicionVerticalMario, movimiento, nivel1) == 1)
				{
					posicioHorizontalMario++;
					accion = 1;
				}*/
				break;
			/*case 's':
				posicionVerticalMario++;
				accion = 2;*/
				/*if (checar_colision(posicioHorizontalMario, posicionVerticalMario, movimiento, nivel1) == 1)
				{
					posicionVerticalMario--;
					accion = 2;
				}*/
				break;
			case 'd':
				posicioHorizontalMario++;
				if (posicionHorizontalMarioRelativa < 39)
					posicionHorizontalMarioRelativa++;
				accion = 3;
				/*if (checar_colision(posicioHorizontalMario, posicionVerticalMario, movimiento, nivel1) == 1)
				{
					posicioHorizontalMario--;
					accion = 3;
				}*/
				break;
			default:
				break;
		}

	 } while (posicioHorizontalMario < 212 && posicioHorizontalMario > 0 && posicionVerticalMario < 14 && posicionVerticalMario >= 0);

	 fclose(mapa);

	return 0;
}