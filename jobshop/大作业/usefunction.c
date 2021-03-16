#ifndef _USEFUNCTION_H_
#define _USEFUNCTION_H_
#include "usefunction.h" 
void exchange(int *a,int *b){	    									 	 	
	int i;
	i=*a;
	*a=*b;
	*b=i;
}

int max(int * serialnumber,int documentnumber){							 
	int i,max=0;
	for(i=1;i<=documentnumber;i++)
		if(max<serialnumber[i])
			max=serialnumber[i];
	return max;
}

int randomNumber(int n){														
	if(n==0){
		return 0;
	}
	else{
	int random_number=rand()%n+1;
	return random_number;
	}
}
#endif
