#include <stdio.h>
#include <stdlib.h>
int documentNumber, machineNumber;
int **Time, **machine, *serialNumber;
void input()
{
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
		printf("[%c]",  ch);
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
int main(int argc, char const *argv[])
{
	input();
	int i, j;
	for (i = 1; i <= documentNumber; i++) {
		for (j = 1; j <= serialNumber[i]; j++)
			printf("[%d][%d] ",  Time[i][j], machine[i][j]);
		printf("\n");
	}
	return 0;
}
