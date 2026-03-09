#ifndef PROCESSING_H
#define PROCESSING_H

#include "data.h"

int filter_companies_by_employees(const Company source[], int 
source_count, 
                                  Company dest[], int min_employees);
void print_filtered_companies(const Company companies[], int count);

#endif
