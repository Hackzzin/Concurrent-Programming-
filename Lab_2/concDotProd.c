#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

long int T; // number of threads to be created
int n; // size of the vectors
float *vec1, *vec2; // vectors to be multiplied

double calcDotProduct(float *vec1, float *vec2, int start, int end){
    double result = 0.0;
    for (int i = start; i < end; i++){
        result += vec1[i] * vec2[i];
    }
    return result;
}

void *dotProduct(void *tid){
    long int id = (long int) tid; 
    int begin, end, chunk; 
    float *ret;
    double localResult = 0.0; // local result of the thread

    chunk = n/T; // get chunk size
    begin = id*chunk; // start of the chunk
    end = begin + chunk; // end of the chunk
    if (id==(T-1)) end = n; // last thread handles the remaining elements

    localResult = calcDotProduct(vec1, vec2, begin, end); 

    ret = (float *) malloc(sizeof(float)); // allocate memory for the return value
    if (ret != NULL) *ret = localResult; // store the result in the allocated memory
    else printf("ERROR: malloc() in thread\n");
    pthread_exit((void*) ret);
}

int main(int argc, char **argv){
    /*
       argv[0] = name of the program
       argv[1] = number of threads to be created
       argv[2] = name of the file to read from, must include the ".bin" extension
    */

    double inputResult, result = 0.0;
    char *fileName;
    float *dotReturnThreads; //auxiliar para retorno das threads
    FILE *fp;
    pthread_t *tidSistema; // thread identifiers

    // check the number of arguments
    if (argc < 3){
        printf("ERROR: type: %s <size of the vector> <name of the file>\n", argv[0]);
        return 0;
    }

    // get the number of threads to be created
    T = atoi(argv[1]);
    if (T <= 0){
        printf("ERROR: number of threads must be greater than 0\n");
        return 1;
    }

    // get the name of the file
    fileName = argv[2];
    if (fileName == NULL){
        printf("ERROR: name of the file must be different from NULL\n");
        return 2;
    }

    // open the file for reading
    fp = fopen(fileName, "rb");
    if (fp == NULL){
        printf("ERROR: couldn't open the file %s\n", fileName);
        return 3;
    }

    // read the size of the vectors from the file
    size_t ret = fread(&n, sizeof(int), 1, fp);
    if (ret != 1){
        printf("ERROR: couldn't read the size of the vectors from the file %s\n", fileName);
        fclose(fp);
        return 4;
    }

    if (n < T){
        T = n;
    }

    vec1 = (float *) malloc(sizeof(float) * n);
    vec2 = (float *) malloc(sizeof(float) * n);
    if (vec1 == NULL || vec2 == NULL){
        printf("ERROR: couldn't allocate memory for the vectors\n");
        fclose(fp);
        return 6;
    }

    // read the vectors from the file
    ret = fread(vec1, sizeof(float), n, fp);
    if (ret != n){
        printf("ERROR: couldn't read the first vector from the file %s\n", fileName);
        free(vec1);
        free(vec2);
        fclose(fp);
        return 7;
    }

    ret = fread(vec2, sizeof(float), n, fp);
    if (ret != n){
        printf("ERROR: couldn't read the second vector from the file %s\n", fileName);
        free(vec1);
        free(vec2);
        fclose(fp);
        return 8;
    }

    // read the dot product from the file
    ret = fread(&inputResult, sizeof(double), 1, fp);
    if (ret != 1){
        printf("ERROR: couldn't read the dot product from the file %s\n", fileName);
        free(vec1);
        free(vec2);
        fclose(fp);
        return 9;
    }

    tidSistema = (pthread_t *) malloc(sizeof(pthread_t) * T);
    if (tidSistema == NULL){
        printf("ERROR: couldn't allocate memory for the thread identifiers\n");
        free(vec1);
        free(vec2);
        fclose(fp);
        return 10;
    }

    // create the threads
    for(long int i = 0; i < T; i++){
        printf("Creating thread %ld\n", i);
        if (pthread_create(&tidSistema[i], NULL, dotProduct, (void *) i)){
            printf("ERROR: couldn't create thread %ld\n", i);
            free(vec1);
            free(vec2);
            free(tidSistema);
            fclose(fp);
            return 11;
        }
    }

    for(int i=0; i<T; i++) {
        if (pthread_join(tidSistema[i], (void *) &dotReturnThreads)) {
            printf("--ERRO: pthread_join()\n"); exit(-1);
        }
        result += *dotReturnThreads;
        free(dotReturnThreads);
     }

    printf("Size of the vectors: %d", n);
    printf("\nDot Product Read: %.10f\n", inputResult);
    printf("Dot Product Computed Concurrently: %.10f\n", result);
    
    double relative_error = fabs((inputResult - result) / inputResult);

    printf("Relative Error: %f\n", relative_error);

    // free resources
    free(vec1);
    free(vec2);
    free(tidSistema);
    fclose(fp);

    return 0;
}