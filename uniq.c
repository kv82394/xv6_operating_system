#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h" // Include the fcntl.h header for O_RDONLY

#define MAX_LINE_LENGTH 512

// Function to compare two strings
// int strcmp(const char *s1, const char *s2) {
//     while (*s1 && (*s1 == *s2)) {
//         s1++;
//         s2++;
//     }
//     return *(unsigned char *)s1 - *(unsigned char *)s2;
// }

// Function to remove duplicate lines from a text
int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = *s1;
        char c2 = *s2;

        // Convert characters to lowercase and compare
        if ('A' <= c1 && c1 <= 'Z') {
            c1 += 'a' - 'A';
        }
        if ('A' <= c2 && c2 <= 'Z') {
            c2 += 'a' - 'A';
        }

        if (c1 != c2) {
            return 1;
        }

        s1++;
        s2++;
    }
    return (*s1 || *s2);
}

void printUniqueLinesCaseInsensitive(const char *input) {
    if (input == 0 || *input == '\0') {
        printf(1,"Invalid input\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char prev_line[MAX_LINE_LENGTH] = "";
    int line_len;

    while (*input != '\0') {
        line_len = 0;

        // Read a line
        while (*input != '\n' && *input != '\0' && line_len < MAX_LINE_LENGTH - 1) {
            line[line_len++] = *input++;
        }
        line[line_len] = '\0';

        // Check for duplicate (case-insensitive comparison)
        if (strcasecmp(line, prev_line) != 0) {
            printf(1,"%s\n", line);
            strcpy(prev_line, line);
        }

        // Move to the next line
        if (*input == '\n') {
            input++;
        }
    }

    // Handle the last line if it doesn't end with '\n'
    if (line_len > 0 && strcasecmp(line, prev_line) != 0) {
        printf(1,"%s\n", line);
    }
}
void printrepeatedLines(const char *input) {
    if (input == 0 || *input == '\0') {
        printf(1, "Invalid input\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char prev_line[MAX_LINE_LENGTH] = "";
    int line_len;

    while (*input != '\0') {
        line_len = 0;

        // Read a line
        while (*input != '\n' && *input != '\0' && line_len < MAX_LINE_LENGTH - 1) {
            line[line_len++] = *input++;
        }
        line[line_len] = '\0';

        // Check for duplicate
        if (strcmp(line, prev_line) == 0) {
            printf(1, "%s\n", line);
        }

        // Move to the next line
        if (*input == '\n') {
            input++;
        }

        // Store the current line as the previous line
        strcpy(prev_line, line);
    }
}


void coutDuplicate(const char *input) {
    
    if (input == 0 || *input == '\0') {
        printf(1, "Invalid input\n");
        return;
    }
    int count = 1;
    char line[MAX_LINE_LENGTH];
    char prev_line[MAX_LINE_LENGTH] = "";
    int line_len;
   // int flag = 2;
    while (*input != '\0') {
        line_len = 0;
        // Read a line
        
        while (*input != '\n' && *input != '\0' && line_len < MAX_LINE_LENGTH - 1) {
            line[line_len++] = *input++;
        }
        line[line_len] = '\0'; 
        // Check for duplicate
        if (strcmp(line, prev_line) != 0) {
            printf(1,"%d ",count);
            printf(1, "%s\n", line); 
            strcpy(prev_line, line);
            count++;
        }
       //flag = 1;
        // Move to the next line
        if (*input == '\n') {
            input++;
        }
    }

    //Handle the last line if it doesn't end with '\n'
    if (line_len > 0 && strcmp(line, prev_line) != 0) {
        printf(1, "%s\n", line);
    }
}
void removeDuplicateLinesAndPrint(const char *input) {
    
    if (input == 0 || *input == '\0') {
        printf(1, "Invalid input\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char prev_line[MAX_LINE_LENGTH] = "";
    int line_len;
   // int flag = 2;
    while (*input != '\0') {
        line_len = 0;
        // Read a line
        
        while (*input != '\n' && *input != '\0' && line_len < MAX_LINE_LENGTH - 1) {
            line[line_len++] = *input++;
        }
        line[line_len] = '\0'; 
        // Check for duplicate
        if (strcmp(line, prev_line) != 0) {
            printf(1, "%s\n", line); 
            strcpy(prev_line, line);
        }
       //flag = 1;
        // Move to the next line
        if (*input == '\n') {
            input++;
        }
    }

    //Handle the last line if it doesn't end with '\n'
    if (line_len > 0 && strcmp(line, prev_line) != 0) {
        printf(1, "%s\n", line);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(1, "Usage: uniq OS611 input_file \n uniq -c input_file \n uniq -i input_file \n uniq -d input_file \n");
        exit();
    }
    char *input_file;
    int flag = 1 ;
    if (argc == 3){input_file = argv[2];flag =1;}
    if (argv[1][0]=='-' && argv[1][1]=='c')flag= 2;
    if (argv[1][0]=='-' && argv[1][1]=='i')flag= 3;
    if (argv[1][0]=='-' && argv[1][1]=='d')flag= 4;

    

    int fd = open(input_file,O_RDONLY);

    if (fd < 0) {
        printf(1, "Error opening the input file\n");
        exit();
    }

    //char prev_line[512] = "";
    char curr_line[512];
    printf(1, "Uniq command is getting executed in user mode.\n");
    while (1) {
        int n = read(fd, curr_line, sizeof(curr_line));
        if (n <= 0) break;

        curr_line[n] = '\0';
        if (flag == 1)removeDuplicateLinesAndPrint(curr_line);
        if (flag ==2)coutDuplicate(curr_line);
        if (flag ==3)printUniqueLinesCaseInsensitive(curr_line);
        if (flag ==4)printrepeatedLines(curr_line);

    }

    close(fd);

   
    //printf(1, "return val of system call is %d\n", uniq());
    exit();
}
