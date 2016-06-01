#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

#define MAX 2000


int M1[MAX][MAX],M2[MAX][MAX],M3[MAX][MAX];


main(int argc, char **argv) {

	// Variables
	int i,j,k;
	struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución


	//Leer argumento de entrada (no de componentes de la matriz)
	if (argc<2){
		printf("Faltan no componentes del vector\n");
		exit(-1);
	}

	unsigned int N = atoi(argv[1]);


	// Inicialización de la matriz y vector;
	for(i=0;i<N ;i++){
		for(j=0;j<N;j++){
			M1[i][j] = i+1;
			M2[i][j] = j+1;
			M3[i][j] = 0;
		}
	}

	int M30,M31,M32,M33;

	// Calculos
	clock_gettime(CLOCK_REALTIME,&cgt1);
	//#pragma omp parallel for private(j)
	for(i=0; i<N; i+=4){
		for(j=0; j<N; j++){
			for(k=0; k <N; k++){
				M3[i][j]+=M1[i][k]*M2[k][j];
				M3[i+1][j]+=M1[i+1][k]*M2[k][j];
				M3[i+2][j]+=M1[i+2][k]*M2[k][j];
				M3[i+3][j]+=M1[i+3][k]*M2[k][j];

			}
		}
	}
	clock_gettime(CLOCK_REALTIME,&cgt2);

	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));


	// Resultados
	printf("Tiempo de ejecución= %2.11f\n",ncgt);
	printf("Primer componente= %d \n",M3[0][0] );
	printf("Ultimo componente= %d \n",M3[N-1][N-1] );

	// Visualiza las matrices si no son muy grandes
	// Se recomienda redirigir la salida a un fichero.
	if (N < 20) {
		printf("\n\t M \n");
		for(i=0; i<N; i++){
			printf("| ");
			for(j=0; j<N; j++)
				printf(" %d ", M1[i][j]);
			printf(" |\n");
		}
		printf("\n\t V1 \n| ");
		for(i=0; i<N; i++){
			for(j=0; j<N;j++)
				printf(" %d ", M2[i][j]);
			printf(" |\n");
		}
		printf(" |\n");

		printf("\n\t V2 \n| ");
		for(i=0; i<N; i++){
			for(j=0; j<N;j++)
				printf(" %d ", M3[i][j]);
			printf(" |\n");
		}
		printf(" |\n");
	}


}
