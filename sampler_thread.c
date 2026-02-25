#include <stdio.h>
#include <unistd.h>
#include "sampler_thread.h"
#include "shared.h"

#define BUFFER_SIZE 100

/* Note: This should not stay void forever */
void* sampler_thread(void* arg){
  // void* arg must be kept as a pthread requirement
  char buffer[BUFFER_SIZE];
  struct CPUStatus prev;
  int has_prev = 0;

  // Cast input arg into mailBox
  struct SharedCPUData* mailBox = (struct SharedCPUData*) arg;
  
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

          // lock mutex
          pthread_mutex_lock(&mailBox->lock);

          // Copy CPU Usage into struct
          mailBox->latest = CPU_usage;

          // Mark data as ready
          mailBox->has_data = 1;

          // unlock mutex
          pthread_mutex_unlock(&mailBox->lock);
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
}