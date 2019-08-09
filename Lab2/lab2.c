#include <stdio.h>
#include <stdlib.h>

#define SIZE_BUFFER 512

/* Esta función cuenta el número de líneas que tiene el archivo, lo que corresponde a la cantidad de filas que tiene la sala.*/

int contarLineasDeArchivo () {
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

/*Lee el archivo y guarda en el arreglo de tamaño cuatro, la cantidad de alumnos por cada grupo,
en donde cada posición representa al grupo, tal como se dijo anteriormente.*/

void leerArchivo (int grupos[]) {
  FILE *archivo;
  char caracter;
  int i;
  for (i=0; i<4; i++) {
    grupos[i] = 0;
  }

  archivo = fopen("entrada.in.txt","r");

  if (archivo == NULL) {
    printf("\nError de apertura del archivo. \n\n");
  }
  else {
    while (feof(archivo) == 0) {
      caracter = fgetc(archivo);

      if (caracter =='A')
        grupos[0] = grupos[0] + 1;
      else if (caracter =='B')
        grupos[1] = grupos[1] + 1;
      else if (caracter =='C')
        grupos[2] = grupos[2] + 1;
      else if (caracter =='D')
        grupos[3] = grupos[3] + 1;
    }
  }
  fclose(archivo);
}
/*Recorre el arreglo que contiene los grupos y busca en cual grupo está el valor de mayor cantidad de alumnos, luego se retorna la posición.*/

int buscarMayor(int grupos[]) {
  int i, pos;
  int mayor = 0;
  for (i=0; i<4; i++) {
    if (mayor < grupos[i]) {
        mayor = grupos[i];
        pos = i;
    }
  }
  return pos;
}

/*Para la totalidad de los alumnos, busca paso por paso el grupo con mayor cantidad de alumnos, mediante el llamado a la función ‘buscarMayor’,
y se van insertando si se cumple con las condiciones indicadas.*/

void reasignar (int n, int m, int z, int grupos[], int salida[n][m]) {
  int i, j, k, pos;
  pos = buscarMayor(grupos);

  for (i=0; i<z; i++) { //iteracion segun el numero de elementos
    for (j=0; j<n; j++) { // iteracion para recorrer las columnas de la matriz de salida
      for (k=0; k<m; k++) {  // iteracion para recorrer las filas de la matriz de salida
        pos = buscarMayor(grupos);
        if (grupos[pos] > 0) {
          if ((salida[j][k] != 0) && (salida[j][k] != 1) && (salida[j][k] != 2) && (salida[j][k] != 3)) { // Verifica si la posicion ya fue ocupada
            if ((salida[j][k+1] != pos) && (salida[j][abs(k-1)] != pos) && (salida[j+1][k] != pos) && (salida[abs(j-1)][k] != pos)) { // Criterio Goloso
              salida[j][k] = pos; // Inserción del elemento
              grupos[pos] = grupos[pos] - 1;
              printf("%d, [%d][%d]\n", pos, j, k);
            }
          }
        }
      }
    }
  }
}

/* Debido a que en la función ‘reasignar’, se insertan los alumnos en una representación de los grupos como números,
entonces se debe pasar estos elementos a la representación inicial.
Posteriormente esta función imprime la matriz solución en un archivo de texto.*/

void mostrarResultado(int n, int m, int salida[n][m], char out[n][m]){
  int i, j;

  for (i=0; i<n; i++){
    for (j=0; j<m; j++) {
      if (salida[i][j] == 0)
        out[i][j] = 'A';
      else if (salida[i][j] == 1)
        out[i][j] = 'B';
      else if (salida[i][j] == 2)
        out[i][j] = 'C';
      else if (salida[i][j] == 3)
        out[i][j] = 'D';
      else
        out[i][j] = '-';
    }
  }

  FILE *f = fopen("salida.out.txt","w");

  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      fprintf(f, "%c ", out[i][j]);
    }
    fprintf(f, "\n");
  }
  fclose(f);
}

int main (){
  system("cls");
  int i, j;
  int n = contarLineasDeArchivo();
  int grupos[4];
  leerArchivo(grupos);
  int suma = 0;
  for (i=0; i<4; i++) {
    suma = suma + grupos[i];
  }

  int m = suma/n;

  int salida[n][m];

  char out[n][m];

  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      salida[i][j] = -1;
    }
  }

  printf("Las dimensiones de la sala son: ");
  printf(" %d filas,", n);
  printf(" y %d columnas\n\n", m);

  printf("El arreglo obtenido, con el numero de alumnos por grupo es: \n");
  for (i=0; i<4; i++) {
    printf("%d ", grupos[i]);
  }
  printf("\n\n");

  reasignar(n, m, suma, grupos, salida);

  printf("\n\n");

  printf("La reasignacion obtenida es:\n\n");
  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      printf("%d ", salida[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  mostrarResultado(n, m, salida, out);

  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      printf("%c ", out[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("\nSe ha creado un archivo llamado 'salida.out', el cual contiene una posible solucion para la reasignacion de posiciones.\n\n");
  return 0;
}
