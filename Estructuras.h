#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

/*Este archivo de cabecera fue creado para aportarle a todos los archivos necesarios la estructura que se utiliza en los archivos de competidores.
	CAL 27/10/2022
*/

typedef struct Competidor{
	int NrOrd; //Número de orden
	int NrCorr; //Número de corredor
	int Dia;
	char Mes[4];
	int Anio;
	int Edad;
	char Pais[4];
	int Activo;
	float Tiempo;
} Competidor;

#endif
