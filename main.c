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
  int has_data;
  pthread_mutex_t lock;
};

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

          // test if data is stored correctly
          print_data(&mailBox->latest);
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

int main() {
  // Initialize your mail box
  struct SharedCPUData mailBox;
  // Thread ID for sampler
  pthread_t sampler_tid;
  // Initialize your mutex
  pthread_mutex_init(&mailBox.lock, NULL);

  // create the sampler thread (last argument is the argument for the function sampler_thread. For now it's NULL, later it will be changed to &mailBox)
  pthread_create(&sampler_tid, NULL, sampler_thread, &mailBox);

  // Join the thread
  pthread_join(sampler_tid, NULL);

  // destroy the mutex
  pthread_mutex_destroy(&mailBox.lock);

  return 0;
}
