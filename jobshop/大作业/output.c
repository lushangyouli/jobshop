#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#include "output.h"
#include <stdio.h>
#include "struct.h"
#include <time.h>
void output(int *Chromosome){										
	int S=max(serialNumber,documentNumber),sum=sumSerial;
	if(S<documentNumber)
		S=documentNumber;
	int SerialNumber=S*4;
	int put[machineNumber+1][SerialNumber+1];
	int i,j;
	for(i=0;i<=machineNumber;i++){
		for(j=0;j<=SerialNumber;j++){
			put[i][j]=0;
		}
	}
	int machinetime[machineNumber+1],machineput[machineNumber+1];
	for(i=0;i<=machineNumber;i++){
		machinetime[i]=0;
		machineput[i]=1;
	}
	int n_num[documentNumber+1];
	int x_num[documentNumber+1];
	for(i=0;i<=documentNumber;i++){
		n_num[i]=0;
		x_num[i]=0;
	}
	for(i=1;i<=sum;i++){
		n_num[Chromosome[i]]++;
		if(n_num[Chromosome[i]]==1){
			put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
			machinetime[machine[Chromosome[i]][1]]+=Time[Chromosome[i]][1];
			x_num[Chromosome[i]]=machinetime[machine[Chromosome[i]][1]];
			machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
			put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=Chromosome[i];
			machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
			put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=n_num[Chromosome[i]];
			machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
			put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
			machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
		}
		else if(n_num[Chromosome[i]]!=1){
			if(machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]] >= x_num[Chromosome[i]]){
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
				machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]]+=Time[Chromosome[i]][n_num[Chromosome[i]]];
				x_num[Chromosome[i]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=Chromosome[i];
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=n_num[Chromosome[i]]; 
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
			}
			else if(machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]] < x_num[Chromosome[i]]){
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=x_num[Chromosome[i]];
				machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]]=x_num[Chromosome[i]]+Time[Chromosome[i]][n_num[Chromosome[i]]];
				x_num[Chromosome[i]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=Chromosome[i];
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=n_num[Chromosome[i]];
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
				put[machine[Chromosome[i]][n_num[Chromosome[i]]]][machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]]=machinetime[machine[Chromosome[i]][n_num[Chromosome[i]]]];
				machineput[machine[Chromosome[i]][n_num[Chromosome[i]]]]++;
			}
		}	
	}
	FILE * fPtr;
	if( (fPtr=fopen ("output.txt","w") )!=NULL) {
		for (i=1;i<=machineNumber;i++) {
			fprintf (fPtr,"M%d",i-1) ;
			for (j=1;j<=SerialNumber;j+=4) {
				if( (put[i][j+2]!=0) && (put[i][j+1]!=0) )
					fprintf (fPtr," (%d,%d-%d,%d)",put[i][j],put[i][j+1]-1,put[i][j+2]-1,put[i][j+3]) ;
			}
			fprintf (fPtr,"\n") ;
		}
		end=clock();
		fprintf(fPtr,"Time Used: %.3fs\n",(double)(end-start)/CLK_TCK);
		fprintf (fPtr,"End Time: ");
		int endtime;
		endtime=fitFunction (Chromosome);
		fprintf (fPtr,"%d\n",endtime);
	}
 	fclose(fPtr);
}
#endif
