#include <stdio.h>
#include <stdlib.h>
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
*/
main(int argc, char **argv) {
	int i, n=16,chunk,a[n],suma=0;
	if(argc < 3) {
		fprintf(stderr,"\nFalta iteraciones o chunk \n");
		exit(-1);
	}

	n = atoi(argv[1]); if (n>200) n=200; chunk = atoi(argv[2]);

	omp_sched_t kind;
	int modifier;

	omp_get_schedule(&kind, & modifier);
	printf("Fuera sin modificar\n");
	printf("dyn-var=%d  nthreads_var=%d  run-sched-var=(%d,%d)\n",
		omp_get_dynamic(),omp_get_max_threads(),kind,modifier);
	// Las modifico
	/*Un valor que indica si el número de subprocesos disponibles en la
	región paralela subsiguiente se puede ajustar el motor en tiempo de
	ejecución.Si es distinto de cero, el runtime puede ajustar el número
	de subprocesos, si cero, el runtime no ajusta dinámicamente el número de subprocesos
	*/
	omp_set_dynamic(4);
	omp_set_num_threads(3);
	kind = 1;
	modifier = 2;
	omp_set_schedule(kind, modifier);
	printf("Fuera modificadas\n");
	printf("dyn-var=%d  nthreads_var=%d  run-sched-var=(%d,%d)\n",
		omp_get_dynamic(),omp_get_max_threads(),kind,modifier);


	for (i=0; i<n; i++) a[i] = i;
		#pragma omp parallel num_threads(4)
		{
			#pragma omp for firstprivate(suma) lastprivate(suma) \
				 schedule(dynamic,chunk)
			for (i=0; i<n; i++){
				suma = suma + a[i];
				if (i==0){
					omp_get_schedule(&kind, & modifier);
					printf("Dentro sin modificar\n");
					printf("dyn-var=%d  nthreads_var=%d  run-sched-var=(%d,%d)\n",
						omp_get_dynamic(),omp_get_max_threads(),kind,modifier);
					printf(" antes get num threads =%d\n",omp_get_num_threads());
					// Las modifico
					omp_set_dynamic(0);
					omp_set_num_threads(7);
					printf("get num threads =%d\n",omp_get_num_threads());
					kind=3;
					modifier=2;
					omp_set_schedule(kind, modifier);
					printf("Dentro Modificadas\n");
					printf("dyn-var=%d  nthreads_var=%d  run-sched-var=(%d,%d)\n",
					omp_get_dynamic(),omp_get_max_threads(),kind,modifier);
				}

				printf(" thread %d suma a[%d]=%d suma=%d \n",
				omp_get_thread_num(),i,a[i],suma);

			}
/*
			#pragma omp single
			{
				omp_get_schedule(&kind, & modifier);
				printf("Fuera sin modificar\n");
				printf("dyn-var=%d  nthreads_var=%d  run-sched-var=(%d,%d)\n",
					omp_get_dynamic(),omp_get_max_threads(),kind,modifier);
				printf(" antes get num threads =%d\n",omp_get_num_threads());
				// Las modifico
				omp_set_dynamic(0);
				omp_set_num_threads(7);
				printf("get num threads =%d\n",omp_get_num_threads());
				kind=3;
				modifier=2;
				omp_set_schedule(kind, modifier);
				printf("Fuera Modificadas\n");
				printf("dyn-var=%d  nthreads_var=%d  run-sched-var=(%d,%d)\n",
					omp_get_dynamic(),omp_get_max_threads(),kind,modifier);
			}*/
		}

	printf("Fuera de 'parallel for' suma=%d\n",suma);
}
