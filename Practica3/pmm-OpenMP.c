#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

/**
* Documentacion
*
*http://sites.uclouvain.be/SystInfo/usr/include/omp.h.html
*
typedef enum omp_sched_t
{
  omp_sched_static = 1,
  omp_sched_dynamic = 2,
  omp_sched_guided = 3,
  omp_sched_auto = 4
}

* 	MCM de 24 y 69 = 192 
*/
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
	
	double *M1, *M2, *M3;
	M1 = (double*) malloc(N*N*sizeof(double));// malloc necesita el tamaño en bytes
	M2 = (double*) malloc(N*N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
	M3 = (double*) malloc(N*N*sizeof(double));
	if ( (M1==NULL) || (M1==NULL) || (M2==NULL) ){
		printf("Error en la reserva de espacio para los vectores\n");
		exit(-2);
	}

	// Inicialización de la matriz y vector;
	#pragma omp parallel for private(j)
	for(i=0;i<N ;i++){
		for(j=0;j<N;j++){
			M1[i*N+j] = i+1;
			M2[i*N+j] = j+1;
			M3[i*N+j] = 0;
		}
	}

	// Calculos
	clock_gettime(CLOCK_REALTIME,&cgt1);
	#pragma omp parallel for private(j,k)
	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			for(k=0; k <N; k ++)
				M3[i*N+j]+=M1[i*N+k]*M2[k*N+j];
	}
	clock_gettime(CLOCK_REALTIME,&cgt2);
	
	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));


	// Resultados
	printf("Tiempo de ejecución= %2.11f\n",ncgt);
	printf("Primer componente= %2.3f \n",M3[0] );
	printf("Ultimo componente= %2.3f \n",M3[N*N-1] );	

	// Visualiza las matrices si no son muy grandes
	// Se recomienda redirigir la salida a un fichero.
	if (N < 20) {
		printf("\n\t M \n");
		for(i=0; i<N; i++){
			printf("| ");
			for(j=0; j<N; j++)
				printf(" %2.2f ", M1[i*N+j]);
			printf(" |\n");
		}
		printf("\n\t V1 \n| ");
		for(i=0; i<N; i++){
			for(j=0; j<N;j++)
				printf(" %2.2f ", M2[i*N+j]);
			printf(" |\n");
		}
		printf(" |\n");
		
		printf("\n\t V2 \n| ");
		for(i=0; i<N; i++){
			for(j=0; j<N;j++)
				printf(" %2.2f ", M3[i*N+j]);
			printf(" |\n");
		}
		printf(" |\n");
	}

	free(M1); // libera el espacio reservado para v1
	free(M2); // libera el espacio reservado para v2
	free(M3); // libera el espacio reservado para v3
	
}