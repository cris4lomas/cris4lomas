#ifndef FUNCIONESVALIDANTES_H
#define FUNCIONESVALIDANTES_H

//Acá se declaran todas aquellas funciones que tengan como objetivo validar algún tipo de dato.

void ObtenerStrFecha(char Fecha[]);

int ValidaNumConDec(char Numero[]);

int ValidaNumSinDec(char Numero[]);

int ValidaAbc(char Texto[]);

int ValidaCSV(FILE * Arch, char Delimitador);

int ValidaFecha(char Fecha[]);

int ConvertirMesAString(int Mes, char CharMes[]);

int ExtraerDeFecha(char Fecha[],char DatoAExtraer, char Separador);

#endif
