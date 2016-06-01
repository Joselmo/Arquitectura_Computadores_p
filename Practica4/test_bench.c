/* Ejemplo de Programa de Prueba */
#include <stdio.h>
#include <math.h>
#include <time.h>
int suma_prod(int a, int b, int n);
main()
{
    /* ------------- */
    int i,j,a,b,n,c;
    /* ------------- */
    clock_t start,stop;
    start= clock();
    /* ------------------------------------------ */
    n=6000;a=1;b=2;
    for (j=1;j<=10000;j++)
    {
    printf("a=%d b=%d n=%d\n",a,b,n);
    c=suma_prod(a,b,n);
    printf("resultado= %d\n",c);
    }
    /* -------------------------------------------- */
    stop = clock();
    printf("Tiempo= %f",difftime(stop,start));
    return 0;
}
