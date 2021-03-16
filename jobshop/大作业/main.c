#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "struct.h"
#define LIMIT 300
int documentNumber, machineNumber,sumSerial;
int **Time, **machine, *serialNumber;
float Pc=50,Pm=50; 
clock_t start,end;

int main(){																//主函数 
	start=clock();	//计时开始 
	srand(time(NULL));   //随机数以时间作为种子 
	int **pop;int **newpop;int count,i,j;
	selectedChromosome chosenChromosome;
	input();
	pop=initialPop();
	if(documentNumber%2!=0){
	   j=documentNumber+1;
	}
	else{
		j=documentNumber;
	}
	int a=fitFunction(bestChromosome(pop)); 
	int x = 0, y = 1;
	int *finalChromosome=malloc(sizeof(int)*(sumSerial+1));
	finalChromosome=bestChromosome(pop);
	for(i=0;i<=30000;i++){
		newpop=createPop();
		for(count=1;count<=j/2;count++){	//循环出一个新的种群 
			chosenChromosome=selectFunction(pop);
			if(randomNumber(100)<Pc){
				chosenChromosome=crossoverFunction(chosenChromosome);	//交叉 
			}
			if(randomNumber(100)<Pm){
				chosenChromosome=variationFunction(chosenChromosome);	//变异 
			}
			newpop[2*count-1]=chosenChromosome.chromosome1;		//接收新的染色体 
			newpop[2*count]=chosenChromosome.chromosome2; 
		} 		
		pop=newpop;	 //跟新种群 
		if(a>fitFunction(bestChromosome(pop))){
			a=fitFunction(bestChromosome(pop));
			finalChromosome=bestChromosome(pop);
			x = 0;
		}
		x++;
		if (x >= 10000 && y <= 6) {
			pop = initialPop();
			i = 0;
			x = 0;
			y++;
			continue;
		}
	}
	output(finalChromosome);
	return 0;
}
