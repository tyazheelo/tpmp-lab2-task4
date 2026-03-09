#ifndef IO_H
#define IO_H

#include "data.h"

int read_companies_from_file(const char *filename, Company companies[], 
int max_count);
void print_company(const Company *company);
void print_companies(const Company companies[], int count);
int write_companies_to_file(const char *filename, const Company 
companies[], int count);
void print_company_to_file(FILE *file, const Company *company);

#endif
