#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "sampler_thread.h"
#include "consumer_thread.h"
#include "shared.h"

int main() {
  // Initialize your mail box
  struct SharedCPUData mailBox;
  // Thread ID for sampler and consumer
  pthread_t sampler_tid;
  pthread_t consumer_tid;
  // Initialize your mutex
  pthread_mutex_init(&mailBox.lock, NULL);

  // create the sampler and consumer threads(last argument is the argument for the function sampler_thread. For now it's NULL, later it will be changed to &mailBox)
  pthread_create(&sampler_tid, NULL, sampler_thread, &mailBox);
  pthread_create(&consumer_tid, NULL, consumer_thread, &mailBox);

  // Join the thread
  pthread_join(sampler_tid, NULL);
  pthread_join(consumer_tid, NULL);

  // destroy the mutex
  pthread_mutex_destroy(&mailBox.lock);

  return 0;
}
