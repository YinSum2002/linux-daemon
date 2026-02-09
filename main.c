#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "parser.h"

#define BUFFER_SIZE 100

int main() {
  char buffer[BUFFER_SIZE];

  while (1) {
    // Open /proc/stat in read mode
    FILE* fp = fopen("/proc/stat", "r");
    if (fp == NULL){
      perror("fopen failed");
      sleep(1);
      continue;
    } else {
      // Read the first line using fgets()
      if (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        //printf("Data from /proc/stat: %s", buffer);

        // Struct to store CPU Data
        struct CPUStatus stats;

        // call parser function
        int result = parse_cpu_line(buffer, &stats);

        // print out data
        if (result == 0){
          printf("User: %llu\n", stats.user);
          printf("Nice: %llu\n", stats.nice);
          printf("System: %llu\n", stats.system);
          printf("Idle: %llu\n", stats.idle);
        }

      } else {
        printf("Count not read a line or file is empty.\n");
      }
      fclose(fp);
      sleep(1);
    }
    
  }

  return 0;
}
