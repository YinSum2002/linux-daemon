#include <unistd.h>
#include "consumer_thread.h"
#include "logging.h"
#include "shared.h"

void* consumer_thread(void* arg){
  // Cast input arg into mailBox
  struct SharedCPUData* mailBox = (struct SharedCPUData*) arg;
  
  // Create local CPUUsage Variable
  struct CPUUsage usage;

  // while loop for filling usage
  while (1){
    // check if has_data is true
    if (mailBox->has_data == 1){
      // Lock Mutex
      pthread_mutex_lock(&mailBox->lock);

      // Copy shared usage into local variable
      usage = mailBox->latest;
      mailBox->has_data = 0;
      // Unlock Mutex
      pthread_mutex_unlock(&mailBox->lock);

      // Print the local copy, presumably through calling print_data
      // print_data(&usage);
      // log
      log_cpu_stats(usage);
      sleep(1);
    }    
  }
  // Exit the thread
  pthread_exit(NULL);
}