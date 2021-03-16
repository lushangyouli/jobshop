#ifndef _HEREDITY_H_
#define _HEREDITY_H_
#include "heredity.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
int **initialPop(){				 				  					    //初始化种群 
int i=0,j=0,m=0,n=0;
int sum=0;
for(i=1;i<=documentNumber;i++){	//得到序列长度 
	sum+=serialNumber[i];
}	  
sumSerial=sum;
int **chromosome;
if(documentNumber%2==0){
	chromosome=(int **)malloc(sizeof(int *)*(documentNumber+1));
	for(i=1;i<=documentNumber;i++){
	chromosome[i]=(int *)malloc(sizeof(int)*(sum+1)); 
}
for(i=1;i<=documentNumber;i++){		//初始化染色体数组 
	for(j=1;j<=sum;j++){
		
		chromosome[i][j]=0; 
	}
}
for(m=1,i=1;m<=documentNumber;m++){	//先初始化一条染色体 
	for(j=1;j<=serialNumber[m];j++,i++){
		chromosome[1][i]=m;
	}
}
for(i=2;i<=documentNumber;i++){
	for(j=1;j<=sum;j++){			//复制初始化的染色体到新染色体上 
		chromosome[i][j]=chromosome[1][j];
	}
	n+=serialNumber[i-1];
	exchange(&chromosome[i][1],&chromosome[i][n+1]); 
}
}
else{
	chromosome=(int **)malloc(sizeof(int *)*(documentNumber+2));
	for(i=1;i<=documentNumber+1;i++){
	chromosome[i]=(int *)malloc(sizeof(int)*(sum+1)); 
}
for(i=1;i<=documentNumber+1;i++){		//初始化染色体数组 
	for(j=1;j<=sum;j++){
		
		chromosome[i][j]=0; 
	}
}
for(m=1,i=1;m<=documentNumber;m++){	//先初始化一条染色体 
	for(j=1;j<=serialNumber[m];j++,i++){
		chromosome[1][i]=m;
	}
}
for(i=2;i<=documentNumber;i++){
	for(j=1;j<=sum;j++){			//复制初始化的染色体到新染色体上 
		chromosome[i][j]=chromosome[1][j];
	}
	n+=serialNumber[i-1];
	exchange(&chromosome[i][1],&chromosome[i][n+1]); 
	}
	chromosome[i]=chromosome[1];
}
return chromosome; 
} 

int fitFunction(int * Chromosome){										//计算给定染色体的适应度 
	int i,max=0; 
	int machinetime[machineNumber+1];
	for(i=0;i<=machineNumber;i++)
		machinetime[i]=0;
	int n_num[documentNumber+1];//暂存染色体的当前工件的工序数
	int x_num[documentNumber+1];//用于判断时间是否合理
	for(i=0;i<=documentNumber;i++){
		n_num[i]=0;
		x_num[i]=0;
	}
	for(i=1;i<=sumSerial;i++){
		n_num[Chromosome[i]]++;
		if(n_num[Chromosome[i]]==1){
			machinetime[machine[Chromosome[i]][1]]+=Time[Chromosome[i]][1];
			x_num[Chromosome[i]]=machinetime[machine[Chromosome[i]][1]];
		}
		else if(n_num[Chromosome[i]]!=1){
			if(machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]] >= x_num[Chromosome[i]]){
				machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]]+=Time[Chromosome[i]][n_num[Chromosome[i]]];
				x_num[Chromosome[i]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
			}
			else if(machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]] < x_num[Chromosome[i]]){
				machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]]=x_num[Chromosome[i]]+Time[Chromosome[i]][n_num[Chromosome[i]]];
				x_num[Chromosome[i]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
			}
		}	
	}
	for(i=1;i<=machineNumber;i++)
		if(max<machinetime[i])
			max=machinetime[i];
	return max;
} 

selectedChromosome selectFunction(int **Pop){     						//从种群中择优选择俩条染色体 
    selectedChromosome choiceChromosome;
    int fitness[documentNumber+1];            //存储适应度
    int i,best1,best2;
    for(i=1;i<=documentNumber;i++){            //跟新适应度
        fitness[i]=fitFunction(Pop[i]);
    }
    if (fitness[1] < fitness[2]) {
        best1 = 1;
        best2 = 2;
    } else {
        best2 = 1;
        best1 = 2;
    }
    for (i = 3; i <= documentNumber; i++){
        if (fitness[i] < fitness[best1]) {
            best2 = best1;
            best1 = i;
        } else if (fitness[i] < fitness[best2]) {
            best2 = i;
        }
    }
    choiceChromosome.chromosome1 = (int *)malloc(sizeof(int)*(sumSerial+1));
    choiceChromosome.chromosome2 = (int *)malloc(sizeof(int)*(sumSerial+1));
    for (i = 1; i <= sumSerial; i++) {
        choiceChromosome.chromosome1[i] = Pop[best1][i];
        choiceChromosome.chromosome2[i] = Pop[best2][i];
    }

    return choiceChromosome;        //返回新染色体
}

selectedChromosome crossoverFunction(selectedChromosome chromosome){	//将两条染色体交叉 
	int random_id, random_part, i ,j, k1 = 0, k2 = 0, zero = 0, zero_ = 0, length=sumSerial;
	random_id = randomNumber(length-1);
	random_part = randomNumber(length-random_id);
	int random_id2 = randomNumber(length-1);
	typedef struct list {
		int d1;
		int d2;	
	} List;
	List list1[length], list2[length], templist1[random_part], templist2[random_part];
	for (i = 1; i < length; i++) {
		for (j = 1; j <= i; j++) {
			if (chromosome.chromosome1[j] == chromosome.chromosome1[i])
				k1++;
			if (chromosome.chromosome2[j] == chromosome.chromosome2[i])
				k2++;
		}
		list1[i-1].d1 = chromosome.chromosome1[i];
		list1[i-1].d2 = k1;
		list2[i-1].d1 = chromosome.chromosome2[i];
		list2[i-1].d2 = k2;
		k1 = k2 = 0;
	}
	for (i = random_id-1; i < random_id+random_part-1; i++) {
		templist1[zero].d1 = list1[i].d1;
		templist1[zero].d2 = list1[i].d2;
		zero++;
	}
	for (i = 0; i < length; i++) {
		for (j = 0; j < zero; j++) {
			if (list2[i].d1 == templist1[j].d1 && list2[i].d2 == templist1[j].d2) {
				templist2[zero_].d1 = list2[i].d1;
				templist2[zero_].d2 = list2[i].d2;
				list2[i].d1 = 0;
				zero_++;
			}
		}
	}
	int temp[length+random_part];
	for (i = random_id; i < random_id+random_part; i++)
		chromosome.chromosome1[i] = templist2[i-random_id].d1;
	zero = 0;
	j = 1;
	for (i = 1; i < length; i++) {
		if (i == random_id2) {
			for (; j < i+random_part; j++) {
				temp[j] = templist1[zero++].d1;
			}
			temp[j] = list2[i-1].d1;
			j++;
			continue;
		}
		temp[j++] = list2[i-1].d1;
	}
	j = 1;
	for (i = 1; i < length+random_part; i++) {
		if (temp[i] != 0)
			chromosome.chromosome2[j++] = temp[i];
	}
	return chromosome;
}

selectedChromosome variationFunction(selectedChromosome a){				//将两条染色体变异 
	int randnumber1,randnumber2,randnumber3,randnumber4,length=sumSerial;
	randnumber1=rand()%(length-1)+1;
	randnumber2=rand()%(length-1)+1;
	randnumber3=rand()%(length-1)+1;
	randnumber4=rand()%(length-1)+1;
	exchange(a.chromosome1+randnumber1,a.chromosome1+randnumber2);
	exchange(a.chromosome2+randnumber3,a.chromosome2+randnumber4);
	return a;
}

int **createPop(){														//创造一个新种群	
	int i;
	int **newPop;
	newPop=(int **)malloc(sizeof(int *)*(documentNumber+1));
	for(i=1;i<=documentNumber;i++){
		newPop[i]=(int *)malloc(sizeof(int)*(sumSerial+1)); 
	}
	return newPop;
}

int *bestChromosome(int **Pop){											//找到种群中的最优染色体 
	int i,choice;
	int fitness[documentNumber+1];
	for(i=1;i<=documentNumber;i++){
		fitness[i]=fitFunction(Pop[i]);
	}
	int max=0;
	for(i=1;i<=documentNumber;i++){
		if(max<fitness[i]){ 
			max=fitness[i];
			choice=i;
		}
	}
	return Pop[choice];
}
#endif
