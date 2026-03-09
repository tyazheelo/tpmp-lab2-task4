#ifndef DATA_H
#define DATA_H

#define MAX_NAME_LEN 100
#define MAX_URL_LEN 200

typedef struct {
    char index[20];
    char country[50];
    char region[50];
    char district[50];
    char city[50];
    char street[50];
    char house[20];
    char apartment[20];
} Address;

typedef struct {
    char name[MAX_NAME_LEN];
    char website[MAX_URL_LEN];
    Address address;
    int years_on_market;
    int employees_count;
    int europe_branches;
} Company;

#endif
