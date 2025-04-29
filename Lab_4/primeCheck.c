#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

pthread_mutex_t mutex; 
long long int nElements;
long long int iter = 1; 
int count; 

typedef struct {
    int id;
    int nthreads;
} t_Args;

int is_prime(long long int n) {
    int i;

    if (n <= 1) return 0; // 0 and 1 are not prime numbers
    if (n == 2) return 1; // 2 is a prime number
    if (n % 2 == 0) return 0; // even numbers greater than 2 are not prime

    for (i = 3; i < sqrt(n) + 1; i += 2) {
        if (n % i == 0) return 0; // n is divisible by i, so it's not prime
    }
    return 1; // n is prime
}

void* chore(void* args){
    t_Args *arg = (t_Args *) args;

    for (int i = arg->id; i <= nElements; i += arg->nthreads){
        if (is_prime(i)){
            pthread_mutex_lock(&mutex); 
            count++; 
            pthread_mutex_unlock(&mutex); 
        }
    }

    pthread_exit(NULL); // exit the thread
}

int main(int argc, char **argv){
    int nThreads;
    t_Args *args;
    pthread_t *threads;
    pthread_t *tid;
    struct timespec start, end;
    double elapsed_time;
    FILE *fp;

    if (argc < 3){
        printf("ERROR: type: %s <number of elements> <number of threads>\n", argv[0]);
        return 0;
    }

    nElements = atoll(argv[1]);
    nThreads = atoi(argv[2]);

    if (nThreads <= 0 || nElements <= 0){
        printf("ERROR: number of threads/elements must be greater than 0\n");
        return 1;
    }

    // Check if the number of threads is greater than the number of elements
    if (nElements < nThreads){
        nThreads = nElements;
    }

    // Allocate memory for the threads
    tid = (pthread_t*) malloc(sizeof(pthread_t)*(nThreads+1));
    if(tid==NULL) {puts("ERRO--malloc"); return 2;}
    args = (t_Args *) malloc(sizeof(t_Args) * nThreads);

    if (args == NULL) {
        printf("ERROR: couldn't allocate memory for the thread identifiers\n");
        free(tid);
        return 3;
    }

    // Inicialize mutex
    pthread_mutex_init(&mutex, NULL);

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create the threads
    for (long int t = 0; t < nThreads; t++){
        args[t].id = t;
        args[t].nthreads = nThreads;
        if(pthread_create(&tid[t], NULL, chore, (void *)&args[t])) {
            printf("--ERROR: pthread_create()\n"); 
            exit(-1);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < nThreads; i++){
        if (pthread_join(tid[i], NULL)) {
            printf("--ERROR: pthread_join() \n"); 
            exit(-1); 
        } 
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Destroy mutex
    pthread_mutex_destroy(&mutex); 

    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Total prime numbers: %d\n", count);
    printf("Execution time: %.6f miliseconds\n", 1000 * elapsed_time);

    fp = fopen("results.txt", "a");
    if (fp == NULL) {
        printf("ERROR: cannot open file 'results.txt'\n");
        exit(4);
    }

    fprintf(fp, "Total prime numbers: %d, %d threads\n", count, nThreads);
    fprintf(fp, "Execution time: %.6f miliseconds\n", 1000 * elapsed_time);

    fclose(fp);

    free(args);
    free(tid);
    return 0;
}