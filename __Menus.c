#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//El presente archivo registra todas las funciones que crean todos los menús que se utilizan en el registro de competidores. CAL 25/10/2022
//La variable "OpcionSel", incluida en cada una de las funciones de menú, representa la opción elegida por el usuario y es la que se retorna al llamado. CAL 25/10/2022
//La variable "OpMaximas", incluida en cada una de las funciones de menú, representa la cantidad máxima de opciones que contiene el menú en cuestión. CAL 25/10/2022


int MenuPrincipal(int MaxOpcionVisible, int MenuDescendiente){
	//El siguiente menú es el que se utiliza en casi todos los ámbitos de la aplicación, es el primero que se muestra.
	//El parámetro "MaxOpcionVisible", determina hasta qué opción se va a visualizar (no puede ser menor a 1).
	//El parámetro "MenuDescendiente", determina si es un menú descendiente: 0 indica FALSO, no es menú descendiente. 1 indica VERDADERO, es menú descendiente.
	//Este menú descendiente solo se limitará a mostrar las opciones "Salir del programa" y "Volver al menú anterior"
	//Si está en 1 el valor de "MenuDescendiente", el valor de "MaxOpcionVisible" es redundante, porque siempre se convierte a 2.
	
	//CAL 25/10/2022
	
	int OpcionSel = -1;
	int OpMaximas = 10;
	
	//Limito las opciones en caso de que el menú sea descendiente:
	if(MenuDescendiente == 1) MaxOpcionVisible = 1;
	
	//Las siguientes dos validaciones verifican que desde el código fuente no se le esté pasando mal algún parámetro. CAL 25/10/2022
	if(MenuDescendiente != 0 && MenuDescendiente != 1) return OpcionSel;
	if(MaxOpcionVisible > OpMaximas || MaxOpcionVisible < 1) return OpcionSel;
	
	//****************
	//IMPRIMO EL MENÚ
	//****************
	
	printf("\n0) Salir del programa.");
	//Si es menú descendiente:
	if(MenuDescendiente == 1) printf("\n1) Volver al men%c anterior.",163);
	//Si NO es menú descendiente:
	if(MenuDescendiente == 0) printf("\n1) Listar archivo de texto.");
	if(MaxOpcionVisible > 1) printf("\n2) Crear archivo cifrado.");
	if(MaxOpcionVisible > 2) printf("\n3) Migrar datos entre archivos.");
	if(MaxOpcionVisible > 3) printf("\n4) Listar archivo cifrado.");
	if(MaxOpcionVisible > 4) printf("\n5) Dar ALTA a competidor.");
	if(MaxOpcionVisible > 5) printf("\n6) Buscar competidor.");
	if(MaxOpcionVisible > 6) printf("\n7) Modificar competidor.");
	if(MaxOpcionVisible > 7) printf("\n8) Dar BAJA L%cGICA a competidor.", 224);
	if(MaxOpcionVisible > 8) printf("\n9) Dar BAJA F%cSICA a competidor.", 214);
	if(MaxOpcionVisible > 9) printf("\n10) Ver lista de bajas f%csicas.",161);
	
	//**************************************
	//SOLICITO Y VALIDO LA OPCIÓN INGRESADA
	//**************************************

	printf("\n\nIngrese una opci%cn:\n", 162);
	
	do{
		scanf("%d", &OpcionSel);
		fflush(stdin);
		printf("\n");
		
		if(OpcionSel < 0 || OpcionSel > MaxOpcionVisible)
			printf("\nHa seleccionado una opci%cn err%cnea. Ingrese un n%cmero mayor o igual a 0 y menor o igual %d: \n", 162,162,163,MaxOpcionVisible);
		
	} while (OpcionSel < 0 || OpcionSel > MaxOpcionVisible);

	return OpcionSel;
}


int MenuListarBinario(){
	//El presente menú representa las opciones a elegir por el usuario al seleccionar la opción "Listar archivo cifrado" desde el menú principal. CAL 25/10/2022
	
	int OpcionSel = -1;
	int OpMaximas = 5;
	
	//****************
	//IMPRIMO EL MENÚ
	//****************
	
	printf("\n0) Salir del programa");
	printf("\n1) Volver al men%c principal",163);
	printf("\n2) Ver todos los usuarios (activos e inactivos)");
	printf("\n3) Ver usuarios activos");
	printf("\n4) Ver por pa%cs", 161);
	printf("\n5) Ver por rango de tiempo");
	
	//**************************************
	//SOLICITO Y VALIDO LA OPCIÓN INGRESADA
	//**************************************
	
	printf("\n\nIngrese una opci%cn:\n", 162);
	
	do{
		scanf("%d", &OpcionSel);
		fflush(stdin);
		printf("\n");
		
		if(OpcionSel < 0 || OpcionSel > OpMaximas)
			printf("\nHa seleccionado una opci%cn err%cnea. Ingrese un n%cmero mayor o igual a 0 y menor o igual %d: \n", 162,162,163,OpMaximas);
		
	} while (OpcionSel < 0 || OpcionSel > OpMaximas);
	
	return OpcionSel;
}


int MenuBuscarComp(){
	//El presente menú representa las opciones a elegir por el usuario al seleccionar la opción "Buscar competidor" desde el menú principal. CAL 25/10/2022
	
	int OpcionSel = -1;
	int OpMaximas = 3;
	
	//****************
	//IMPRIMO EL MENÚ
	//****************
	
	printf("\n0) Salir del programa");
	printf("\n1) Volver al men%c principal",163);
	printf("\n2) Buscar por n%cmero de orden", 163);
	printf("\n3) Buscar por n%cmero de corredor", 163);
	
	//**************************************
	//SOLICITO Y VALIDO LA OPCIÓN INGRESADA
	//**************************************
	
	printf("\n\nIngrese una opci%cn:\n", 162);
	
	do{
		scanf("%d", &OpcionSel);
		fflush(stdin);
		printf("\n");
		
		if(OpcionSel < 0 || OpcionSel > OpMaximas)
			printf("\nHa seleccionado una opci%cn err%cnea. Ingrese un n%cmero mayor o igual a 0 y menor o igual %d: \n", 162,162,163,OpMaximas);
		
	} while (OpcionSel < 0 || OpcionSel > OpMaximas);
	
	return OpcionSel;
}
