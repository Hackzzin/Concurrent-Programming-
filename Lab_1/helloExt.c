//Name: Matheus Silva Hack
//Teacher: Silvana Rossetto

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    int nthreads;
} t_Args;

void *hello_thread(void* arg){
    t_Args *args = (t_Args *) arg;
    long int id = args->id;
    int nthreads = args->nthreads;
    printf("Hello World - Thread %ld\n nthread: %d\n", id, nthreads);
    pthread_exit(NULL); //funcao de termino da thread, para retorno de valores
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
        t_Args *args = (t_Args *) malloc(sizeof(t_Args));
        if (args == NULL){
            printf("Memory allocation ERROR");
            return 2;
        }

        args->id = i;
        args->nthreads = nthreads;
        int ret = pthread_create (&tid[i], NULL, hello_thread, (void *)args);

        if (ret){
            printf("Thread <%d> creation ERROR: %d\n", i, ret);
            return 3;
        }
    }


    // wait for the threads to end
    for (long int i=0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
    }

    // end the program
    return 0;
}