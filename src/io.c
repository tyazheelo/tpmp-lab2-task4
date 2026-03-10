#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/io.h"

int read_companies_from_file(const char *filename, Company companies[], int max_count) {
    printf("Открытие файла: %s\n", filename);
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("ОШИБКА: Не удалось открыть файл %s\n", filename);
        perror("Причина ошибки");
        return -1;
    }
    
    printf("Файл успешно открыт. Начинаем чтение...\n");
    
    int count = 0;
    char buffer[2048];
    
    // Пропускаем заголовок
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf("Файл пуст\n");
        fclose(file);
        return 0;
    }
    
    printf("Заголовок файла: %s", buffer);
    
    // Чтение данных построчно
    while (count < max_count && fgets(buffer, sizeof(buffer), file)) {
        // Удаляем символ новой строки и возврата каретки
        buffer[strcspn(buffer, "\r\n")] = 0;
        
        // Пропускаем пустые строки
        if (strlen(buffer) == 0) {
            continue;
        }
        
        printf("Чтение строки %d: %s\n", count + 1, buffer);
        
        Company *comp = &companies[count];
        
        // Очищаем поля компании
        memset(comp->name, 0, sizeof(comp->name));
        memset(comp->website, 0, sizeof(comp->website));
        memset(comp->address.index, 0, sizeof(comp->address.index));
        memset(comp->address.country, 0, sizeof(comp->address.country));
        memset(comp->address.region, 0, sizeof(comp->address.region));
        memset(comp->address.district, 0, sizeof(comp->address.district));
        memset(comp->address.city, 0, sizeof(comp->address.city));
        memset(comp->address.street, 0, sizeof(comp->address.street));
        memset(comp->address.house, 0, sizeof(comp->address.house));
        memset(comp->address.apartment, 0, sizeof(comp->address.apartment));
        comp->years_on_market = 0;
        comp->employees_count = 0;
        comp->europe_branches = 0;
        
        // Разбираем строку вручную, учитывая пустые поля
        char *ptr = buffer;
        int field = 0;
        char current_field[256];
        int char_index = 0;
        
        while (*ptr != '\0' && field < 13) {
            if (*ptr == ',') {
                // Завершаем текущее поле
                current_field[char_index] = '\0';
                
                // Сохраняем поле (даже если оно пустое)
                switch(field) {
                    case 0: strcpy(comp->name, current_field); break;
                    case 1: strcpy(comp->website, current_field); break;
                    case 2: strcpy(comp->address.index, current_field); break;
                    case 3: strcpy(comp->address.country, current_field); break;
                    case 4: strcpy(comp->address.region, current_field); break;
                    case 5: strcpy(comp->address.district, current_field); break;
                    case 6: strcpy(comp->address.city, current_field); break;
                    case 7: strcpy(comp->address.street, current_field); break;
                    case 8: strcpy(comp->address.house, current_field); break;
                    case 9: strcpy(comp->address.apartment, current_field); break;
                    case 10: comp->years_on_market = atoi(current_field); break;
                    case 11: comp->employees_count = atoi(current_field); break;
                    case 12: comp->europe_branches = atoi(current_field); break;
                }
                
                // Сбрасываем для следующего поля
                field++;
                char_index = 0;
                ptr++;
                continue;
            }
            
            // Добавляем символ в текущее поле
            if (char_index < 255) {
                current_field[char_index++] = *ptr;
            }
            ptr++;
        }
        
        // Обрабатываем последнее поле (после последней запятой)
        if (field < 13) {
            current_field[char_index] = '\0';
            switch(field) {
                case 0: strcpy(comp->name, current_field); break;
                case 1: strcpy(comp->website, current_field); break;
                case 2: strcpy(comp->address.index, current_field); break;
                case 3: strcpy(comp->address.country, current_field); break;
                case 4: strcpy(comp->address.region, current_field); break;
                case 5: strcpy(comp->address.district, current_field); break;
                case 6: strcpy(comp->address.city, current_field); break;
                case 7: strcpy(comp->address.street, current_field); break;
                case 8: strcpy(comp->address.house, current_field); break;
                case 9: strcpy(comp->address.apartment, current_field); break;
                case 10: comp->years_on_market = atoi(current_field); break;
                case 11: comp->employees_count = atoi(current_field); break;
                case 12: comp->europe_branches = atoi(current_field); break;
            }
            field++;
        }
        
        // Проверяем, что прочитали все поля
        if (field == 13) {
            printf("  УСПЕХ: Компания '%s' загружена\n", comp->name);
            count++;
        } else {
            printf("  ОШИБКА: Ожидалось 13 полей, найдено %d\n", field);
        }
    }
    
    fclose(file);
    printf("ИТОГ: Загружено %d компаний из файла %s\n", count, filename);
    return count;
}

void print_company(const Company *company) {
    printf("Название: %s\n", company->name);
    printf("Сайт: %s\n", company->website);
    printf("Индекс: %s\n", company->address.index);
    printf("Страна: %s\n", company->address.country);
    printf("Область: %s\n", company->address.region);
    printf("Район: %s\n", company->address.district);
    printf("Город: %s\n", company->address.city);
    printf("Улица: %s\n", company->address.street);
    printf("Дом: %s\n", company->address.house);
    printf("Квартира: %s\n", company->address.apartment);
    printf("На рынке: %d лет\n", company->years_on_market);
    printf("Сотрудников: %d\n", company->employees_count);
    printf("Филиалов в Европе: %d\n", company->europe_branches);
    printf("------------------------\n");
}

void print_companies(const Company companies[], int count) {
    printf("\n=== СПИСОК ВСЕХ КОМПАНИЙ ===\n");
    printf("Всего компаний: %d\n\n", count);
    for (int i = 0; i < count; i++) {
        printf("Компания #%d:\n", i + 1);
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
    printf("Сохранение в файл: %s\n", filename);
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        perror("Причина ошибки");
        return -1;
    }
    
    // Записываем заголовок
    fprintf(file, "Название,Сайт,Индекс,Страна,Область,Район,Город,Улица,Дом,Квартира,Лет на рынке,Сотрудников,Филиалов в Европе\n");
    
    int success_count = 0;
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
                companies[i].europe_branches) > 0) {
            success_count++;
        }
    }
    
    fclose(file);
    printf("Сохранено %d компаний в файл %s\n", success_count, filename);
    return success_count;
}