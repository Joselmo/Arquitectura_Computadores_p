#!/bin/bash
#Se asigna al trabajo el nombre pmtv-OpenMP
#PBS -N pmtv-OpenMP
#Se asigna al trabajo la cola ac
#PBS -q ac

#Se ejecuta pmtv-OpenMP, que está en el directorio en el que se ha ejecutado qsub,
#             N  SC CH
export OMP_SCHEDULE="static"
echo "static - default"
./pmtv-OpenMP 576
export OMP_SCHEDULE="static,1"
echo "static - 1"
./pmtv-OpenMP 576
export OMP_SCHEDULE="static,64"
echo "static - 64"
./pmtv-OpenMP 576
echo "----------------------------------------"
export OMP_SCHEDULE="dynamic"
echo "dynamic - default"
./pmtv-OpenMP 576
export OMP_SCHEDULE="dynamic,1"
echo "dynamic - 1"
./pmtv-OpenMP 576
export OMP_SCHEDULE="dynamic,64"
echo "dynamic - 64"
./pmtv-OpenMP 576
echo "-----------------------------------------"
export OMP_SCHEDULE="guided"
echo "guided - default"
./pmtv-OpenMP 576
export OMP_SCHEDULE="guided,1"
echo "guided - 1"
./pmtv-OpenMP 576
export OMP_SCHEDULE="guided,64"
echo "guided - 64"
./pmtv-OpenMP 576 
echo "fin correctamente"
