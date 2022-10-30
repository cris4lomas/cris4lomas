#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int ValidaNumConDec(char Numero[]){
	
	/*La siguiente funci�n se encarga de validar que el texto pasado solo contenga numeros o exactamente un separador de decimales (no admite separador de mil�simos).
	Devuelve 1 si el texto se reconoce como n�mero con o sin decimales.
	Devuelve 0 si se encuentra alg�n caracter alfab�tico, caracter especial o si encuentra m�s de un punto o una coma o si encuentra un punto y una coma.
	CAL 29/10/2022
	*/
	
	//Si el string est� vac�o, devolver FALSO.
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
		} else {//Si no es separador, debe ser d�gito
			if(!isdigit(Numero[i])) Flag = 0;
		}
	}
	
	return Flag;
	
};
int ValidaNumSinDec(char Numero[]){
	
	/*La siguiente funci�n se encarga de validar que el texto pasado solo contenga numeros sin decimales ni ning�n tipo de separador.
	Devuelve 1 si el texto se reconoce como n�mero sin separadores.
	Devuelve 0 si se encuentra alg�n caracter alfab�tico, caracter especial o separador.
	CAL 29/10/2022
	*/
	
	//Si el string est� vac�o, devolver FALSO.
	if(strlen(Numero) == 0) return 0;
	
	//Utilizo bandera para devolver valor. CAL 29/10/2022
	int Flag = 1;
	
	//Valida caracter a caracter que sea numero.
	for (int i = 0; i < strlen(Numero); i++) if(!isdigit(Numero[i])) Flag = 0;
	
	return Flag;
	
};


int ValidaAbc(char Texto[]){
	/*La siguiente funci�n se encarga de validar que el texto pasado solo contenga letras o espacios.
	Devuelve 1 si el texto se reconoce como alfab�tico
	Devuelve 0 si se encuentra alg�n n�mero o caracter especial.
	CAL 29/10/2022
	*/
	
	//Si el string est� vac�o, devolver FALSO.
	if(strlen(Texto) == 0) return 0;
	
	//Utilizo bandera para devolver valor. CAL 29/10/2022
	int Flag = 1;
	
	//Valida caracter a caracter que sea espacio o letra.
	for (int i = 0; i < strlen(Texto); i++){
		if(!isalpha(Texto[i]) && !isspace(Texto[i])) Flag = 0;
		
		//Valido que, al menos, las primeras tres letras de la palabra no est�n en blanco. CAL 30/10/2022
		if(i == 0 || i == 1 || i == 2){
			if(!isalpha(Texto[i])) Flag = 0;
		}
	}
	return Flag;
};

int ValidaCSV(FILE * Arch, char Delimitador){
	/*Esta funci�n se cre� con el objetivo de verificar que un archivo
	de extensi�n .CSV tenga el delimitador que necesitemos.
	Devuelve 1 si el delimitador se encuentra en el archivo.
	Devuelve 0 si NO se encuentra el delimitador en el archivo.
	La funci�n devuelve -1 si el archivo es NULL.
		CAL 27/10/2022
	*/
	
	if(Arch == NULL) return -1;
	
	//La variable Flag indicar� la presencia del delimitador. CAL 27/10/2022
	int Flag = 0;
	//La siguiente variable se encargar� de almacenar al menos 1 l�nea para verificar la inclusi�n del delimitador. CAL 27/10/2022
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
	/*La siguiente funci�n verifica que el string pasado como par�metro sea una fecha v�lida.
	Admite los siguientes 4 separadores de fecha: " " (espacio), "-", "/" y "."
	Modifica los separadores de fecha que se hayan ingresado y se reemplazan por '/'
	Entre sus verificaciones, se encuentran:
	
	*) Que solo contenga dos separadores
	*) Que el d�a se adec�e al mes y a�o que lo acompa�an
	*) Que el mes sea v�lido
	*) Que el a�o sea bisiesto
	
	Devuelve 0 si el valor pasado no es una fecha admisible, o 1 en caso contrario.
	CAL 28/10/2022
	*/
	
	//************************************
	//SECCI�N DE VERIFICACI�N DE FORMATO
	//************************************
	
	//Suponiendo que pasen una fecha del estilo '1-1-2001', el m�nimo de caracteres admisibles es 8. - CAL 28/102022
	//El m�ximo admisible es 10, suponiendo que pasen '31-12-2022'.
	if(strlen(Fecha) < 8 || strlen(Fecha) > 10) return 0;
	
	//Bandera de cantidad de separadores. CAL 28/10/2022
	int CantSeparadores = 0;
	
	/*Verifico que los separadores est�n donde deben estar.
	
	*)Hay dos posibilidades para el primer separador:
	1/MM/YYYY - 2� Posici�n
	01/MM/YYYY - 3� Posici�n
	
	*)Para el segundo separador, las opciones var�an seg�n d�nde se encuentre
	el primer separador:
	1/1/YYYY - 2� Pos. (primer separador) y 4� posici�n (segundo separador)
	1/12/YYYY - 2� Pos. y 5� posici�n
	31/1/YYYY - 3� Pos. y 5 posici�n
	01/01/YYYY - 3� Pos. y 6� posici�n
	
	En resumen:
	*) Si el primer separador est� en la 2� posici�n, el segundo separador solo puede estar en la 4� o 5� posici�n.
	*) Si el primer separador est� en la 3� posici�n, el segundo separador solo puede estar en la 5� o 6� posici�n.
	
	CAL 28/10/2022
	*/
	
	//Guardo el �ndice del primer y segundo separador: - CAL 28/10/2022
	int PrimeraPosicion, SegundaPosicion;
	
	//Verifico que el a�o tenga 4 d�gitos. Para esto, empiezo a contar los d�gitos desde el segundo separador. CAL 28/10/2022
	int DigitosAnio = 0;
	
	for(int i = 0; i < strlen(Fecha);i++){
		
		//Cuento los d�gitos del a�o a partir del segundo separador. CAL 28/10/2022
		if (CantSeparadores == 2) DigitosAnio++;
		
		//Compruebo que contenga dos caracteres separadores admisibles y que est�n en donde deben. CAL 28/10/2022
		if(Fecha[i] == ' ' || Fecha[i] == '-' || Fecha[i] == '/' || Fecha[i] == '.'){
			Fecha[i] = '/';
			CantSeparadores++;
			if(CantSeparadores == 1){ //Si estamos en el primer separador, verificamos que su posici�n sea la 2� o 3�
				PrimeraPosicion = i + 1;
				if(PrimeraPosicion != 2 && PrimeraPosicion != 3) return 0; //Si no es la posici�n correcta, la funci�n devuelve falso. CAL 28/10/2022
			}
			else if(CantSeparadores == 2){ //Si estamos en el segundo separador, verificamos que su posici�n se adec�e respecto a la posici�n del primer separador.
				SegundaPosicion = i + 1;
				if (PrimeraPosicion == 2) {if(SegundaPosicion != 4 && SegundaPosicion != 5) return 0;} //Si el primero est� 2�, el segundo puede estar 4� o 5�. CAL 28/10/2022 
				else if (PrimeraPosicion == 3) {if(SegundaPosicion != 5 && SegundaPosicion != 6) return 0;} //Si el primero est� 3�, el segundo puede estar 5� o 6�. CAL 28/10/2022
			}
			else return 0; //Si la cantidad de separadores supera los 2, devuelve FALSO. CAL 28/10/2022
			
		} else { //Si el caracter actual no es un separador, debe ser num�rico.
			if(!isdigit(Fecha[i])) return 0;
		}
	}
	
	
	//Verifico que el a�o tenga 4 d�gitos. CAL 28/10/2022
	if(DigitosAnio != 4) return 0;
	
	
	//************************************
	//SECCI�N DE VERIFICACI�N DE VALORES
	//************************************
	
	//Creo las variables que necesito para dividir la fecha en d�a, mes y a�o y realizar las validaciones de valores. CAL 28/10/2022
	char CDia[3] = {""};
	char CMes[3] = {""};
	char CAnio[5] = {""};
	
	//Copio el d�a hasta la primera posici�n divisora encontrada previamente. CAL 28/10/2022
	strncpy(CDia, Fecha, (PrimeraPosicion - 1));
	
	//Repito la operaci�n con la que copi� el d�a para obtener los datos del mes. Apunto la cadena hacia despu�s del primer divisor. CAL 28/10/2022
	strncpy(CMes, Fecha + PrimeraPosicion, (SegundaPosicion - PrimeraPosicion - 1));
	
	//Por �ltimo, copio el a�o que ya se verific� tiene 4 d�gitos. CAL 28/10/2022
	strncpy(CAnio, Fecha + SegundaPosicion, 4); 
	
	//Valido el primer d�gito del a�o. CAL 28/10/2022
	if (CAnio[0] != '1' && CAnio[0] != '2') return 0; //Si no es milenio 1000 o 2000, devuelve falso.
	
	//Valido el mes. CAL 28/10/2022
	if ( atoi(CMes) < 1 || atoi(CMes) > 12 ) return 0;
	
	//Por �ltimo, valido el d�a dependiendo del mes, y al mismo tiempo de que el a�o sea o no bisiesto. CAL 28/10/2022
	if (atoi(CDia) < 1) return 0;
	
	//Valido si el a�o es bisiesto:
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
		
	} //Omitimos el caso default porque ya se verific� que el mes est� entre 1 y 12. CAL 28/10/2022
	
	//Si supera todas las validaciones, devuelve VERDADERO.
	return 1;
	
}

int ConvertirMesAString(int Mes, char CharMes[]){
	/*La siguiente funci�n toma un mes v�lido en forma de entero (pasado en el primer par�metro)
	e inserta las primeras tres letras en min�sculas del nombre del mes en el arreglo de caracteres pasado como segundo par�metro.
	Devuelve 0 si el mes dado en entero es err�neo, o 1 si la operaci�n fue exitosa.
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
	/* 1� Extrae de la fecha pasada como primer par�metro, el dato pasado como segundo par�metro.
	2� El segundo par�metro puede ser: 'd': D�a, 'm': Mes o 'a': A�o (indistintamente de si se pasa con may�sculas o min�sculas) y devuelve este dato como entero.
	3� La fecha debe estar separada con el separador indicado como tercer par�metro.
	Adem�s el formato de fecha debe inclu�r todos sus datos en forma num�rica (el mes no puede estar expresado en letras), indistintamente de si se utilizan 1 o 2 d�gitos para el d�a y mes y 4 o 2 para el a�o.
	Se recomienda usar la funci�n 'ValidaFecha' antes de usar esta funci�n ya que esta no se encarga de realizar todas las validaciones.
	Devuelve 0 si la fecha pasada es vac�a, si se encuentra alg�n error de formato o si se pas� algun par�metro en forma err�nea.
	CAL 29/10/2022
	*/
	
	//Si el string es vac�o, devolver FALSO
	if(strlen(Fecha) == 0) return 0;
	
	//Si el formato es: d/m/aa el m�nimo de caracteres es 6
	//Si el formato es: dd/mm/aaaa el m�ximo de caracteres es 10
	if(strlen(Fecha) < 6 || strlen(Fecha) > 10) return 0;
	
	//Almaceno la cantidad de separadores que se encuentran (deben ser 2)
	int CantSeparadores = 0;
	
	
	int PosSeparador1 = 0;
	int PosSeparador2 = 0;
	
	for(int i = 0; i < strlen(Fecha); i++){
		if(Fecha[i] == Separador){
			//Si encuentra un separador, verifica que no supere los dos y almacena su posici�n
			CantSeparadores ++;
			if(CantSeparadores == 1) PosSeparador1 = i + 1;
			else if (CantSeparadores == 2) PosSeparador2 = i + 1;
			else return 0;
		} else{
			if(!isdigit(Fecha[i])) return 0;
		}
	}
	
	if (CantSeparadores != 2) return 0;
	
	//Defino la variable en la que se guardar� el dato. CAL 29/10/2022
	char Dato[5] = {""};
	DatoAExtraer = toupper(DatoAExtraer);
	
	switch(DatoAExtraer){
	case 'D': //En caso de que se haya solicitado el d�a
		strncpy(Dato,Fecha, PosSeparador1 - 1);
		break;
	case 'M': //En caso de que se haya solicitado el mes
		strncpy(Dato,Fecha + PosSeparador1, PosSeparador2 - PosSeparador1 - 1);
		break;
	case 'A': //En caso de que se haya pedido el a�o.
		strncpy(Dato,Fecha + PosSeparador2, strlen(Fecha) - PosSeparador2);
		break;
	default:
		return 0;
	}
	
	return atoi(Dato);
	
}
