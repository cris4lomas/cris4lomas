#ifndef FUNCIONESDEDATOS_H
#define FUNCIONESDEDATOS_H

//Acá se declaran todas aquellas funciones que tengan como objetivo realizar operaciones con datos y archivos.

void ListarTxt(char * NArch);

void CrearBinario(const char * NombreDat);

void MigrarDatos(char * NArchOrg, char * NArchDst);

void ListarDat(char * NArch, int Metodo);

void AltaCompetidor(char * NArch);

void BuscarModifComp(char * NArch, int Metodo, char Opcion);

void BajaLogica(char * NArch);

void BajaFisica(char * NArchDAT, const char * NombreArchBajasFis);

#endif
