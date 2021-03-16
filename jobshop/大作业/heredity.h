#include "struct.h"
int **initialPop();
int fitFunction(int * Chromosome);
selectedChromosome selectFunction(int **Pop);
selectedChromosome crossoverFunction(selectedChromosome chromosome);
selectedChromosome variationFunction(selectedChromosome a);
int **createPop();
int *bestChromosome(int **Pop);

extern int documentNumber, machineNumber,sumSerial;
extern int **Time, **machine, *serialNumber;

