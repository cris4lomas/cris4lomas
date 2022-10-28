#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "FuncionesValidantes.h"
#include "Estructuras.h"

void ListarTxt(FILE * Arch){
	//La siguiente función utiliza un archivo de extensión .CSV para listar su contenido en forma de tabla.
	//El archivo debe contener las siguientes columnas y debe tener permitida la lectura de sus datos:
	//Orden(int) | Corredor(int) | Fecha (3 columnas) | Edad (int) | Pais (char[3]) | Tiempo (.6 double)
	
	//**************************************************
	//Creación de los títulos de la tabla (en variables)
	//**************************************************
	
	const char * COrden = {"Orden"}; // Columna 1: Ancho 6
	const char * CCorredor = {"Corredor"}; //Columna 2: Ancho 10
	const char * CDia = {"Dia"}; // Columna 3: Ancho 6
	const char * CMes = {"Mes"}; //Columna 4: Ancho 6
	//Columna 5 (Año): Ancho 6 -> La escribí en el printf, ya que no puedo asignar la letra 'ñ' en un const char *
	const char * CEdad = {"Edad"}; //Columna 6: Ancho 6
	const char * CPais = {"Pais"}; //Columna 7: Ancho 6
	const char * CTiempo = {"Tiempo"}; //Columna 8: Ancho 10
	
	//La siguiente variable me sirve para crearle los bordes superior e inferior a la tabla. CAL 26/10/2022
	const char * LineasDivisoras = {"-------------------------------------------------------------------------------"};
	
	//***********************************************************************************
	//Creación de las variables que se usarán para almacenar los datos del archivo .CSV
	//***********************************************************************************
	
	int Orden, Corredor, Dia, Anio, Edad;
	char Mes[4], Pais[4];
	float Tiempo;
	
	if(Arch != NULL){
		
		//Control de error #2: Verifico que el archivo .CSV contenga el delimitador que necesito (punto y coma ';').
		//Para esto, creé una función que realiza esa validación (incluída en el código '__FuncionesValidantes.c'). CAL 27/10/2022
		
		//La variable Flag contiene el resultado de la función de validación (si el valor es 1, el delimitador está incluído en el .CSV). CAL 27/10/2022
		int Flag = ValidaCSV(Arch, ';');
		
		//Si el delimitador se encontró:
		if (Flag == 1){
			
			//*******************************
			//INICIO DE CREACIÓN DE TABLA
			//*******************************
			printf("\t| %-6s | %-10s | %-6s | %-6s | A%co%-3s | %-6s | %-6s | %-12s |\n", COrden, CCorredor, CDia, CMes, 164,"", CEdad, CPais, CTiempo);
			printf("\t| %s |", LineasDivisoras);
			
			//Debo repetir la siguiente línea, porque si la incluyo dentro de un do..while o un while... me repite la última linea. CAL 27/10/2022
			fscanf(Arch, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Orden,&Corredor,&Dia,Mes,&Anio,&Edad,Pais,&Tiempo);
			
			do{
				printf("\n\t| %-6d | %-10d | %-6d | %-6s | %-6d | %-6d | %-6s | %-12.6f |",Orden, Corredor, Dia, Mes, Anio, Edad, Pais, Tiempo);
				fscanf(Arch, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Orden,&Corredor,&Dia,Mes,&Anio,&Edad,Pais,&Tiempo);
			}while (!feof(Arch));
			
			printf("\n\t| %s |", LineasDivisoras);
			printf("\n\n");
			
			//*******************************
			//FIN DE CREACIÓN DE TABLA
			//*******************************
			
		} else if(Flag == -1) printf("\nHa ocurrido algo con el archivo .CSV que devuelve NULL\n");
		
		//Si Flag es 0 (no se encontró el delimitador):
		else printf("\nSe esperaba un archivo delimitado con caracteres ';' (punto y coma). Por favor, verifique que el archivo otorgado sea un '.CSV' delimitado con ';' y vuelva a intentarlo.\n");
	
	//Si archivo es NULL:
	} else printf("\nHa ocurrido un error con el archivo. Verifique que exista, reinicie el programa e intente nuevamente. \n");
	
};
	
void CrearBinario(FILE * Arch, const char * NombreDat){
	//La presente función crea un archivo binario en el que se irán volcando todos los datos del resto del programa.
	//En un principio, verifica que el archivo no exista.
	//Si el archivo ya existe, pregunta si se desea reescribir (lo que borraría todo el archivo anterior).
	//Si no existe, lo crea directamente.
	//CAL 26/10/2022
	
	if (Arch == NULL){ //Si el archivo no existe, se crea. CAL 26/10/2022
		Arch = fopen(NombreDat, "w+b");
		
		//Control de error #3: si hay algún error con la creación del archivo, emito un mensaje. CAL 26/10/2022
		if(Arch != NULL) printf("\nSe ha creado el archivo binario: '%s'\n", NombreDat);
		else printf("Ha habido un error con la creaci%cn del archivo binario: '%s'",162, NombreDat);
		
	} else { //Si existe, pregunta si desea sobreescribir. CAL 26/10/2022
		printf("\nAtenci%cn...\nEl archivo ya existe, si lo crea nuevamente perder%c todos los datos que ten%ca previamente. Confirme si desea crearlo nuevamente: (S/N)\n",162,160,161);
		//La siguiente variable sirve para verificar si se desea o no sobreescribir el archivo existente:
		char Confirm = '0';
		do{
			scanf("%c",&Confirm);
			fflush(stdin);
			Confirm = toupper(Confirm);
			printf("\n");
			if(Confirm != 'S' && Confirm!='N') printf("Ha seleccionado err%cneamente. Elija S (Si) o N (No) \n",162);
		} while (Confirm != 'S' && Confirm!='N');
		
		if (Confirm == 'S'){
			//Se cierra el archivo antes de volver a abrirlo (aunque sea para reemplazarlo). CAL 26/10/2022
			fclose(Arch);
			Arch = fopen(NombreDat, "w+b");
			printf("\nSe ha creado nuevamente el archivo y se han borrado todos los datos anteriores con %cxito.\n\n", 130);
		} else{
			//En caso de que se haya denegado el reemplazo del archivo, no se hace nada con el que ya estaba abierto. CAL 26/10/2022
			printf("\nEl archivo no se ha sobreescrito y permanece intacto.\n\n");
		}
	}
};
	
void MigrarDatos(FILE * ArchOrgn, FILE * ArchDstn){
	//La siguiente función se encarga de traspasar todos los datos de competidores desde el archivo '.CSV' al archivo '.DAT'
	//Siempre va a colocar los datos al inicio del archivo .DAT, por lo que si hay datos previos en el archivo destino, los va a reemplazar. CAL 27/10/2022
	//El parámetro 1, es decir el archivo origen, debe tener permitida la lectura de datos. CAL 27/10/2022
	//El parámetro 2 (el archivo destino) debe tener permitida la escritura de datos en modo BINARIO. CAL 27/10/2022
	
	//Control de error: Verifico que ambos archivos existan. CAL 27/10/2022
	if(ArchOrgn != NULL && ArchDstn != NULL){
		
		//Control de error: verifico que el delimitador exista en el archivo .CSV:
		//Para esto utilizo la función validante definida en '__FuncionesValidantes.c'
		//Almaceno el valor de dicha función en una variable Flag. CAL 27/10/2022
		int Flag = ValidaCSV(ArchOrgn,';');
		
		//Si se encontró el delimitador en el .CSV: / CAL 27/10/2022
		if (Flag == 1){
			
			//Establecemos el puntero de ambos archivos al inicio de los mismos. CAL 27/10/2022
			rewind(ArchOrgn);
			rewind(ArchDstn);
			
			//Definimos la variable Comp de tipo 'struct Competidor' (estructura definida en 'Estructuras.h'). CAL 27/10/2022
			//El uso de la variable será transportar  cada una de las líneas del .CSV hacia el .DAT
			Competidor Comp;
			
			//Establecemos el valor 'ACTIVO = 1' para que a cada competidor que se traspase desde el .CSV se le asigne "Activo". CAL 27/10/2022
			Comp.Activo = 1;
			
			//Almacenamos los valores desde el .CSV en el struct 'Comp' (a esta línea la copio para que no se repita la última fila): / CAL 27/10/2022
			fscanf(ArchOrgn, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Comp.NrOrd,&Comp.NrCorr,&Comp.Dia,Comp.Mes,&Comp.Anio,&Comp.Edad,Comp.Pais,&Comp.Tiempo);
			
			//*************************************
			//INICIO DEL CICLO QUE COPIA LOS DATOS
			//*************************************
			
			do{
				
				//Traspasamos el struct 'Comp' al archivo .DAT / CAL 27/10/2022
				fwrite(&Comp,sizeof(Competidor),1,ArchDstn);
				
				//Realizamos la nueva toma de datos desde el .CSV y guardamos los datos en el struct 'Comp': / CAL 27/10/2022
				fscanf(ArchOrgn, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Comp.NrOrd,&Comp.NrCorr,&Comp.Dia,Comp.Mes,&Comp.Anio,&Comp.Edad,Comp.Pais,&Comp.Tiempo);
				
			} while(!feof(ArchOrgn));

			//*************************************
			//FIN DEL CICLO QUE COPIA LOS DATOS
			//*************************************
			
			printf("\n\n****************************************\n");
			printf("Se han migrado los datos correctamente.");
			printf("\n****************************************\n\n");
			
		
		//Si el caracter delimitador no se encontró en el archivo origen .CSV:
		} else if(Flag == -1) printf("\nHa ocurrido algo con el archivo .CSV que devuelve NULL\n");
		else printf("\nSe esperaba un archivo delimitado con caracteres ';' (punto y coma). Por favor, verifique que el archivo otorgado sea un '.CSV' delimitado con ';' y vuelva a intentarlo.\n");
		
	
	//Si alguno de los dos archivos es nulo, la función avisa de esto pero no hace ningún tipo de migración. CAL 27/10/2022
	} else {
		if (ArchOrgn == NULL) printf("\nHay un problema con la apertura del archivo origen (de extensi%cn '.CSV'). Verifique que exista.",162);
		if (ArchDstn == NULL) printf("\nHay un problema con la apertura del archivo destino (de extensi%cn '.DAT'). Verifique que exista.",162);
		printf("\n");
	}
};

void ListarDat(FILE * Arch, int Metodo){
	/*La presente función lista todos los usuarios de la lista del archivo '.dat' pasado como primer parámetro.
	El archivo debe tener habilitado el modo de ESCRITURA BINARIA.
	El segundo parámetro indica el tipo de visualización que se va a efectuar (se puede ver la función 'MenuListarBinario' para tener una ayuda visual):
	
	Si método es 2: Se listarán todos los usuarios (Activos e inactivos).
	Si método es 3: Se listarán solamente los usuarios activos.
	Si método es 4: Se pedirá que se ingrese un país y se mostrarán únicamente todos los usuarios pertenecientes a ese país.
	Si método es 5: Se pedirá un rango de tiempo y se mostrarán únicamente todos los usuarios que tengan la columna "Tiempo" dentro de ese rango.
		-CAL 27.10.2022-
	*/
	
	//Control de errores: verifico que el archivo no sea NULL y que el método se encuentre entre 2 y 5. /CAL 27.10.2022
	if(Arch != NULL && Metodo >= 2 && Metodo <= 5){
		
		//Creamos la variable 'Comp' de tipo struct 'Competidor' definida en 'Estructuras.h' /CAL 27.10.2022
		//La variable nos va a ayudar a almacenar los datos del archivo .DAT en forma temporal así podemos visualizarlos. /CAL 27.10.2022
		Competidor Comp;
		
		//Posicionamos el puntero al inicio del archivo. /CAL 27.10.2022
		rewind(Arch);
		
		switch(Metodo){
		case 2:
			printf("\nSe han listado todos los usuarios del .dat\n");
			break;
		case 3:
			printf("\nSe han listado los usuarios activos del .dat\n");
			break;
		case 4:
			printf("\nSe han listado los usuarios por pais .dat\n");
			break;
		case 5:
			printf("\nSe han listado los usuarios por rango de tiempo del archivo .dat\n");
			break;
		}
		
	} else{ //Si el archivo es nulo, o el metodo pasado no está entre los valores admitidos: /CAL 27.10.2022/
		
		if(Arch == NULL) printf("\nHa ocurrido un error con el archivo .DAT (devuelve NULL)... Verifique.\n");
		if(Metodo < 2 || Metodo > 5) printf("\nEl m%ctodo pasado como segundo par%cmetro debe ser mayor o igual a 2 y menor o igual a 5.\n",130, 160);
		
	}
	
	
};


void AltaCompetidor(FILE * Arch){
	printf("\nSe ha dado de alta un nuevo competidor en el archivo .dat\n");
};


void BuscarCompetidor(FILE * Arch, int Metodo){
	/*La presente función busca y muestra los datos de un competidor dado mediante dos métodos distintos, el cual se elige en el segundo parámetro.
	Para una ayuda más visual, se puede ver 'MenuBuscarComp'
	* Si método es 2: Busca un competidor por número de orden.
	* Si método es 3: Busca un competidor por número de corredor.
	*/
	switch(Metodo){
	case 2:
		printf("\nSe ha buscado y devuelvo un competidor por nro de orden.\n");
		break;
	case 3:
		printf("\nSe ha buscado y devuelvo un competidor por nro de corredor.\n");
		break;
	}
};
	
void ModificarCompetidor(FILE * Arch){
	printf("\nSe ha modificado un competidor.\n");
};
	
void BajaLogica(FILE * Arch){
	printf("\nSe ha dado la baja logica de un competidor.\n");
};
	
void BajaFisica(FILE * ArchDat, FILE * ArchBajasFis){
	printf("\nSe ha dado la baja fisica de un competidor.\n");
};
	
void VerBajasFisicas(FILE * Arch){
	printf("\nSe han visualizado las bajas fisicas hechas.\n");
};
