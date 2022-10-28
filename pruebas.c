#include <stdio.h>

void AbrirArch(FILE * Arch, const char * NArch){
	if(Arch == NULL){
		printf("El archivo no existe");
		Arch = fopen("doc1.txt", "w");
	}
	else printf("El archivo existe");
	
}


int main(){
	
	const char * NArch = {"doc123.txt"};
	//const char * NArch2 = {"doc2.txt"};
	
	FILE * Arch = fopen(NArch, "w");
	
	//fclose(Arch);
	
	if(Arch == NULL){
		printf("El archivo se cerró");
	}
	else{
		printf("El archivo se mantuvo abierto");
		fputc('H',Arch);
	}
	
	//AbrirArch(Arch, NArch);
	
	
	getchar();
	
	return 0;
}
