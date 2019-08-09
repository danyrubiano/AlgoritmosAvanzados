#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define SIZE_BUFFER 512

int contarLineasDeCodigo(){
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

int factorial(int N) {
  if(N==0)
    return 1;
  if(N==1)
    return 1;
  else
    return N*factorial(N-1);
}

/* Funcion que lee una archivo de texto y pasa a una matriz los valores.*/

void lecturaArchivo(int n, int matriz[n][n]){
  FILE *f = fopen("entrada.in.txt","r");
  char *buffer = (char *)malloc(SIZE_BUFFER * sizeof(char));
  char *auxiliar=(char*)malloc (sizeof(char));

  int i = 0;
  while((fgets(buffer, SIZE_BUFFER, f)!=NULL)&&(i<n)){
    auxiliar = strtok(buffer," ");
    int j=0;
    while((auxiliar != NULL)&&(j<n)){
      matriz[i][j]= atoi(auxiliar);
      j++;
      auxiliar = strtok(NULL," ");
    }
  i++;
  }
  fclose(f);
}

void process(int* P, int m, int matriz[][m+1], int l) {
  int i=m;
  int j=0;
  while((i>0)&&(j<m)){
    matriz[l][j] = P[i];
    i--;
    j++;
  }
}

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void reverse (int *P, int m) {
  int i = 1;
  while ( i < (m+1-i) ) {
    swap(&P[i], &P[m+1-i]);
    i ++;
  }
}

int B(int m, int c) {
  return ( (m % 2) != 0 ? 1 : c );
}

void permuta (int *P, int m, int matriz[][m+1]) {

  int i;
  int c[m];
  for (i = m; i > 1; i --) {
    c[i] = 1;
  }
  i = 2;
  process(P,m,matriz,0);
  int l = 1;

  do {
    if (c[i] < i) {
      swap(&P[i],&P[c[i]]);
      reverse(P,i-1); /* inversion parcial! */
      process(P,m,matriz,l);
      c[i] ++;
      i = 2;
      l++;
    } else {
      c[i] = 1;
      i ++;
    }
  } while (i <= m);
}

int obtenerTiempos (int m, int f, int A[m][m], int B[f][m+1]) {
  int i, j, temp, posicionMejor;
  int suma = 0;
  for (i=0; i<f; i++){
    for(j=0; j<m; j++){
      temp = B[i][j]-1;
      suma += A[temp][j];
    }
    B[i][m] = suma;
    suma = 0;
  }
  int mejor = 0;
  for(i=0; i<f; i++) {
    if (mejor < B[i][m]) {
        mejor = B[i][m];
		posicionMejor = i;
    }
  }
  return posicionMejor;
}


int main(){
  system("cls");
  int n = contarLineasDeCodigo();

  int entrada[n][n];
  /* La matriz "entrada" representa la asociación entre el número de tarea y la persona que lo puede cubrir.
     Las filas indican las personas y las columnas las tareas.*/

  int facto = factorial(n);
  /* Numero de combinaciones que se pueden dar. Esto responde a la permutacion.*/

  int combinaciones[facto][n+1];
  /* La matriz "combinaciones" representa la asociación entre las tareas y la combinacion que se puede dar
     al establecer personas para dichas tareas.
     Las filas indican las combinaciones y las columnas las tareas.
     La ultima columna es la suma de los tiempos de las posibles combinaciones.
     Y los elementos dentro de la matriz representan a los trabajadores.*/
  system("cls");
  lecturaArchivo(n, entrada);

  int i,j;

  /*
  for (i=0; i<facto; i++){
    for (j=0; j<m; j++){
      printf("%d ", entrada[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  */

  int m, P[n];
  m= n + 1;
  for (i=0; i<m; i++) P[i] = i;
  permuta(P, n, combinaciones);

  int p = obtenerTiempos(n, facto, entrada, combinaciones);

  /*for (i=0; i<facto; i++){
    for (j=0; j<m; j++){
      printf("%d ", combinaciones[i][j]);
    }
    printf("\n");
  }
  printf("\n");
 */

  FILE *f = fopen("salida.out.txt","w");

  for (j=0; j<n; j++){
    fprintf(f, "%d ", combinaciones[p][j]);
  }
  fclose(f);

  printf("\nSe ha creado un archivo llamado 'salida.out', el cual contiene la mejor combinacion para la asignacion de las tareas.\n\n");
  return 0;

}
