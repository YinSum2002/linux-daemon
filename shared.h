#ifndef SHARED_H
#define SHARED_H
#include "cpu_stats.h"
#include <pthread.h>

struct SharedCPUData {
  pthread_mutex_t lock;
  pthread_cond_t data_ready;
  int has_data;
  struct CPUUsage latest;
};

#endif