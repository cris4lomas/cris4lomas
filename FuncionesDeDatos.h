#ifndef FUNCIONESDEDATOS_H
#define FUNCIONESDEDATOS_H

//Acá se declaran todas aquellas funciones que tengan como objetivo realizar operaciones con datos y archivos.

void ListarTxt(FILE * Arch);

void CrearBinario(FILE * Arch, const char * NombreDat);

void MigrarDatos(FILE * ArchOrgn, FILE * ArchDstn);

void ListarDat(FILE * Arch, int Metodo);

void AltaCompetidor(FILE * Arch);

void BuscarModifComp(FILE * Arch, int Metodo, char Opcion);

void ModificarCompetidor(FILE * Arch);

void BajaLogica(FILE * Arch);

void BajaFisica(FILE * ArchDat, FILE * ArchBajas, const char * NombreArchBajasFis);

void VerBajasFisicas(FILE * Arch);

#endif
