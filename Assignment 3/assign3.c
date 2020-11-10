#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

struct acc{
	int type; //0 is business,1 is personal
	int depFee,withFee,transfFee,transactFee,extraTransactFee, odraftFee; //Fees
	int numTransact,amntToDep,amntToWith;
	int balance;
	int odraft;//0 is NO, 1 is YES
};

struct acc *accnt;
pthread_mutex_t lock;

void *deposit_money(void *account){
	pthread_mutex_lock(&lock);  // ENTRY REGION
	struct acc *temp = (struct acc*) account;//CRITICAL STARTS
	temp->balance = temp->balance + temp->amntToDep;//Deposit money into account!//CRITICAL ENDS
	printf("Acc Balance: %d \n",temp->balance);//Print to console
	pthread_mutex_unlock(&lock); // EXIT REGION
}

int main(){
	int err_thread;
	int numOfAccs;
	const char *type = "type",*business = "business",*personal = "personal";
	int numAccs = 0;

	FILE *fp, *fpOut;
	char str[100],str1[100];

	//OPEN AND READ input file
	fp = fopen("assignment_3_input_file.txt","r");
	if (fp == NULL){
		perror("Error opening file.");
		return(-1);
	}

	//OPEN for WRITING to output file
	fpOut = fopen("assignment_3_output_file.txt","w");
	if (fpOut == NULL){
                perror("Error opening file.");
                return(-1);
        }
	while (fgets(str,100,fp)!= NULL){//Get each line from text file
		char* token = strtok(str, " ");//Tokenize each "word" with a space between
		while (token != NULL){
			if (strchr(token,'a')){//IF this word has an "a"..
				token = strtok(NULL," ");//Go to next word and...
				const char *type = "type";
				if (strcmp(token,type) == 0){//If next word is "type, keep trach of number of Accs
					if (numAccs == 0){
						accnt = (struct acc*)malloc(sizeof(struct acc));
					}
					else if (numAccs > 0){//Reallocate memory for new accounts
						accnt = (struct acc *)realloc(accnt,(numAccs + 1) * sizeof(struct acc));
					}

					numAccs = numAccs + 1;
					numOfAccs = numAccs;
					token = strtok(NULL," ");
					if (strcmp(token,business) == 0){
						accnt[numAccs - 1].type = 0;
						printf("Account'n");
					}
					else if (strcmp(token,personal) == 0){
                                                accnt[numAccs - 1].type = 1;

                                        }
					token = strtok(NULL," ");
					token = strtok(NULL," ");
					accnt[numAccs - 1].depFee = atoi(token);

                                        token = strtok(NULL," ");
					token = strtok(NULL," ");
					accnt[numAccs - 1].withFee = atoi(token);

					token = strtok(NULL," ");
                                        token = strtok(NULL," ");
                                        accnt[numAccs - 1].transfFee = atoi(token);

					token = strtok(NULL," ");
                                        token = strtok(NULL," ");
                                        accnt[numAccs - 1].numTransact = atoi(token);

					token = strtok(NULL," ");
                                        accnt[numAccs - 1].extraTransactFee = atoi(token);

					token = strtok(NULL," ");
                                        token = strtok(NULL," ");
					if (strchr(token,'Y')){
						accnt[numAccs - 1].odraft = 1;
						token = strtok(NULL," ");
						accnt[numAccs - 1].odraftFee = atoi(token);
					}
					else if (strchr(token,'N')){
                                                accnt[numAccs - 1].odraft = 0;
                                        }
					accnt[numAccs - 1].balance = 0;//INITIALIZE BALANCE FOR ACCOUNT TO 0
				}
			}
			else if (strchr(token,'p')){
				while (token != NULL){
					token = strtok(NULL," ");
					if (token == NULL){//If end of deposit line of text, break loop
                                                break;
                                        }

                                	token = strtok(NULL," ");
                                	int accountNum = atoi(token + 1); printf("%d ",accountNum);//Get accountNum to depos
                                	token = strtok(NULL," ");
                                	int depAmount = atoi(token); printf("%d ",depAmount);
					printf("test\n");
					if (pthread_mutex_init(&lock, NULL) != 0){
        					printf("\n mutex init failed\n");
        					return 1;
    					}
					pthread_t depThread;//Deposit thread
					accnt[accountNum - 1].amntToDep = depAmount;//Add this to struct so that can pass only one struct argument to pthread_create
					err_thread = pthread_create(&depThread, NULL, &deposit_money,&accnt[accountNum -1]);
					pthread_join(depThread, NULL);
					pthread_mutex_destroy(&lock);
				}
			}
		}
	}

	if (accnt){
               	free(accnt);
	}
	fclose(fp);
	fclose(fpOut);

	return 0;
}
