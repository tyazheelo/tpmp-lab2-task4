#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/io.h"

int read_companies_from_file(const char *filename, Company companies[], int max_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s для чтения\n", filename);
        return -1;
    }
    
    int count = 0;
    char buffer[1024];
    
    // Пропускаем заголовок
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf("Файл пуст\n");
        fclose(file);
        return 0;
    }
    
    // Чтение данных: 10 строковых полей и 3 числовых
    while (count < max_count && 
           fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",
                  companies[count].name,
                  companies[count].website,
                  companies[count].address.index,
                  companies[count].address.country,
                  companies[count].address.region,
                  companies[count].address.district,
                  companies[count].address.city,
                  companies[count].address.street,
                  companies[count].address.house,
                  companies[count].address.apartment,
                  &companies[count].years_on_market,
                  &companies[count].employees_count,
                  &companies[count].europe_branches) == 13) {
        count++;
    }
    
    fclose(file);
    printf("Загружено %d компаний из файла %s\n", count, filename);
    return count;
}

void print_company(const Company *company) {
    printf("Название: %s\n", company->name);
    printf("Сайт: %s\n", company->website);
    printf("Адрес: %s, %s, %s, %s, %s, %s, %s, %s\n",
           company->address.index,
           company->address.country,
           company->address.region,
           company->address.district,
           company->address.city,
           company->address.street,
           company->address.house,
           company->address.apartment);
    printf("На рынке: %d лет\n", company->years_on_market);
    printf("Сотрудников: %d\n", company->employees_count);
    printf("Филиалов в Европе: %d\n", company->europe_branches);
    printf("------------------------\n");
}

void print_companies(const Company companies[], int count) {
    printf("\n=== СПИСОК ВСЕХ КОМПАНИЙ ===\n");
    printf("Всего компаний: %d\n\n", count);
    for (int i = 0; i < count; i++) {
        print_company(&companies[i]);
    }
}

void print_company_to_file(FILE *file, const Company *company) {
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d\n",
            company->name,
            company->website,
            company->address.index,
            company->address.country,
            company->address.region,
            company->address.district,
            company->address.city,
            company->address.street,
            company->address.house,
            company->address.apartment,
            company->years_on_market,
            company->employees_count,
            company->europe_branches);
}

int write_companies_to_file(const char *filename, const Company companies[], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        return -1;
    }
    
    // Записываем заголовок
    if (fprintf(file, "Название,Сайт,Индекс,Страна,Область,Район,Город,Улица,Дом,Квартира,Лет на рынке,Сотрудников,Филиалов в Европе\n") < 0) {
        printf("Ошибка записи заголовка\n");
        fclose(file);
        return -1;
    }
    
    for (int i = 0; i < count; i++) {
        if (fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d\n",
                companies[i].name,
                companies[i].website,
                companies[i].address.index,
                companies[i].address.country,
                companies[i].address.region,
                companies[i].address.district,
                companies[i].address.city,
                companies[i].address.street,
                companies[i].address.house,
                companies[i].address.apartment,
                companies[i].years_on_market,
                companies[i].employees_count,
                companies[i].europe_branches) < 0) {
            printf("Ошибка записи компании %s\n", companies[i].name);
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    printf("Сохранено %d компаний в файл %s\n", count, filename);
    return count;
}