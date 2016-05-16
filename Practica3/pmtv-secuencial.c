#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

main(int argc, char **argv) {

	// Variables
	int i,j;


	//Leer argumento de entrada (no de componentes de la matriz)
	if (argc<2){
		printf("Faltan no componentes del vector\n");
		exit(-1);
	}

	unsigned int N = atoi(argv[1]);
	
	double *M, *v1, *v2;
	M  = (double*) malloc(N*N*sizeof(double));// malloc necesita el tamaño en bytes
	v1 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
	v2 = (double*) malloc(N*sizeof(double));
	if ( (M==NULL) || (v1==NULL) || (v2==NULL) ){
		printf("Error en la reserva de espacio para los vectores\n");
		exit(-2);
	}


	// Inicialización de la matriz y vector;
	for(i=0;i<N ;i++){
		for(j=0;j<N;j++)
			if(j<=i){
				M[i*N+j] = i+j+1;
			}else{
				M[i*N+j] = 0;
			}
		v1[i] = i+1;
	}

	// Calculos
	for(i=0; i<N; i++){
		for(j=0; j<=i; j++)
			v2[i]+=M[i*N+j]*v1[j];
	}

	// Resultados
	printf("Primer componente= %2.3f \n",v2[0] );
	printf("Ultimo componente= %2.3f \n",v2[N-1] );	

	// Visualiza las matrices si no son muy grandes
	// Se recomienda redirigir la salida a un fichero.
	if (N < 20) {
		printf("\n\t M \n");
		for(i=0; i<N; i++){
			printf("| ");
			for(j=0; j<N; j++)
				printf(" %2.2f ", M[i*N+j]);
			printf(" |\n");
		}
		printf("\n\t V1 \n| ");
		for(i=0; i<N; i++){
			printf(" %2.2f ", v1[i]);
		}
		printf(" |\n");
		
		printf("\n\t V2 \n| ");
		for(i=0; i<N; i++){
			printf(" %2.2f ", v2[i]);
		}
		printf(" |\n");
	}

	free(M); // libera el espacio reservado para v1
	free(v1); // libera el espacio reservado para v2
	free(v2); // libera el espacio reservado para v3
	
}