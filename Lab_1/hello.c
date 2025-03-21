//Name: Matheus Silva Hack
//Teacher: Silvana Rossetto

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hello_thread(void* arg){
    long int id = (long  int) arg;
    printf("Hello World - Thread %ld\n", id);
}

int main (int argc, char** argv){

    // declare the variable
    int nthreads;  
    pthread_t *tid;

    // receive the arguments
    if (argc < 2){
        printf("\ninput ERROR: type: %s <number of threads>\n", argv[0]);
        return 1;
    }

    // initialize the variables
    nthreads = atoi(argv[1]);
    tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL){
        printf("Memory allocation ERROR");
        return 2;
    }

    // create the threads
    for(int i = 0; i < nthreads; i++){
        pthread_create (&tid[i], NULL, hello_thread, (void *)i);
    }


    // wait for the threads to end
    for (long int i=0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
    }

    // end the program
    return 0;
}