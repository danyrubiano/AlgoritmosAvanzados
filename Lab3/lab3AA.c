/* Dany Rubiano Jiménez
   22.250.855-k
   Enunciado 2, Programacion Dinamica */

#include <stdio.h>
#include <stdlib.h>

#define SIZE_BUFFER 512

/* Estructura ------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/* Estructura para guardar la suma y el camino de las submatrices para escoger el menor*/

struct cam{
  int sum, filaI, filaF, colI, colF;
};


/*Funciones de lectura de archivos ---------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/* Obtiene el tamaño tanto de las filas, como de las columnas de la submatriz, siguiendo la forma que tiene el archivo de texto */

void getFilasYColumnasSubMatriz(int arr[]){
  FILE *f = fopen("entrada.in.txt","r");
  char *buffer = (char *)malloc(SIZE_BUFFER * sizeof(char));
  char *auxiliar=(char*)malloc (sizeof(char));

  int i = 0;
  while((fgets(buffer, SIZE_BUFFER, f)!=NULL)&&(i<1)){
    auxiliar = strtok(buffer," ");
    int j=0;
    while((auxiliar != NULL)&&(j<=1)){
      arr[j]= atoi(auxiliar);
      j++;
      auxiliar = strtok(NULL," ");
    }
  i++;
  }
  fclose(f);
}

/* Obtiene el tamaño tanto de las filas, como de las columnas de la matriz del archivo
de texto para declarar una matriz que contenga los datos, sin desperdiciar memoria */

int getFilasYColumnasMatriz(){
  FILE *archivo;
  char caracter;
  int contador = 1;
  archivo = fopen("entrada.in.txt","r");

  if (archivo == NULL){
    printf("\nError de apertura del archivo. \n\n");
  }
  else{
    while (feof(archivo) == 0){
      caracter = fgetc(archivo);
      if(caracter == '\n'){
        contador++;
      }
    }
    return contador;
  }
  fclose(archivo);
  return 0;
}


/* Obtiene el los datos de la matriz del archivo pasandolos a la matriz creada */

void lecturaArchivo(int m, int matriz[m][m]){
  FILE *f = fopen("entrada.in.txt","r");
  char *buffer = (char *)malloc(SIZE_BUFFER * sizeof(char));
  char *auxiliar=(char*)malloc (sizeof(char));

  int i = 0;
  while((fgets(buffer, SIZE_BUFFER, f)!=NULL)&&(i<m+1)){
    if(i!=0){
      auxiliar = strtok(buffer," ");
      int j=0;
      while((auxiliar != NULL)&&(j<m)){
        matriz[i-1][j]= atoi(auxiliar);
        j++;
        auxiliar = strtok(NULL," ");
      }
    }
  i++;
  }
  fclose(f);
}

/* Funciones de Programacion Dinamica ------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/
void camino1(int a, int s1, int s2, int m, int matriz[m][m], struct cam tabla[a][m] ){
  int i, j, k, suma=0;
  for(i=0; i<a; i++){
    for(j=0; j<m; j++){
      for(k=i; k<s1+i; k++){
        suma += matriz[k][j];
      }
      tabla[i][j].sum = suma;
      suma = 0;
      tabla[i][j].filaI = i;
      tabla[i][j].filaF = k;
      tabla[i][j].colI = j;
      tabla[i][j].colF = j;
    }
  }
  /*for(i=0; i<a; i++){
    for(j=0; j<m; j++){
      printf("[%d, %d, %d, %d, %d] ", tabla[i][j].sum, tabla[i][j].filaI, tabla[i][j].filaF, tabla[i][j].colI, tabla[i][j].colF);
    }
    printf("\n");
  }
  printf("\n");*/
}

void camino2(int a, int s1, int s2, int m, int matriz[m][m], struct cam tabla[m][a]){
  int i, j, k, suma=0;

  for(i=0; i<a; i++){
    for(j=0; j<m; j++){
      for(k=i; k<s2+i; k++){
        suma += matriz[j][k];
      }
      tabla[i][j].sum = suma;
      suma = 0;
      tabla[i][j].filaI = j;
      tabla[i][j].filaF = j;
      tabla[i][j].colI = i;
      tabla[i][j].colF = k;
    }
  }
  /*for(i=0; i<m; i++){
    for(j=0; j<a; j++){
      printf("[%d, %d, %d, %d, %d] ", tabla[j][i].sum, tabla[j][i].filaI, tabla[j][i].filaF, tabla[j][i].colI, tabla[j][i].colF);
    }
    printf("\n");
  }
  printf("\n");*/
}

int getSubmatriz1(int a, int s1, int s2, int m, struct cam tabla[a][m], int arr[]){
  int i, j, mejor=0;
  for(i=0; i<a; i++){
    for(j=0; j<m; j++){
      if(mejor<= tabla[i][j].sum){
        mejor = tabla[i][j].sum;
        arr[0] = tabla[i][j].sum;
        arr[1] = tabla[i][j].filaI;
        arr[2] = tabla[i][j].filaF;
        arr[3] = tabla[i][j].colI;
        arr[4] = tabla[i][j].colF;
      }
    }
  }

  int temp = tabla[arr[1]][arr[3]].sum;
  for(j=1; j<s2; j++){
    if(tabla[arr[1]][arr[3]-1].sum + temp >= tabla[arr[1]][arr[3]+1].sum + temp){
      temp += tabla[arr[1]][arr[3]-j].sum;
    }
    else if(tabla[arr[1]][arr[3]-1].sum + temp < tabla[arr[1]][arr[3]+1].sum + temp){
      temp += tabla[arr[1]][arr[3]+j].sum;
    }
  }

  if((tabla[arr[1]][arr[3]-1].sum >= tabla[arr[1]][arr[3]+1].sum) && (arr[3]-j+1 < arr[3]))
    arr[3]= arr[3]-j+1;
  else if((tabla[arr[1]][arr[3]-1].sum < tabla[arr[1]][arr[3]+1].sum) && (arr[3]+j-1 > arr[3]))
    arr[4]= arr[3]+j-1;

  return temp;
}

int getSubmatriz2(int a, int s1, int s2, int m, struct cam tabla[m][a], int arr[]){
  int i, j, mejor=0;
  for(i=0; i<a; i++){
    for(j=0; j<m; j++){
      if(mejor<= tabla[i][j].sum){
        mejor = tabla[i][j].sum;
        arr[0] = tabla[i][j].sum;
        arr[1] = tabla[i][j].filaI;
        arr[2] = tabla[i][j].filaF;
        arr[3] = tabla[i][j].colI;
        arr[4] = tabla[i][j].colF;
      }
    }
  }

  int temp = tabla[arr[1]][arr[3]].sum;
  for(j=1; j<s1; j++){
    if(tabla[arr[1]-1][arr[3]].sum + temp >= tabla[arr[1]+1][arr[3]].sum + temp)
      temp += tabla[arr[1]-j][arr[3]].sum;
    else if(tabla[arr[1]-1][arr[3]].sum + temp < tabla[arr[1]+1][arr[3]].sum + temp)
      temp += tabla[arr[1]+j][arr[3]].sum;
  }

  if((tabla[arr[1]-1][arr[3]].sum >= tabla[arr[1]+1][arr[3]].sum) && (arr[1]-j+1 < arr[1]))
    arr[1]= arr[1]-j+1;
  else if((tabla[arr[1]-1][arr[3]].sum < tabla[arr[1]+1][arr[3]].sum) && (arr[1]+j-1 > arr[1]))
    arr[2]= arr[1]+j-1;


  return temp;
}

/* Funcion Principal -----------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/
int main (){
  int tam_s[2], tam_m;
  getFilasYColumnasSubMatriz(tam_s);
  printf("Submatriz: \n Filas: %d, Columnas: %d \n\n", tam_s[0], tam_s[1]);

  tam_m = getFilasYColumnasMatriz()-1;
  int matriz [tam_m][tam_m];
  //printf("%d, %d \n", tam_m[0], tam_m[1]);

  lecturaArchivo(tam_m, matriz);

  printf("Matriz leida:\n ");
  int i, j;
  for (i=0; i<tam_m; i++){
    for (j=0; j<tam_m; j++){
      printf("%d ", matriz[i][j]);
    }
    printf("\n ");
  }
  printf("\n");

  int arr[5], suma;

  /* Si el numero de filas de la submatriz es mayor que el numero de columnas, escogemos dividir la matriz según las columnas
  para realizar menos operaciones */
  if(tam_s[0] >= tam_s[1]){
    int a = tam_m-tam_s[0]+1;
    struct cam tabla[a][tam_m];
    camino1(a, tam_s[0], tam_s[1], tam_m, matriz, tabla);
    //getMejor1(a, tam_m, tabla, arr);
    suma = getSubmatriz1(a, tam_s[0], tam_s[1], tam_m, tabla, arr);
    arr[0]=suma;
    printf("Suma: %d\n", suma);

    //printf("%d, %d, %d, %d, %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
  }

  /* Si el numero de filas de la submatriz es menor que el numero de columnas, escogemos dividir la matriz según las filas,
  para realizar menos operaciones */
  if(tam_s[0] < tam_s[1]){
    int a = tam_m-tam_s[1]+1;
    struct cam tabla[tam_m][a];
    camino2(a, tam_s[0], tam_s[1], tam_m, matriz, tabla);
    //getMejor2(a, tam_m, tabla, arr);
    suma = getSubmatriz2(a, tam_s[0], tam_s[1], tam_m, tabla, arr);
    arr[0]=suma;
    printf("Suma: %d\n", suma);
    //printf("%d, %d, %d, %d, %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
  }

  FILE *f = fopen("salida.out.txt","w");

  for(i=arr[1]; i<arr[2]; i++){
    for(j=arr[3]; j<=arr[4]; j++){
      fprintf(f, "%d ", matriz[i][j]);
    }
    fprintf(f, "\n");
  }
  fprintf(f, "Suma: %d", suma);
  fclose(f);
  printf("\nSe ha creado un archivo llamado 'salida.out', el cual contiene la solucion requerida.\n\n");
  system("pause");

  return 0;
}
