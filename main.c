#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "parser.h"
#include "cpu_stats.h"

#define BUFFER_SIZE 100

struct SharedCPUData {
  struct CPUUsage latest;
  pthread_mutex_t lock;
};

int main() {
  char buffer[BUFFER_SIZE];
  struct CPUStatus prev;
  int has_prev = 0;

  struct SharedCPUData mailBox;

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
        struct CPUUsage CPU_usage;

        // call parser function
        (void) parse_cpu_line(buffer, &stats);
        // call usage calculation
        if (has_prev != 0){
          (void) compute_usage(&prev, &stats, &CPU_usage);
          print_data(&CPU_usage);
        } else {
          has_prev++;
        }
        
        prev = stats;
        
      } else {
        printf("Count not read a line or file is empty.\n");
      }
      fclose(fp);
      sleep(1);
    }
    
  }

  return 0;
}
