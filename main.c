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
El siguiente programa registra los datos de distintos competidores (país, marcas de tiempo, número de competidor, etc...) en un archivo binario.
Además, permite realizar nuevos registros, modificar registros existentes y/o eliminarlos y llevar un control en un archivo aparte de los registros eliminados.

Los Archivos necesarios para su utilización son:

1) Menus.h y __Menus.c
2) FuncionesValidantes.h y __FuncionesValidantes.c
3) FuncionesDeDatos.h y __FuncionesDeDatos.c
4) Además necesita de librerías estándar como las que están incluídas en stdio.h, stdlib.h, string.h, ctype.h y time.h
5) Por último, necesita de un archivo llamado 'corredores_v1.csv', que incluye datos precargados de los competidores.

Autor: Cristian Alejandro Lomas (CAL)
Fecha de entrega: 10/11/2022
*/

int main(){
	
	//En primer lugar, defino los nombres de los archivos que se van a utilizar en todo el programa.
	const char * NombreTxt = {"corredores_v1.csv"};
	//El archivo 'corredores.dat', será un archivo binario que se puede crear desde el programa y en el cual se van a volcar todos los datos que operemos.
	const char * NombreDat = {"corredores.dat"};
	//El archivo 'bajas_fisicas.dat', será un archivo binario que se crea automáticamente al dar de 'BAJA FÍSICA' a un competidor. Registra todas las bajas físicas que se hayan realizado.
	const char * NombreBajasFis = {"bajas_fis.dat"};
	
	//La variable 'OpcionSel' se irá modificando a lo largo de todo el programa a medida que el usuario vaya seleccionando opciones entre los distintos menúes.
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
	
	//El siguiente ciclo se encarga de ejecutar casi infinitamente todas las opciones de menú disponibles, hasta que la opción elegida sea cero (0).
	//Todo el control de errores se realiza dentro de las distintas funciones de menú (Por ejemplo, que se ingrese un número menor a cero).
	//CAL 25/10/2022
	
	do{
		
		//Abro en cada ciclo el archivo .dat (luego lo cierro), para verificar siempre que se haya creado y/o que exista. CAL 25/10/2022
		FILE * ArchDat = fopen(NombreDat,"rb+");
		FILE * ArchBajasFis = fopen(NombreBajasFis,"rb+");
		
		//Si el archivo '.dat' no existe, solo se van a mostrar las opciones hasta la de crear ese archivo, de lo contrario se mostrará el resto de opciones. CAL 25/10/2022
		if(ArchDat == NULL) OpcionSel = MenuPrincipal(2,0);
		else OpcionSel = MenuPrincipal(10,0);
		
		//Elijo la función que voy a utilizar en función de la opción que se haya seleccionado. CAL 25/10/2022
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
			//La opción número 4 tiene un menú interno, para el cual también se utiliza la variable 'OpcionSel'
			//La variable 'OpcionSel' luego se restablece a 0 o 1, dependiendo la elección del usuario de si quiere volver al menú anterior o finalizar.
			//Ejecuto un ciclo interno para que la opción "volver al menú anterior" permita hacer eso y no redirija al menú principal. CAL 25/10/2022
			
			do{
				OpcionSel = MenuListarBinario();
				
				if(OpcionSel > 1){
					//Si la opción seleccionada es mayor a 1 (al rango máximo se indica dentro de la función 'ListarDat'), entonces significa que no seleccionó ni finalizar programa, ni volver al menú anterior.
					//Entonces llamamos a la función con el parámetro correspondiente al tipo de visualización de datos que deseamos:
					// 2: Ver todos los usuarios, 3: Ver usuarios activos, 4: Ver usuarios por país, 5: Ver usuarios por rango de tiempo.
					ListarDat(ArchDat, OpcionSel);
					//En la siguiente sentencia restablecemos el valor de 'OpcionSel' luego de listar todos los usuarios.
					//La idea es darle la opción al usuario de si quiere finalizar el programa, o volver al menú principal CAL 25/10/2022
					OpcionSel = MenuPrincipal(0,1);
				} else break;
				
			} while (OpcionSel == 1);
			
			break;
		
		case 5:
			AltaCompetidor(ArchDat);
			break;
			
		case 6:
			//Casi todo el caso 6 es idéntico al caso 4, excepto por el menú y la función que utiliza. La explicación de su uso está en el caso 4. CAL 25/10/2022
			do{
				//La opción número 6 tiene un menú interno al igual que la opción 4:
				OpcionSel = MenuBuscarComp();
				
				//La explicación del if es idéntica a la del caso 4:
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
