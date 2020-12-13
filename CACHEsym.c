#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMORIA_RAM "./RAM.bin"
#define ACCESOS "./accesos_memoria.txt"

typedef struct{
        short int ETQ;
        short int DATOS[8];
} T_LINEA_CACHE;

FILE *M;
FILE *F;
T_LINEA_CACHE cache[4];
int tiempoglobal = 0;
int numfallos = 0;
int numAccesos = 0;
char binSol[16] = "";
unsigned char RAM[1024];

void readRAM(){

	if ((M = fopen(MEMORIA_RAM,"r")) == NULL){
		puts("No es posible abrir el archivo RAM.bin.");
		exit(1);
    	}
    	fread(RAM,sizeof(RAM),1,M);
    	
}


char* fromHexToBinary(char hexNumber[4]){
	memset(binSol,0, 16 );
	for(int i=0;i<4;i++){
		switch(hexNumber[i])
            {
                case '0':
                    strcat(binSol, "0000");
                    break;
                case '1':
                    strcat(binSol, "0001");
                    break;
                case '2':
                    strcat(binSol, "0010");
                    break;
                case '3':
                    strcat(binSol, "0011");
                    break;
                case '4':
                    strcat(binSol, "0100");
                        break;
                case '5':
                    strcat(binSol, "0101");
                    break;
		case '6':
                    strcat(binSol, "0110");
                    break;
                case '7':
                    strcat(binSol, "0111");
                    break;
                case '8':
                    strcat(binSol, "1000");
                    break;
		case '9':
                    strcat(binSol, "1001");
                    break;
                case 'a':
                case 'A':
                    strcat(binSol, "1010");
                    break;
                case 'b':
                case 'B':
                    strcat(binSol, "1011");
                    break;
                case 'c':
                case 'C':
                    strcat(binSol, "1100");
                    break;
                case 'd':
                case 'D':
                    strcat(binSol, "1101");
                    break;
                case 'e':
                case 'E':
                    strcat(binSol, "1110");
                    break;
		case 'f':
                case 'F':
                    strcat(binSol, "1111");
                    break;
                default:
                    printf("VA MAL");
                    

        }
	
	}
	printf("Addr: %s\n", binSol);
	return binSol;
}

int binaryToHexadecimal(char etiqueta[12]){
    char *a = etiqueta;
    int num = 0;
    do {
        int b = *a=='1'?1:0;
        num = (num<<1)|b;
        *a++;
    } while (*a);
    return num;
}

void checkCache(int ADDR, int ETQ,int LINEA,int PALABRA,int BLOQUE){
	int status = 0;
	int bloqNum = 0;
         bloqNum = BLOQUE;
         bloqNum = bloqNum * 8;
         int lineaNum = 0;
         lineaNum = LINEA;
         if(cache[lineaNum].ETQ == ETQ){
             status = 0;
         }else{
             status = 1;
         }
         if (status == 0) {
             tiempoglobal++;
             printf("T: %d, Acierto de CACHE, ADDR %04X ETQ %i linea %02i palabra %02i bloque %02i\n",tiempoglobal, ADDR, ETQ, LINEA, PALABRA, BLOQUE);
             for (int j=0; j<4; j++) {
                 printf("ETQ %d",cache[j].ETQ);
                 printf(" DATOS: ");
                 for (int i = 0; i<=7; i++) {
                     printf("%x",cache[j].DATOS[i]);
                     printf(" ");
                 }
                 printf("\n");
             }
             printf("\n");
             sleep(2);
         }else if(status == 1){
             numfallos++;
             tiempoglobal = tiempoglobal + 10;
             printf("T: %d, Fallo de CACHE %d, ADDR %04X ETQ %i linea %02i palabra %02i bloque %02i\n", tiempoglobal, numfallos, ADDR, ETQ, LINEA, PALABRA, BLOQUE);
             printf("Cargando el bloque %02i en la linea %i", BLOQUE, LINEA);
             cache[lineaNum].ETQ = ETQ;
             for (int i = 0; i <= 7; i++) {
                 cache[lineaNum].DATOS[i] = RAM[bloqNum + 7 - i];
             }
             printf("\n");
             for (int j=0; j<4; j++) {
                 printf("ETQ %d",cache[j].ETQ);
                 printf(" DATOS: ");
                 for (int i = 0; i<=7; i++) {
                     printf("%x",cache[j].DATOS[i]);
                     printf(" ");
                 }
                 printf("\n");
             }
             printf("\n");
             sleep(2);
         }
         numAccesos++;
}

void splitAddress(char* addr){
	char ETQ[13];
	char LINEA[20];
	char PALABRA[30];
	char BLOQUE[15];
	memmove(ETQ, binSol, 16-5);
 	memmove(LINEA, binSol+11, 2);
 	memmove(PALABRA, binSol+13, 3);
 	memmove(BLOQUE, binSol, 16-3);
 	printf("Etiqueta: |%s|\n", ETQ);
 	printf("Linea: |%s|\n", LINEA);
	printf("Palabra: |%s|\n", PALABRA);
	printf("Bloque: |%s|\n", BLOQUE);
	int hexAddr = binaryToHexadecimal(addr);
	int hexETQ = binaryToHexadecimal(ETQ);
	int hexLIN = binaryToHexadecimal(LINEA);
	int hexPAL = binaryToHexadecimal(PALABRA);
	int hexBLOQ = binaryToHexadecimal(BLOQUE);
	checkCache(hexAddr, hexETQ, hexLIN, hexPAL, hexBLOQ);
}

void readMemoryData(){

    	unsigned char elto[12];
    	if ((F = fopen(ACCESOS,"rt")) == NULL){
        	puts("No es posible abrir el archivo.");
        	exit(1);
        }
    	while(fgets(elto, 12, F)!=NULL){
       	fromHexToBinary(elto);
       	splitAddress(binSol);
    	}

     fclose(F);
}

void showFinalStats(){
	printf("---------------------------------------------\n");
	printf("Número total de accesos: %d\n", numAccesos);
	printf("Número de fallos totales: %d\n", numfallos);
	printf("Tiempo total: %ds\n", tiempoglobal);
	printf("Tiempo medio: %ds\n", tiempoglobal/numAccesos);
}



int main(){
    	

	for(int i=0;i<4;i++)
		cache[i].ETQ = 0xFF;
	readRAM();
	readMemoryData();
	showFinalStats();
	return 0;
}
