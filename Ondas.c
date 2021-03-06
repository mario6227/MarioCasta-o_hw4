#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

int main(void){

  /*--------------------------------------------------------------------------------------------------
  Solucion parte 1: Cuerda con extremos fijos
  --------------------------------------------------------------------------------------------------*/
  
  //Condiciones iniciales del problema
  int t,p;
  int n = 129; //Numero de datos en la condicion inicial
  double L = 0.64;
  double c = 250.0; //Velocidad de propagacion
  double dx = 0.005; //Igual que en la condicion inicial
  double dt = (0.1*dx) / c;
  int m = (1/dt) + 1; //Cantidad de iteraciones a realizar (1 segundo)
  int per = (2*L / c) / dt; //periodo de oscilacion
  /*
  //inicializacion de vectores y matriz de soluciones
  double * x = malloc(n*sizeof(double));
  double * y_inicial = malloc(n*sizeof(double));
  double ** cuerda = malloc(m*sizeof(double*));

  //Se aparta memoria para cada uno de los vectores de la matriz
  for( t = 0; t < m; t++){
    cuerda[t] = malloc(n*sizeof(double));
  }

  FILE * inicial; //Archivo de condiciones iniciales
  inicial = fopen("cond_ini_cuerda.dat","r");

  FILE * resultadosC; //Archivo de condiciones finales
  resultadosC = fopen("cuerda.txt", "w");

  //Lectura de la condicion inicial
  int i;
  for (i=0;i<n; i++)
    {
      fscanf(inicial,"%lf %lf\n", &x[i],&y_inicial[i]);
    }

  //Inicializacion de la matriz solucion con ceros
  for( p = 0; p < n; p++){
    for( t = 0; t < m; t++){
      cuerda[t][p] = 0.0;
    }
  }

  //Definicion de la condicion inicial
  for(p=0; p<n; p++){
    cuerda[0][p] = y_inicial[p];
    cuerda[1][p] = y_inicial[p]; //se duplica esta fila para evitar problemas con diferencias finitas centradas
  }

  //Extremos fijos (condiciones de frontera)
  for(t=1; t<m; t++){
    cuerda[t][0] = 0.0;
    cuerda[t][n-1] = 0.0;
  }
  
  //Solucion general cuerda usando diferencias finitas centradas
  for( t = 1; t < m-1; t++){
    for( p = 1; p < n-1; p++){
      cuerda[t+1][p] = 2.0*cuerda[t][p] - 1.0*cuerda[t-1][p] + pow((c*dt/dx),2.0)*(cuerda[t][p-1] - 2.0*cuerda[t][p] + cuerda[t][p+1]);
    }
  }
  
  //txt solucion final cuerda extremos fijos
  
  for( p = 0; p < n; p++){
    fprintf(resultadosC, "%f %c", x[p], ' ');
    for( t = 0; t <= per; t++){
      fprintf(resultadosC, "%f %c", cuerda[t][p], ' ');
    }
    fprintf(resultadosC, "\n");
  }
  

  /*--------------------------------------------------------------------------------------------------
  Solucion parte 2: perturbacion en un extremo

  En este caso se reusan el vector x (posiciones iguales) y la matriz cuerda
  --------------------------------------------------------------------------------------------------*/
  /*
  int per2 = (4*L / c) / dt; //periodo de oscilacion, extremo libre
  
  //se re-inicializa la matriz en ceros (cond. inicial, amplitud 0).
  for( p = 0; p < n; p++){
    for( t = 0; t < m; t++){
      cuerda[t][p] = 0.0;
    }
  }

  FILE * resultadosC2; //Archivo de condiciones finales
  resultadosC2 = fopen("cuerda2.txt", "w");

  //Extremo izquierdo con perturbacion, derecho fijo (condiciones de frontera)
  for(t=1; t<m; t++){
    cuerda[t][0] = sin((2*PI*c/L)*(t*dt));
    cuerda[t][n-1] = 0.0;
  }

  //Solucion general cuerda usando diferencias finitas centradas
  for( t = 1; t < m-1; t++){
    for( p = 1; p < n-1; p++){
      cuerda[t+1][p] = 2.0*cuerda[t][p] - 1.0*cuerda[t-1][p] + pow((c*dt/dx),2.0)*(cuerda[t][p-1] - 2.0*cuerda[t][p] + cuerda[t][p+1]);
    }
  }

  //txt solucion final cuerda con perturbacion en un extremo
  for( p = 0; p < n; p++){
    fprintf(resultadosC2, "%f %c", x[p], ' ');
    for( t = 0; t <= per2; t++){
      fprintf(resultadosC2, "%f %c", cuerda[t][p], ' ');
    }
    fprintf(resultadosC2, "\n");
  }


  /*--------------------------------------------------------------------------------------------------
  Solucion parte 3: tambor cuadrado
  --------------------------------------------------------------------------------------------------*/

  int nx = 101; //numero de datos en la condicion inicial en cada dimension
  int ny = 101;
  int px, py, pt; //variables de posicion espacial y temporal
  int nt = 2001;
  double LT = 0.5;
  double *** tambor = malloc(nx*sizeof(double**));
  
  for (px = 0; px < nx; px++) {
    tambor[px] = malloc(ny*sizeof(double*));
    for (py = 0; py < ny; py++) {
      tambor[px][py] = malloc(nt*sizeof(double));
    }
  }

  
  FILE * inicialT; //Archivo de condiciones iniciales
  inicialT = fopen("cond_ini_tambor.dat","r");

  FILE * resultadosT; //Archivo de condiciones finales
  resultadosT = fopen("tambor.txt", "w");
  

  //Inicializacion del arreglo en ceros
  for(px = 0; px < nx; px++){
    for(py = 0; py < ny; py++){
      for(pt = 0; pt < nt; pt++){
	tambor[px][py][pt] = 0.0;
      }
    }
  }

  //lectura del archivo y condicion inicial
  double vart;
  for(px = 0; px < nx; px++){
    for(py = 0; py < ny; py++){
      fscanf(inicialT, "%lf", &vart);
      tambor[px][py][0] = vart;
      tambor[px][py][1] = vart; //se repite para evitar problemas con diferencias finitas
    }
  }

  //Extremos fijos
  for(px = 0; px < nx; px++){
    for(py = 0; py < ny; py++){
      for(pt = 0; pt < nt; pt++){
	tambor[0][py][pt] = 0.0;
	tambor[nx-1][py][pt] = 0.0;
	tambor[px][0][pt] = 0.0;
	tambor[px][ny-1][pt] = 0.0;
      }
    }
  }

  //Solucion general usando diferencias finitas centradas
  double deltaX = 0.5/100.0;
  double deltaY = deltaX;
  double deltaT = 0.1/2000.0;
  double r = deltaT/deltaX;
  int perT = 10*(LT/c)/deltaT;
  
  for(px = 1; px < nx-1; px++){
    for(py = 1; py < ny-1; py++){
      for(pt = 1; pt < nt-1; pt++){
        tambor[px][py][pt+1] = 2*tambor[px][py][pt] - tambor[px][py][pt-1] + pow(r,2)*(tambor[px+1][py][pt] + tambor[px-1][py][pt] + tambor[px][py+1][pt] + tambor[px][py-1][pt] - 4*tambor[px][py][pt]);
      }
    }
  }

  //txt solucion final (t = 0, T/8, T/4, T/2)
  for(px = 0; px < nx; px++){
    for(py = 0; py < ny; py++){
      fprintf(resultadosT, "%lf ", tambor[px][py][0]);
    }
    fprintf(resultadosT, "\n");
  }
  for(px = 0; px < nx; px++){
    for(py = 0; py < ny; py++){
      fprintf(resultadosT, "%lf ", tambor[px][py][perT/8]);
    }
    fprintf(resultadosT, "\n");
  }
  for(px = 0; px < nx; px++){
    for(py = 0; py < ny; py++){
      fprintf(resultadosT, "%lf ", tambor[px][py][perT/4]);
    }
    fprintf(resultadosT, "\n");
  }
  for(px = 0; px < nx; px++){
    for(py = 0; py < ny; py++){
      fprintf(resultadosT, "%lf ", tambor[px][py][perT/2]);
    }
    fprintf(resultadosT, "\n");
  }
  
  
  return 0;
}
