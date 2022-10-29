#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "FuncionesValidantes.h"
#include "Estructuras.h"

void ListarTxt(FILE * Arch){
	//La siguiente funci�n utiliza un archivo de extensi�n .CSV para listar su contenido en forma de tabla.
	//El archivo debe contener las siguientes columnas:
	//Orden(int) | Corredor(int) | Fecha (3 columnas) | Edad (int) | Pais (char[3]) | Tiempo (.6 double)
	
	//**************************************************
	//Creaci�n de los t�tulos de la tabla (en variables)
	//**************************************************
	
	const char * COrden = {"Orden"}; // Columna 1: Ancho 6
	const char * CCorredor = {"Corredor"}; //Columna 2: Ancho 10
	const char * CDia = {"Dia"}; // Columna 3: Ancho 6
	const char * CMes = {"Mes"}; //Columna 4: Ancho 6
	//Columna 5 (A�o): Ancho 6 -> La escrib� en el printf, ya que no puedo asignar la letra '�' en un const char *
	const char * CEdad = {"Edad"}; //Columna 6: Ancho 6
	const char * CPais = {"Pais"}; //Columna 7: Ancho 6
	const char * CTiempo = {"Tiempo"}; //Columna 8: Ancho 10
	
	//La siguiente variable me sirve para crearle los bordes superior e inferior a la tabla. CAL 26/10/2022
	const char * LineasDivisoras = {"-------------------------------------------------------------------------------"};
	
	//***********************************************************************************
	//Creaci�n de las variables que se usar�n para almacenar los datos del archivo .CSV
	//***********************************************************************************
	
	int Orden, Corredor, Dia, Anio, Edad;
	char Mes[4], Pais[4];
	float Tiempo;
	
	if(Arch != NULL){
		
		//Control de error #2: Verifico que el archivo .CSV contenga el delimitador que necesito (punto y coma ';').
		//Para esto, cre� una funci�n que realiza esa validaci�n (inclu�da en el c�digo '__FuncionesValidantes.c'). CAL 27/10/2022
		
		//La variable Flag contiene el resultado de la funci�n de validaci�n (si el valor es 1, el delimitador est� inclu�do en el .CSV). CAL 27/10/2022
		int Flag = ValidaCSV(Arch, ';');
		
		//Si el delimitador se encontr�:
		if (Flag == 1){
			
			//Posicionamos el puntero al inicio del archivo:
			rewind(Arch);
			
			//*******************************
			//INICIO DE CREACI�N DE TABLA
			//*******************************
			printf("\t| %-6s | %-10s | %-6s | %-6s | A%co%-3s | %-6s | %-6s | %-12s |\n", COrden, CCorredor, CDia, CMes, 164,"", CEdad, CPais, CTiempo);
			printf("\t| %s |", LineasDivisoras);
			
			//Debo repetir la siguiente l�nea, porque si la incluyo dentro de un do..while o un while... me repite la �ltima linea. CAL 27/10/2022
			fscanf(Arch, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Orden,&Corredor,&Dia,Mes,&Anio,&Edad,Pais,&Tiempo);
			
			do{
				printf("\n\t| %-6d | %-10d | %-6d | %-6s | %-6d | %-6d | %-6s | %-12.6f |",Orden, Corredor, Dia, Mes, Anio, Edad, Pais, Tiempo);
				fscanf(Arch, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Orden,&Corredor,&Dia,Mes,&Anio,&Edad,Pais,&Tiempo);
			}while (!feof(Arch));
			
			printf("\n\t| %s |", LineasDivisoras);
			printf("\n\n");
			
			//*******************************
			//FIN DE CREACI�N DE TABLA
			//*******************************
			
		} else if(Flag == -1) printf("\nHa ocurrido algo con el archivo .CSV que devuelve NULL\n");
		
		//Si Flag es 0 (no se encontr� el delimitador):
		else printf("\nSe esperaba un archivo delimitado con caracteres ';' (punto y coma). Por favor, verifique que el archivo otorgado sea un '.CSV' delimitado con ';' y vuelva a intentarlo.\n");
	
	//Si archivo es NULL:
	} else printf("\nHa ocurrido un error con el archivo. Verifique que exista, reinicie el programa e intente nuevamente. \n");
	
};
	
void CrearBinario(FILE * Arch, const char * NombreDat){
	//La presente funci�n crea un archivo binario en el que se ir�n volcando todos los datos del resto del programa.
	//En un principio, verifica que el archivo no exista.
	//Si el archivo ya existe, pregunta si se desea reescribir (lo que borrar�a todo el archivo anterior).
	//Si no existe, lo crea directamente.
	//CAL 26/10/2022
	
	if (Arch == NULL){ //Si el archivo no existe, se crea. CAL 26/10/2022
		Arch = fopen(NombreDat, "w+b");
		
		//Control de error #3: si hay alg�n error con la creaci�n del archivo, emito un mensaje. CAL 26/10/2022
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
			//En caso de que se haya denegado el reemplazo del archivo, no se hace nada con el que ya estaba abierto.
			printf("\nEl archivo no se ha sobreescrito y permanece intacto.\n\n");
			rewind(Arch);
		}
	}
};
	
void MigrarDatos(FILE * ArchOrgn, FILE * ArchDstn){
	//La siguiente funci�n se encarga de traspasar todos los datos de competidores desde el archivo '.CSV' al archivo '.DAT'
	//Siempre va a colocar los datos al inicio del archivo .DAT, por lo que si hay datos previos en el archivo destino, los va a reemplazar. CAL 27/10/2022
	
	//Control de error: Verifico que ambos archivos existan.
	if(ArchOrgn != NULL && ArchDstn != NULL){
		
		//Control de error: verifico que el delimitador exista en el archivo .CSV:
		//Para esto utilizo la funci�n validante definida en '__FuncionesValidantes.c'
		//Almaceno el valor de dicha funci�n en una variable Flag. CAL 27/10/2022
		
		int Flag = ValidaCSV(ArchOrgn,';');
		
		if (Flag == 1){
			
			//Definimos la variable Comp de tipo 'struct Competidor' (estructura definida en 'Estructuras.h'). CAL 27/10/2022
			//El uso de la variable ser� transportar  cada una de las l�neas del .CSV hacia el .DAT
			Competidor Comp;
			
			//Posicionamos los punteros de ambos archivos al inicio
			rewind(ArchOrgn);
			rewind(ArchDstn);
			
			//El valor de "Activo" siempre es 1 al migrar los datos.
			Comp.Activo = 1;
			
			//Repetimos esta l�nea al final del ciclo para evitar que nos repita la �ltima fila
			fscanf(ArchOrgn, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Comp.NrOrd, &Comp.NrCorr,&Comp.Dia,Comp.Mes,&Comp.Anio,&Comp.Edad, Comp.Pais, &Comp.Tiempo);
			
			//Iniciamos el ciclo que transporta los datos
			do{
				fwrite(&Comp,sizeof(Competidor),1,ArchDstn);
				fscanf(ArchOrgn, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Comp.NrOrd, &Comp.NrCorr,&Comp.Dia,Comp.Mes,&Comp.Anio,&Comp.Edad, Comp.Pais, &Comp.Tiempo); 
			} while(!feof(ArchOrgn));
			
			printf("\n\n******************************************\n");
			printf("Se han migrado los datos correctamente.");
			printf("\n******************************************\n\n");
			
		
		//Si el caracter delimitador no se encontr� en el archivo origen .CSV:
		} else if(Flag == -1) printf("\nHa ocurrido algo con el archivo .CSV que devuelve NULL\n");
		else printf("\nSe esperaba un archivo delimitado con caracteres ';' (punto y coma). Por favor, verifique que el archivo otorgado sea un '.CSV' delimitado con ';' y vuelva a intentarlo.\n");
		
	
	//Si alguno de los dos archivos es nulo, la funci�n avisa de esto pero no hace ning�n tipo de migraci�n. CAL 27/10/2022
	} else {
		if (ArchOrgn == NULL) printf("\nHay un problema con la apertura del archivo origen (de extensi%cn '.CSV'). Verifique que exista.",162);
		if (ArchDstn == NULL) printf("\nHay un problema con la apertura del archivo destino (de extensi%cn '.DAT'). Verifique que exista.",162);
		printf("\n");
	}
};

void ListarDat(FILE * Arch, int Metodo){
	/*La presente funci�n lista todos los usuarios de la lista del archivo '.dat' pasado como primer par�metro.
	El segundo par�metro indica el tipo de visualizaci�n que se va a efectuar (se puede ver la funci�n 'MenuListarBinario' para tener una ayuda visual):
	
	Si m�todo es 2: Se listar�n todos los usuarios (Activos e inactivos).
	Si m�todo es 3: Se listar�n solamente los usuarios activos.
	Si m�todo es 4: Se pedir� que se ingrese un pa�s y se mostrar�n �nicamente todos los usuarios pertenecientes a ese pa�s.
	Si m�todo es 5: Se pedir� un rango de tiempo y se mostrar�n �nicamente todos los usuarios que tengan la columna "Tiempo" dentro de ese rango.
	*/
	
	//Verifico que el archivo no sea nulo
	if(Arch != NULL) {
	
		//Defino las variables que puedo llegar a necesitar seg�n el m�todo:
		
		//La siguiente bandera nos servir� en cada caso para verificar datos. (0 = FALSO, 1 = VERDADERO). CAL 29/10/2022
		int Flag = 0;
		
		//Para que el usuario sea libre de escribir el nombre de un pa�s completo en caso de que el m�todo sea 4:
		char PaisLargo[25];
		char PaisCorto[4]; //Se mostraran solo los 3 primeros caracteres del pa�s
		
		//En caso de que el m�todo sea 5, las cadenas almacenan los valores ingresados por el usuario y los validan:
		char ChTiempoMin[13] = {""};
		char ChTiempoMax[13] = {""};
		
		//Los valores flotantes se usan para filtrar los datos de los competidores:
		float TiempoMin = -1;
		float TiempoMax = -1;
		
		if(Metodo == 4){
			//Se pregunta por el pa�s
			printf("\nHa seleccionado mostrar a los competidores filtrados por pa%cs\n", 161);
			printf("Ingrese el pa%cs para filtrar:\n", 161);
			
			//Inicio del ciclo que verifica que el pa�s sea v�lido
			do{
				gets(PaisLargo);
				PaisLargo[23] = '\0'; //Fuerzo el �ltimo caracter a que sea NULL en caso de que se hayan ingresado m�s de 24 caracteres.
				
				//Se realiza la validaci�n de que el string solo contenga caracteres alfab�ticos. CAL 29/10/2022
				if(ValidaAbc(PaisLargo) == 0) printf("\n\nHa ingresado un pa%cs err%cneo. Ingrese un pa%cs %cnicamente ingresando valores alfab%cticos:\n",161,162,161,163,130);
			}
			while(ValidaAbc(PaisLargo) == 0);
			
			//Convertimos las letras del pa�s a may�sculas:
			for(int i = 0; i < strlen(PaisLargo); i++) PaisLargo[i] = toupper(PaisLargo[i]);
			
			//Copiamos los tres primeros caracteres del pa�s escrito
			strncpy(PaisCorto,PaisLargo,3);
			
			printf("\n\n************************************************\n");
			printf("Mostrando datos del pa%cs: %s",161,PaisLargo);
			printf("\n************************************************\n\n");
			
		} else if(Metodo == 5) {
			//Se pregunta por el tiempo. CAL 29/10/2022
				
			//*****************************************************
			//INICIO DEL CICLO DE VALIDACI�N PARA EL TIEMPO M�NIMO
			//*****************************************************
			
			//SE UTILIZA LA BANDERA 'FLAG' EN ESTE CASO. CAL 29/10/2022
			
			//Se solicitan los datos. CAL 29/10/2022
			printf("\nHa seleccionado mostrar a los competidores filtrados por tiempo\n");
			printf("Ingrese el tiempo m%cnimo para filtrar (puede contener decimales, pero no use separador de mil%csimos):\n", 161,130);
			
			do{
				gets(ChTiempoMin);
				ChTiempoMin[11] = '\0'; //Fuerzo el �ltimo caracter a nulo en caso de que se hayan introducido m�s valores de lo esperado.
				
				if(ValidaNumConDec(ChTiempoMin) == 0){
					Flag = 0;
					printf("\n\nHa introducido un tiempo m%cnimo incorrecto. Introduza solo n%cmeros o a lo sumo con un separador de decimales:\n",161,163);
				}
				else{
					if(atof(ChTiempoMin) <= 0) {
						Flag = 0;
						printf("\n\nHa introducido un tiempo m%cnimo incorrecto. Introduza un n%cmero mayor a cero:\n",161,163);
					} else {Flag = 1;}
				}
			} while(Flag == 0);
			
			//Se asigna el valor como flotante en caso de que se haya superado la validaci�n. CAL 29/10/2022
			TiempoMin = (float) atof(ChTiempoMin);
			
			//*****************************************************
			//INICIO DEL CICLO DE VALIDACI�N PARA EL TIEMPO M�XIMO
			//*****************************************************
			
			//Se solicitan los datos. CAL 29/10/2022
			printf("\n\nHa seleccionado como tiempo m%cnimo: %.6f\n", 161,TiempoMin);
			printf("Ingrese el tiempo m%cximo (puede contener decimales, pero no use separador de mil%csimos):\n", 160,130);
			
			//En este ciclo, adem�s se deber� verificar que el tiempo m�ximo sea mayor al tiempo m�nimo elegido.
			do{
				gets(ChTiempoMax);
				ChTiempoMax[11] = '\0'; //Fuerzo el �ltimo caracter a nulo en caso de que se hayan introducido m�s valores de lo esperado.
				
				if(ValidaNumConDec(ChTiempoMax) == 0){
					Flag = 0;
					printf("\n\nHa introducido un tiempo m%cximo incorrecto. Introduza solo n%cmeros o a lo sumo con un separador de decimales:\n",160,163);
				}
				else{
					//Si el tiempo m�ximo es menor al tiempo m�nimo, se emite mensaje de error. CAL 29/10/2022
					if(atof(ChTiempoMax) < TiempoMin) {
						Flag = 0;
						printf("\n\nHa introducido un tiempo m%cximo menor al tiempo m%cnimo ingresado anteriormente.\n",160,161);
						printf("Introduza un n%cmero mayor a %.6f:\n",163, TiempoMin);
					} else {Flag = 1;}
				}
			} while(Flag == 0);
			
			//Se asigna el valor como flotante en caso de que se haya superado la validaci�n. CAL 29/10/2022
			TiempoMax = (float) atof(ChTiempoMax);
			
			printf("\n\n************************************************\n");
			printf("Mostrando datos de entre: \n");
			printf("*)Tiempo m%cnimo %.6f\n", 161,TiempoMin);
			printf("*)Tiempo m%cximo %.6f", 160,TiempoMax);
			printf("\n************************************************\n\n");
			
		}
		
		//Luego de comprobar los dos m�todos que solicitan datos, procedo a la creaci�n del esqueleto de la tabla:
		
		const char * COrden = {"Orden"}; // Columna 1: Ancho 5
		const char * CCorredor = {"Corredor"}; //Columna 2: Ancho 10
		const char * CDia = {"Dia"}; // Columna 3: Ancho 5
		const char * CMes = {"Mes"}; //Columna 4: Ancho 5
		//Columna 5 (A�o): Ancho 5 -> La escrib� en el printf, ya que no puedo asignar la letra '�' en un const char *
		const char * CEdad = {"Edad"}; //Columna 6: Ancho 5
		const char * CPais = {"Pais"}; //Columna 7: Ancho 5
		const char * CActivo = {"Activo"}; //Columna 8: Ancho 6
		const char * CTiempo = {"Tiempo"}; //Columna 9: Ancho 10
		
		//La siguiente variable me sirve para crearle los bordes superior e inferior a la tabla. CAL 26/10/2022
		const char * LineasDivisoras = {"------------------------------------------------------------------------------------"};
		
		//Imprimo los t�tulos. CAL 29/10/2022
		printf("\n\t| %-5s | %-10s | %-5s | %-5s | A%co%-2s | %-5s | %-5s | %-6s | %-12s |\n", COrden, CCorredor, CDia, CMes, 164,"", CEdad, CPais, CActivo, CTiempo);
		printf("\t|%s|", LineasDivisoras);
		
		//********************************************
		//INICIO DEL CICLO QUE RECORRE CADA REGISTRO
		//********************************************
		
		//Uso la bandera 'Flag' en cada caso para comprobar si el competidor debe imprimirse o no.
		//Me posiciono al inicio del archivo (antes del inicio del ciclo). CAL 29/10/2022
		rewind(Arch);
		
		//Declaro la variable de tipo Competidor en la que voy a almacenar los datos del archivo.
		Competidor Comp;
		
		//Repito la siguiente l�nea al final del ciclo para evitar que repita la �ltima fila. CAL 29/10/2022
		fread(&Comp, sizeof(Competidor),1,Arch);
		
		do{
			//Restablezco la bandera en FALSO en cada vuelta de ciclo
			Flag = 0;
			
			switch(Metodo){
			case 2:
				//Mostrar todos los usuarios(el n�mero de orden debe ser distinto de cero). CAL 29/10/2022
				if(Comp.NrOrd > 0) Flag = 1;
				break;
			case 3:
				if(Comp.Activo == 1) Flag = 1;
				break;
			case 4:
				if(strncmp(Comp.Pais,PaisCorto,3) == 0) Flag = 1;
				break;
			case 5:
				if(Comp.Tiempo > TiempoMin && Comp.Tiempo < TiempoMax) Flag = 1;
				break;
			default:
				break;
			}
			
			//Si se activ� la bandera, imprimir los datos del competidor.
			if(Flag == 1) {
				printf("\n\t| %-5d | %-10d | %-5d | %-5s | %-5d | %-5d | %-5s | %-6d | %-12.6f |", Comp.NrOrd, Comp.NrCorr, Comp.Dia, Comp.Mes, Comp.Anio, Comp.Edad, Comp.Pais, Comp.Activo, Comp.Tiempo);
			}
			
			fread(&Comp, sizeof(Competidor),1,Arch);
			
		} while (!feof(Arch));
		
		printf("\n\t|%s|\n\n", LineasDivisoras);
	
	//Si el archivo es nulo:
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
}


void AltaCompetidor(FILE * Arch){
	/*La siguiente funci�n registra un nuevo competidor en el archivo de extensi�n .DAT.
	Dicho archivo debe tener habilitada la opci�n de "ESCRITURA BINARIA"
	CAL 29/10/2022
	*/
	
	//Verifico que el archivo no sea nulo.
	if(Arch != NULL){
		printf("\nSe ha dado de alta un nuevo competidor en el archivo .dat\n");
	//Si el archivo es nulo:
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);

}


void BuscarCompetidor(FILE * Arch, int Metodo){
	/*La presente funci�n busca y muestra los datos de un competidor dado mediante dos m�todos distintos, el cual se elige en el segundo par�metro.
	Para una ayuda m�s visual, se puede ver 'MenuBuscarComp'
	* Si m�todo es 2: Busca un competidor por n�mero de orden.
	* Si m�todo es 3: Busca un competidor por n�mero de corredor.
	*/
	
	//Verifico que el archivo existe y el m�todo sea v�lido. CAL 29/10/2022
	if(Arch != NULL && Metodo > 1 && Metodo < 4){
		
		switch(Metodo){
		case 2:
			printf("\nSe ha buscado y devuelvo un competidor por nro de orden.\n");
			break;
		case 3:
			printf("\nSe ha buscado y devuelvo un competidor por nro de corredor.\n");
			break;
		}
	
	//Si el archivo es nulo o se pas� err�neamente un m�todo: - CAL 29/10/2022
	} else{
		if(Arch == NULL) printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
		if(Metodo < 2 || Metodo > 3) printf("\n\nHa pasado un par%cmetro de m%ctodo err%cneo. Verifique la funci%cn desde el c%cdigo fuente.\n",160,130,162,162,162);
	}
}
	
void ModificarCompetidor(FILE * Arch){
	/*La siguiente funci�n modifica un competidor en el archivo de extensi�n .DAT.
	Dicho archivo debe tener habilitada la opci�n de "ESCRITURA BINARIA"
	CAL 29/10/2022
	*/
	
	//Verifico que el archivo exista. CAL 29/10/2022
	if(Arch != NULL){
		
		printf("\nSe ha modificado un competidor.\n");
		
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	
}
	
void BajaLogica(FILE * Arch){
	/*La siguiente modifica el campo "Activo" de un competidor en el archivo de extensi�n .DAT y lo deja en cero (0).
	Dicho archivo debe tener habilitada la opci�n de "ESCRITURA BINARIA"
	CAL 29/10/2022
	*/
	//Verifico que el archivo exista. CAL 29/10/2022
	if(Arch != NULL){
	
		printf("\nSe ha dado la baja logica de un competidor.\n");
		
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	
}
	
void BajaFisica(FILE * ArchDat, FILE * ArchBajasFis, const char * NombreArchBajasFis){
	/*La siguiente funci�n modifica los datos de un competidor en el archivo de extensi�n .DAT y deja todos sus campos en cero (0).
	Dicho archivo debe tener habilitada la opci�n de "ESCRITURA BINARIA"
	Adem�s, esta funci�n registra las bajas f�sicas en otro archivo .DAT que crea en caso de que no exista (si no, los agrega al inicio del documento).
	CAL 29/10/2022
	*/
	//Verifico que ambos archivos existan. CAL 29/10/2022
	
	if(ArchBajasFis == NULL) {
		//Si no existe el archivo, lo creo. CAL 29/10/2022
		ArchBajasFis = fopen(NombreArchBajasFis,"wb+");
	}
	
	//Si el archivo DAT que contiene la informaci�n de los competidores activos no existe, entonces la funci�n no puede ejecutar nada. CAL 29/10/2022
	if(ArchDat != NULL){
	
		printf("\nSe ha dado la baja fisica de un competidor.\n");
		
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	
}
	
void VerBajasFisicas(FILE * Arch){
	//Verifico que el archivo exista. CAL 29/10/2022
	if(Arch != NULL){
	
		printf("\nSe han visualizado las bajas fisicas hechas.\n");
		
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	
}
