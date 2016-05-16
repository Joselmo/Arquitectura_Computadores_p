/* pmv-secuencial.c

Para compilar usar (-lrt: real time library):
gcc -O2 pmv-secuencial.c -o pmv-secuencial –lrt
gcc -O2 –S pmv-secuencial.c –lrt
//para generar el código ensamblador
Para ejecutar use: pmv-secuencial global/dinamico longitud
*/
#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#define omp_get_num_threads 1
#endif

#define VECTOR_GLOBAL	// descomentar para que los vectores sean variables ...
						// globales (su longitud no estará limitada por el ...
						// tamaño de la pila del programa)
//#define VECTOR_DYNAMIC 	// descomentar para que los vectores sean variables ...
						// dinámicas (memoria reutilizable durante la ejecución)

#ifdef VECTOR_GLOBAL
#define MAX 50//33554432 //=2^25
double M[MAX][MAX], v1[MAX], v2[MAX];
#endif


int main(int argc, char** argv){
	int i,j,suma;
	struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución
	
	//Leer argumento de entrada (no de componentes del vector)
	if (argc<2){
		printf("Faltan no componentes del vector\n");
		exit(-1);
	}
	unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

	#ifdef VECTOR_GLOBAL
		if (N>MAX) N=MAX;
	#endif

	#ifdef VECTOR_DYNAMIC
		double *M, *v1, *v2;
		M  = (double*) malloc(N*N*sizeof(double));// malloc necesita el tamaño en bytes
		v1 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
		v2 = (double*) malloc(N*sizeof(double));
		if ( (M==NULL) || (v1==NULL) || (v2==NULL) ){
		printf("Error en la reserva de espacio para los vectores\n");
		exit(-2);
		}
	#endif

	//Inicializar vectores
	#pragma omp parallel for private(j) schedule(static)
	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			M[i][j] = N*0.1+i*0.1; 
	}

	#pragma omp parallel for
	for(i=0; i<N; i++){
		v1[i] = N*0.1-i*0.1; //los valores dependen de N
		v2[i] = 0;
	}

	// Calculo 
	clock_gettime(CLOCK_REALTIME,&cgt1);
	#pragma omp parallel for private(j) schedule(static)
		for(i=0; i<N; i++){
			for(j=0; j<N; j++)
				v2[i]+=M[i][j]*v1[j];
		}
	
	clock_gettime(CLOCK_REALTIME,&cgt2);
	
	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

	printf("Tiempo de ejecución= %2.11f\n",ncgt);
	printf("Primer componente= %2.3f \n",v2[0] );
	printf("Ultimo componente= %2.3f \n",v2[N-1] );

	// Visualiza las matrices si no son muy grandes
	// Se recomienda redirigir la salida a un fichero.
	if (N < 20) {
		printf("\n\t M \n");
		for(i=0; i<N; i++){
			printf("| ");
			for(j=0; j<N; j++)
				printf(" %2.2f ", M[i][j]);
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
	
	#ifdef VECTOR_DYNAMIC
		free(M); // libera el espacio reservado para v1
		free(v1); // libera el espacio reservado para v2
		free(v2); // libera el espacio reservado para v3
	#endif


	return 0;
}