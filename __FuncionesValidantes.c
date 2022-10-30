#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int ValidaNumConDec(char Numero[]){
	
	/*La siguiente función se encarga de validar que el texto pasado solo contenga numeros o exactamente un separador de decimales (no admite separador de milésimos).
	Devuelve 1 si el texto se reconoce como número con o sin decimales.
	Devuelve 0 si se encuentra algún caracter alfabético, caracter especial o si encuentra más de un punto o una coma o si encuentra un punto y una coma.
	CAL 29/10/2022
	*/
	
	//Si el string está vacío, devolver FALSO.
	if(strlen(Numero) == 0) return 0;
	
	//Utilizo bandera para devolver valor. CAL 29/10/2022
	int Flag = 1;
	
	//Utilizo acumulador de separadores.
	int CantSeparadores = 0;
	
	//Valida caracter a caracter que sea numero o separador.
	for (int i = 0; i < strlen(Numero); i++){
		if(Numero[i] == '.' || Numero[i] == ','){
			Numero[i] = '.';
			CantSeparadores ++;
			if(CantSeparadores > 1) Flag = 0;
		} else {//Si no es separador, debe ser dìgito
			if(!isdigit(Numero[i])) Flag = 0;
		}
	}
	
	return Flag;
	
};
int ValidaNumSinDec(char Numero[]){
	
	/*La siguiente función se encarga de validar que el texto pasado solo contenga numeros sin decimales ni ningún tipo de separador.
	Devuelve 1 si el texto se reconoce como número sin separadores.
	Devuelve 0 si se encuentra algún caracter alfabético, caracter especial o separador.
	CAL 29/10/2022
	*/
	
	//Si el string está vacío, devolver FALSO.
	if(strlen(Numero) == 0) return 0;
	
	//Utilizo bandera para devolver valor. CAL 29/10/2022
	int Flag = 1;
	
	//Valida caracter a caracter que sea numero.
	for (int i = 0; i < strlen(Numero); i++) if(!isdigit(Numero[i])) Flag = 0;
	
	return Flag;
	
};


int ValidaAbc(char Texto[]){
	/*La siguiente función se encarga de validar que el texto pasado solo contenga letras o espacios.
	Devuelve 1 si el texto se reconoce como alfabético
	Devuelve 0 si se encuentra algún número o caracter especial.
	CAL 29/10/2022
	*/
	
	//Si el string está vacío, devolver FALSO.
	if(strlen(Texto) == 0) return 0;
	
	//Utilizo bandera para devolver valor. CAL 29/10/2022
	int Flag = 1;
	
	//Valida caracter a caracter que sea espacio o letra.
	for (int i = 0; i < strlen(Texto); i++){
		if(!isalpha(Texto[i]) && !isspace(Texto[i])) Flag = 0;
		
		//Valido que, al menos, las primeras tres letras de la palabra no estén en blanco. CAL 30/10/2022
		if(i == 0 || i == 1 || i == 2){
			if(!isalpha(Texto[i])) Flag = 0;
		}
	}
	return Flag;
};

int ValidaCSV(FILE * Arch, char Delimitador){
	/*Esta función se creó con el objetivo de verificar que un archivo
	de extensión .CSV tenga el delimitador que necesitemos.
	Devuelve 1 si el delimitador se encuentra en el archivo.
	Devuelve 0 si NO se encuentra el delimitador en el archivo.
	La función devuelve -1 si el archivo es NULL.
		CAL 27/10/2022
	*/
	
	if(Arch == NULL) return -1;
	
	//La variable Flag indicará la presencia del delimitador. CAL 27/10/2022
	int Flag = 0;
	//La siguiente variable se encargará de almacenar al menos 1 línea para verificar la inclusión del delimitador. CAL 27/10/2022
	char LineaDePrueba[100] = {" "};
	
	//Posicionamos el puntero al inicio del archivo .CSV:
	rewind(Arch);
	fgets(LineaDePrueba,100,Arch);
	
	for (int i = 0; i < 100; i++){
		if(LineaDePrueba[i] == Delimitador){
			Flag = 1;
			break;
		}
	}
	//Volvemos a posicionar el puntero al inicio del archivo:
	rewind(Arch);
	
	return Flag;
};

int ValidaFecha(char Fecha[]){
	/*La siguiente función verifica que el string pasado como parámetro sea una fecha válida.
	Admite los siguientes 4 separadores de fecha: " " (espacio), "-", "/" y "."
	Modifica los separadores de fecha que se hayan ingresado y se reemplazan por '/'
	Entre sus verificaciones, se encuentran:
	
	*) Que solo contenga dos separadores
	*) Que el día se adecúe al mes y año que lo acompañan
	*) Que el mes sea válido
	*) Que el año sea bisiesto
	
	Devuelve 0 si el valor pasado no es una fecha admisible, o 1 en caso contrario.
	CAL 28/10/2022
	*/
	
	//************************************
	//SECCIÓN DE VERIFICACIÓN DE FORMATO
	//************************************
	
	//Suponiendo que pasen una fecha del estilo '1-1-2001', el mínimo de caracteres admisibles es 8. - CAL 28/102022
	//El máximo admisible es 10, suponiendo que pasen '31-12-2022'.
	if(strlen(Fecha) < 8 || strlen(Fecha) > 10) return 0;
	
	//Bandera de cantidad de separadores. CAL 28/10/2022
	int CantSeparadores = 0;
	
	/*Verifico que los separadores estén donde deben estar.
	
	*)Hay dos posibilidades para el primer separador:
	1/MM/YYYY - 2° Posición
	01/MM/YYYY - 3° Posición
	
	*)Para el segundo separador, las opciones varían según dónde se encuentre
	el primer separador:
	1/1/YYYY - 2° Pos. (primer separador) y 4° posición (segundo separador)
	1/12/YYYY - 2° Pos. y 5° posición
	31/1/YYYY - 3° Pos. y 5 posición
	01/01/YYYY - 3° Pos. y 6° posición
	
	En resumen:
	*) Si el primer separador está en la 2° posición, el segundo separador solo puede estar en la 4° o 5° posición.
	*) Si el primer separador está en la 3° posición, el segundo separador solo puede estar en la 5° o 6° posición.
	
	CAL 28/10/2022
	*/
	
	//Guardo el índice del primer y segundo separador: - CAL 28/10/2022
	int PrimeraPosicion, SegundaPosicion;
	
	//Verifico que el año tenga 4 dígitos. Para esto, empiezo a contar los dígitos desde el segundo separador. CAL 28/10/2022
	int DigitosAnio = 0;
	
	for(int i = 0; i < strlen(Fecha);i++){
		
		//Cuento los dígitos del año a partir del segundo separador. CAL 28/10/2022
		if (CantSeparadores == 2) DigitosAnio++;
		
		//Compruebo que contenga dos caracteres separadores admisibles y que estén en donde deben. CAL 28/10/2022
		if(Fecha[i] == ' ' || Fecha[i] == '-' || Fecha[i] == '/' || Fecha[i] == '.'){
			Fecha[i] = '/';
			CantSeparadores++;
			if(CantSeparadores == 1){ //Si estamos en el primer separador, verificamos que su posición sea la 2° o 3°
				PrimeraPosicion = i + 1;
				if(PrimeraPosicion != 2 && PrimeraPosicion != 3) return 0; //Si no es la posición correcta, la función devuelve falso. CAL 28/10/2022
			}
			else if(CantSeparadores == 2){ //Si estamos en el segundo separador, verificamos que su posición se adecúe respecto a la posición del primer separador.
				SegundaPosicion = i + 1;
				if (PrimeraPosicion == 2) {if(SegundaPosicion != 4 && SegundaPosicion != 5) return 0;} //Si el primero está 2°, el segundo puede estar 4° o 5°. CAL 28/10/2022 
				else if (PrimeraPosicion == 3) {if(SegundaPosicion != 5 && SegundaPosicion != 6) return 0;} //Si el primero está 3°, el segundo puede estar 5° o 6°. CAL 28/10/2022
			}
			else return 0; //Si la cantidad de separadores supera los 2, devuelve FALSO. CAL 28/10/2022
			
		} else { //Si el caracter actual no es un separador, debe ser numérico.
			if(!isdigit(Fecha[i])) return 0;
		}
	}
	
	
	//Verifico que el año tenga 4 dígitos. CAL 28/10/2022
	if(DigitosAnio != 4) return 0;
	
	
	//************************************
	//SECCIÓN DE VERIFICACIÓN DE VALORES
	//************************************
	
	//Creo las variables que necesito para dividir la fecha en día, mes y año y realizar las validaciones de valores. CAL 28/10/2022
	char CDia[3] = {""};
	char CMes[3] = {""};
	char CAnio[5] = {""};
	
	//Copio el día hasta la primera posición divisora encontrada previamente. CAL 28/10/2022
	strncpy(CDia, Fecha, (PrimeraPosicion - 1));
	
	//Repito la operación con la que copié el día para obtener los datos del mes. Apunto la cadena hacia después del primer divisor. CAL 28/10/2022
	strncpy(CMes, Fecha + PrimeraPosicion, (SegundaPosicion - PrimeraPosicion - 1));
	
	//Por último, copio el año que ya se verificó tiene 4 dígitos. CAL 28/10/2022
	strncpy(CAnio, Fecha + SegundaPosicion, 4); 
	
	//Valido el primer dígito del año. CAL 28/10/2022
	if (CAnio[0] != '1' && CAnio[0] != '2') return 0; //Si no es milenio 1000 o 2000, devuelve falso.
	
	//Valido el mes. CAL 28/10/2022
	if ( atoi(CMes) < 1 || atoi(CMes) > 12 ) return 0;
	
	//Por último, valido el día dependiendo del mes, y al mismo tiempo de que el año sea o no bisiesto. CAL 28/10/2022
	if (atoi(CDia) < 1) return 0;
	
	//Valido si el año es bisiesto:
	int Bisiesto;
	
	if(atoi(CAnio) % 4 == 0) Bisiesto = 1;
	else Bisiesto = 0;
	
	switch (atoi(CMes)){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (atoi(CDia) > 31) return 0;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (atoi(CDia) > 30) return 0;
	case 2:
		if(Bisiesto == 1){
			if (atoi(CDia) > 29) return 0;
		} else {
			if (atoi(CDia) > 28) return 0;
		}
		break;
		
	} //Omitimos el caso default porque ya se verificó que el mes esté entre 1 y 12. CAL 28/10/2022
	
	//Si supera todas las validaciones, devuelve VERDADERO.
	return 1;
	
}

int ConvertirMesAString(int Mes, char CharMes[]){
	/*La siguiente función toma un mes válido en forma de entero (pasado en el primer parámetro)
	e inserta las primeras tres letras en minúsculas del nombre del mes en el arreglo de caracteres pasado como segundo parámetro.
	Devuelve 0 si el mes dado en entero es erróneo, o 1 si la operación fue exitosa.
	CAL 29/10/2022
	*/
	
	if (Mes < 1 || Mes > 12) return 0;
	
	switch(Mes){
	case 1:
		strcpy(CharMes,"ene");
		break;
	case 2:
		strcpy(CharMes,"feb");
		break;
	case 3:
		strcpy(CharMes,"mar");
		break;
	case 4:
		strcpy(CharMes,"abr");
		break;
	case 5:
		strcpy(CharMes,"may");
		break;
	case 6:
		strcpy(CharMes,"jun");
		break;
	case 7:
		strcpy(CharMes,"jul");
		break;
	case 8:
		strcpy(CharMes,"ago");
		break;
	case 9:
		strcpy(CharMes,"sep");
		break;
	case 10:
		strcpy(CharMes,"oct");
		break;
	case 11:
		strcpy(CharMes,"nov");
		break;
	case 12:
		strcpy(CharMes,"dic");
		break;
	default:
		return 0;
	}
	
	return 1;
}

	
int ExtraerDeFecha(char Fecha[],char DatoAExtraer, char Separador){
	/* 1º Extrae de la fecha pasada como primer parámetro, el dato pasado como segundo parámetro.
	2º El segundo parámetro puede ser: 'd': Día, 'm': Mes o 'a': Año (indistintamente de si se pasa con mayúsculas o minúsculas) y devuelve este dato como entero.
	3º La fecha debe estar separada con el separador indicado como tercer parámetro.
	Además el formato de fecha debe incluír todos sus datos en forma numérica (el mes no puede estar expresado en letras), indistintamente de si se utilizan 1 o 2 dígitos para el dìa y mes y 4 o 2 para el año.
	Se recomienda usar la función 'ValidaFecha' antes de usar esta función ya que esta no se encarga de realizar todas las validaciones.
	Devuelve 0 si la fecha pasada es vacía, si se encuentra algún error de formato o si se pasó algun parámetro en forma errónea.
	CAL 29/10/2022
	*/
	
	//Si el string es vacío, devolver FALSO
	if(strlen(Fecha) == 0) return 0;
	
	//Si el formato es: d/m/aa el mínimo de caracteres es 6
	//Si el formato es: dd/mm/aaaa el máximo de caracteres es 10
	if(strlen(Fecha) < 6 || strlen(Fecha) > 10) return 0;
	
	//Almaceno la cantidad de separadores que se encuentran (deben ser 2)
	int CantSeparadores = 0;
	
	
	int PosSeparador1 = 0;
	int PosSeparador2 = 0;
	
	for(int i = 0; i < strlen(Fecha); i++){
		if(Fecha[i] == Separador){
			//Si encuentra un separador, verifica que no supere los dos y almacena su posición
			CantSeparadores ++;
			if(CantSeparadores == 1) PosSeparador1 = i + 1;
			else if (CantSeparadores == 2) PosSeparador2 = i + 1;
			else return 0;
		} else{
			if(!isdigit(Fecha[i])) return 0;
		}
	}
	
	if (CantSeparadores != 2) return 0;
	
	//Defino la variable en la que se guardará el dato. CAL 29/10/2022
	char Dato[5] = {""};
	DatoAExtraer = toupper(DatoAExtraer);
	
	switch(DatoAExtraer){
	case 'D': //En caso de que se haya solicitado el día
		strncpy(Dato,Fecha, PosSeparador1 - 1);
		break;
	case 'M': //En caso de que se haya solicitado el mes
		strncpy(Dato,Fecha + PosSeparador1, PosSeparador2 - PosSeparador1 - 1);
		break;
	case 'A': //En caso de que se haya pedido el año.
		strncpy(Dato,Fecha + PosSeparador2, strlen(Fecha) - PosSeparador2);
		break;
	default:
		return 0;
	}
	
	return atoi(Dato);
	
}
