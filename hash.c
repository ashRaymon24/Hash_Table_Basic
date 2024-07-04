#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define TABLE_SIZE 31
void setup(void);
void addHash(void);
void printTable(void);
void subHash(void);
void searchHash(void);

string hash_table [TABLE_SIZE];
int prev_table [TABLE_SIZE];

int main (void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = "__";
    }
    for (int j = 0; j < TABLE_SIZE; j++)
    {
        prev_table[j] = 0;
    }
    printf("Welcome to my Hash WORLD!!\n");
    setup();
}

void setup(void)
{
    int choice;
    printf("Enter 1 to ADD a person, Enter 2 to REMOVE a person, Enter 3 to SEARCH a person, Enter 4 to EXIT: ");
    scanf("%i", &choice);
    switch (choice)
    {
        case 1:
            addHash();
            break;
        case 2:
            subHash();
        case 3:
            searchHash();
        case 4:
            return;
        default:
            setup();
            break;
    }
}

int hasher (string first, string last)
{
    int temp1 = first[0] - 64;
    int temp2 = last[0] - 64;
    int hashed = ((temp1 * 6) + (temp2 * 6)) % TABLE_SIZE;
    return hashed;
}

void printTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("%i, %s\n", i + 1, hash_table[i]);
    }
    return;
}

void addHash()
{
    char first_name[50];
    char last_name[50];
    char full_name[100];
    printf("Enter the first name: ");
    scanf("%s", first_name);
    int length = strlen(first_name);
    printf("Enter the last name: ");
    scanf("%s", last_name);
    strcpy(full_name, first_name);
    full_name[length] = 32;
    strcat(full_name, last_name);

    string temp = NULL;
    int position = hasher(first_name, last_name);
    temp = hash_table[position];
    while (strcmp(temp, "__") != 0)
    {
        position += 1;
        temp = hash_table[position];
    }
    hash_table[position] = full_name;
    printTable();
    setup();
    return;
}

void subHash(void)
{
    char first_name[50];
    char last_name[50];
    char full_name[100];
    const char limit[] = " ";
    printf("Enter the first name to DELETE: ");
    scanf("%s", first_name);
    int length = strlen(first_name);
    printf("Enter the last name to DELETE: ");
    scanf("%s", last_name);
    strcpy(full_name, first_name);
    full_name[length] = 32;
    strcat(full_name, last_name);

    string temp = NULL;
    int position = hasher(first_name, last_name);
    temp = hash_table[position];
    while ((strcmp(temp, full_name) != 0) && ((strcmp(temp, "__") != 0) || (prev_table[position] = 1)))
    {
        position += 1;
        if (position < TABLE_SIZE)
        {
            break;
        }
        temp = hash_table[position];

    }
    if (strcmp(temp, full_name) != 0)
    {
        printf("Name has not been deleted\n");
    }
    else
    {
        hash_table[position] = "__";
        prev_table[position] = 1;
        printTable();
        printf("%s has been deleted\n", full_name);
    }

    setup();
    return;
}

void searchHash(void)
{
    char first_name[50];
    char last_name[50];
    char full_name[100];
    const char limit[] = " ";
    printf("Enter the first name to SEARCH: ");
    scanf("%s", first_name);
    int length = strlen(first_name);
    printf("Enter the last name to SEARCH: ");
    scanf("%s", last_name);
    strcpy(full_name, first_name);
    full_name[length] = 32;
    strcat(full_name, last_name);

    string temp = NULL;
    int position = hasher(first_name, last_name);
    temp = hash_table[position];
    while ((strcmp(temp, full_name) != 0) &&
            ((strcmp(temp, "__") != 0) ||
            (prev_table[position] = 1)))
    {
        position += 1;
        if (position < TABLE_SIZE)
        {
            break;
        }
        temp = hash_table[position];

    }
    printTable();
    if (strcmp(temp, full_name) != 0)
    {
        printf("Name is not in hash table\n");
    }
    else
    {
        printf("%s is in position: %i\n", full_name, position + 1);
    }
    setup();
    return;
}
