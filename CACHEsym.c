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


void readMemoryData(){

    	unsigned char elto[12];
    	if ((F = fopen(ACCESOS,"rt")) == NULL){
        	puts("No es posible abrir el archivo.");
        	exit(1);
        }
    	while(fgets(elto, 12, F)!=NULL){
       	fromHexToBinary(elto);
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
