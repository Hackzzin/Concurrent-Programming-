#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 1000 //max value a vector element can assume
#define MIN -1000 //min value a vector element can assume

float *genRandVec(int n){
    int i;

    // allocate memory for the vector
    float *vec = (float *) malloc(sizeof(float) * n);
    if (vec == NULL){
        printf("ERROR: couldn't \n");
        return NULL;
    }
    
    // generate the random numbers
    for (i = 0; i < n; i++){
        vec[i] = rand() % (MAX - MIN + 1) + MIN;
    }
    
    return vec;
}

float dotProd(float *vec1, float *vec2, int n){
    int i;
    float prod = 0.0;

    // calculate the dot product
    for (i = 0; i < n; i++){
        prod += vec1[i] * vec2[i];
    }
    
    return prod;
}

int main(int argc, char **argv){
    /* 
       argv[0] = name of the program
       argv[1] = size of the vectors to be generated
       argv[2] = name of the file to be generated, must include the ".bin" extension
    */

    int i, size;
    float *vec1, *vec2;
    double result;
    char *name;
    srand(time(NULL));
    FILE *fp;

    // check the number of arguments
    if (argc < 3){
        printf("ERROR: type: %s <size of the vector> <name of the file>\n", argv[0]);
        return 0;
    }

    // get the size of the vector
    size = atoi(argv[1]);
    if (size <= 0){
        printf("ERROR: size of the vector must be greater than 0\n");
        return 0;
    }

    // get the name of the file
    name = argv[2];
    if (name == NULL){
        printf("ERROR: name of the file must be different from NULL\n");
        return 1;
    }

    // generate the vectors
    vec1 = genRandVec(size);
    vec2 = genRandVec(size);
    if (vec1 == NULL || vec2 == NULL){
        printf("ERROR: couldn't generate the vectors\n");
        return 2;
    }
    
    // print the vectors
    for (i = 0; i < size; i++){
        printf("%f ", vec1[i]);
    }
    printf("\n");   

    for (i = 0; i < size; i++){
        printf("%f ", vec2[i]);
    }

    result = (double) dotProd(vec1, vec2, size);
    printf("\nDot product of the vectors: %f\n", result);
    
    // open the file
    fp = fopen(name, "wb");
    if (fp == NULL){
        printf("ERROR: couldn't open the file\n");
        return 4;
    }

    // write the size of the vector in the file
    fwrite(&size, sizeof(int), 1, fp);
    // write the vectors in the file
    fwrite(vec1, sizeof(float), size, fp);
    fwrite(vec2, sizeof(float), size, fp);
    // write the dot product in the file
    fwrite(&result, sizeof(double), 1, fp);

    fclose(fp);
    free(vec1);
    free(vec2);
    return 0;
}