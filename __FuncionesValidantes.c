#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int ValidaFecha(char Fecha[], char Separador){};
int ValidaNumero(char Numero[]){};
int ValidaAbc(char Texto[]){};

int ValidaCSV(FILE * Arch, char Delimitador){
	/*Esta funci�n se cre� con el objetivo de verificar que un archivo
	de extensi�n .CSV tenga el delimitador que necesitemos.
	Devuelve 1 si el delimitador se encuentra en el archivo.
	Devuelve 0 si NO se encuentra el delimitador en el archivo.
	La funci�n devuelve -1 si el archivo es NULL.
		CAL 27/10/2022
	*/
	
	if(Arch == NULL) return -1;
	
	//La variable Flag indicar� la presencia del delimitador. CAL 27/10/2022
	int Flag = 0;
	//La siguiente variable se encargar� de almacenar al menos 1 l�nea para verificar la inclusi�n del delimitador. CAL 27/10/2022
	char LineaDePrueba[100] = {" "};
	
	//Posicionamos el puntero al inicio del archivo .CSV:
	rewind(Arch);
	fgets(LineaDePrueba,100,Arch);
	
	for (int i = 0; i < 100; i++){
		if(LineaDePrueba[i] == Delimitador){
			Flag = 1;
			break;
		}
	}
	//Volvemos a posicionar el puntero al inicio del archivo:
	rewind(Arch);
	
	return Flag;
};
