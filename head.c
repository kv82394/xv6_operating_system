#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h" // Include the fcntl.h header for O_RDONLY

int main(int argc, char *argv[]) {
    int lines = 14; // Default number of lines to print

    if (argc > 1 && argv[1][0] == '-') {
        // If the first argument starts with '-', it specifies the number of lines
        lines = atoi(argv[2]); // Extract the number of lines from the argument
        argc--;
        argc--;
        argv++;
        argv++;

    }

    printf(1, "Head command is getting executed in user mode.\n");
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);

        if (fd < 0) {
            printf(1, "head: cannot open '%s'\n", argv[i]);
            continue;
        }
        printf(1,"Reading text from file : %s\n",argv[i]);
        char buffer[512];
        int bytesRead = 0;
        int lineCount = 0;

        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0 && lineCount < lines) {
            for (int j = 0; j < bytesRead && lineCount < lines; j++) {
                printf(1, "%c", buffer[j]);
                if (buffer[j] == '\n') {
                    lineCount++;
                }
            }
        }
        close(fd);
    }

    exit();
}
