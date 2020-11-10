/*
Harish Nagallapati,250922183
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>


int main (){
	pid_t pid_1, pid_2, pid_3, parent_pid;

	pid_1 = fork();	//Create first child process.

	//Parent process will run this code
	if (pid_1 > 0){               //If child_1 creation was successfull..
                parent_pid  = getpid();
                printf("Parent PID# %d created Child_1 PID# %d.\n",parent_pid,pid_1);

		//Wait until child_1 terminates
                printf("Parent PID# %d is waiting for Child_1 PID# %d to complete before creating Child_2.\n",parent_pid,pid_1);
	        wait(NULL);

		printf("Child_1 PID# %d has now completed.\n",pid_1);

		pid_3 = fork();       //Create Child_2 process.
                if (pid_3 > 0){ //If Child_2 creation successful
                        printf("Parent PID# %d created Child_2 PID# %d\n",parent_pid,pid_3);

                }

		//Child_2 will run this code
	        else if(pid_3 == 0){
			int status;
			pid_3 = getpid();
                	printf("Child_2 PID# %d is calling an external program external_program.out and leaving child_2.\n",pid_3);
			status = execl("external_program.out",NULL);
			if (status < 0){
        			perror("exec");
        			printf("main: errno is %d\n",errno);
      			}
        	}
        }

	//Child_1 will run this code
	else if (pid_1 == 0){
		pid_1 = getpid();
		pid_2 = fork();	//Create Child_1.1

		if (pid_2 > 0){
			printf("Child_1 PID# %d created Child_1.1 PID# %d.\n",pid_1,pid_2);
		}
        }
	return 0;
}
