#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <sys/queue.h>
#include <string.h>

int main(){
	FILE * fp, *fpOut;
	char str[250],str1[250],*token,*subtoken;

	//OPEN and READ input file
	fp = fopen("cpu_scheduling_input_file.txt","r");
	if (fp == NULL){
		perror("Error opening file.");
		return(-1);
	}
	fpOut = fopen("cpu_scheduling_output_file.txt","w");
	int queueNum = 0;
	while (fgets(str,250,fp)!= NULL){
		strcpy(str1,str);//Make copy of line
		int quant,burst;
		token = strtok(str," ");

		const char *tq = "tq";
		int pcount = 0;

		while (token != NULL){
			if (strchr(token,'p')){
				pcount = pcount + 1;
			}
			token = strtok(NULL," ");
		}
		int queue[pcount];//Create queue array with size of number of processes

		token = strtok(str1," ");
		int i = 0;
		while (token != NULL){
			if (strcmp(token,tq)==0){//Look for tq in this line
                                token = strtok(NULL, " ");//Go to next token for the integer time quantum
                                quant = atoi(token);//Set time quantum for this queue
                        }
                        else if (strchr(token,'p')){
                                token = strtok(NULL," ");
			 	burst = atoi(token);
				queue[i] = burst;
				i++;
                        }
                        token = strtok(NULL," ");
                }
		queueNum = queueNum + 1;

		//FCFS
		printf("Ready Queue %d applying FCFS Scheduling:\n\n",queueNum);
		printf("Order of selection by CPU:\n");
		fprintf(fpOut,"Ready Queue %d applying FCFS Scheduling:\n\n",queueNum);
                fprintf(fpOut,"Order of selection by CPU:\n");

		for (int i = 1; i <= pcount; i++){
                        printf("p%d ",i);
			fprintf(fpOut,"p%d ",i);

                }
		int sumFCFS = 0;
		int avgSum = 0;
		fprintf(fpOut,"\n\nIndividual waiting times for each process:\n");
		printf("\n\nIndividual waiting times for each process:\n");
		for (int i = 0; i < pcount; i++){
			int j = i + 1;
			avgSum = avgSum + sumFCFS;
			printf("p%d: %d\n",j,sumFCFS);
			fprintf(fpOut,"p%d: %d\n",j,sumFCFS);
			sumFCFS = queue[i] + sumFCFS;
                }
		printf("\nAverage waiting time: %.1f\n",(float)avgSum/pcount);

		//SJF
		printf("\nReady Queue %d applying SJF Scheduling:\n\n",queueNum);
                printf("Order of selection by CPU:\n");
		fprintf(fpOut,"\nAverage waiting time: %.1f\n",(float)avgSum/pcount);
                fprintf(fpOut,"\nReady Queue %d applying SJF Scheduling:\n\n",queueNum);
                fprintf(fpOut,"Order of selection by CPU:\n");

		int copyQueue[pcount];
		for (int i = 0; i < pcount; i++){//COPY queue
			copyQueue[i] = queue[i];
                }

		for (int i = 0; i < pcount; ++i){
			for (int j = i + 1; j < pcount; ++j){//Sort from min to max
				if (copyQueue[i] > copyQueue[j]){
					int a = copyQueue[i];
                    			copyQueue[i] = copyQueue[j];
                    			copyQueue[j] = a; 
                		}
            		}
        	}
		int queueIndex[pcount];
		for (int i = 0; i < pcount; i++){
			for (int j = 0; j < pcount; j++){
				if (copyQueue[i] == queue[j]){//Copy index match of queue 
					queueIndex[i] = j+1;
	                        }
			}
                }
		for (int i = 0; i < pcount; i++){
			printf("p%d ",queueIndex[i]);
			fprintf(fpOut,"p%d ",queueIndex[i]);

		}
		fprintf(fpOut,"\n\nIndividual waiting times for each process:\n\n");
		printf("\n\nIndividual waiting times for each process:\n\n");
		int sumSJF = 0,avgSumSJF = 0;

		for (int i = 0; i < pcount; i++){
			avgSumSJF = avgSumSJF + sumSJF;
			fprintf(fpOut,"p%d: %d\n",queueIndex[i],sumSJF);
                        printf("p%d: %d\n",queueIndex[i],sumSJF);
			sumSJF = copyQueue[i] + sumSJF;
                }
		
		fprintf(fpOut,"\nAverage waiting time: %.1f\n",(float)avgSumSJF/pcount);
		printf("\nAverage waiting time: %.1f\n",(float)avgSumSJF/pcount);

		//RR
		fprintf(fpOut,"\nReady Queue %d applying RR Scheduling:\n\n",queueNum);
		printf("\nReady Queue %d applying RR Scheduling:\n\n",queueNum);
		printf("Order of selection by CPU:\n\n");
		fprintf(fpOut,"Order of selection by CPU:\n\n");
		int copyQueue2[pcount];
		for (int i = 0; i < pcount; i++){//Copy queue
			copyQueue2[i] = queue[i];
		}
		int ind = 0;//index
		while (copyQueue2[ind] != 0){
			if(copyQueue2[ind] <= quant){
				
			}
			if (copyQueue2[ind] > quant){
				copyQueue2[ind] = copyQueue2[ind] - quant;
				
			}

			ind++;
		}

	}
	fclose(fp);
	fclose(fpOut);
	return 0;
}
