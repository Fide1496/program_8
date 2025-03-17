#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();  // Fork a child process
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        execl("./myRand", "myRand", NULL);  // Execute myRand
        perror("execl failed");  // If execl fails
        exit(1);
    }

    // Parent process waits for child to complete
    wait(&status);
    
    if (WIFEXITED(status)) {
        int X = WEXITSTATUS(status);  // Get exit status (random number X)

        // Create file name
        char filename[20];
        snprintf(filename, sizeof(filename), "data%d.dat", X);

        // Open file for reading
        FILE *file = fopen(filename, "r");
        if (!file) {
            perror("Failed to open file");
            exit(1);
        }

        // Read and process 60 numbers
        int num, sum = 0, count = 0;
        while (fscanf(file, "%d", &num) == 1) {
            printf("%d ", num);
            sum += num;
            count++;
        }
        fclose(file);

        if (count == 60) {
            printf("\nAverage: %.2f\n", (float)sum / count);
        } else {
            printf("\nError: Expected 60 values, but read %d\n", count);
        }

        // Delete the file
        if (unlink(filename) != 0) {
            perror("Failed to delete file");
        }
    } else {
        printf("Child process did not terminate normally.\n");
    }

    return 0;
}
