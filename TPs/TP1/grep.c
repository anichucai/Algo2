#include "cola.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100



bool FuerzaBruta(char* linea, char* clave){

	if(!linea) return false;

	size_t len_linea = strlen(linea);
	size_t len_clave = strlen(clave);
	size_t i, j, k;

	size_t tam=0;
	(len_linea>len_clave)? (tam=len_linea-len_clave):(tam=len_clave-len_linea);

    for (i = 0; i <= tam; i++) {
    	for (j = 0, k = i; linea[k] == clave [j] && j < len_clave; j++, k++);
        if (j == len_clave) return true;
	}

	return false;
}


void grep(char* clave, int n, FILE* archivo){
	
	cola_t* cola = cola_crear();
	if (!cola)return;

	int ncola=0; int nline=0; char aux[MAX];

	while(fgets(aux,MAX,archivo)){

		char* line = (char*) malloc(sizeof(char)*MAX);
		if (!line){cola_destruir(cola,free);return;}
		strcpy(line,aux);

		if (FuerzaBruta(line, clave)){
			while(!cola_esta_vacia(cola)){
				char* a_imprimir = (char*)cola_desencolar(cola);
				fprintf(stdout, "%s", a_imprimir);
				free(a_imprimir);
			}
			fprintf(stdout, "%s", line);
			free(line);
			ncola=-1;
		} else{
			if(ncola>=n) free(cola_desencolar(cola));
			cola_encolar(cola,line);
		}

		nline++;ncola++;

	}

	cola_destruir(cola,free);
}
 
 

int ejecutar_grep(int argc,char* argv[]){

	if (argc<3 || argc>4){
		fprintf(stderr, "%s", "Cantidad de parametros erronea");
		return 1;
	}
	
	if (strcmp(argv[2],"0")!=0 && atoi(argv[2])==0) {
		fprintf(stderr, "%s", "Tipo de parametro incorrecto");
		return 1;
	}

	if (argc==4){
		FILE* archivo = fopen(argv[3], "r");
		if (!archivo){
			fprintf(stderr, "%s", "No se puede ver el archivo indicado");
			return 1;
		}
		grep(argv[1], atoi(argv[2]), archivo);
		fclose(archivo);
	} else {
		grep(argv[1], atoi(argv[2]), stdin);
	}

	return 0;
}
