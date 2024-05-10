/*Empleando el mismo enfoque revisado en la última sesión (clasificador de limones y naranjas), realiza el entrenamiento de un clasificador sencillo con los datos del archivo train.csv
Prueba primero con la variable petallength,
Luego prueba con petalwidth.
Una vez que definiste el umbral de separación, prueba con los datos del archivo test.csv.
Clasifica los datos de la variable petallength, compara con la clase real y cuenta cuántas patrones clasificaste correctamente.
Clasifica los datos de la variable petalwidth, compara con la clase real y cuenta cuántos patrones clasificaste correctamente.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


void clasificador(int columna, int fila, float valor_f[columna][fila]);

int main()
{
	FILE *archivo;
	int i=0,j=0;
	char nom_archivo[50];

	printf("\n\tEjecicio de Lab. 8");
	printf("\n\n\tClasificador de petalos\n");
	printf("\n\tIntroduce el nombre del archivo: ");
	scanf("%s",nom_archivo);
	
	archivo = fopen(nom_archivo,"r");
	if(archivo == NULL)
		printf("\n\tError en la apertura del archivo");

	int c,fila=1,coma=0,columna;
	while ((c = fgetc(archivo)) != EOF) 
	{
		if(c == '\n')
		{
			fila++;
		}
		else if(c == ',')
		{	
			coma++;
		}
    	}
	//printf("Fila : %d",fila);
	//printf("Comas : %d",coma);
	fila = fila - 1;
	columna = (coma/fila) + 1;
	//printf("Columnas : %d",columna);
	fseek(archivo,0,SEEK_SET);

	char line[1024];
	char arr[columna][fila][100];
	float valor_f[columna][fila];
	
    	while (fgets(line, sizeof(line), archivo) != NULL) 
	{
        
        	char *token = strtok(line, ",");
        	while (token != NULL) 
		{
			//printf("\t%s\n", token);
			if (strchr(token, '\n') != NULL) 
			{
            			token[strcspn(token, "\n")] = '\0';
        		}
			strcpy(arr[i][j], token);
           		token = strtok(NULL, ",");
			i++;
        	}
		j++;
		i=0;
	}
	for(i=0;i<columna;i++) 
	{
		//printf("\n\tColumna %d:\n\n\t[",i+1);
        	for (j=0;j<fila;j++) 
		{
			//printf("%s,",arr[i][j]);
			valor_f[i][j] = atof(arr[i][j]);
			//printf("\n\tAtof vale: %.2f\n",atof(arr[i][j]));
        	}
		 	//printf("]\n");
    	}	
	/*for(i=1;i<fila;i++)
	{
		printf("\n\tArreglo[0][%d] vale: %s",i,arr[0][i]);
		printf("\n\tValor_f en %d: %.2f",i,valor_f[0][i]);
		printf("\n\tAtof vale: %.2f\n",atof(arr[0][i]));
	}*/
	
	
	fclose(archivo);

	clasificador(columna,fila,valor_f);
	return 0;
}

void clasificador(int columna, int fila, float valor_f[columna][fila])
{	
	int i=0,j=1;
	/*for(i=1;i<43;i++)
	{
		printf("\n\tValor_f en %d: %f",i,valor_f[0][i]);
	}*/
	char clase[][16] = {"Iris-setosa","Iris-versicolor","Iris-virginica"};
	int flag[fila];
	
	//Se obtiene el area (Weigth x Length)
	for(i=1;i<fila;i++)
	{
		//printf("\n\tC1 vale: %.2f",valor_f[0][i]);
		//printf("\n\tC2 vale: %.2f",valor_f[0][i]);
		//printf("\n\tMultiplicacion vale: %.2f",valor_f[0][i]*valor_f[1][i]);
		
		if(valor_f[0][i]*valor_f[1][i] < 1)
		{
			flag[j] = 1;//Iris-setosa
		}
		else if(valor_f[0][i]*valor_f[1][i] < 7.6)
		{
			flag[j] = 2;//Iris-versicolor
		}
		else
		{
			flag[j] = 3;//Iris-virginica
		}
		j++;
	}
	
	/*for(i=1;i<fila;i++)
	{
		printf("\n\tFlag1 en %d: %d",i,flag[i]);
	}*/
	for(i=1;i<fila;i++)
	{
		if(flag[i] == 1)
		{
			printf("\n\tEl elemento no. %d pertenece a la clase %s",i,clase[0]);
		}
		else if(flag[i] == 2)
		{
			printf("\n\tEl elemento no. %d pertenece a la clase %s",i,clase[1]);
		}
		else 
		{
			printf("\n\tEl elemento no. %d pertenece a la clase %s",i,clase[2]);
		}
	}
	printf("\n");
	
}