#ifndef FUNCIONESVALIDANTES_H
#define FUNCIONESVALIDANTES_H

//Ac� se declaran todas aquellas funciones que tengan como objetivo validar alg�n tipo de dato.

int ValidaFecha(char Fecha[], char Separador);
int ValidaNumero(char Numero[]);
int ValidaAbc(char Texto[]);
int ValidaCSV(FILE * Arch, char Delimitador);

#endif
