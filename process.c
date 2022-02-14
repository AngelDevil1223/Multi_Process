#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


// function declrations
void calc_average(char *filename, int *fd);



// we are creating pid_t cpid[] array to handle multiple processes and to save their ID
// we are using fd[][2] array to store pipe handlers.
// they are sent to calc_average where they are written to the pipe handlers

int main(int argc, char **argv){
    int fd[argc - 1][2];
    double sum = 0;
    int num = 0;
    pid_t cpid[argc - 1];
    for(int i = 0; i < argc - 1; ++i){
        if(pipe(fd[i]) == -1){
            fprintf(stderr, "fork Failed");
            return 1;
        }
        cpid[i] = fork();
        if(cpid[i] < 0){
            fprintf(stderr, "fork Failed cannot create new process");
            return 1;
        }
        else if (cpid[i] == 0){
            // we are in child process
            close(fd[i][0]);
            calc_average(argv[i + 1], fd[i]);
            // killing the child process here
            exit(0);
        }
        else{
            // we are in parent process
            close(fd[i][1]);
        }
    }
    for(int i = 0; i < argc - 1; ++i){
        double result_sum;
        int result_num;
        char result_string[100];
        read(fd[i][0], result_string, sizeof(result_string));
        sscanf(result_string, "%lf %d", &result_sum, &result_num);
        sum += result_sum;
        num += result_num;
        printf("%s SUM=%lf NUMS=%d AVG=%lf\n", argv[i + 1], result_sum, result_num, result_sum / result_num);
    }
    // here we are waiting for all the processes to finish
    wait(0);
    double average = sum / num;
    printf("AVERAGE=%lf\n", average);
    return 0;
}


// @param char *filename is the filename that the function will calculate 
//             average of.
// @patam int *fd is the pipe handler using which we will communicate with the 
//             parent thread
void calc_average(char *filename, int *fd){
    FILE *f;
    f = fopen(filename, "r");
    double num, sum = 0;
    int total_nums = 0;
    // reading one number at a time
    while(fscanf(f, "%lf ", &num) != EOF){
        total_nums++;
        sum += num;
    }
    char result_string[100];
    sprintf(result_string, "%lf %d", sum, total_nums);
    // sending result back to the parent thread
    write(fd[1], result_string, strlen(result_string) + 1);
}
