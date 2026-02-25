#ifndef SHARED_H
#define SHARED_H
#include "cpu_stats.h"
#include <pthread.h>

struct SharedCPUData {
  struct CPUUsage latest;
  int has_data;
  pthread_mutex_t lock;
};

#endif