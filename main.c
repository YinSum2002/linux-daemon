#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "parser.h"
#include "cpu_stats.h"

#define BUFFER_SIZE 100

int main() {
  char buffer[BUFFER_SIZE];
  struct CPUStatus prev;
  int has_prev = 0;

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
        // call usage calculation
        if (has_prev != 0){
          double usage = compute_usage(&prev, &stats);
          printf("%f\n", usage);
        } else {
          has_prev++;
        }
        
        prev = stats;

        // print out data
        /*
        if (result == 0){
          printf("User: %llu\n", stats.user);
          printf("Nice: %llu\n", stats.nice);
          printf("System: %llu\n", stats.system);
          printf("Idle: %llu\n", stats.idle);
          printf("iowait: %llu\n", stats.iowait);
          printf("irq: %llu\n", stats.irq);
          printf("softirq: %llu\n", stats.softirq);
          printf("Steal: %llu\n", stats.steal);
          printf("Guest: %llu\n", stats.guest);
          printf("Guest Nice: %llu\n", stats.guest_nice);
        }
        */
        

      } else {
        printf("Count not read a line or file is empty.\n");
      }
      fclose(fp);
      sleep(1);
    }
    
  }

  return 0;
}
