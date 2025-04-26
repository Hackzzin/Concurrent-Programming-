#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix {
    int rows;
    int cols;
    float *data;
    long long int size;
} Matrix;

int main (int argc, char*argv[]) {
    Matrix matrix; // Struct to hold matrix data
    FILE *file; // File pointer for output file
    size_t ret; // Return value for file operations

    // Check for correct number of arguments
    if(argc < 4) {
        fprintf(stderr, "Usage: %s <rows> <cols> <output_file>\n", argv[0]);
        return 1;
    }

    /*
        argv[1] = number of rows
        argv[2] = number of columns
        argv[3] = output file name, must include the .bin extension
    */

    // Parse command line arguments
    matrix.rows = atoi(argv[1]); 
    matrix.cols = atoi(argv[2]);
    matrix.size = matrix.rows * matrix.cols;

    // Allocate memory for the matrix data
    matrix.data = (float*) malloc(sizeof(float) * matrix.size);
    if(!matrix.data) {
        fprintf(stderr, "Memory allocation error\n");
        return 2;
    }

    // Fill the matrix with random float values
    srand(time(NULL));
    for(long long int i=0; i<matrix.size; i++) {
        *(matrix.data+i) = (rand() % 1000) * 0.3;
    }

   //imprimir na saida padrao a matriz gerada
   for(int i=0; i<matrix.rows; i++) {
      for(int j=0; j<matrix.cols; j++)
        fprintf(stdout, "%.6f ", matrix.data[i*matrix.cols+j]);
      fprintf(stdout, "\n");
   }

   // Open the output file for binary writing
   file = fopen(argv[3], "wb");
   if(!file) {
       fprintf(stderr, "File open error\n");
       free(matrix.data); // Free allocated memory before exiting
       return 3;
   }

   // Write the number of rows and columns to the file
   ret = fwrite(&matrix.rows, sizeof(int), 1, file);
   ret = fwrite(&matrix.cols, sizeof(int), 1, file);

   // Write the matrix data to the file
   ret = fwrite(matrix.data, sizeof(float), matrix.size, file);

   // Close the file and free allocated memory
   fclose(file);
   free(matrix.data);

   return 0;
}