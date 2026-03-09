#include "logging.h"

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "cpu_stats.h"

static FILE* log_file = NULL;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

int logger_init(const char* filename) {
  /* Prepare logging system once at program start */
  log_file = fopen(filename, "a");
  return log_file ? 0 : -1;
}

void log_cpu_stats(struct CPUUsage usage) {
  char buffer[256];
  snprintf(
      buffer, sizeof(buffer),
      "total=%.2f user=%.2f nice=%.2f system=%.2f idle=%.2f "
      "iowait=%.2f irq=%.2f softirq=%.2f steal=%.2f guest=%.2f guest_nice=%.2f",
      usage.total, usage.user, usage.nice, usage.system, usage.idle,
      usage.iowait, usage.irq, usage.softirq, usage.steal, usage.guest,
      usage.guest_nice);

  logger_log(LOG_INFO, buffer);
}

void logger_log(log_level_t level, const char* fmt) {
  /* Main public API used by the rest of the program */
  if (!log_file) {
    return;
  }

  pthread_mutex_lock(&log_mutex);

  //

  pthread_mutex_unlock(&log_mutex);
}

void logger_close(void) {
  /* Clean exit behavior */
  if (log_file) {
    fclose(log_file);
  }
}

// open log file

// thread-safe writes

// timestamps

// log levels