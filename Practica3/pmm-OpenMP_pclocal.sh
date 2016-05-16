#!/bin/bash
#Se asigna al trabajo el nombre pmtv-OpenMP
#PBS -N pmtv-OpenMP
#Se asigna al trabajo la cola ac
#PBS -q ac

#Se ejecuta pmtv-OpenMP, que está en el directorio en el que se ha ejecutado qsub,
#             N  SC CH
export OMP_NUM_THREADS=2
echo "threads = 2 - 1"
./pmm-OpenMP 576
echo "threads = 2 - 2"
./pmm-OpenMP 576
export OMP_NUM_THREADS=4
echo "threads = 4 - 1"
./pmm-OpenMP 576
echo "threads = 4 - 2"
./pmm-OpenMP 576
export OMP_NUM_THREADS=8
echo "threads = 8 - 1"
./pmm-OpenMP 576
echo "threads = 8 - 2"
./pmm-OpenMP 576
#export OMP_NUM_THREADS=16
#echo "threads = 16 - 1"
#./pmm-OpenMP 576
#echo "threads = 16 - 2"
#./pmm-OpenMP 576
