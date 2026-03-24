#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "cpu_stats.h"
#include "parser.h"
#include "sampler_thread.h"
#include "consumer_thread.h"
#include "shared.h"
#include "logging.h"

int main() {
  // Initialize your mail box
  struct SharedCPUData mailBox;
  // Thread ID for sampler and consumer
  pthread_t sampler_tid;
  pthread_t consumer_tid;
  // Initialize your mutex
  pthread_mutex_init(&mailBox.lock, NULL);

  // initialize logger
  logger_init("cpu_monitor.log");

  // create the sampler and consumer threads
  pthread_create(&sampler_tid, NULL, sampler_thread, &mailBox);
  pthread_create(&consumer_tid, NULL, consumer_thread, &mailBox);

  // Join the thread
  pthread_join(sampler_tid, NULL);
  pthread_join(consumer_tid, NULL);

  // shutdown logger
  logger_close();

  // destroy the mutex
  pthread_mutex_destroy(&mailBox.lock);

  return 0;
}
