#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "FuncionesValidantes.h"
#include "Estructuras.h"

void ListarTxt(FILE * Arch){
	//La siguiente función utiliza un archivo de extensión .CSV para listar su contenido en forma de tabla.
	//El archivo debe contener las siguientes columnas:
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
			
			//Posicionamos el puntero al inicio del archivo:
			rewind(Arch);
			
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
			//En caso de que se haya denegado el reemplazo del archivo, no se hace nada con el que ya estaba abierto.
			printf("\nEl archivo no se ha sobreescrito y permanece intacto.\n\n");
			rewind(Arch);
		}
	}
};
	
void MigrarDatos(FILE * ArchOrgn, FILE * ArchDstn){
	//La siguiente función se encarga de traspasar todos los datos de competidores desde el archivo '.CSV' al archivo '.DAT'
	//Siempre va a colocar los datos al inicio del archivo .DAT, por lo que si hay datos previos en el archivo destino, los va a reemplazar. CAL 27/10/2022
	
	//Control de error: Verifico que ambos archivos existan.
	if(ArchOrgn != NULL && ArchDstn != NULL){
		
		//Control de error: verifico que el delimitador exista en el archivo .CSV:
		//Para esto utilizo la función validante definida en '__FuncionesValidantes.c'
		//Almaceno el valor de dicha función en una variable Flag. CAL 27/10/2022
		
		int Flag = ValidaCSV(ArchOrgn,';');
		
		if (Flag == 1){
			
			//Definimos la variable Comp de tipo 'struct Competidor' (estructura definida en 'Estructuras.h'). CAL 27/10/2022
			//El uso de la variable será transportar  cada una de las líneas del .CSV hacia el .DAT
			Competidor Comp;
			
			//Posicionamos los punteros de ambos archivos al inicio
			rewind(ArchOrgn);
			rewind(ArchDstn);
			
			//El valor de "Activo" siempre es 1 al migrar los datos.
			Comp.Activo = 1;
			
			//Repetimos esta línea al final del ciclo para evitar que nos repita la última fila
			fscanf(ArchOrgn, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Comp.NrOrd, &Comp.NrCorr,&Comp.Dia,Comp.Mes,&Comp.Anio,&Comp.Edad, Comp.Pais, &Comp.Tiempo);
			
			//Iniciamos el ciclo que transporta los datos
			do{
				fwrite(&Comp,sizeof(Competidor),1,ArchDstn);
				fscanf(ArchOrgn, "%d;%d;%d;%3s;%d;%d;%3s;%f",&Comp.NrOrd, &Comp.NrCorr,&Comp.Dia,Comp.Mes,&Comp.Anio,&Comp.Edad, Comp.Pais, &Comp.Tiempo); 
			} while(!feof(ArchOrgn));
			
			printf("\n\n******************************************\n");
			printf("Se han migrado los datos correctamente.");
			printf("\n******************************************\n\n");
			
		
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
	El segundo parámetro indica el tipo de visualización que se va a efectuar (se puede ver la función 'MenuListarBinario' para tener una ayuda visual):
	
	Si método es 2: Se listarán todos los usuarios (Activos e inactivos).
	Si método es 3: Se listarán solamente los usuarios activos.
	Si método es 4: Se pedirá que se ingrese un país y se mostrarán únicamente todos los usuarios pertenecientes a ese país.
	Si método es 5: Se pedirá un rango de tiempo y se mostrarán únicamente todos los usuarios que tengan la columna "Tiempo" dentro de ese rango.
	*/
	
	//La siguiente bandera nos servirá en la función para verificar datos. (0 = FALSO, 1 = VERDADERO). CAL 29/10/2022
	int Flag = 1;
	
	//Verificamos que el archivo binario contenga datos:
	rewind(Arch);
	fseek(Arch,0,SEEK_END);
	if(ftell(Arch) / sizeof(Competidor) == 0) Flag = 0; //Si el archivo está vacío, setear la bandera en FALSO.
	rewind(Arch); //Por seguridad, siempre seteo el puntero al inicio del archivo. CAL 29/10/2022
	
	
	//Verifico que el archivo no sea nulo y que tenga datos
	if(Arch != NULL && Flag == 1) {
	
		//Defino las variables que puedo llegar a necesitar según el método:
		
		//Para que el usuario sea libre de escribir el nombre de un país completo en caso de que el método sea 4:
		char PaisLargo[25];
		char PaisCorto[4]; //Se mostraran solo los 3 primeros caracteres del país
		
		//En caso de que el método sea 5, las cadenas almacenan los valores ingresados por el usuario y los validan:
		char ChTiempoMin[13] = {""};
		char ChTiempoMax[13] = {""};
		
		//Los valores flotantes se usan para filtrar los datos de los competidores:
		float TiempoMin = -1;
		float TiempoMax = -1;
		
		if(Metodo == 4){
			//Se pregunta por el país
			printf("\nHa seleccionado mostrar a los competidores filtrados por pa%cs\n", 161);
			printf("Ingrese el pa%cs para filtrar:\n", 161);
			
			//Inicio del ciclo que verifica que el país sea válido
			do{
				gets(PaisLargo);
				PaisLargo[23] = '\0'; //Fuerzo el último caracter a que sea NULL en caso de que se hayan ingresado más de 24 caracteres.
				
				//Se realiza la validación de que el string solo contenga caracteres alfabéticos. CAL 29/10/2022
				if(ValidaAbc(PaisLargo) == 0) printf("\n\nHa ingresado un pa%cs err%cneo. Ingrese un pa%cs %cnicamente ingresando valores alfab%cticos:\n",161,162,161,163,130);
			}
			while(ValidaAbc(PaisLargo) == 0);
			
			//Convertimos las letras del país a mayúsculas:
			for(int i = 0; i < strlen(PaisLargo); i++) PaisLargo[i] = toupper(PaisLargo[i]);
			
			//Copiamos los tres primeros caracteres del país escrito
			strncpy(PaisCorto,PaisLargo,3);
			
			printf("\n\n************************************************\n");
			printf("Mostrando datos del pa%cs: %s",161,PaisLargo);
			printf("\n************************************************\n\n");
			
		} else if(Metodo == 5) {
			//Se pregunta por el tiempo. CAL 29/10/2022
				
			//*****************************************************
			//INICIO DEL CICLO DE VALIDACIÓN PARA EL TIEMPO MÍNIMO
			//*****************************************************
			
			//SE UTILIZA LA BANDERA 'FLAG' EN ESTE CASO. CAL 29/10/2022
			
			//Se solicitan los datos. CAL 29/10/2022
			printf("\nHa seleccionado mostrar a los competidores filtrados por tiempo\n");
			printf("Ingrese el tiempo m%cnimo para filtrar (puede contener decimales, pero no use separador de mil%csimos):\n", 161,130);
			
			do{
				gets(ChTiempoMin);
				ChTiempoMin[11] = '\0'; //Fuerzo el último caracter a nulo en caso de que se hayan introducido más valores de lo esperado.
				
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
			
			//Se asigna el valor como flotante en caso de que se haya superado la validación. CAL 29/10/2022
			TiempoMin = (float) atof(ChTiempoMin);
			
			//*****************************************************
			//INICIO DEL CICLO DE VALIDACIÓN PARA EL TIEMPO MÁXIMO
			//*****************************************************
			
			//Se solicitan los datos. CAL 29/10/2022
			printf("\n\nHa seleccionado como tiempo m%cnimo: %.6f\n", 161,TiempoMin);
			printf("Ingrese el tiempo m%cximo (puede contener decimales, pero no use separador de mil%csimos):\n", 160,130);
			
			//En este ciclo, además se deberá verificar que el tiempo máximo sea mayor al tiempo mínimo elegido.
			do{
				gets(ChTiempoMax);
				ChTiempoMax[11] = '\0'; //Fuerzo el último caracter a nulo en caso de que se hayan introducido más valores de lo esperado.
				
				if(ValidaNumConDec(ChTiempoMax) == 0){
					Flag = 0;
					printf("\n\nHa introducido un tiempo m%cximo incorrecto. Introduza solo n%cmeros o a lo sumo con un separador de decimales:\n",160,163);
				}
				else{
					//Si el tiempo máximo es menor al tiempo mínimo, se emite mensaje de error. CAL 29/10/2022
					if(atof(ChTiempoMax) < TiempoMin) {
						Flag = 0;
						printf("\n\nHa introducido un tiempo m%cximo menor al tiempo m%cnimo ingresado anteriormente.\n",160,161);
						printf("Introduza un n%cmero mayor a %.6f:\n",163, TiempoMin);
					} else {Flag = 1;}
				}
			} while(Flag == 0);
			
			//Se asigna el valor como flotante en caso de que se haya superado la validación. CAL 29/10/2022
			TiempoMax = (float) atof(ChTiempoMax);
			
			printf("\n\n************************************************\n");
			printf("Mostrando datos de entre: \n");
			printf("*)Tiempo m%cnimo %.6f\n", 161,TiempoMin);
			printf("*)Tiempo m%cximo %.6f", 160,TiempoMax);
			printf("\n************************************************\n\n");
			
		}
		
		//Luego de comprobar los dos métodos que solicitan datos, procedo a la creación del esqueleto de la tabla:
		
		const char * COrden = {"Orden"}; // Columna 1: Ancho 5
		const char * CCorredor = {"Corredor"}; //Columna 2: Ancho 10
		const char * CDia = {"Dia"}; // Columna 3: Ancho 5
		const char * CMes = {"Mes"}; //Columna 4: Ancho 5
		//Columna 5 (Año): Ancho 5 -> La escribí en el printf, ya que no puedo asignar la letra 'ñ' en un const char *
		const char * CEdad = {"Edad"}; //Columna 6: Ancho 5
		const char * CPais = {"Pais"}; //Columna 7: Ancho 5
		const char * CActivo = {"Activo"}; //Columna 8: Ancho 6
		const char * CTiempo = {"Tiempo"}; //Columna 9: Ancho 10
		
		//La siguiente variable me sirve para crearle los bordes superior e inferior a la tabla. CAL 26/10/2022
		const char * LineasDivisoras = {"------------------------------------------------------------------------------------"};
		
		//Imprimo los títulos. CAL 29/10/2022
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
		
		//Repito la siguiente línea al final del ciclo para evitar que repita la última fila. CAL 29/10/2022
		fread(&Comp, sizeof(Competidor),1,Arch);
		
		do{
			//Restablezco la bandera en FALSO en cada vuelta de ciclo
			Flag = 0;
			
			switch(Metodo){
			case 2:
				//Mostrar todos los usuarios(el número de orden debe ser distinto de cero). CAL 29/10/2022
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
			
			//Si se activó la bandera, imprimir los datos del competidor.
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
	/*La siguiente función registra un nuevo competidor en el archivo de extensión .DAT.
	Dicho archivo debe tener habilitada la opción de "ESCRITURA BINARIA"
	Todos los registros vacíos que estén entre el primer competidor y el número de orden ingresado tendrán todos sus campos convertidos en cero.
	CAL 29/10/2022
	*/
	
	//Verifico que el archivo no sea nulo.
	if(Arch != NULL){
		
		//*********************************
		//INICIO DE CICLOS EN SECUENCIA
		//*********************************
		
		//Cada uno de los ciclos tendrá como finalidad asegurarse de que los datos solicitados sean válidos.
		//El método de validación consiste en hacer uso de las funciones diseñadas especialmente para validar datos en '__FuncionesValidantes.c'
		//Hasta que la función validante no devuelva VERDADERO, no se sale del ciclo.
		
		//Para validarlos se hará uso de la siguiente bandera:
		int Flag; //0 indica FALSO y 1 VERDADERO - CAL 29/10/2022
		
		//Creamos el competidor que almacenará los datos a ingresar.
		Competidor Comp;
		
		//Nos posicionamos al inicio del archivo y obtenemos cuántos registros existen
		//(será de utilidad para verificar que el orden no supere la cantidad de registros) - CAL 29/10/2022
		
		rewind(Arch);
		fseek(Arch,0,SEEK_END);
		int CantDeRegistros = ftell(Arch) / sizeof(Competidor);
		
		//Volvemos a posicionarnos la inicio
		rewind(Arch);
		
		//*****************
		//CICLO DE ORDEN:
		//*****************
		//Verifica que el orden no esté ocupado y, además, que sea un número entero válido.
		
		printf("\nIngrese un n%cmero de orden para dar de alta. Debe ser un entero positivo y no puede contener m%cs de 7 caracteres:\n",163,160);
		
		//Almacenamos el orden ingresado en un char para comprobar su validez. CAL 29/10/2022
		char ChOrden[9] ={""};
		
		do{
			Flag = 0; //Seteamos la bandera en FALSO en cada vuelta.
			gets(ChOrden);
			ChOrden[7] = '\0'; //Seteamos en NULL los últimos dígitos del char en caso de que ingresen más caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			if(ValidaNumSinDec(ChOrden) == 1){
				//En caso de que el número de orden ingresado sea válido, se procederá a verificar que no esté ocupado por otro competidor. CAL 29/10/2022
				if(atoi(ChOrden) > CantDeRegistros){ //Si el número de orden supera la cantidad de registros existentes, solo puede ser válido.
					Flag = 1;
				} else{ //En caso de que no supere la cantidad de registros, se verifica que el número sea mayor a cero y que no esté ocupado por otro competidor. CAL 29/10/2022
					if(atoi(ChOrden) < 1){
						printf("\n\nError. El n%cmero ingresado debe ser mayor a cero. Ingrese un n%cmero de orden v%clido:\n",163,163,160);
						Flag = 0;
					} else{ //En caso de que el orden sea válido pero sea menor o igual a la cantidad de registros, se verifica que no esté ocupado. CAL 29/10/2022
						
						//Los rewind son por seguridad, descartan que el archivo pueda haber quedado apuntado en otro lugar
						rewind(Arch);
						fseek(Arch, sizeof(Competidor) * (atoi(ChOrden) - 1),SEEK_CUR);
						fread(&Comp,sizeof(Competidor),1,Arch);
						rewind(Arch);
						
						if(Comp.NrOrd != 0){
							printf("\n\nEl n%cmero de orden ingresado ya est%c ocupado. Ingrese un nuevo n%cmero de orden:\n",163,160,163);
							Flag = 0;
						} else{ //En caso de que el lugar no esté ocupado, se habilita la bandera.
							Flag = 1;
						}
						
					}
					
					
				}
			} else{ //En caso de que no supere la validación de la función 'ValidaNumSinDec':
				printf("\n\nHa ingresado un n%cmero de orden no v%clido. Ingrese un n%cmero entero mayor a cero:\n",163,160,163);
				Flag = 0;
			}
			
		} while (Flag == 0);
		
		
		//******************************
		//CICLO DE NÚMERO DE CORREDOR:
		//******************************
		//Simplemente verifica sea un número entero válido y positivo, y que el número de corredor no se repita con otro.
		
		printf("\nIngrese un n%cmero de corredor. Debe ser un entero positivo y no puede contener m%cs de 8 caracteres. Tampoco puede estar repetido:\n",163,160);
		
		//Almacenamos el nro de corredor ingresado en un char para comprobar su validez. CAL 29/10/2022
		char ChCorredor[10] ={""};
		
		do{
			Flag = 0; //Seteamos la bandera en FALSO en cada vuelta.
			gets(ChCorredor);
			ChCorredor[8] = '\0'; //Seteamos en NULL los últimos dígitos del char en caso de que ingresen más caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			if(ValidaNumSinDec(ChCorredor) == 1){
				//Si supera la validación de número entero:
				
				//Debe ser un número mayor a cero.
				if(atoi(ChCorredor) < 1) {
					printf("\n\nEl n%cmero de corredor debe ser mayor a cero.\n",163);
					Flag = 0;
				} else {
					//Si el número de corredor es válido, se verifica que no esté repetido.
					
					//Se establece la bandera en "Verdadero" y se desactiva si el número de corredor se encuentra en otro competidor.
					Flag = 1;
					
					rewind(Arch);
					
					for(int i = 0; i < CantDeRegistros; i++){
						fread(&Comp,sizeof(Competidor),1,Arch);
						if(Comp.NrCorr == atoi(ChCorredor)) Flag = 0;
					}
					
					rewind(Arch);
					//Si el número de corredor se encontró repetido, emite un mensaje de error:
					if (Flag == 0) printf("\n\nEl n%cmero de corredor ingresado ya existe con el n%cmero de orden: %d. Ingrese otro n%cmero de corredor.\n",163,163,Comp.NrOrd,163);
				} 
				
			} else { //Si no supera la validación de número entero:
				printf("\n\nHa ingresado un n%cmero incorrecto. Ingrese un n%cmero entero sin signos ni caracteres especiales:\n",163,163);
				Flag = 0;
			}
		} while (Flag == 0);
		
		
		//****************
		//CICLO DE FECHA:
		//****************
		//Valida que la fecha sea válida.
		
		printf("\n\nIngrese la fecha del corredor con formato 'dd-mm-yyyy' (en vez de guiones puede separar los valores con barras '/', espacios ' ' o puntos '.', pero lo importante es que todos los d%cgitos sean num%cricos:\n",161,163);
		
		//Almacenamos la fecha en un char para comprobar su validez. CAL 29/10/2022
		char ChFecha[13] ={""};
		
		do{
			Flag = 0; //Seteamos la bandera en FALSO en cada vuelta.
			gets(ChFecha);
			ChFecha[11] = '\0'; //Seteamos en NULL los últimos dígitos del char en caso de que ingresen más caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
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
		//Valida que la edad sea válida.
		
		printf("\n\nIngrese la edad del corredor:\n");
		char ChEdad[5] = {""};
		
		do{
			Flag = 0;
			gets(ChEdad);
			ChEdad[3] = '\0'; //Seteamos en NULL los últimos dígitos del char en caso de que ingresen más caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			//Si el número leído no supera la validación:
			if(ValidaNumSinDec(ChEdad) == 0){
				printf("\n\nHa ingresado un n%cmero err%cneo. Ingrese una edad v%clida:\n",163,162,160);
				Flag = 0;
			} else {
				//Si supera la validación de fórmula, se procede a verificar que la edad sea real:
				if(atoi(ChEdad) > 0 && atoi(ChEdad) < 161) {
					Flag = 1;
				} else {
					printf("\n\nNo es posible que un competidor tenga la edad indicada. Ingrese una edad verdadera:\n");
					Flag = 0;
				}
			}
		} while (Flag == 0);
		
		
		//********************
		//CICLO DE PAÍS
		//********************
		//Se procede a verificar que el país esté bien escrito. CAL 29/10/2022
		
		printf("\n\nIngrese el pa%cs del corredor:\n",161);
		char ChPais[25] = {""};
		
		do{
			Flag = 0;
			gets(ChPais);
			ChEdad[23] = '\0'; //Seteamos en NULL los últimos dígitos del char en caso de que ingresen más caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			//Si el pais leído no supera la validación:
			if(ValidaAbc(ChPais) == 0){
				printf("\n\nHa ingresado un pa%cs err%cneo. Ingrese un pa%cs v%clido usando solamente caracteres alfab%cticos:\n",161,162,161,160,130);
				Flag = 0;
			} else {
				//Se convierten los caracteres del país en mayúsculas
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
			ChTiempo[23] = '\0'; //Seteamos en NULL los últimos dígitos del char en caso de que ingresen más caracteres que los permitidos con el 'gets'. CAL 29/10/2022
			
			//Si el pais leído no supera la validación:
			if(ValidaNumConDec(ChTiempo) == 0){
				printf("\n\nHa ingresado un tiempo err%cneo. Ingrese un tiempo v%clido usando solamente separador de decimales en caso de que lo necesite (no use separadores de mil%csimos):\n",162,160,130);
				Flag = 0;
			} else {
				//Se convierten los caracteres del país en mayúsculas
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
		
		//Si el número de orden ingresado es mayor a la cantidad de registros existentes, me posiciono al final del archivo y voy cargando en cero todos los datos intermedios. CAL 29/10/2022
		
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
			El ciclo recorre todo el archivo binario a partir de la última posición e irá rellenando con ceros todas aquellas posiciones intermedias
			Entre la última fila preexistente y el nuevo número de orden.
			*/
			
			//Declaro una variable que será la que almacene el tope del bucle:
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
		
		//Una vez finalizada la etapa de validación y una vez llegado a la posición del número de orden, se procede a almacenar el competidor. CAL 29/10/2022
		Comp.NrOrd = atoi(ChOrden);
		Comp.NrCorr = atoi(ChCorredor);
		Comp.Dia = ExtraerDeFecha(ChFecha,'d','/');
		
		//Comp.Mes: Para el mes, se crea una variable que servirá para almacenar el valor entero del mes y luego se usará una función predefinida para almacenar sus tres primeros caracteres. CAL 29/10/2022
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
	/*La presente función busca y muestra los datos de un competidor dado mediante dos métodos distintos, el cual se elige en el segundo parámetro.
	Para una ayuda más visual, se puede ver 'MenuBuscarComp' en el archivo '__Menus.c'
	* Si método es 2: Busca un competidor por número de orden. (acceso directo)
	* Si método es 3: Busca un competidor por número de corredor. (acceso secuencial)
	CAL 29/10/2022
	*/
	
	//Se usa una bandera para indicar si el dato que se busca está disponible:
	int Flag = 1; //Por defecto la seteamos en VERDADERO
	
	//Creo la variable que conte
	int CantDeRegistros;
	
	//Si el archivo es NULO, se setea la bandera en falso y la función finaliza.
	if(Arch != NULL){
		//Si el archivo no es falso, se verifica que contenga datos...
		//Almacenamos la cantidad de registros. CAL 29/10/2022
		rewind(Arch);
		fseek(Arch,0,SEEK_END);
		CantDeRegistros = ftell(Arch) / sizeof(Competidor);
		rewind(Arch);
		
		//Si el archivo no tiene registros, se emite un mensaje de error y la función finaliza al setearse la bandera en falso. CAL 29/10/2022
		if(CantDeRegistros == 0){
			Flag = 0;
			printf("\n\nEl archivo binario est%c vac%co. Pruebe la opci%cn 'Migrar datos entre archivos' o ingrese registros manualmente con la opci%cn 'Dar ALTA a competidor'\n",160,161,162,162);
		}
		
	} else{ //Si el archivo es nulo:
		Flag = 0;
		printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	}
	
	
	//Verifico que el archivo existe y el método sea válido. CAL 29/10/2022
	if(Flag == 1 && Metodo > 1 && Metodo < 4){
		
		//La siguiente variable funciona tanto para el número de orden como para el número de competidor . CAL 30/10/2022
		char NumBuscado[12];

		
		if(Metodo == 2)	printf("\n\nIngrese el n%cmero de orden:\n",163);
		else if(Metodo == 3) printf("\n\nIngrese el n%cmero de corredor:\n",163);
		
		do{
			gets(NumBuscado);
			NumBuscado[10] = '\0'; //Cortamos la cadena en caso de que ingresen un número de más de 9 dígitos. CAL 30/10/2022
			
			if(ValidaNumSinDec(NumBuscado) == 0){ //Si no es un número entero válido
				printf("\nHa ingresado un n%cmero incorrecto. Ingrese un n%cmero entero positivo v%lido.\n",163,163,160);
			}
			
		} while(ValidaNumSinDec(NumBuscado) == 0);
		
	//Si se pasó erróneamente un método o ya se comprobó (y se dio aviso) de que el archivo es NULL o está vacío: - CAL 29/10/2022
	} else{
		if(Metodo < 2 || Metodo > 3) printf("\n\nHa pasado un par%cmetro de m%ctodo err%cneo. Verifique la funci%cn desde el c%cdigo fuente.\n",160,130,162,162,162);
	}
}
	
void ModificarCompetidor(FILE * Arch){
	/*La siguiente función modifica un competidor en el archivo de extensión .DAT.
	Dicho archivo debe tener habilitada la opción de "ESCRITURA BINARIA"
	CAL 29/10/2022
	*/
	
	//Verifico que el archivo exista. CAL 29/10/2022
	if(Arch != NULL){
		
		printf("\nSe ha modificado un competidor.\n");
		
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	
}
	
void BajaLogica(FILE * Arch){
	/*La siguiente modifica el campo "Activo" de un competidor en el archivo de extensión .DAT y lo deja en cero (0).
	Dicho archivo debe tener habilitada la opción de "ESCRITURA BINARIA"
	CAL 29/10/2022
	*/
	//Verifico que el archivo exista. CAL 29/10/2022
	if(Arch != NULL){
	
		printf("\nSe ha dado la baja logica de un competidor.\n");
		
	} else printf("\n\nHubo un error con el archivo. Verifique que exista, que no est%c siendo utilizado por ning%cn otro programa y vuelva a intentarlo.\n", 160,163);
	
}
	
void BajaFisica(FILE * ArchDat, FILE * ArchBajasFis, const char * NombreArchBajasFis){
	/*La siguiente función modifica los datos de un competidor en el archivo de extensión .DAT y deja todos sus campos en cero (0).
	Dicho archivo debe tener habilitada la opción de "ESCRITURA BINARIA"
	Además, esta función registra las bajas físicas en otro archivo .DAT que crea en caso de que no exista (si no, los agrega al inicio del documento).
	CAL 29/10/2022
	*/
	//Verifico que ambos archivos existan. CAL 29/10/2022
	
	if(ArchBajasFis == NULL) {
		//Si no existe el archivo, lo creo. CAL 29/10/2022
		ArchBajasFis = fopen(NombreArchBajasFis,"wb+");
	}
	
	//Si el archivo DAT que contiene la información de los competidores activos no existe, entonces la función no puede ejecutar nada. CAL 29/10/2022
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
