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
	
	//La siguiente bandera nos servir� en la funci�n para verificar datos. (0 = FALSO, 1 = VERDADERO). CAL 29/10/2022
	int Flag = 1;
	
	//Verificamos que el archivo binario contenga datos:
	rewind(Arch);
	fseek(Arch,0,SEEK_END);
	if(ftell(Arch) / sizeof(Competidor) == 0) Flag = 0; //Si el archivo est� vac�o, setear la bandera en FALSO.
	rewind(Arch); //Por seguridad, siempre seteo el puntero al inicio del archivo. CAL 29/10/2022
	
	
	//Verifico que el archivo no sea nulo y que tenga datos
	if(Arch != NULL && Flag == 1) {
	
		//Defino las variables que puedo llegar a necesitar seg�n el m�todo:
		
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
	
	//Si el archivo es nulo o si no contiene datos:
	} else{
		if(Arch == NULL) printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
		else printf("\n\nEl archivo est%c vac%co. Seleccione 'Migrar datos entre archivos' o ingrese datos en forma manual para poder listarlos.\n",160,161);
	}
}


void AltaCompetidor(FILE * Arch){
	/*La siguiente funci�n registra un nuevo competidor en el archivo de extensi�n .DAT.
	Dicho archivo debe tener habilitada la opci�n de "ESCRITURA BINARIA"
	Todos los registros vac�os que est�n entre el primer competidor y el n�mero de orden ingresado tendr�n todos sus campos convertidos en cero.
	CAL 29/10/2022
	*/
	
	//Verifico que el archivo no sea nulo.
	if(Arch != NULL){
		
		//*********************************
		//INICIO DE CICLOS EN SECUENCIA
		//*********************************
		
		//Cada uno de los ciclos tendr� como finalidad asegurarse de que los datos solicitados sean v�lidos.
		//El m�todo de validaci�n consiste en hacer uso de las funciones dise�adas especialmente para validar datos en '__FuncionesValidantes.c'
		//Hasta que la funci�n validante no devuelva VERDADERO, no se sale del ciclo.
		
		//Para validarlos se har� uso de la siguiente bandera:
		int Flag; //0 indica FALSO y 1 VERDADERO - CAL 29/10/2022
		
		//Creamos el competidor que almacenar� los datos a ingresar.
		Competidor Comp;
		
		//Nos posicionamos al inicio del archivo y obtenemos cu�ntos registros existen
		//(ser� de utilidad para verificar que el orden no supere la cantidad de registros) - CAL 29/10/2022
		
		rewind(Arch);
		fseek(Arch,0,SEEK_END);
		int CantDeRegistros = ftell(Arch) / sizeof(Competidor);
		
		//Volvemos a posicionarnos la inicio
		rewind(Arch);
		
		//*****************
		//CICLO DE ORDEN:
		//*****************
		//Verifica que el orden no est� ocupado y, adem�s, que sea un n�mero entero v�lido.
		
		printf("\nIngrese un n%cmero de orden para dar de alta. Debe ser un entero positivo y no puede contener m%cs de 7 caracteres:\n",163,160);
		
		//Almacenamos el orden ingresado en un char para comprobar su validez. CAL 29/10/2022
		char ChOrden[9] ={""};
		
		do{
			Flag = 0; //Seteamos la bandera en FALSO en cada vuelta.
			gets(ChOrden);
			ChOrden[7] = '\0'; //Seteamos en NULL los �ltimos d�gitos del char en caso de que ingresen m�s caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			if(ValidaNumSinDec(ChOrden) == 1){
				//En caso de que el n�mero de orden ingresado sea v�lido, se proceder� a verificar que no est� ocupado por otro competidor. CAL 29/10/2022
				if(atoi(ChOrden) > CantDeRegistros){ //Si el n�mero de orden supera la cantidad de registros existentes, solo puede ser v�lido.
					Flag = 1;
				} else{ //En caso de que no supere la cantidad de registros, se verifica que el n�mero sea mayor a cero y que no est� ocupado por otro competidor. CAL 29/10/2022
					if(atoi(ChOrden) < 1){
						printf("\n\nError. El n%cmero ingresado debe ser mayor a cero. Ingrese un n%cmero de orden v%clido:\n",163,163,160);
						Flag = 0;
					} else{ //En caso de que el orden sea v�lido pero sea menor o igual a la cantidad de registros, se verifica que no est� ocupado. CAL 29/10/2022
						
						//Los rewind son por seguridad, descartan que el archivo pueda haber quedado apuntado en otro lugar
						rewind(Arch);
						fseek(Arch, sizeof(Competidor) * (atoi(ChOrden) - 1),SEEK_CUR);
						fread(&Comp,sizeof(Competidor),1,Arch);
						rewind(Arch);
						
						if(Comp.NrOrd != 0){
							printf("\n\nEl n%cmero de orden ingresado ya est%c ocupado. Ingrese un nuevo n%cmero de orden:\n",163,160,163);
							Flag = 0;
						} else{ //En caso de que el lugar no est� ocupado, se habilita la bandera.
							Flag = 1;
						}
						
					}
					
					
				}
			} else{ //En caso de que no supere la validaci�n de la funci�n 'ValidaNumSinDec':
				printf("\n\nHa ingresado un n%cmero de orden no v%clido. Ingrese un n%cmero entero mayor a cero:\n",163,160,163);
				Flag = 0;
			}
			
		} while (Flag == 0);
		
		
		//******************************
		//CICLO DE N�MERO DE CORREDOR:
		//******************************
		//Simplemente verifica sea un n�mero entero v�lido y positivo, y que el n�mero de corredor no se repita con otro.
		
		printf("\nIngrese un n%cmero de corredor. Debe ser un entero positivo y no puede contener m%cs de 8 caracteres. Tampoco puede estar repetido:\n",163,160);
		
		//Almacenamos el nro de corredor ingresado en un char para comprobar su validez. CAL 29/10/2022
		char ChCorredor[10] ={""};
		
		do{
			Flag = 0; //Seteamos la bandera en FALSO en cada vuelta.
			gets(ChCorredor);
			ChCorredor[8] = '\0'; //Seteamos en NULL los �ltimos d�gitos del char en caso de que ingresen m�s caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			if(ValidaNumSinDec(ChCorredor) == 1){
				//Si supera la validaci�n de n�mero entero:
				
				//Debe ser un n�mero mayor a cero.
				if(atoi(ChCorredor) < 1) {
					printf("\n\nEl n%cmero de corredor debe ser mayor a cero.\n",163);
					Flag = 0;
				} else {
					//Si el n�mero de corredor es v�lido, se verifica que no est� repetido.
					
					//Se establece la bandera en "Verdadero" y se desactiva si el n�mero de corredor se encuentra en otro competidor.
					Flag = 1;
					
					rewind(Arch);
					
					for(int i = 0; i < CantDeRegistros; i++){
						fread(&Comp,sizeof(Competidor),1,Arch);
						if(Comp.NrCorr == atoi(ChCorredor)) Flag = 0;
					}
					
					rewind(Arch);
					//Si el n�mero de corredor se encontr� repetido, emite un mensaje de error:
					if (Flag == 0) printf("\n\nEl n%cmero de corredor ingresado ya existe con el n%cmero de orden: %d. Ingrese otro n%cmero de corredor.\n",163,163,Comp.NrOrd,163);
				} 
				
			} else { //Si no supera la validaci�n de n�mero entero:
				printf("\n\nHa ingresado un n%cmero incorrecto. Ingrese un n%cmero entero sin signos ni caracteres especiales:\n",163,163);
				Flag = 0;
			}
		} while (Flag == 0);
		
		
		//****************
		//CICLO DE FECHA:
		//****************
		//Valida que la fecha sea v�lida.
		
		printf("\n\nIngrese la fecha del corredor con formato 'dd-mm-yyyy' (en vez de guiones puede separar los valores con barras '/', espacios ' ' o puntos '.', pero lo importante es que todos los d%cgitos sean num%cricos:\n",161,163);
		
		//Almacenamos la fecha en un char para comprobar su validez. CAL 29/10/2022
		char ChFecha[13] ={""};
		
		do{
			Flag = 0; //Seteamos la bandera en FALSO en cada vuelta.
			gets(ChFecha);
			ChFecha[11] = '\0'; //Seteamos en NULL los �ltimos d�gitos del char en caso de que ingresen m�s caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			if(ValidaFecha(ChFecha) == 1){
				Flag = 1;
			} else{
				Flag = 0;
				printf("\n\nHa ingresado una fecha err%cnea. Verifique que el formato sea correcto y que la fecha sea una fecha v%clida e ingr%csela nuevamente:\n",162,160,130);
			}
		} while(Flag == 0);
		
		//****************
		//CICLO DE EDAD:
		//****************
		//Valida que la edad sea v�lida.
		
		printf("\n\nIngrese la edad del corredor:\n");
		char ChEdad[5] = {""};
		
		do{
			Flag = 0;
			gets(ChEdad);
			ChEdad[3] = '\0'; //Seteamos en NULL los �ltimos d�gitos del char en caso de que ingresen m�s caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			//Si el n�mero le�do no supera la validaci�n:
			if(ValidaNumSinDec(ChEdad) == 0){
				printf("\n\nHa ingresado un n%cmero err%cneo. Ingrese una edad v%clida:\n",163,162,160);
				Flag = 0;
			} else {
				//Si supera la validaci�n de f�rmula, se procede a verificar que la edad sea real:
				if(atoi(ChEdad) > 0 && atoi(ChEdad) < 161) {
					Flag = 1;
				} else {
					printf("\n\nNo es posible que un competidor tenga la edad indicada. Ingrese una edad verdadera:\n");
					Flag = 0;
				}
			}
		} while (Flag == 0);
		
		
		//********************
		//CICLO DE PA�S
		//********************
		//Se procede a verificar que el pa�s est� bien escrito. CAL 29/10/2022
		
		printf("\n\nIngrese el pa%cs del corredor:\n",161);
		char ChPais[25] = {""};
		
		do{
			Flag = 0;
			gets(ChPais);
			ChEdad[23] = '\0'; //Seteamos en NULL los �ltimos d�gitos del char en caso de que ingresen m�s caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			//Si el pais le�do no supera la validaci�n:
			if(ValidaAbc(ChPais) == 0){
				printf("\n\nHa ingresado un pa%cs err%cneo. Ingrese un pa%cs v%clido usando solamente caracteres alfab%cticos:\n",161,162,161,160,130);
				Flag = 0;
			} else {
				//Se convierten los caracteres del pa�s en may�sculas
				for(int i = 0; i < strlen(ChPais); i++) ChPais[i] = toupper(ChPais[i]);
				Flag = 1;
			}
		} while (Flag == 0);
		
		
		//********************
		//CICLO DE TIEMPO
		//********************
		//Se procede a verificar que el tiempo tenga el formato correcto. CAL 29/10/2022
		
		printf("\n\nIngrese el tiempo del corredor (no puede ser mayor a 999):\n");
		char ChTiempo[25] = {""};
		
		do{
			Flag = 0;
			gets(ChTiempo);
			ChTiempo[23] = '\0'; //Seteamos en NULL los �ltimos d�gitos del char en caso de que ingresen m�s caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			//Si el pais le�do no supera la validaci�n:
			if(ValidaNumConDec(ChTiempo) == 0){
				printf("\n\nHa ingresado un tiempo err%cneo. Ingrese un tiempo v%clido usando solamente separador de decimales en caso de que lo necesite (no use separadores de mil%csimos):\n",162,160,130);
				Flag = 0;
			} else {
				//Se convierten los caracteres del pa�s en may�sculas
				if(atof(ChTiempo) > 999 || atof(ChTiempo) < 1){
					printf("\n\nEl tiempo debe ser mayor o igual a '1' y no puede superar '999' porque todos esos competidores quedan descalificados y no es posible insertarlos en la base. Ingrese un tiempo v%clido para continuar:\n",160);
					Flag = 0;
				} else{
					Flag = 1;
				}
			}
		} while (Flag == 0);
		
		
		//**********************************
		//FIN DE LOS CICLOS EN SERIE
		//**********************************
		
		//Si el n�mero de orden ingresado es mayor a la cantidad de registros existentes, me posiciono al final del archivo y voy cargando en cero todos los datos intermedios. CAL 29/10/2022
		
		if(atoi(ChOrden) > CantDeRegistros){
			//Si me excedo de la cantidad de registros existentes, posiblemente deba almacenar espacios en blanco
			Comp.NrOrd = 0;
			Comp.NrCorr = 0;
			Comp.Dia = 0;
			strcpy(Comp.Mes,"0  ");
			Comp.Anio = 0;
			Comp.Edad = 0;
			strcpy(Comp.Pais,"0  ");
			Comp.Activo = 0;
			Comp.Tiempo = 0;
			
			/***************
			Inicio ciclo
			****************
			El ciclo recorre todo el archivo binario a partir de la �ltima posici�n e ir� rellenando con ceros todas aquellas posiciones intermedias
			Entre la �ltima fila preexistente y el nuevo n�mero de orden.
			*/
			
			//Declaro una variable que ser� la que almacene el tope del bucle:
			int Tope = atoi(ChOrden) - CantDeRegistros;
			
			//Me posiciono al final del archivo. CAL 29/10/2022
			rewind(Arch);
			fseek(Arch,0,SEEK_END);
			
			for (int i = 0; i < Tope; i++){
				if( i == Tope - 1) break; //Si se llega a la
				fwrite(&Comp,sizeof(Competidor),1,Arch);
			}
			
		} else{
			//Si no se supera la cantidad de registros, entonces se debe acceder de forma directa. CAL 29/10/2022
			rewind(Arch);
			fseek(Arch,sizeof(Competidor) * (atoi(ChOrden) - 1),SEEK_CUR);
		}
		
		//Una vez finalizada la etapa de validaci�n y una vez llegado a la posici�n del n�mero de orden, se procede a almacenar el competidor. CAL 29/10/2022
		Comp.NrOrd = atoi(ChOrden);
		Comp.NrCorr = atoi(ChCorredor);
		Comp.Dia = ExtraerDeFecha(ChFecha,'d','/');
		
		//Comp.Mes: Para el mes, se crea una variable que servir� para almacenar el valor entero del mes y luego se usar� una funci�n predefinida para almacenar sus tres primeros caracteres. CAL 29/10/2022
		int Mes = ExtraerDeFecha(ChFecha,'m','/');
		ConvertirMesAString(Mes,Comp.Mes);
		
		Comp.Anio = ExtraerDeFecha(ChFecha,'a','/');
		Comp.Edad = atoi(ChEdad);
		
		//Comp.Pais
		strncpy(Comp.Pais,ChPais,3);
		
		Comp.Activo = 1;
		Comp.Tiempo = (float) atof(ChTiempo);
		
		fwrite(&Comp,sizeof(Competidor),1,Arch);
		
		printf("\n\n*******************************\n");
		printf("Datos cargados exitosamente.");
		printf("\n*******************************\n\n");
		printf("Nr. Orden: %d\n", Comp.NrOrd);
		printf("Nr. Corredor: %d\n", Comp.NrCorr);
		printf("Fecha: %s\n", ChFecha);
		printf("Edad: %d\n", Comp.Edad);
		printf("Pa%cs: %s\n",161, ChPais);
		printf("Tiempo: %.6f\n", Comp.Tiempo);
		
			
		
	//Si el archivo es nulo:
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);

}


void BuscarCompetidor(FILE * Arch, int Metodo){
	/*La presente funci�n busca y muestra los datos de un competidor dado mediante dos m�todos distintos, el cual se elige en el segundo par�metro.
	Para una ayuda m�s visual, se puede ver 'MenuBuscarComp' en el archivo '__Menus.c'
	* Si m�todo es 2: Busca un competidor por n�mero de orden. (acceso directo)
	* Si m�todo es 3: Busca un competidor por n�mero de corredor. (acceso secuencial)
	CAL 29/10/2022
	*/
	
	//Se usa una bandera para indicar si el dato que se busca est� disponible:
	int Flag = 1; //Por defecto la seteamos en VERDADERO
	
	//Creo la variable que conte
	int CantDeRegistros;
	
	//Si el archivo es NULO, se setea la bandera en falso y la funci�n finaliza.
	if(Arch != NULL){
		//Si el archivo no es falso, se verifica que contenga datos...
		//Almacenamos la cantidad de registros. CAL 29/10/2022
		rewind(Arch);
		fseek(Arch,0,SEEK_END);
		CantDeRegistros = ftell(Arch) / sizeof(Competidor);
		rewind(Arch);
		
		//Si el archivo no tiene registros, se emite un mensaje de error y la funci�n finaliza al setearse la bandera en falso. CAL 29/10/2022
		if(CantDeRegistros == 0){
			Flag = 0;
			printf("\n\nEl archivo binario est%c vac%co. Pruebe la opci%cn 'Migrar datos entre archivos' o ingrese registros manualmente con la opci%cn 'Dar ALTA a competidor'\n",160,161,162,162);
		}
		
	} else{ //Si el archivo es nulo:
		Flag = 0;
		printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	}
	
	
	//Verifico que el archivo existe y el m�todo sea v�lido. CAL 29/10/2022
	if(Flag == 1 && Metodo > 1 && Metodo < 4){
		
		//La siguiente variable funciona tanto para el n�mero de orden como para el n�mero de competidor . CAL 30/10/2022
		char NumBuscado[12];

		
		if(Metodo == 2)	printf("\n\nIngrese el n%cmero de orden:\n",163);
		else if(Metodo == 3) printf("\n\nIngrese el n%cmero de corredor:\n",163);
		
		do{
			gets(NumBuscado);
			NumBuscado[10] = '\0'; //Cortamos la cadena en caso de que ingresen un n�mero de m�s de 9 d�gitos. CAL 30/10/2022
			
			if(ValidaNumSinDec(NumBuscado) == 0){ //Si no es un n�mero entero v�lido
				printf("\nHa ingresado un n%cmero incorrecto. Ingrese un n%cmero entero positivo v%lido.\n",163,163,160);
			}
			
		} while(ValidaNumSinDec(NumBuscado) == 0);
		
	//Si se pas� err�neamente un m�todo o ya se comprob� (y se dio aviso) de que el archivo es NULL o est� vac�o: - CAL 29/10/2022
	} else{
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
