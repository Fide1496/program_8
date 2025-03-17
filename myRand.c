#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    srand(time(NULL));  // Seed random number generator
    int X = rand() % 256;  // Generate a random number between 0 and 255

    // Create file name
    char filename[20];
    snprintf(filename, sizeof(filename), "data%d.dat", X);

    // Open file for writing
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Write 60 random numbers between 0 and 100
    for (int i = 0; i < 60; i++) {
        fprintf(file, "%d\n", rand() % 101);
    }
    
    fclose(file);
    return X;  // Exit with status X
}
