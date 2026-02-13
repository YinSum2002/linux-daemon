#ifndef CPUSTATS_H
#define CPUSTATS_H
#include "parser.h"

struct CPUUsage {
    double total;
    double user;
    double nice;
    double system;
    double idle;
    double iowait;
    double irq;
    double softirq;
    double steal;
    double guest;
    double guest_nice;
};

unsigned long long total_time(struct CPUStatus* s);

unsigned long long idle_time(struct CPUStatus* s);

void print_metric(const char *label, double value_fraction);

void print_data(struct CPUUsage* u);

double compute_percent(unsigned long long curr, unsigned long long total);

int compute_usage(struct CPUStatus* prev, struct CPUStatus* curr, struct CPUUsage* out);

#endif