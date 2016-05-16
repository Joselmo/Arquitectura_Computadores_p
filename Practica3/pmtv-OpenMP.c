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
	int i,j;
	struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución
	omp_sched_t kind;
	int modifier;

	//Leer argumento de entrada (no de componentes de la matriz)
	if (argc<2){
		printf("Error: ./pmtv-OpenMP N kind chunk\n");
		exit(-1);
	}

	unsigned int N = atoi(argv[1]);
//	kind = atoi(argv[2]);
//	modifier = atoi(argv[3]);


	double *M, *v1, *v2;
	M  = (double*) malloc(N*N*sizeof(double));// malloc necesita el tamaño en bytes
	v1 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
	v2 = (double*) malloc(N*sizeof(double));
	if ( (M==NULL) || (v1==NULL) || (v2==NULL) ){
		printf("Error al reservar de espacio para los vectores\n");
		exit(-2);
	}

	// Pido los parametros de OMP_SCHEDULE
	// indicar que pido por la funcion por que tiene mas sentido
//	#ifdef _OPENMP
		//omp_set_schedule(kind);
		omp_get_schedule(&kind, & modifier);
		printf("Asignado run-sched-var=(%d,%d)\n",kind,modifier);
//s	#endif


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
	clock_gettime(CLOCK_REALTIME,&cgt1);
	#pragma omp parallel for private(j)
	for(i=0; i<N; i++){
		for(j=0; j<=i; j++)
			v2[i]+=M[i*N+j]*v1[j];
	}
	clock_gettime(CLOCK_REALTIME,&cgt2);

	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));


	// Resultados
//	printf("Tiempos de schedule= %d  \t chunk= %d --------------\n",kind,modifier );
	printf("Tiempo de ejecución= %2.11f\n",ncgt);
	printf("Primer componente= %2.3f \n",v2[0] );
	printf("Ultimo componente= %2.3f \n",v2[N-1] );
//	printf("--------------------------------------------------------\n");

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
