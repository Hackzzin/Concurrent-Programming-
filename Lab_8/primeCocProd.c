#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <time.h>

sem_t prod, cons;
pthread_mutex_t mutex; 
long long int nElements, nCons, M;
long long int *buffer; 
int in = 0, out = 0;

typedef struct {
    int id;
    int countLocal;
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

void* producer(void* arg) {
    for (long long int i = 0; i < nElements; i++) {
        sem_wait(&prod);
        pthread_mutex_lock(&mutex);
        buffer[in] = i;
        in = (in + 1) % M;
        pthread_mutex_unlock(&mutex);
        sem_post(&cons);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    t_Args* args = (t_Args*) arg;
    long long int item;

    while (1) {
        pthread_mutex_lock(&mutex);
        static long long int processed = 0;
        if (processed >= nElements) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        processed++;
        pthread_mutex_unlock(&mutex);

        sem_wait(&cons);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        out = (out + 1) % M;
        pthread_mutex_unlock(&mutex);
        sem_post(&prod);

        if (is_prime(item)) {
            args->countLocal++;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    pthread_t *tid;
    t_Args *args;
    long long int winnerIdx = 0, countGlobal = 0;
    FILE *file;
    clock_t start_time, end_time;
    double cpu_time_used;

    /*
        argv[1] = number of elements to check for primality
        argv[2] = number of consumers
        argv[3] = size of the buffer (M)
    */

    if (argc < 4){
        printf("ERROR: type: %s <number of elements> <number of consumers> <buffer size>\n", argv[0]);
        return 1;
    }

    nElements = atoll(argv[1]);
    nCons = atoll(argv[2]);
    M = atoll(argv[3]);

    if (nCons <= 0 || nElements <= 0 || M <= 0){
        printf("ERROR: number of consumers/elements/buffer size must be greater than 0\n");
        return 2;
    }

    // Allocate memory for the threads
    tid = (pthread_t*) malloc(sizeof(pthread_t)*(nCons+1));
    if(tid==NULL) {puts("ERRO--malloc"); return 2;}
    args = (t_Args *) malloc(sizeof(t_Args) * nCons);

    if (args == NULL) {
        printf("ERROR: couldn't allocate memory for the thread identifiers\n");
        return 3;
    }

    // Allocate memory for the buffer
    buffer = (long long int *) malloc(sizeof(long long int) * M);
    if (buffer == NULL) {
        printf("ERROR: couldn't allocate memory for the buffer\n");
        return 4;
    }

    // Initialize mutex and sems
    pthread_mutex_init(&mutex, NULL);
    sem_init(&prod, 0, M); // Buffer is initially empty
    sem_init(&cons, 0, 0); // No items to consume initially

    start_time = clock();

    // Create producer thread at index 0
    pthread_create(&tid[0], NULL, producer, NULL);

    // Create consumer threads at the remaining indices
    for (long int t = 0; t < nCons; t++){
        args[t].id = t;
        args[t].countLocal = 0;
        pthread_create(&tid[t + 1], NULL, consumer, (void*)&args[t]);
    }

    // Wait for all threads to finish
    for (int i = 0; i <= nCons; i++){
        pthread_join(tid[i], NULL);
    }

    // Calculate the total count of prime numbers
    for (int i = 0; i <= nCons; i++) {
        countGlobal += args[i].countLocal;
    }

    // Find the consumer with the maximum count of prime numbers
    for(long long int i = 0; i < nCons; i++) {
        if (args[i].countLocal > args[winnerIdx].countLocal) {
            winnerIdx = i;
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Total primes found: %lld\n", countGlobal);
    printf("Winner consumer thread: %lld (with %d primes found)\n", winnerIdx, args[winnerIdx].countLocal);

    file = fopen("results.txt", "a");
    if (file == NULL) {
        printf("ERROR: couldn't open results file.\n");
    } else {
        fprintf(file, "Threads: %lld | Primes: %lld | Time: %.4f s | Buffer: %lld | Winner: %lld\n",
                nCons, countGlobal, cpu_time_used, M, winnerIdx);
        fclose(file);
    }

    free(buffer);
    free(tid);
    free(args);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&prod);
    sem_destroy(&cons);
    return 0;
}