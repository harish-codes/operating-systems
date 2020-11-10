#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

int sum = 0;

void *thread_sums_to_z(void *num){
	int *add_Num = (int*)num;//CAST

	sum += *add_Num; //Add number to sum to create new current sum;
}


int main(){
	int x = 10, y = 20, z = 0;;
	pid_t pid_1;

	pthread_t thread_1, thread_2;

	int fd[2],readZ;
        if (pipe(fd) < 0){      //Create pipe and check if error
                perror("Pipe Error.\n");
                exit(0);
        }

	pid_1 = fork();

	if (pid_1 > 0){//PARENT
		wait(NULL);//WAIT for CHILD to complete

		read(fd[0],&readZ,sizeof(readZ));//READ from pipe
		printf("Value of z(process): %d\n",readZ);

		pthread_create(&thread_1, NULL, thread_sums_to_z, &x);//Create thread, pass int x to start routine
		pthread_create(&thread_2, NULL, thread_sums_to_z, &y);//Create thread, pass int y to start routine

		pthread_join(thread_1, NULL);//Wait until thread_1 finishes
		pthread_join(thread_2, NULL);//Wait until thread_2 finishes

		z = sum; //Make z equal to sum from thread start routine function
		printf("Value of z(thread): %d\n",z);

	}

	else if (pid_1 == 0){//CHILD
		z = x + y;
		write(fd[1],&z, sizeof(z));//WRITE to pipe
	}

	return 0;
}
