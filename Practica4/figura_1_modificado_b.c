

#include <stdlib.h>
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()

#define VECTOR_GLOBAL

#ifdef VECTOR_GLOBAL
#define MAX 40000
int R[MAX];
int X1, X2, x11,x12,x13,x21,x22,x23;
#endif

struct {
    int a;
    int b;
} s[10000];


int main(int argc, char** argv){


	struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución
    int i,ii;
    char * mensaje;

    mensaje = argv[1];

    for(i=0; i < 10000;i++){
        s[i].a = 0;
        s[i].b = 0;
    }

    clock_gettime(CLOCK_REALTIME,&cgt1);
    for (ii=0; ii<40000;ii++) {
        X1=0; X2=0;
        for(i=0; i<10000;i+=4){
            X1+=s[i].a+ii;
            x11+=s[i+1].a+ii;
            x12+=s[i+2].a+ii;
            x13+=s[i+3].a+ii;
        }
        X1 += x11 + x12 +x13;
        X1 *=2; // Cambio 1
        for(i=0; i<10000;i+=4){
            X2+=s[i].b-ii;
            x21+=s[i+1].b-ii;
            x22+=s[i+2].b-ii;
            x23+=s[i+3].b-ii;
        }
        X2 += x21 + x22 +x23;
        X2 *=3; // cambio 1
        if (X1<X2)
            R[ii]=X1;
        else
            R[ii]=X2;
    }
    clock_gettime(CLOCK_REALTIME,&cgt2);



	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    printf("%s\n",mensaje );
    printf("Tiempo de ejecución= %2.11f\n",ncgt);
    printf("Primer componente= %d \n",R[0] );
    printf("Ultimo componente= %d \n",R[39999] );

    return EXIT_SUCCESS;
}
