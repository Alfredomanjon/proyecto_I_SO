#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMORIA_RAM "./RAM.bin"
#define ACCESOS "./accesos_memoria.txt"

typedef struct{
        short int ETQ;
        short int Datos[8];
} T_LINEA_CACHE;

FILE *M;
FILE *F;
int tiempoglobal = 0;
int numfallos = 0;
char binSol[16] = "";
unsigned char RAM[1024];
unsigned char memoryData[48] = { 0 };

void readRAM(){

	if ((M = fopen(MEMORIA_RAM,"r")) == NULL){
		puts("No es posible abrir el archivo RAM.bin.");
		exit(1);
    	}
    	fread(RAM,sizeof(RAM),1,M);
    	
}

void readMemoryData(){

	int cont2=0;
    	char letra2;
    	if ((F = fopen(ACCESOS,"rt")) == NULL){
        	puts("No es posible abrir el archivo.");
        	exit(1);
        }
    	while((letra2 = fgetc(F))!= EOF ){
       	memoryData[cont2]=letra2;
      		//printf ("%c", letra2);
       	cont2++;
    	}

     fclose(F);
}

int main(){
    	
	T_LINEA_CACHE cache[4];
	for(int i=0;i<4;i++)
		cache[i].ETQ = 0xFF;
	readRAM();
	readMemoryData();
	
	return 0;
}
