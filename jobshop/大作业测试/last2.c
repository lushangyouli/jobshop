#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#define LIMIT 300
struct selected{
	int *chromosome1;
	int *chromosome2;
};
typedef struct selected selectedChromosome;	
void input();int **intialPop();
void exchange();void selection();
clock_t start,end;
int randomNumber();int sum(); 
int max();int fitFuntion();
int documentNumber, machineNumber;
int **Time, **machine, *serialNumber;
selectedChromosome selectFunction();selectedChromosome crosscoverFunction();selectedChromosome variationFuntion();
int sumSerial;
float Pc=75,Pm=50; 

void input(){
	FILE *fp = fopen("input.txt", "r");
	if (fp) {
		fscanf(fp, "%d%d",  &documentNumber, &machineNumber);
		Time = (int **)malloc(sizeof(int *) * (documentNumber+1));
		machine = (int **)malloc(sizeof(int *) * (documentNumber+1));
		serialNumber = (int *)malloc(sizeof(int) * (documentNumber+1));
		int i = 0, j = 1, n = 0;
		int ch;
		fseek(fp ,4*sizeof(char), 0);
		ch = fgetc(fp);
		while (i < documentNumber) {
			int *time1, *machine1;
			while (ch != '\n' && ch != EOF || i == n) {
				if (i == n)
					i = n+1;
				int *temp_1, *temp_2;
				temp_1 = (int *)malloc(sizeof(int) * (j+1));
				temp_2 = (int *)malloc(sizeof(int) * (j+1));
				int k = 1;
				temp_1[j] = temp_2[j] = 0;
				while ((ch = fgetc(fp)) != ' ') {
					temp_2[j] *= 10;
					temp_2[j] += ch-'0';
				}
				temp_2[j]++;
				while ((ch = fgetc(fp)) != ' ' && ch != '\n' && ch != EOF) {
					temp_1[j] *= 10;
					temp_1[j] += ch-'0';
				}
				while (k < j) {		
					temp_1[k] = time1[k];
					temp_2[k] = machine1[k];
					k++;
				}
				time1 = temp_1;
				machine1 = temp_2;
				temp_1 = temp_2 = NULL;
				j++;
			}
			serialNumber[i] = j-1;
			Time[i] = (int *)malloc(sizeof(int) * j);					
			machine[i] = (int *)malloc(sizeof(int) * j);
			int k;
			for (k = 1; k < j; k++) {
				Time[i][k] = time1[k];									
				machine[i][k] = machine1[k];
			}
			free(time1);
			free(machine1);
			j = 1;
			n++;
		}
	fclose(fp);
	}
}

int **initialPop(){	//初始化种群的数组 			（测试已通过） 
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

void exchange(int *a,int *b){	//交换俩个数的位置 	 	(测试已通过) 
	int i;
	i=*a;
	*a=*b;
	*b=i;
}

int randomNumber(int n){		//n以内的随机数 		(测试已通过)
	if(n==0){
		return 0;
	}
	else{
	int random_number=rand()%n+1;
	return random_number;
	}
}
 
int **createPop(){		//(测试已通过)
	int i;
	int **newPop;
	newPop=(int **)malloc(sizeof(int *)*(documentNumber+1));
	for(i=1;i<=documentNumber;i++){
		newPop[i]=(int *)malloc(sizeof(int)*(sumSerial+1)); 
	}
	return newPop;
}

int fitFunction(int * Chromosome,int sum){	//(测试已通过)
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
	for(i=1;i<=sum;i++){
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

selectedChromosome selectFunction(int **Pop){     //(测试已通过)
    selectedChromosome choiceChromosome;
    int fitness[documentNumber+1];            //存储适应度
    int i,best1,best2;
    for(i=1;i<=documentNumber;i++){            //跟新适应度
        fitness[i]=fitFunction(Pop[i],sumSerial);
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
    // fixed me ! important to copy instead of directly assigning the pointer of Pop.
    choiceChromosome.chromosome1 = (int *)malloc(sizeof(int)*(sumSerial+1));
    choiceChromosome.chromosome2 = (int *)malloc(sizeof(int)*(sumSerial+1));
    for (i = 1; i <= sumSerial; i++) {
        choiceChromosome.chromosome1[i] = Pop[best1][i];
        choiceChromosome.chromosome2[i] = Pop[best2][i];
    }

    return choiceChromosome;        //返回新染色体
}

int max(int * serialnumber,int documentnumber){
	int i,max=0;
	for(i=1;i<=documentnumber;i++)
		if(max<serialnumber[i])
			max=serialnumber[i];
	return max;
}

selectedChromosome crossoverFunction(selectedChromosome chromosome, int length){
	int random_id, random_part, i ,j, k1 = 0, k2 = 0, zero = 0, zero_ = 0;
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

selectedChromosome variationFunction(selectedChromosome a,int lenth){
	int randnumber1,randnumber2,randnumber3,randnumber4;
	randnumber1=rand()%(lenth-1)+1;
	randnumber2=rand()%(lenth-1)+1;
	randnumber3=rand()%(lenth-1)+1;
	randnumber4=rand()%(lenth-1)+1;
	exchange(a.chromosome1+randnumber1,a.chromosome1+randnumber2);
	exchange(a.chromosome2+randnumber3,a.chromosome2+randnumber4);
	return a;
}

int *bestChromosome(int **Pop){
	int i,choice;
	int fitness[documentNumber+1];
	for(i=1;i<=documentNumber;i++){
		fitness[i]=fitFunction(Pop[i],sumSerial);
	}
	int max=0;
	for(i=1;i<=documentNumber;i++){
		if(max<fitness[i]){//为什么要max小于； 
			max=fitness[i];
			choice=i;
		}
	}
	return Pop[choice];//为什么要return i而不是choice 
} 

void output(int *Chromosome,int sum){
	int S=max(serialNumber,documentNumber);
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
	int machinetime[machineNumber+1],machineput[machineNumber+1];//machineput数组用于保存put二维数组列数 
	for(i=0;i<=machineNumber;i++){
		machinetime[i]=0;
		machineput[i]=1;
	}
	int n_num[documentNumber+1];//暂存染色体的当前工件的工序数
	int x_num[documentNumber+1];//用于判断时间是否合理
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
					fprintf (fPtr," (%d %d-%d %d)",put[i][j],put[i][j+1]-1,put[i][j+2]-1,put[i][j+3]) ;
			}
			fprintf (fPtr,"\n") ;
		}
		end=clock();
		fprintf(fPtr,"Time Used: %.3fs\n",(double)(end-start)/CLK_TCK);
		fprintf (fPtr,"End Time: ") ;
		int endtime;
		endtime=fitFunction (Chromosome,sum) ;
		fprintf (fPtr,"%d",endtime) ;
	}
 	fclose(fPtr);
}

int main(){	
	start=clock();
	int **Pop;
	int **newPop;
	int count,i,j;
	srand(time(NULL));
	selectedChromosome chosenChromosome;
	input();
	Pop=initialPop();
	if(documentNumber%2!=0){
	   j=documentNumber+1;
	}
	else{
		j=documentNumber;
	}
	int a=fitFunction(bestChromosome(Pop),sumSerial); 
	int *finalChromosome=malloc(sizeof(int)*(sumSerial+1));
	finalChromosome=bestChromosome(Pop);
	for(i=0;i<=20000;i++){
		newPop=createPop();
		for(count=1;count<=j/2;count++){	//循环出一个新的种群 
			chosenChromosome=selectFunction(Pop);
			if(randomNumber(100)<Pc){
				chosenChromosome=crossoverFunction(chosenChromosome,sumSerial);	//85%概率交叉 
			}
			if(randomNumber(100)<Pm){
				chosenChromosome=variationFunction(chosenChromosome,sumSerial);	//5%变异 
			}
			newPop[2*count-1]=chosenChromosome.chromosome1;		//接收新的染色体 
			newPop[2*count]=chosenChromosome.chromosome2; 
		} 
		//free(Pop);		//跟新种群 
		Pop=newPop;
		if(a>fitFunction(bestChromosome(Pop),sumSerial)){
			a=fitFunction(bestChromosome(Pop),sumSerial);
			finalChromosome=bestChromosome(Pop);
		}
	}
	output(finalChromosome,sumSerial);
	return 0;
} 

