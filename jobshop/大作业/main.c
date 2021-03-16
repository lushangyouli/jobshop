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

int main(){																//������ 
	start=clock();	//��ʱ��ʼ 
	srand(time(NULL));   //�������ʱ����Ϊ���� 
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
		for(count=1;count<=j/2;count++){	//ѭ����һ���µ���Ⱥ 
			chosenChromosome=selectFunction(pop);
			if(randomNumber(100)<Pc){
				chosenChromosome=crossoverFunction(chosenChromosome);	//���� 
			}
			if(randomNumber(100)<Pm){
				chosenChromosome=variationFunction(chosenChromosome);	//���� 
			}
			newpop[2*count-1]=chosenChromosome.chromosome1;		//�����µ�Ⱦɫ�� 
			newpop[2*count]=chosenChromosome.chromosome2; 
		} 		
		pop=newpop;	 //������Ⱥ 
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
