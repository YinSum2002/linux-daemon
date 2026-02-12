#ifndef CPUSTATS_H
#define CPUSTATS_H
#include "parser.h"

unsigned long long total_time(struct CPUStatus* s);

unsigned long long idle_time(struct CPUStatus* s);

double compute_usage(struct CPUStatus* prev, struct CPUStatus* curr);

#endif