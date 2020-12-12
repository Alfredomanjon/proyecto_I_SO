#include <stdio.h>
#include <string.h>
typedef struct{
        short int ETQ;
        short int Datos[8];
} T_LINEA_CACHE;

int tiempoglobal = 0;
int numfallos = 0;
char binSol[16] = "";
unsigned int strtol();

int main(){
	T_LINEA_CACHE cache[4];
	for(int i=0;i<4;i++)
		cache[i].ETQ = 0xFF;
	
	
	return 0;
}
