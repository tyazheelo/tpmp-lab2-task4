#include <stdio.h>
#include "../include/processing.h"
#include "../include/io.h"

int filter_companies_by_employees(const Company source[], int 
source_count, 
                                  Company dest[], int min_employees) {
    int dest_count = 0;
    
    for (int i = 0; i < source_count; i++) {
        if (source[i].employees_count > min_employees) {
            dest[dest_count] = source[i];
            dest_count++;
        }
    }
    
    return dest_count;
}

void print_filtered_companies(const Company companies[], int count) {
    printf("\n=== КОМПАНИИ С КОЛИЧЕСТВОМ СОТРУДНИКОВ БОЛЕЕ 10000 ===\n");
    if (count == 0) {
        printf("Компании, удовлетворяющие условию, не найдены\n");
    } else {
        for (int i = 0; i < count; i++) {
            print_company(&companies[i]);
        }
        printf("Всего найдено: %d компаний\n", count);
    }
}
