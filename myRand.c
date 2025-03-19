#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

int checkError(int val, const char *msg){
    if (val == -1)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return val;
}

int main() {
    srand(time(NULL)); 
    int X = rand() % 256;
    
    const char *output_file;
    // char filename[20];
    snprintf(output_file, sizeof(output_file), "data%d.dat", X);
    output_file = "data%d.dat";

    int output_fd = checkError(fopen(output_file, "w"), "Opening output file");

    for (int i = 0; i < 60; i++) {
        fprintf(output_fd, "%d\n", rand() % 101);
    }
    
    fclose(output_fd);
    return X;  
}
