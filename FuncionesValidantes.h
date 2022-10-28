#ifndef FUNCIONESVALIDANTES_H
#define FUNCIONESVALIDANTES_H

//Acá se declaran todas aquellas funciones que tengan como objetivo validar algún tipo de dato.

int ValidaFecha(char Fecha[], char Separador);
int ValidaNumero(char Numero[]);
int ValidaAbc(char Texto[]);
int ValidaCSV(FILE * Arch, char Delimitador);

#endif
