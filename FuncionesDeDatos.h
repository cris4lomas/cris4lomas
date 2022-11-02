<<<<<<< HEAD
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
=======
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

#endif
>>>>>>> 9eaae4970333a7ad57c6f30a78e8c2e4071682c0
