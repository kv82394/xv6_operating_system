#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h" // Include the fcntl.h header for O_RDONLY

char buf[512];
#define MAX_LINE_LENGTH 512
void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
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

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit();
  }
  if(argv[2][0]=='-'){
    uniq();
    char *input_file = argv[1];
    int fd = open(input_file,O_RDONLY);
    char curr_line[512];
    int n = read(fd, curr_line, sizeof(curr_line));
    if (n <= 0){printf(1, "cat: cannot open %s\n", argv[1]);exit();}
    removeDuplicateLinesAndPrint(curr_line);
    exit();
  }
  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}
