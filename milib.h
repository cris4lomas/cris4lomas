#ifndef MILIB_H
#define MILIB_H


void imprimirHistograma(int d[], int n){
int i;
 for (i=0; i<d[n]; i++)
    printf("*");
 }

void emitirFacturacionSemanal(int d[], int t) {
 int i;
   printf("\n\n\n******HISTOGRAMA*******");
   for (i=0; i<t; i++){
        printf("\ndia %d  ->", (i+1));
        imprimirHistograma(d, i);
   }
}

void ingresarDiaria( int d[], int t) {
 int i;
   for (i=0; i<t; i++)
   {
   printf("Ingrese el total facturado en el dia %d: ", i+1);
   scanf("%d", &d[i]);
   }
}

#endif
