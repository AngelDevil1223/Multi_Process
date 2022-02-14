#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

volatile int running_threads = 0;
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

// this makes function calling and passing data to threads very easier
struct FileInfo{
    char filename[100];
    double sum;
    int numbers;
};

// function declrations
void* calc_average(void *arg);


int main(int argc, char **argv) 
{
    pthread_t thread_id[argc - 1];
    double sum = 0;
    int total_nums = 0;
    struct FileInfo results[argc - 1];
    for(int i = 0 ; i < argc - 1; ++i){
        strcpy(results[i].filename , argv[i + 1]);
        results[i].sum = 0;
        results[i].numbers = 0;
        // increasing the counter for new thread
        pthread_mutex_lock(&running_mutex);
        running_threads++;
        pthread_mutex_unlock(&running_mutex);
        // creating new thread
        pthread_create(&thread_id[i], NULL, calc_average, (void *) &results[i]);
    }
    while(running_threads > 0){
        // waiting for all the thread to get completed
        sleep(1);
    }
    for(int i = 0 ; i < argc - 1 ; ++i){
        sum += results[i].sum;
        total_nums += results[i].numbers;
        printf("%s SUM=%lf NUM=%d AVG=%lf\n", 
                results[i].filename, results[i].sum, 
                results[i].numbers , results[i].sum / results[i].numbers);
    }
    printf("AVERAGE=%lf\n", sum / total_nums);
    return 0;
}


// @param arg is the pointer to the FileInfo datatype 
// that is later used to pass the data back to the main thread
void* calc_average(void *arg){
    struct FileInfo *fileinfo = (struct FileInfo * )arg;
    FILE *f;
    f = fopen(fileinfo->filename, "r");
    double num;
    // reading one number at a time
    while(fscanf(f, "%lf ", &num) != EOF){
        fileinfo->numbers += 1;
        fileinfo->sum += num;
    }
    // reseting the running_threads counter as the thread is exiting
    pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
    return NULL;
}

