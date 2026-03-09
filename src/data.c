#include <stdio.h>
#include <string.h>
#include "../include/data.h"

/* Функции для работы с данными компаний */
void init_company(Company *company) {
    strcpy(company->name, "");
    strcpy(company->website, "");
    strcpy(company->address.index, "");
    strcpy(company->address.country, "");
    strcpy(company->address.region, "");
    strcpy(company->address.district, "");
    strcpy(company->address.city, "");
    strcpy(company->address.street, "");
    strcpy(company->address.house, "");
    strcpy(company->address.apartment, "");
    company->years_on_market = 0;
    company->employees_count = 0;
    company->europe_branches = 0;
}
