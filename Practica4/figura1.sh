#!/bin/bash
#               - O2
echo "gcc -O2 figura_1.c -o figura_1"
gcc -O2 figura_1.c -o figura_1
echo "gcc -O2 figura_1_modificado_a.c -o figura_1_modificado1"
gcc -O2 figura_1_modificado_a.c -o figura_1_modificado1
echo "gcc -O2 figura_1_modificado_b.c -o figura_1_modificado2"
gcc -O2 figura_1_modificado_b.c -o figura_1_modificado2

./figura_1 "original" > tiempos_figura1
./figura_1_modificado1 "modificado 1" >> tiempos_figura1
./figura_1_modificado2 "modificado 2" >> tiempos_figura1
cat tiempos_figura1
