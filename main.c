#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Menus.h"
#include "FuncionesValidantes.h"
#include "FuncionesDeDatos.h"
#include "Estructuras.h"

/*
El siguiente programa registra los datos de distintos competidores (pa�s, marcas de tiempo, n�mero de competidor, etc...) en un archivo binario.
Adem�s, permite realizar nuevos registros, modificar registros existentes y/o eliminarlos y llevar un control en un archivo aparte de los registros eliminados.

Los Archivos necesarios para su utilizaci�n son:

1) Menus.h y __Menus.c
2) FuncionesValidantes.h y __FuncionesValidantes.c
3) FuncionesDeDatos.h y __FuncionesDeDatos.c
4) Adem�s necesita de librer�as est�ndar como las que est�n inclu�das en stdio.h, stdlib.h, string.h, ctype.h y time.h
5) Por �ltimo, necesita de un archivo llamado 'corredores_v1.csv', que incluye datos precargados de los competidores.

Autor: Cristian Alejandro Lomas (CAL)
Fecha de entrega: 10/11/2022
*/

int main(){
	
	//En primer lugar, defino los nombres de los archivos que se van a utilizar en todo el programa.
	const char * NombreTxt = {"corredores_v1.csv"};
	//El archivo 'corredores.dat', ser� un archivo binario que se puede crear desde el programa y en el cual se van a volcar todos los datos que operemos.
	const char * NombreDat = {"corredores.dat"};
	//El archivo 'bajas_fisicas.dat', ser� un archivo binario que se crea autom�ticamente al dar de 'BAJA F�SICA' a un competidor. Registra todas las bajas f�sicas que se hayan realizado.
	const char * NombreBajasFis = {"bajas_fis.dat"};
	
	//La variable 'OpcionSel' se ir� modificando a lo largo de todo el programa a medida que el usuario vaya seleccionando opciones entre los distintos men�es.
	int OpcionSel = -1;
	
	//Abro el archivo .csv, con el obetivo de verificar que existe en el mismo directorio que el programa.
	FILE * ArchTxt = fopen(NombreTxt,"r");
	
	//Control de error #1: Si el archivo "corredores_v1.csv" no existe en el mismo directorio que el programa, no se puede continuar y se finaliza.
	if(ArchTxt == NULL){
		printf("El archivo txt: '%s' no existe. El programa no puede continuar sin el mismo. Aseg%crese de inclu%cr el archivo en el mismo directorio en el que se encuentra este programa y vuelva a ejecutarlo.\n",NombreTxt,163,161);
		exit(-1);
	};
	
	//*****************************
	//INICIO DEL CICLO PRINCIPAL
	//*****************************
	
	//El siguiente ciclo se encarga de ejecutar casi infinitamente todas las opciones de men� disponibles, hasta que la opci�n elegida sea cero (0).
	//Todo el control de errores se realiza dentro de las distintas funciones de men� (Por ejemplo, que se ingrese un n�mero menor a cero).
	//CAL 25/10/2022
	
	do{
		
		//Abro en cada ciclo el archivo .dat (luego lo cierro), para verificar siempre que se haya creado y/o que exista. CAL 25/10/2022
		FILE * ArchDat = fopen(NombreDat,"rb+");
		FILE * ArchBajasFis = fopen(NombreBajasFis,"rb+");
		
		//Si el archivo '.dat' no existe, solo se van a mostrar las opciones hasta la de crear ese archivo, de lo contrario se mostrar� el resto de opciones. CAL 25/10/2022
		if(ArchDat == NULL) OpcionSel = MenuPrincipal(2,0);
		else OpcionSel = MenuPrincipal(10,0);
		
		//Elijo la funci�n que voy a utilizar en funci�n de la opci�n que se haya seleccionado. CAL 25/10/2022
		switch (OpcionSel){
		
		case 1:
			ListarTxt(ArchTxt);
			break;
			
		case 2:
			CrearBinario(ArchDat,NombreDat);
			break;
			
		case 3:
			MigrarDatos(ArchTxt, ArchDat);
			break;
			
		case 4:
			//La opci�n n�mero 4 tiene un men� interno, para el cual tambi�n se utiliza la variable 'OpcionSel'
			//La variable 'OpcionSel' luego se restablece a 0 o 1, dependiendo la elecci�n del usuario de si quiere volver al men� anterior o finalizar.
			//Ejecuto un ciclo interno para que la opci�n "volver al men� anterior" permita hacer eso y no redirija al men� principal. CAL 25/10/2022
			
			do{
				OpcionSel = MenuListarBinario();
				
				if(OpcionSel > 1){
					//Si la opci�n seleccionada es mayor a 1 (al rango m�ximo se indica dentro de la funci�n 'ListarDat'), entonces significa que no seleccion� ni finalizar programa, ni volver al men� anterior.
					//Entonces llamamos a la funci�n con el par�metro correspondiente al tipo de visualizaci�n de datos que deseamos:
					// 2: Ver todos los usuarios, 3: Ver usuarios activos, 4: Ver usuarios por pa�s, 5: Ver usuarios por rango de tiempo.
					ListarDat(ArchDat, OpcionSel);
					//En la siguiente sentencia restablecemos el valor de 'OpcionSel' luego de listar todos los usuarios.
					//La idea es darle la opci�n al usuario de si quiere finalizar el programa, o volver al men� principal CAL 25/10/2022
					OpcionSel = MenuPrincipal(0,1);
				} else break;
				
			} while (OpcionSel == 1);
			
			break;
		
		case 5:
			AltaCompetidor(ArchDat);
			break;
			
		case 6:
			//Casi todo el caso 6 es id�ntico al caso 4, excepto por el men� y la funci�n que utiliza. La explicaci�n de su uso est� en el caso 4. CAL 25/10/2022
			do{
				//La opci�n n�mero 6 tiene un men� interno al igual que la opci�n 4:
				OpcionSel = MenuBuscarComp();
				
				//La explicaci�n del if es id�ntica a la del caso 4:
				if(OpcionSel > 1){
					BuscarCompetidor(ArchDat, OpcionSel);
					OpcionSel = MenuPrincipal(0,1);
				} else break;
				
			} while(OpcionSel == 1);
			
			break;
		
		case 7:
			ModificarCompetidor(ArchDat);
			break;
			
		case 8:
			BajaLogica(ArchDat);
			break;
			
		case 9:
			BajaFisica(ArchDat, ArchBajasFis, NombreBajasFis);
			break;
			
		case 10:
			VerBajasFisicas(ArchBajasFis);
			break;
		}
		
		//Para evitar posibles errores, cierro los archivos antes del fin de cada ciclo. CAL 25/10/2022
		fclose(ArchDat);
		fclose(ArchBajasFis);
		
	} while (OpcionSel > 0);
	
	fclose(ArchTxt);
	
	return 0;
}
