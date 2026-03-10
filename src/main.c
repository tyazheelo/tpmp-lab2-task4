#include <stdio.h>
#include <stdlib.h>
#include "../include/io.h"
#include "../include/processing.h"

#define INPUT_FILE "data/input.txt"
#define OUTPUT_FILE "data/output.txt"

int main() {
    printf("=== Программа обработки данных о международных компаниях ===\n\n");
    
    Company all_companies[MAX_COMPANIES];
    Company filtered_companies[MAX_COMPANIES];
    
    // Чтение данных из файла
    int count = read_companies_from_file(INPUT_FILE, all_companies, MAX_COMPANIES);
    if (count <= 0) {
        printf("Не удалось загрузить данные. Проверьте наличие файла %s\n", INPUT_FILE);
        return 1;
    }
    
    // Просмотр всех компаний
    print_companies(all_companies, count);
    
    // Фильтрация компаний с количеством сотрудников > 10000
    int filtered_count = filter_companies_by_employees(all_companies, count, 
                                                       filtered_companies, 10000);
    
    // Вывод отфильтрованных компаний
    print_filtered_companies(filtered_companies, filtered_count);
    
    // Сохранение результатов в новый файл
    if (filtered_count > 0) {
        write_companies_to_file(OUTPUT_FILE, filtered_companies, filtered_count);
        printf("\nРезультаты сохранены в файл %s\n", OUTPUT_FILE);
    } else {
        printf("\nНет компаний для сохранения\n");
    }
    
    return 0;
}