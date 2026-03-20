#ifndef LOGGING_H
#define LOGGING_H

typedef enum {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

int logger_init(const char *filename);
void log_cpu_stats(struct CPUUsage usage);
void logger_log(log_level_t level, const char *fmt);
void logger_close(void);

#endif